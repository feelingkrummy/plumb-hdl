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

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#define ALLOCATOR_PAGE_SIZE 4096

bool is_power_of_two(size_t value);
uintptr_t align_forward(uintptr_t ptr, size_t alignment);
size_t round_size_up_to_page(size_t size);


#endif
