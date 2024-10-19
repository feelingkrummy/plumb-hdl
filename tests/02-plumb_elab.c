#include <stdio.h>
#include <string.h>

#include <criterion/criterion.h>

#include "common/str.h"
#include "plumb_elab/tokens.h"
#include "plumb_elab/lex.h"

Test(plumb_elab, good_keywords) {
    const int MAX_ITER = 100; 
    int iter = 0;

    char* good_keywords_string = "and begin end input logic module nand nor not or output xnor xor";
    str8 good_keywords = {
        .ptr=(uint8_t*)good_keywords_string,
        .len=strlen(good_keywords_string)
    };

    PlumbToken expected_tokens[] = {
        {{1, 1},    PTT_And     },
        {{1, 5},    PTT_Begin   },
        {{1, 11},   PTT_End     },
        {{1, 15},   PTT_Input   },
        {{1, 21},   PTT_Logic   },
        {{1, 27},   PTT_Module  },
        {{1, 34},   PTT_Nand    },
        {{1, 39},   PTT_Nor     },
        {{1, 43},   PTT_Not     },
        {{1, 47},   PTT_Or      },
        {{1, 50},   PTT_Output  },
        {{1, 57},   PTT_Xnor    },
        {{1, 62},   PTT_Xor     }
    };
    int expected_len = sizeof(expected_tokens)/sizeof(PlumbToken);
    
    PlumbLexer lex = create_plumb_lexer(good_keywords);

    for (int i = 0; i < expected_len; i += 1) {
        PlumbToken tok = plumb_lexer_next_token(&lex); 
        cr_assert(tok.type == expected_tokens[i].type);
    }
}

Test(plumb_elab, good_keywords) {
    const int MAX_ITER = 100; 
    int iter = 0;

    char* good_keywords_string = "and begin end input logic module nand nor not or output xnor xor";
    str8 good_keywords = {
        .ptr=(uint8_t*)good_keywords_string,
        .len=strlen(good_keywords_string)
    };

    PlumbToken expected_tokens[] = {
        {{1, 1},    PTT_And     },
        {{1, 5},    PTT_Begin   },
        {{1, 11},   PTT_End     },
        {{1, 15},   PTT_Input   },
        {{1, 21},   PTT_Logic   },
        {{1, 27},   PTT_Module  },
        {{1, 34},   PTT_Nand    },
        {{1, 39},   PTT_Nor     },
        {{1, 43},   PTT_Not     },
        {{1, 47},   PTT_Or      },
        {{1, 50},   PTT_Output  },
        {{1, 57},   PTT_Xnor    },
        {{1, 62},   PTT_Xor     }
    };
    int expected_len = sizeof(expected_tokens)/sizeof(PlumbToken);
    
    PlumbLexer lex = create_plumb_lexer(good_keywords);

    for (int i = 0; i < expected_len; i += 1) {
        PlumbToken tok = plumb_lexer_next_token(&lex); 
        cr_assert(tok.type == expected_tokens[i].type);
    }
}
