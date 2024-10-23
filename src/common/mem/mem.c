/*
Copyright 2024 Kameron A. Rummel 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "common/mem/mem.h"

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
