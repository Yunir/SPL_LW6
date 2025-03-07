#include <stdio.h>
#include "mem.h"

int main() {
    heap_init(1);
	memalloc_debug_heap(stdout, HEAP_START);
    void* block_1 = _malloc(101);
    void* block_2 = _malloc(202);
    void* block_3 = _malloc(303);
    void* block_4 = _malloc(404);
	memalloc_debug_heap(stdout, HEAP_START);
    _free(block_2);
    memalloc_debug_heap(stdout, HEAP_START);
    _free(block_3);
    memalloc_debug_heap(stdout, HEAP_START);
    return 0;
}
