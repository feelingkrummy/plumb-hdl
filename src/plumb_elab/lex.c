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

static void advance(PlumbLexer* lex) {
    lex->loc.col += 1;
    lex->start_pos += c[0].len;
    lex->c[0] = lex->c[1];
    Utf8Cp cp = utf8_decode(lex->src.str);
    if (cp.val != UINT32_MAX) {
        // If we don't have a decode error, advance the decode_pos
        // If we do have a deocde error, don't advance, lexer has errored
        lex->decode_pos += cp.len;
    }
    lex->c[1] = cp;
}

static int match_single_char_token(PlumbLexer* lex, PlumbToken* token_out) {
    switch( lex->c[0].val ) {
        case '(' :
            token_out->type = PTT_LeftParen;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case ')' :
            token_out->type = PTT_RightParen;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case '{' :
            token_out->type = PTT_LeftBrace;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case '}' :
            token_out->type = PTT_RightBrace;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case '[' :
            token_out->type = PTT_LeftBracket;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case ']' :
            token_out->type = PTT_LeftBracket;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case '+' : 
            token_out->type = PTT_Plus;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case '-' : 
            token_out->type = PTT_Minus;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case '/' : 
            token_out->type = PTT_Slash;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        case ';' : 
            token_out->type = PTT_SemiColon;
            token_out->loc = lex->loc;
            advance(lex);
            return 1;
        default : 
            return 0;
    }
}

static int is_double_char_token(PlumbLexer* lex, PlumbToken* token_out) {
    switch( lex->c[0].val ) {
        case '*' :
            if (lex->c[1].val == '*') {
                token_out->type = PTT_StarStar;
                token_out->loc = lex->loc;
                advance(lex);
                advance(lex);
            } else {
                token_out->type = PTT_Star;
                token_out->loc = lex->loc;
                advance(lex);
            }
            return 1;
        case '=' :
            if (lex->c[1].val == '=') {
                token_out->type = PTT_EqualEqual;
                token_out->loc = lex->loc;
                advance(lex);
                advance(lex);
            } else {
                token_out->type = PTT_Equal;
                token_out->loc = lex->loc;
                advance(lex);
            }
            return 1;
        case '!' :
            if (lex->c[1].val == '=') {
                token_out->type = PTT_BangEqual;
                token_out->loc = lex->loc;
                advance(lex);
                advance(lex);
            } else {
                token_out->type = PTT_Bang;
                token_out->loc = lex->loc;
                advance(lex);
            }
            return 1;
        case '<' :
            if (lex->c[1].val == '=') {
                token_out->type = PTT_LeftArrowEqual;
                token_out->loc = lex->loc;
                advance(lex);
                advance(lex);
            } else {
                token_out->type = PTT_LeftArrow;
                token_out->loc = lex->loc;
                advance(lex);
            }
            return 1;
        case '>' :
            if (lex->c[1].val == '=') {
                token_out->type = PTT_RightArrowEqual;
                token_out->loc = lex->loc;
                advance(lex);
                advance(lex);
            } else {
                token_out->type = PTT_RightArrow;
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
        .str = lex->src.str + start_pos, // Pointer arithmetic! D:
        .len = 0
    };

    do {
        lexeme.len += lex->c[0].len;
        advance();
    } while ( utf8_isalphanumeric(lex->c[0]) || (lex->c[0].val == '_') );

    return lexeme;
}

static int is_keyword(PlumbLexer* lex, str8 lexeme, PlumbToken *token_out) {
    uint32_t low = PTT_And;
    uint32_t high = PTT_Xor;

    uint32_t mid = 0;
    int cond = 0;

    while ( low <= high ) {
        mid = low + (high - low) / 2;
        cond = str8_cmp(lexeme, plumbtokentype_str8[mid]);
        if ( cont < 0 ) {
            high = mid - 1;
        } else if ( cond > 0 ) {
            low = mid + 1;
        } else {
            token_out->type = (PlumbTokenTyp)mid;
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
    advance(lex);
    advance(lex);

    lex.start_pos = 0;

    return lex;
}

PlumbToken plumb_lexer_next_token(PlumbLexer* lex) {
    PlumbToken tok = {0};

    if (match_single_char_token(lex, &tok)) {
        return tok;
    }

    if (match_double_char_token(lex, &tok)) {
        return tok;
    }

    if ( utf8_isalpha(lex->c[0]) || (lex->c[0].val == '_') ) {
        str8 lexeme = get_lexeme(lex);
        if ( is_keyword(lex, lexeme, &tok) ) {
            return token;
        }
        tok.type = PPT_Ident;
        tok.loc = lex->loc;
        tok.ident = lexeme;
        return token
    }
    
    tok.type = PTT_Invalid;
    tok.loc = lex->loc;
    return tok;
}

TokenList plumb_lexer_scan_entire_file(str8 src) {
    PlumbLexer lex = create_plumb_lexer(src);
}
