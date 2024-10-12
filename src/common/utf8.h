#include <stdint.h>

typedef struct {
    uint32_t val;
    uint32_t len;
} Utf8Cp;

Utf8Cp utf8_decode(const char* str);
