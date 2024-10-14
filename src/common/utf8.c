static uint8_t masks[] = {
    0x7F,
    0x1F,
    0x0F,
    0x07
};

static uint32_t get_length(const uint8_t* s) {
    uint8_t c = s[0];
    if ( (c & 0x80) == 0x0 ) return 1;
    if ( (c & 0xE0) == 0xC0 ) return 2;
    if ( (c & 0xF0) == 0xE0 ) return 3;
    if ( (c & 0xF1) == 0xF0 ) return 4;
    return 0;
}


Utf8Cp utf8_decode(const char* str) {
    const uint8_t* s = (uint8_t*)str;

    if ( s[0] < 0x7F ) {
        return (Utf8Cp){ .val = (uint32_t)s[0], .len = 1 };
    }
   
    Utf8Cp cp = {0};
    cp.len = get_length(s);
    if (cp.len == 0) {
        cp.val = UINT32_MAX;
        return cp;
    }

    cp.val = s[0] & masks[cp.len-1];
    for (int i = 1; i < cp.len; i++) {
        uint8_t c = s[i];
        if ((c >> 6) != 0b10) {
            cp.val = UINT32_MAX;
            cp.len = 0;
        }
        cp.val <<= 6;
        cp.val |= c & 0x3F;
    }
    return cp;
}

int utf8_isalphanumeric(Utf8Cp cp) {
    return iswalnum(cp.val);
}

int utf8_isalpha(Utf8Cp cp) {
    return iswalpha(cp.val);
}
