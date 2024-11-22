#include <stdlib.h>

#include "common/str.h"
#include "plumb-elab/tokens.h"

const str8 plumbtokentype_str8[] = {
	[PLUMB_TOKEN_INVALID]			= STR8("Invalid"),
	[PLUMB_TOKEN_EOF]				= STR8("EOF"),

	[PLUMB_TOKEN_LEFTPAREN]			= STR8("("), 
	[PLUMB_TOKEN_RIGHTPAREN]		= STR8(")"), 
	[PLUMB_TOKEN_LEFTBRACE]			= STR8("{"), 
	[PLUMB_TOKEN_RIGHTBRACE]		= STR8("}"), 
	[PLUMB_TOKEN_LEFTBRACKET]		= STR8("["), 
	[PLUMB_TOKEN_RIGHTBRACKET]		= STR8("]"), 
	[PLUMB_TOKEN_PLUS]				= STR8("+"), 
	[PLUMB_TOKEN_MINUS]				= STR8("-"), 
	[PLUMB_TOKEN_COLON]				= STR8(":"), 
	[PLUMB_TOKEN_SEMICOLON]			= STR8(";"), 

	[PLUMB_TOKEN_STAR]				= STR8("*"), 
	[PLUMB_TOKEN_STARSTAR]			= STR8("**"), 
	[PLUMB_TOKEN_EQUAL]				= STR8("="), 
	[PLUMB_TOKEN_EQUALEQUAL]		= STR8("=="),
	[PLUMB_TOKEN_SLASH]				= STR8("/"), 
	[PLUMB_TOKEN_SLASHEQUAL]		= STR8("/="),
	[PLUMB_TOKEN_LEFTARROW]			= STR8(">"),
	[PLUMB_TOKEN_LEFTARROWEQUAL]	= STR8(">="),
	[PLUMB_TOKEN_RIGHTARROW]		= STR8("<"),
	[PLUMB_TOKEN_RIGHTARROWEQUAL]	= STR8("<="),
	
	[PLUMB_TOKEN_IDENT]				= STR8("ident"),

	// Begin Keywords
	// These must be in alphabetical order
	// so the is_keyword binary search works
	// correctly
	[PLUMB_TOKEN_AND]				= STR8("and"),
	[PLUMB_TOKEN_BEGIN]				= STR8("begin"),
	[PLUMB_TOKEN_END]				= STR8("end"),
	[PLUMB_TOKEN_INPUT]				= STR8("input"),
	[PLUMB_TOKEN_LOGIC]				= STR8("logic"),
	[PLUMB_TOKEN_MOD]				= STR8("mod"),
	[PLUMB_TOKEN_MODULE]			= STR8("module"),
	[PLUMB_TOKEN_NAND]				= STR8("nand"),
	[PLUMB_TOKEN_NOR]				= STR8("nor"),
	[PLUMB_TOKEN_NOT]				= STR8("not"),
	[PLUMB_TOKEN_OR]				= STR8("or"),
	[PLUMB_TOKEN_OUTPUT]			= STR8("output"),
	[PLUMB_TOKEN_XNOR]				= STR8("xnor"),
	[PLUMB_TOKEN_XOR]				= STR8("xor")
	// End Keywords

};

/*
void destroy_token_list(TokenList* list) {
	list->cap = 0;
	list->len = 0;
	if (list->tokens != NULL) {
		free(list->tokens);
	}
}
*/
