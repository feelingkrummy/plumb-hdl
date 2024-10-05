#ifndef PLUMB_LEX_H_
#define PLUMB_LEX_H_

#include <stdint.h>

#include "common/types.h"

typedef struct {
    str8 src; 
    uint32_t start;
    uint32_t current;
} PlumbLexer

PlumbLexer create_plumb_lexer(str8 source);
PlumbToken plumb_lexer_next_token(PlumbLexer* lex);

TokenList plumb_lexer_scan_entire_file(str8 source);

#endif
