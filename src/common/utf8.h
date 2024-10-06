
typedef Utf8Char {
    uint32_t char;
    uint32_t len;
}

Utf8Char utf8_decode(const char* str);
// uint8_t utf8_length(uint32_t cp);
