#inlcude "str.h"

int str8_cmp(str8 a, str8 b) {
    uint64_t len = ( a.len < b.len ) ? a.len : b.len;
    // Do normal string cmp
    for ( uint64_t i = 0; i < len; i += 1 ) {
        if ( a.str[i] < b.str[i] ) return -1;
        if ( a.str[i] > b.str[i] ) return 1;
    }
    
    // If we get here, then the first characters of the string are equal
    // Check if they're not the same length
    if ( a.len < b.len ) return -1;
    if ( a.len > b.len ) return 1;

    return 0;
}
