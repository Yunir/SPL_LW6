#include <stdio.h>
#include "mem.h"

int main() {
    heap_init(1);
    void* block_1 = _malloc(1024);
    void* block_2 = _malloc(4096);
	memalloc_debug_heap(stdout, HEAP_START);
    _free(block_2);
    memalloc_debug_heap(stdout, HEAP_START);
    return 0;
}
