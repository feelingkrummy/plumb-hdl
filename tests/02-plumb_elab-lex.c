#include "common/kassert.h"
#include "common/kassert.c"

#include "common/str.h"
#include "common/str.c"

#include <stdio.h>

int main(void) {
    
    str8 good_keywords[] = {
        STR8("and"),
        STR8("begin"),
        STR8("end"),
        STR8("input"),
        STR8("logic"),
        STR8("module"),
        STR8("nand"),
        STR8("nor"),
        STR8("not"),
        STR8("or"),
        STR8("output"),
        STR8("xnor"),
        STR8("xor")
    };
    int good_keywords_len = sizeof(good_keywords)/sizeof(str8);

    return 0;
}
