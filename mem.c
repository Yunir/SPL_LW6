#include "mem.h"

/* map new area from OS to save new information */
struct mem* set_new_block(struct mem* last, size_t query) {
    size_t temp = query/BLOCK_MIN_SIZE;
    char* addr = (char*) (last) + last->capacity + sizeof(struct mem);
    size_t size = query+sizeof(struct mem);

    struct mem* block = mmap(addr, query, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED)
        block = mmap(NULL, query, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED)
        return NULL;

    struct mem* next = NULL;
    if ((temp+1) * 4096 >= size + sizeof(struct mem)) {
        next = (struct mem*) (addr + size);
        next->next = NULL;
        next->is_free = 1;
        next->capacity = (temp+1)*BLOCK_MIN_SIZE - query - 2*(sizeof(struct mem));
    }
    block->capacity = query;
    block->is_free = 0;
    block->next = next;
    return block;
}

/* return last block of memory */
struct mem* get_last_block(struct mem* block) {
    while (block->next)
        block = block->next;
    return block;
}

/* return first faced free block of memory with enough capacity else null */
struct mem* find_block(struct mem* block, size_t query) {
    while (block) {
        if (block->is_free && block->capacity >= query)
            return block;
        block = block->next;
    }
    return NULL;
}

/*
   split found free block to one busy and one free, then linking one to another
   if can't find - get last element and map new area from OS and
*/
void *_malloc(size_t query) {
    struct mem* block = find_block(HEAP_START, query);
    struct mem* new = NULL;
    if (block) {
        new = (struct mem*)((char*)block + query + sizeof(struct mem));
        new->capacity = block->capacity - query - sizeof(struct mem);
        new->is_free = 1;

        block->next = new;
        block->capacity = query;
        block->is_free = 0;
    } else {
        block = get_last_block(HEAP_START);
        new = set_new_block(block, query);
        block->next = new;
        return new + 1;
    }
    return (int8_t*) block + sizeof(struct mem);
}

struct mem* find_previous_block (struct mem* block, void* wanted) {
    while (block->next) {
        struct mem* next = block->next+1;
        if(next == (struct mem*)wanted)
            return block;
        block = block->next;
    }
    return NULL;
}

void _free(void* mem) {
    struct mem* previous_block = find_previous_block(HEAP_START, mem);
    struct mem* block = HEAP_START;
    if (previous_block)
        block = block->next;
        if (block) {
            block->is_free = 1;
            if (block->next) {
                if (block->next->is_free == 1) {
                    block->capacity += block->next->capacity + sizeof(struct mem);
                    block->next = block->next->next;
                }
            }
            if(previous_block) {
                if(previous_block->is_free == 1) {
                    previous_block->capacity += block->capacity + sizeof(struct mem);
                    previous_block->next = block->next;
                }
            }
        }
}

void heap_init(size_t initial_size) {
    void* mapped_heap = mmap(HEAP_START, initial_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    struct mem* head = HEAP_START;
    head->next = NULL;
	head->capacity = initial_size*BLOCK_MIN_SIZE - sizeof(struct mem);
	head->is_free = 1;
}

void memalloc_debug_struct_info(FILE* f, struct mem const* const address) {
    size_t i;
    fprintf(f, "start: %p\nsize: %lu\nis_free: %d\n", (void*) address, address->capacity, address->is_free);
    for ( i = 0; i <  DEBUG_FIRST_BYTES  &&  i <  address-> capacity; ++i )
        fprintf( f, "%hhX", ((char*)address)[ sizeof( struct mem ) + i ] );
    putc( '\n', f );
}

void memalloc_debug_heap( FILE* f, struct mem const* ptr ) {
    for(; ptr; ptr = ptr->next)
        memalloc_debug_struct_info( f, ptr );
    printf("================\n");
}
