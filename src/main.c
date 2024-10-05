#include <stdio.h>

#include "plumb_elab/tokens.h"
#include "common/types.h"

int main(void) {
    str8 test = {0};
    printf("Hello, world!\n");

    PlumbToken tok = {0};
    if ( !tok.type ) {
        printf("Not token!\n");
    } else {
        printf("Token!\n");
    }

    tok.type = PTT_And;
    if ( !tok.type ) {
        printf("Not token!\n");
    } else {
        printf("Token!\n");
    }

    return 0;
}
