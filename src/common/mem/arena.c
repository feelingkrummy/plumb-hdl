#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
//#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>

#include "kassert/kassert.h"
#include "mem/mem.h"
#include "mem/arena.h"

//
// Private function
//
static void add_block(MemArena* self, size_t size) {
    size_t block_size = sizeof(MemArenaBlock) + size;
    // block_size = round_size_up_to_page(block_size);
    
    /*
    MemArenaBlock *new_block = (MemArenaBlock*)mmap(
            NULL,
            block_size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANON,
            -1,
            0
        );
    KASSERT_MSG((uintptr_t)new_block != -1, "mmap failed, abort!");
    */

    MemArenaBlock *new_block = (MemArenaBlock*)malloc(block_size);
    KASSERT_MSG(new_block, "malloc failed, abort!");

    // Initalized new block
    new_block->next_block = NULL;
    new_block->capacity = block_size - sizeof(MemArenaBlock);
    new_block->prev_ptr = (uintptr_t)new_block->mem;
    new_block->offset_ptr = (uintptr_t)new_block->mem;

    // Append new block to end
    self->curr_block->next_block = new_block;

    // Move curr block to new block if not a large block
    // if ( block_size - sizeof(MemArenaBlock) <= self->default_block_size ) { 
    //     self->curr_block = new_block;
    // }
    self->curr_block = new_block;
}

static void destroy_all_blocks(MemArenaBlock *block) {
    if ( block->next_block != NULL ) {
        destroy_all_blocks(block->next_block);
        block->next_block = NULL;
    }
    // int err = munmap((void*)block, (block->capacity + sizeof(MemArenaBlock)));
    // KASSERT_MSG(err != -1, "munmap failed, abort!");
    free((void*)block);
}

//
// Header functions
//
MemArena mem_arena_init(size_t default_block_size) {

    // Allocate first block with default size
    size_t block_size = sizeof(MemArenaBlock) + default_block_size;
    // block_size = round_size_up_to_page(block_size);

    MemArena new_arena = {
        // .default_block_size = block_size - sizeof(MemArenaBlock),
        .default_block_size = default_block_size,
        .start_block = NULL,
        .curr_block = NULL,
    };

    /*
    MemArenaBlock* new_block = (MemArenaBlock*)mmap(
            NULL,
            block_size,
            PROT_READ | PROT_WRITE,
            MAP_PRIVATE | MAP_ANON,
            -1,
            0
        );
    KASSERT_MSG((uintptr_t)new_block != -1, "mmap failed, abort!");
    */

    MemArenaBlock *new_block = (MemArenaBlock*)malloc(block_size);
    KASSERT_MSG(new_block, "malloc failed, abort!");

    new_block->next_block = NULL;
    new_block->capacity = block_size - sizeof(MemArenaBlock);
    new_block->prev_ptr = (uintptr_t)new_block->mem;
    new_block->offset_ptr = (uintptr_t)new_block->mem;

    new_arena.start_block = new_block;
    new_arena.curr_block = new_block;

    return new_arena;
}

// Reset all blocks to 0, does not free allocated pages
void mem_arena_reset(MemArena *self) {
    MemArenaBlock *block = self->start_block;
    while (block != NULL) {
        block->prev_ptr = (uintptr_t)block->mem;
        block->offset_ptr = (uintptr_t)block->mem;
        block = block->next_block;
    }
    self->curr_block = self->start_block;
}


void mem_arena_deinit(MemArena *self) {
    destroy_all_blocks(self->start_block);
    self->start_block = NULL;
    self->curr_block = NULL;
}

void* mem_arena_alloc(MemArena *self, size_t size, size_t alignment) {
    KASSERT_MSG(is_power_of_two(alignment), "Alignment is not a power of two!"); 
    KASSERT_MSG(self, "self pointer is null, abort!");

    // This is kind of hacky but it works
    // After added large block to end we want to rewind
    // to previous block to avoid wasted memory
    bool added_large_block = false;
    MemArenaBlock* previous_block = NULL;

    uintptr_t ptr = align_forward(self->curr_block->offset_ptr, alignment);
    uintptr_t block_end_ptr = (uintptr_t)self->curr_block->mem + self->curr_block->capacity;

    // This lets us move through the blocks to find one with space
    while ( ptr + size > block_end_ptr && self->curr_block->next_block != NULL ) {
        self->curr_block = self->curr_block->next_block;

        // Update values
        ptr = align_forward(self->curr_block->offset_ptr, alignment);
        block_end_ptr = (uintptr_t)self->curr_block->mem + self->curr_block->capacity;
    }

    // This is a final check incase we've reached the end
    if ( ptr + size > block_end_ptr ) {
        if ( size + (alignment - 1) > self->default_block_size ) {
            added_large_block = true;
            previous_block = self->curr_block;
            add_block(self, size + alignment - 1);
        } else {
            add_block(self, self->default_block_size);
        }

        // Update values
        ptr = align_forward(self->curr_block->offset_ptr, alignment);
        block_end_ptr = (uintptr_t)self->curr_block->mem + self->curr_block->capacity;
    }

    self->curr_block->prev_ptr = ptr;
    self->curr_block->offset_ptr += size;

    // I can just cast an integer to a void pointer
    // I'm sure that will never be a bad thing
    memset((void*)ptr, 0, size);

    if ( added_large_block ) {
        self->curr_block = previous_block; 
    }

    return (void*)ptr;
}

void* mem_arena_realloc(MemArena *self, void *mem, size_t old_size, size_t new_size, size_t alignment) {
    KASSERT_MSG(is_power_of_two(alignment), "Alignment is not a power of two!"); 
    KASSERT_MSG(self, "Self pointer is null, abort!");

    uintptr_t ptr_to_resize = (uintptr_t)mem;

    // Handle edge cases
    if ( mem == NULL || old_size == 0 ) {
        return mem_arena_alloc(self, new_size, alignment);
    }

    // If new size is smaller than old_size, just return pointer
    // we don't support shrinking in this arena
    if ( new_size < old_size ) {
        return mem;
    }

    if ( ptr_to_resize == self->curr_block->prev_ptr ) {
        // We can resize, do the resize
        size_t size_diff = new_size - old_size;
        self->curr_block->offset_ptr += size_diff;
        return mem;
    } else {
        // Can not resize or out of bounds, alloc and copy
        void* new_mem = mem_arena_alloc(self, new_size, alignment);
        memcpy(new_mem, mem, old_size);
        return new_mem;
    }
}

void mem_arena_free(MemArena *self, void *mem, size_t size) {
    // DO NOTHING
    (void)0;
}

void mem_arena_dump(MemArena self) {
    fprintf(stderr,     "Arena Dump :\n");
    fprintf(stderr,     "  default_block_size : %zu\n", self.default_block_size );
    fprintf(stderr,     "  start_block : %p\n", self.start_block );
    fprintf(stderr,     "  curr_block  : %p\n", self.curr_block );
    fprintf(stderr,     "\n");
    fprintf(stderr,     "  Blocks : \n");

    MemArenaBlock *block = self.start_block;
    uint64_t block_num = 0;
    while ( block != NULL ) {
        fprintf(stderr,     "    Block %lu (%p): ", block_num, block);
        if ( block_num == 0 ) {
            fprintf(stderr,     "(start_block) ");
        }
        if ( block == self.curr_block ) {
            fprintf(stderr,     "(curr_block) ");
        }

        uintptr_t prev_ptr_offset = (uintptr_t)block->prev_ptr - (uintptr_t)block->mem;
        uintptr_t offset_ptr_offset = (uintptr_t)block->offset_ptr - (uintptr_t)block->mem;

        fprintf(stderr,     "\n");
        fprintf(stderr,     "      next_block   : %p\n", block->next_block);
        fprintf(stderr,     "      capacity     : %zu\n", block->capacity);
        fprintf(stderr,     "      prev_ptr     : 0x%lx (offset = %lu)\n", block->prev_ptr, prev_ptr_offset);
        fprintf(stderr,     "      offset_ptr   : 0x%lx (offset = %lu)\n", block->offset_ptr, offset_ptr_offset);
        fprintf(stderr,     "      mem          : %p\n", block->mem);
        block = block->next_block;
        block_num += 1;
    }
}
