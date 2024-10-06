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

static int match_single_char_token(PlumbLexer* lex, PlumbToken* tok) {
    switch( lex->src[lex->current] ) {
        case '(' :
            tok->type = PTT_LeftParen;
            tok->pos = lex->current;
            return 1;
        case ')' :
            tok->type = PTT_RightParen;
            tok->pos = lex->current;
            return 1;
        case '{' :
            tok->type = PTT_LeftBrace;
            tok->pos = lex->current;
            return 1;
        case '}' :
            tok->type = PTT_RightBrace;
            tok->pos = lex->current;
            return 1;
        case '[' :
            tok->type = PTT_LeftBracket;
            tok->pos = lex->current;
            return 1;
        case ']' :
            tok->type = PTT_LeftBracket;
            tok->pos = lex->current;
            return 1;
        case '+' : 
            tok->type = PTT_Plus;
            tok->pos = lex->current;
            return 1;
        case '-' : 
            tok->type = PTT_Minus;
            tok->pos = lex->current;
            return 1;
        case '/' : 
            tok->type = PTT_Slash;
            tok->pos = lex->current;
            return 1;
        case ';' : 
            tok->type = PTT_SemiColon;
            tok->pos = lex->current;
            return 1;
        default : 
            return 0;
    }
}

static int is_double_char_token(PlumbLexer* lex, PlumbToken* tok) {
    switch( lex->src[lex->current] ) {
        case '*' :
    }
}

PlumbLexer create_plumb_lexer(str8 src) {
    return (PlumbLexer){
        .src = src,
        .start = 0,
        .current = 0,
    };
}

PlumbToken plumb_lexer_next_token(PlumbLexer* lex) {
    PlumbToken tok = {0};

    if (match_single_char_token(lex, &tok)) {
        lex->current += 1;
        lex->start = lex->current;
        return tok;
    }

    int advance = 0;
    if ( advance = match_double_char_token(lex, &tok) ) {
        lex->current += 2;
        lex->start = lex->current;
        return tok;
    }
}

TokenList plumb_lexer_scan_entire_file(str8 src) {
    PlumbLexer lex = create_plumb_lexer(src);
}
