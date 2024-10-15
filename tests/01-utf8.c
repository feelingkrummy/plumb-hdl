#include "common/kassert.h"
#include "common/kassert.c"

#include "common/utf8.h"
#include "common/utf8.c"

char* characters =
    "ABCD"
    "\u{A3}\u{B5}\u{F8}"
    "\u{16B7}\u{16C4}\u{1F20}\u{1F74}"
    "\u{1F600}\u{1F605}\u{1FAE1}"
;

const Utf8Cp expected[] = {
    { .val = 'A',       .len = 1 },
    { .val = 'B',       .len = 1 },
    { .val = 'C',       .len = 1 },
    { .val = 'D',       .len = 1 },
    { .val = 0xA3,      .len = 2 },
    { .val = 0xB5,      .len = 2 },
    { .val = 0xF8,      .len = 2 },
    { .val = 0x16B7,    .len = 3 },
    { .val = 0x16C4,    .len = 3 },
    { .val = 0x1F20,    .len = 3 },
    { .val = 0x1F74,    .len = 3 },
    { .val = 0x1F600,   .len = 4 },
    { .val = 0x1F605,   .len = 4 },
    { .val = 0x1FAE1,   .len = 4 }
};

int main(void) {
    int len = sizeof(expected)/sizeof(Utf8Cp); 
    char* current = characters; 

    for ( int i = 0; i < len; i++ ) {
        Utf8Cp cp = utf8_decode(current);

        KASSERT_MSG(cp.val == expected[i].val,
                "Iter %d : Decoded val 0x%0X is not expected 0x%0X",
                i, cp.val, expected[i].val );

        KASSERT_MSG(cp.len == expected[i].len,
                "Iter %d : Decoded len %d is not expected %d",
                i, cp.len, expected[i].len );

        current += cp.len;
    }

    return 0;
}
