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

#ifndef PLUMB_TOKENS_H_
#define PLUMB_TOKENS_H_

#include <stdint.h>

typedef enum {
	PLUMB_TOKEN_INVALID = 0, 
	PLUMB_TOKEN_EOF, 
	
	// Single Char Tokens
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
	PLUMB_TOKEN_SEMICOLON, 

	// Double Char Token
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
	
	PLUMB_TOKEN_IDENT,
   
	// Begin Keywords
	// These must be in alphabetical order
	// so the is_keyword binary search works
	// correctly
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
	// End Keywords
} PlumbTokenType;

extern const str8 plumbtokentype_str8[];

typedef struct {
	uint32_t line;
	uint32_t col;
} PlumbTokenLoc;

#define INIT_LOCATION (PlumbTokenLoc){.line=1, .col=1}

typedef struct {
	PlumbTokenLoc loc;
	PlumbTokenType type;
	union {
		str8 ident;
	};
} PlumbToken;

/*
typedef struct {
	uint64_t cap;
	uint64_t len;
	PlumbToken* tokens;
} TokenList;

void destroy_token_list(TokenList* list);
*/

#endif
