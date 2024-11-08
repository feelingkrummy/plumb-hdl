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

#include <stdio.h>

#include "plumb-elab/tokens.h"
#include "common/types.h"

int main(void) {
	str8 test = {0};
	printf("Hello, world!\n");

	PlumbToken tok = {0};
	if ( !tok.type ) {
		printf("Not token!\n");
	} else {
		printf("Token!\n");
	}

	tok.type = PLUMB_TOKEN_AND;
	if ( !tok.type ) {
		printf("Not token!\n");
	} else {
		printf("Token!\n");
	}

	return 0;
}
