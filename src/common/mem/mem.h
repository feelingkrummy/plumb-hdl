#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#define ALLOCATOR_PAGE_SIZE 4096

bool is_power_of_two(size_t value);
uintptr_t align_forward(uintptr_t ptr, size_t alignment);
size_t round_size_up_to_page(size_t size);


#endif
