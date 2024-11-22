/*
Copyright 2024 Kameron A. Rummel 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "plumb-elab/lex.h"

static void advance(PlumbLexer* lex) {
	lex->loc.col += 1;
	// Increase current by 1 and move c[1] to c[0]
	lex->current += 1;
	lex->c[0] = lex->c[1];
	// If next is still in bounds increment and get next
	// otherwise, assign EOF
	if ( lex->next < lex->src.len ) {
		lex->next += 1;
		lex->c[1] = lex->src.ptr[lex->next];
	} else {
		lex->c[1] = EOF;
	}
}

static void skip_whitespace(PlumbLexer* lex) {
	while ( isspace(lex->c[0]) ) {
		if ( lex->c[0] == '\n' ) {
			lex->loc.line += 1;
			lex->loc.col = 1;
		}
		advance(lex);
	}
}

static int is_single_char_token(PlumbLexer* lex, PlumbToken* token_out) {
	switch( lex->c[0] ) {
		case '(' :
			token_out->type = PLUMB_TOKEN_LEFTPAREN;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case ')' :
			token_out->type = PLUMB_TOKEN_RIGHTPAREN;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case '{' :
			token_out->type = PLUMB_TOKEN_LEFTBRACE;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case '}' :
			token_out->type = PLUMB_TOKEN_RIGHTBRACE;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case '[' :
			token_out->type = PLUMB_TOKEN_LEFTBRACKET;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case ']' :
			token_out->type = PLUMB_TOKEN_RIGHTBRACKET;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case '+' : 
			token_out->type = PLUMB_TOKEN_PLUS;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case '-' : 
			token_out->type = PLUMB_TOKEN_MINUS;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case ':' : 
			token_out->type = PLUMB_TOKEN_COLON;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		case ';' : 
			token_out->type = PLUMB_TOKEN_SEMICOLON;
			token_out->loc = lex->loc;
			advance(lex);
			return 1;
		default : 
			return 0;
	}
}

static int is_double_char_token(PlumbLexer* lex, PlumbToken* token_out) {
	switch( lex->c[0] ) {
		case '*' :
			if (lex->c[1] == '*') {
				token_out->type = PLUMB_TOKEN_STARSTAR;
				token_out->loc = lex->loc;
				advance(lex);
				advance(lex);
			} else {
				token_out->type = PLUMB_TOKEN_STAR;
				token_out->loc = lex->loc;
				advance(lex);
			}
			return 1;
		case '/' :
			if (lex->c[1] == '=') {
				token_out->type = PLUMB_TOKEN_SLASHEQUAL;
				token_out->loc = lex->loc;
				advance(lex);
				advance(lex);
			} else {
				token_out->type = PLUMB_TOKEN_SLASH;
				token_out->loc = lex->loc;
				advance(lex);
			}
			return 1;
		case '=' :
			if (lex->c[1] == '=') {
				token_out->type = PLUMB_TOKEN_EQUALEQUAL;
				token_out->loc = lex->loc;
				advance(lex);
				advance(lex);
			} else {
				token_out->type = PLUMB_TOKEN_EQUAL;
				token_out->loc = lex->loc;
				advance(lex);
			}
			return 1;
		case '<' :
			if (lex->c[1] == '=') {
				token_out->type = PLUMB_TOKEN_LEFTARROWEQUAL;
				token_out->loc = lex->loc;
				advance(lex);
				advance(lex);
			} else {
				token_out->type = PLUMB_TOKEN_LEFTARROW;
				token_out->loc = lex->loc;
				advance(lex);
			}
			return 1;
		case '>' :
			if (lex->c[1] == '=') {
				token_out->type = PLUMB_TOKEN_RIGHTARROWEQUAL;
				token_out->loc = lex->loc;
				advance(lex);
				advance(lex);
			} else {
				token_out->type = PLUMB_TOKEN_RIGHTARROW;
				token_out->loc = lex->loc;
				advance(lex);
			}
			return 1;
		default: 
			return 0;
	}
}

static str8 get_lexeme(PlumbLexer* lex) {
	str8 lexeme = {
		.ptr = lex->src.ptr + lex->current, // Pointer arithmetic! D:
		.len = 0
	};

	do {
		lexeme.len += 1;
		advance(lex);
	} while ( isalnum(lex->c[0]) || (lex->c[0] == '_') );

	return lexeme;
}

static int is_keyword(PlumbLexer* lex, str8 lexeme, PlumbToken *token_out) {
	uint32_t low = PLUMB_TOKEN_AND;
	uint32_t high = PLUMB_TOKEN_XOR;

	uint32_t mid = 0;
	int cond = 0;

	while ( low <= high ) {
		mid = low + (high - low) / 2;
		cond = str8_cmp(lexeme, plumbtokentype_str8[mid]);
		if ( cond < 0 ) {
			high = mid - 1;
		} else if ( cond > 0 ) {
			low = mid + 1;
		} else {
			token_out->type = (PlumbTokenType)mid;
			token_out->loc = lex->loc;
			return 1;
		}
	}
	return 0;
}

PlumbLexer create_plumb_lexer(str8 src) {
	PlumbLexer lex = {0};
	lex.src = src;
	lex.loc = INIT_LOCATION;

	// Initialize lex characters
	advance(&lex);
	advance(&lex);

	// Set current to 0
	lex.current = 0;

	printf("Lex: \n");
	printf("	current: %lu\n", lex.current);
	printf("	next: %lu\n", lex.next);
	printf("	loc:\n");
	printf("		line: %d\n", lex.loc.line);
	printf("		col: %d\n", lex.loc.col);
	printf("	c[0]: %d, %c\n", lex.c[0], lex.c[0]);
	printf("	c[1]: %d, %c\n", lex.c[1], lex.c[1]);
	
	return lex;
}

PlumbToken plumb_lexer_next_token(PlumbLexer* lex) {
	PlumbToken tok = {0};

	skip_whitespace(lex);

	if ( lex->c[0] == EOF ) {
		tok.type = PLUMB_TOKEN_EOF;
		tok.loc = lex->loc;
		return tok;
	}

	if (is_single_char_token(lex, &tok)) {
		return tok;
	}

	if (is_double_char_token(lex, &tok)) {
		return tok;
	}

	if ( isalpha(lex->c[0]) || (lex->c[0] == '_') ) {
		str8 lexeme = get_lexeme(lex);
		printf("Lexeme : %*s\n", (int)lexeme.len, lexeme.ptr);
		if ( is_keyword(lex, lexeme, &tok) ) {
			return tok;
		}
		tok.type = PLUMB_TOKEN_IDENT;
		tok.loc = lex->loc;
		tok.ident = lexeme;
		return tok;
	}
	
	tok.type = PLUMB_TOKEN_INVALID;
	tok.loc = lex->loc;
	return tok;
}

/*
TokenList plumb_lexer_scan_entire_file(str8 src) {
	PlumbLexer lex = create_plumb_lexer(src);
	TokenList list = {0};

	// This is a guess as to how many tokens we'll need
	// If text is ASCII (as it likely will) we'll only need
	// to resize once or twice
	// If the text is all 4 byte UTF-8 chars (highly unlikely)
	// we only use half this memory
	uint64_t init_cap = src.len/2;
	list.cap = init_cap;
	list.tokens = calloc(init_cap, sizeof(PlumbToken));

	PlumbToken tok = {0};
	do {
		tok = plumb_lexer_next_token(&lex);
		list.tokens[list.len++] = tok;
		if (list.len == list.cap) {
			list.cap += list.cap/2;
			list.tokens = realloc(list.tokens, list.cap*sizeof(PlumbToken));
		}
	} while( tok.type != PLUMB_TOKEN_EOF && tok.type != PLUMB_TOKEN_INVALID );

	return list;
}
*/
