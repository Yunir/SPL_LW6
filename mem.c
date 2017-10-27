#include "mem.h"

void* _malloc(size_t query) {

}

void _free(void* mem) {

}

void* heap_init(size_t initial_size) {
    void* mapped_heap = mmap(HEAP_START, initial_size*BLOCK_MIN_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, -1, 0);

    struct mem* head = HEAP_START;
    head->next = NULL;
	head->capacity = initial_size*BLOCK_MIN_SIZE - sizeof(struct mem);
	head->is_free = 1;

    return mapped_heap;
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
}
