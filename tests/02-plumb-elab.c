#include <stdio.h>
#include <string.h>

#include <criterion/criterion.h>

#include "common/str.h"
#include "plumb-elab/tokens.h"
#include "plumb-elab/lex.h"

Test(plumb_elab, good_keywords) {

	char* good_keywords_string = "and begin end input logic mod module nand nor not or output xnor xor";
	str8 good_keywords = {
		.ptr=(uint8_t*)good_keywords_string,
		.len=strlen(good_keywords_string)
	};

	PlumbTokenType expected_token_types[] = {
		PLUMB_TOKEN_AND,
		PLUMB_TOKEN_BEGIN,
		PLUMB_TOKEN_END,
		PLUMB_TOKEN_INPUT,
		PLUMB_TOKEN_LOGIC,
		PLUMB_TOKEN_MOD,
		PLUMB_TOKEN_MODULE,
		PLUMB_TOKEN_NAND,
		PLUMB_TOKEN_NOR,
		PLUMB_TOKEN_NOT,
		PLUMB_TOKEN_OR,
		PLUMB_TOKEN_OUTPUT,
		PLUMB_TOKEN_XNOR,
		PLUMB_TOKEN_XOR
	};
	int expected_len = sizeof(expected_token_types)/sizeof(PlumbTokenType);
	
	PlumbLexer lex = create_plumb_lexer(good_keywords);

	for (int i = 0; i < expected_len; i += 1) {
		PlumbToken tok = plumb_lexer_next_token(&lex); 
		cr_assert(tok.type == expected_token_types[i]);
	}
}

Test(plumb_elab, bad_keywords) {
	const int MAX_ITER = 100;
	int iter = 0;

	char* bad_keywords_string = "tand bend in modu nort dont orr out xnr xr";
	str8 bad_keywords = {
		.ptr=(uint8_t*)bad_keywords_string,
		.len=strlen(bad_keywords_string)
	};

	PlumbLexer lex = create_plumb_lexer(bad_keywords);

	PlumbToken tok = {0};
	while ( (tok = plumb_lexer_next_token(&lex)).type != PLUMB_TOKEN_EOF && iter < MAX_ITER) {
		for (int type = PLUMB_TOKEN_AND; type <= PLUMB_TOKEN_XOR; type += 1) {
			cr_assert(tok.type != type);
		}
		iter += 1;
	}

	cr_assert(iter != MAX_ITER, "While loop maxed out! Tok : %s", plumbtokentype_str8[tok.type].ptr);
}

Test(plumb_elab, single_char_tokens) {
	str8 single_char_test = STR8("(){}[]+-/:;");

	PlumbTokenType expected_types[] = {
		PLUMB_TOKEN_LEFTPAREN, 
		PLUMB_TOKEN_RIGHTPAREN, 
		PLUMB_TOKEN_LEFTBRACE, 
		PLUMB_TOKEN_RIGHTBRACE, 
		PLUMB_TOKEN_LEFTBRACKET, 
		PLUMB_TOKEN_RIGHTBRACKET, 
		PLUMB_TOKEN_PLUS, 
		PLUMB_TOKEN_MINUS, 
		PLUMB_TOKEN_SLASH, 
		PLUMB_TOKEN_COLON, 
		PLUMB_TOKEN_SEMICOLON
	};
	int expected_len = sizeof(expected_types)/sizeof(PlumbTokenType);

	PlumbLexer lex = create_plumb_lexer(single_char_test);

	for (int i = 0; i < expected_len; i += 1) {
		PlumbToken tok = plumb_lexer_next_token(&lex); 
		cr_assert(tok.type == expected_types[i],
				"\"%s\" != \"%s\"",
				plumbtokentype_str8[tok.type].ptr, plumbtokentype_str8[expected_types[i]].ptr );
	}
}

Test(plumb_elab, double_char_tokens) {
	str8 single_char_test = STR8("* ** = == ! != < <= > >=");

	PlumbTokenType expected_types[] = {
		PLUMB_TOKEN_STAR, 
		PLUMB_TOKEN_STARSTAR, 
		PLUMB_TOKEN_EQUAL, 
		PLUMB_TOKEN_EQUALEQUAL, 
		PLUMB_TOKEN_BANG, 
		PLUMB_TOKEN_BANGEQUAL, 
		PLUMB_TOKEN_LEFTARROW, 
		PLUMB_TOKEN_LEFTARROWEQUAL, 
		PLUMB_TOKEN_RIGHTARROW, 
		PLUMB_TOKEN_RIGHTARROWEQUAL, 
	};
	int expected_len = sizeof(expected_types)/sizeof(PlumbTokenType);

	PlumbLexer lex = create_plumb_lexer(single_char_test);

	for (int i = 0; i < expected_len; i += 1) {
		PlumbToken tok = plumb_lexer_next_token(&lex); 
		cr_assert(tok.type == expected_types[i],
				"\"%s\" != \"%s\"",
				plumbtokentype_str8[tok.type].ptr, plumbtokentype_str8[expected_types[i]].ptr );
	}
}
