
static int is_single_char_token(PlumbLexer* lex, PlumbToken* tok) {
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

static int is_double_char_token(lex, &tok) {

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

    if (is_single_char_token(lex, &tok)) {
        lex->current += 1;
        lex->start = lex->current;
        return tok;
    }

    if (is_double_char_token(lex, &tok)) {
        lex->current += 2;
        lex->start = lex->current;
        return tok;
    }
}

TokenList plumb_lexer_scan_entire_file(str8 src) {
    PlumbLexer lex = create_plumb_lexer(src);
}
