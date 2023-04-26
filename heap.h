#ifndef PROJECT1_HEAP_H
#define PROJECT1_HEAP_H

#include "stdlib.h"

enum pointer_type_t
{
    pointer_null=0,
    pointer_heap_corrupted=1,
    pointer_control_block=2,
    pointer_inside_fences=3,
    pointer_inside_data_block=4,
    pointer_unallocated=5,
    pointer_valid=6
};

typedef struct __attribute__((packed)) block_t{
    struct block_t* pprev;
    struct block_t* pnext;
    int size;
    int free;

    struct block_t* pprev2;
    struct block_t* pnext2;
    int size2;
    int free2;
}block_t;

int heap_setup(void);
void heap_clean(void);

void* heap_malloc(size_t size);
void* heap_calloc(size_t number, size_t size);
void* heap_realloc(void* memblock, size_t size);
void  heap_free(void* ptr);

size_t heap_get_largest_used_block_size(void);
enum pointer_type_t get_pointer_type(const void* pointer);
int heap_validate(void);

void heap_show();
void combine_blocks(block_t* ptr);
block_t* first_fit(size_t size);

#endif
