#include <stdio.h>
#include "mem.h"

int main() {
    heap_init(1);
	memalloc_debug_heap(stdout, HEAP_START);
    void* block_1 = _malloc(1024);
    void* block_3 = _malloc(1024);
    void* block_2 = _malloc(1024);
    void* block_4 = _malloc(4079);
    void* block_5 = _malloc(4080);
    void* block_6 = _malloc(5000);
    //void* block_7 = _malloc(4096);
	memalloc_debug_heap(stdout, HEAP_START);
    _free(block_1);
    _free(block_3);
    _free(block_2);
    memalloc_debug_heap(stdout, HEAP_START);
    return 0;
}
