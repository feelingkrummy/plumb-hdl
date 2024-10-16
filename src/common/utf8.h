#include <stdint.h>

typedef struct {
    uint32_t val;
    uint32_t len;
} Utf8Cp;

Utf8Cp utf8_decode(const uint8_t* str);

int utf8_isalphanumeric(Utf8Cp cp);
int utf8_isalpha(Utf8Cp cp);
int utf8_isspace(Utf8Cp cp);
