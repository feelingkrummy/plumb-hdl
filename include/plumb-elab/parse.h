#ifndef PLUMB_PARSE_H_
#define PLUMB_PARSE_H_

#include "plumb-elab/tokens.h"
#include "plumb-elab/lex.h"

typedef struct {
	PlumbLexer lex;
	PlumbTokens token[2];
} PlumbParse;

PlumbExpr* plumb_parse_expr(PlumbParser* parser);

#endif
