#ifndef PLUMB_PARSE_H_
#define PLUMB_PARSE_H_

#include "plumb-elab/tokens.h"
#include "plumb-elab/lex.h"
#include "plumb-elab/expr.h"

typedef struct {
	PlumbLexer lex;
	PlumbToken token[2];
} PlumbParser;

PlumbExpr* plumb_parse_expr(PlumbParser* parser);

#endif
