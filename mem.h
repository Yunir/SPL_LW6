#ifndef _MEM_H_
#define _MEM_H_

#define _USE_MISC

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <stdbool.h>

#define  HEAP_START  ((void*)0x04040000)
#define BLOCK_MIN_SIZE 4096
#define PAGE_SIZE 4096

struct mem;

#pragma pack(push, 1)
struct mem {
    struct mem* next;
    size_t capacity;
    bool is_free;
};
#pragma pack(pop)

#define DEBUG_FIRST_BYTES 4

void* _malloc(size_t query);
void _free(void* mem);
void heap_init(size_t initial_size);
void memalloc_debug_struct_info(FILE* f, struct mem const* const address);
void memalloc_debug_heap(FILE* f, struct mem const* ptr);

#endif
