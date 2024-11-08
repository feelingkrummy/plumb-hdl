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

#ifndef STR_H_
#define STR_H_

#include <stdint.h>

#define STR8(s) (str8){.ptr=(uint8_t*)s, .len=(sizeof(s)/sizeof(*s))-1}

typedef struct {
	uint64_t len;
	uint8_t* ptr;
} str8;

int str8_cmp(str8 a, str8 b);

#endif
