#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "mem/mem.h"

bool is_power_of_two(size_t value) {
    return (value & (value - 1)) == 0;
}

uintptr_t align_forward(uintptr_t ptr, size_t alignment) {
    uintptr_t aligned_ptr = ptr;
    uintptr_t align = (uintptr_t)alignment;
    
    uintptr_t modulo = ptr & ( align - 1 );
    if ( modulo != 0 ) {
        aligned_ptr += align - modulo;
    }
    return aligned_ptr;
}

size_t round_size_up_to_page(size_t size) {
    size_t num_of_pages = ( size + ALLOCATOR_PAGE_SIZE - 1 ) / ALLOCATOR_PAGE_SIZE;
    size_t rounded_size = num_of_pages*ALLOCATOR_PAGE_SIZE;
    return rounded_size;
}
