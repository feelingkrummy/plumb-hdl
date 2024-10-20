#include <stdio.h>
#include <string.h>

#include <criterion/criterion.h>

#include "common/str.h"
#include "plumb_elab/tokens.h"
#include "plumb_elab/lex.h"

Test(plumb_elab, good_keywords) {

    char* good_keywords_string = "and begin end input logic module nand nor not or output xnor xor";
    str8 good_keywords = {
        .ptr=(uint8_t*)good_keywords_string,
        .len=strlen(good_keywords_string)
    };

    PlumbTokenType expected_token_types[] = {
        PTT_And,
        PTT_Begin,
        PTT_End,
        PTT_Input,
        PTT_Logic,
        PTT_Module,
        PTT_Nand,
        PTT_Nor,
        PTT_Not,
        PTT_Or,
        PTT_Output,
        PTT_Xnor,
        PTT_Xor
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

    char* bad_keywords_string = "tand bend in mod nort dont orr out xnr xr";
    str8 bad_keywords = {
        .ptr=(uint8_t*)bad_keywords_string,
        .len=strlen(bad_keywords_string)
    };

    PlumbLexer lex = create_plumb_lexer(bad_keywords);

    PlumbToken tok = {0};
    while ( (tok = plumb_lexer_next_token(&lex)).type != PTT_Eof && iter < MAX_ITER) {
        for (int type = PTT_And; type <= PTT_Xor; type += 1) {
            cr_assert(tok.type != type);
        }
        iter += 1;
    }

    cr_assert(iter != MAX_ITER, "While loop maxed out! Tok : %s", plumbtokentype_str8[tok.type].ptr);
}

Test(plumb_elab, single_char_tokens) {
    str8 single_char_test = STR8("(){}[]+-/:;");

    PlumbTokenType expected_types[] = {
        PTT_LeftParen, 
        PTT_RightParen, 
        PTT_LeftBrace, 
        PTT_RightBrace, 
        PTT_LeftBracket, 
        PTT_RightBracket, 
        PTT_Plus, 
        PTT_Minus, 
        PTT_Slash, 
        PTT_Colon, 
        PTT_SemiColon
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
        PTT_Star, 
        PTT_StarStar, 
        PTT_Equal, 
        PTT_EqualEqual, 
        PTT_Bang, 
        PTT_BangEqual, 
        PTT_LeftArrow, 
        PTT_LeftArrowEqual, 
        PTT_RightArrow, 
        PTT_RightArrowEqual, 
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
