#ifndef ARENAALLOC_H
#define ARENAALLOC_H

#include <stdint.h>

typedef struct MemArenaBlock {
    struct MemArenaBlock *next_block;
    size_t capacity;
    uintptr_t prev_ptr;
    uintptr_t offset_ptr;
    uint8_t mem[];
} MemArenaBlock;

typedef struct MemArena {
    size_t default_block_size;
    MemArenaBlock *start_block;
    MemArenaBlock *curr_block;
} MemArena;


MemArena mem_arena_init(size_t default_block_size);
void mem_arena_reset(MemArena *self);
void mem_arena_deinit(MemArena *self);

void* mem_arena_alloc(MemArena *self, size_t size, size_t alignment);
void* mem_arena_realloc(MemArena *self, void *mem, size_t old_size, size_t new_size, size_t alignment);
void mem_arena_free(MemArena *self, void *mem, size_t size);

void mem_arena_dump(MemArena self);

#endif
