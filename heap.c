#include "heap.h"
#include <string.h>
#include <stdio.h>

#define FOUR_KB 4096
#define FENCE_LEN 16

void* memory_block = NULL;
int usage = 0;


int ask_for_memory(unsigned int multiplier)
{
    if(multiplier == 0)
        return 0;

    void* add_mem = custom_sbrk(FOUR_KB * multiplier);

    if( add_mem == (void*) -1 )
        return 1;

    usage += FOUR_KB * multiplier;
    return 0;
}

void init_control_block_checker(block_t* ptr)
{
    ptr->pprev2 = ptr->pprev;
    ptr->pnext2 = ptr->pnext;
    ptr->size2 = ptr->size;
    ptr->free2 = ptr->free;
}

int check_control_blocks()
{
    block_t* pcurrent = (block_t*)memory_block;

    while(pcurrent != NULL)
    {
        if(pcurrent->pnext != pcurrent->pnext2)
            return 1;
        if(pcurrent->pprev != pcurrent->pprev2)
            return 1;
        if(pcurrent->size != pcurrent->size2)
            return 1;
        if(pcurrent->free != pcurrent->free2)
            return 1;

        pcurrent = pcurrent->pnext;
    }

    return 0;
}

void heap_show()
{
    if(!memory_block)
        return;

    block_t* pcurrent = (block_t*)memory_block;

    for(int i=1; pcurrent; pcurrent = pcurrent->pnext, i++)
    {
        printf("BLOK %d:\t", i);
        printf("  [size: %d", pcurrent->size);
        printf("  free: %d", pcurrent->free);
    }
    printf("usage: %d", usage);
    printf("\n\n");
}

int heap_setup(void)
{
    if(memory_block != NULL)
        return 1;

    memory_block = custom_sbrk(0);

    if(ask_for_memory(1))
        return 1;

    block_t* ptr = (block_t*)memory_block;

    ptr->pprev = NULL;
    ptr->pnext = NULL;
    ptr->size = usage - (int)sizeof(block_t);
    ptr->free = 1;
    init_control_block_checker(ptr);

    return 0;
}

void heap_clean(void)
{
    if(!memory_block)
        return;

    memset(memory_block, 0, usage);
    custom_sbrk(-usage);
    usage=0;
    memory_block = NULL;
}

block_t* first_fit(size_t size)
{
    int temp = (int)size + (2 * FENCE_LEN);

    for(block_t* ptr = (block_t*)memory_block; ptr != NULL; ptr = ptr->pnext)
    {
        if(ptr->free == 1 && ptr->size >= temp)
            return ptr;
    }
    return NULL;
}

block_t* get_last_block()
{
    for(block_t* ptr = (block_t*)memory_block; ptr != NULL; ptr = ptr->pnext)
    {
        block_t* temp = ptr->pnext;
        if(temp == NULL)
            return ptr;
    }
    return NULL;
}

void combine_blocks(block_t* pcurrent)
{
    if(!pcurrent || heap_validate())
        return;

    block_t* next = pcurrent->pnext;
    if(!next)
        return;
    if(next->free != 1)
        return;

    char* curr = (char*)pcurrent + sizeof(block_t);
    char* next_pos = (char*)next + sizeof(block_t) + next->size;
    block_t* next_next = next->pnext;

    int len = next_pos - curr;

    if(next_next)
    {
        next_next->pprev = pcurrent;
        pcurrent->pnext = next_next;
        init_control_block_checker(next_next);
    }
    else
        pcurrent->pnext = NULL;

    pcurrent->size = len;
    init_control_block_checker(pcurrent);
}

void insert_fences(void* wsk)
{
    char* ptr = (char*)wsk;

    for(int i=0; i<FENCE_LEN; i++)
        ptr[i] = '#';
}

void* heap_malloc(size_t size)
{
    if(!memory_block || size <= 0 || heap_validate())
        return NULL;

    block_t* ptr = first_fit(size);

    if(ptr == NULL)
    {
        block_t* temp = get_last_block();

        int x=0;
        size_t req_size = (int)size + (2 * FENCE_LEN) + sizeof(block_t);
        size_t res = 0;

        char* next_pos;
        if(temp->free == 1)
            next_pos = (char*)temp + sizeof(block_t) + temp->size + req_size;
        if(temp->free == 0)
            next_pos = (char*)temp + sizeof(block_t) + temp->size + (2 * FENCE_LEN) + req_size;

        int i=0;
        char* curr = (char*)memory_block;
        while(next_pos != curr)
        {
            i++;
            curr++;
        }

        if(i > usage)
        {
            int difference = i - usage;

            while(res < (size_t)difference)
            {
                x++;
                res = FOUR_KB * x;
            }

            if(ask_for_memory(x))
                return NULL;
        }

        char* wsk;
        if(temp->free == 1)
            wsk = (char*)temp + sizeof(block_t) + temp->size;
        if(temp->free == 0)
            wsk = (char*)temp + sizeof(block_t) + temp->size + (2 * FENCE_LEN);

        int len = (char*)custom_sbrk(0) - wsk - sizeof(block_t);
        len = abs(len);

        block_t* new = (block_t*)wsk;
        new->pprev = temp;
        new->pnext = NULL;
        new->size = len;
        new->free = 1;
        init_control_block_checker(new);

        temp->pnext = new;
        init_control_block_checker(temp);

        if(new->pprev->free == 1)
            combine_blocks(new->pprev);

        ptr = first_fit(size);
    }

    ptr->free = 0;
    ptr->size = (int)size;
    init_control_block_checker(ptr);

    char* fences_place = (char*)ptr + sizeof(block_t);
    insert_fences(fences_place);
    fences_place += FENCE_LEN + ptr->size;
    insert_fences(fences_place);

    void* result = (char*)ptr + sizeof(block_t) + FENCE_LEN;
    return result;
}

void* heap_calloc(size_t number, size_t size)
{
    if(!memory_block)
        return NULL;

    size_t s = number * size;
    char* ptr = heap_malloc(s);

    if(!ptr)
        return NULL;

    memset(ptr, 0, s);
    return ptr;
}

void* heap_realloc(void* memblock, size_t size)
{
    if(heap_validate())
        return NULL;

    if(size == 0)
    {
        heap_free(memblock);
        return NULL;
    }

    if(memblock == NULL)
        return heap_malloc(size);

    if(get_pointer_type(memblock) != pointer_valid)
        return NULL;

    char* temp = (char*)memblock - FENCE_LEN - sizeof(block_t);
    block_t* ptr = (block_t*)temp;

    if((size_t)ptr->size == size)
        return memblock;


    // Downsizing
    if(ptr->size >= (int)size)
    {
        char* fences = (char*)ptr + sizeof(block_t) + FENCE_LEN + size;
        insert_fences(fences);
        ptr->size = (int)size;
        init_control_block_checker(ptr);

        return memblock;
    }

    // Increasing size
    if(ptr->size < (int)size)
    {
        block_t* next = ptr->pnext;

        // Next block == NULL
        if(next == NULL)
        {
            block_t* pcurrent = ptr;
            char* curr = (char*)pcurrent + sizeof(block_t);
            char* next_pos = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + size + FENCE_LEN;
            char* end = (char*)memory_block + usage;
            int res=0, len, x=0, available;

            len = next_pos - curr;
            available = end - curr;

            if(len > available)
            {
                int difference = len - available;

                while(res < difference)
                {
                    x++;
                    res = FOUR_KB * x;
                }

                if(ask_for_memory(x))
                    return NULL;
            }

            pcurrent->size = (int)size;
            init_control_block_checker(pcurrent);
            char* fences = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + size;
            insert_fences(fences);

            return memblock;
        }

        // Next block free == 0
        else if(next->free == 0)
        {
            block_t* pcurrent = ptr;
            char* curr = (char*)pcurrent + sizeof(block_t);
            char* next_pos = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + size + FENCE_LEN;
            int required, available;

            required = next_pos - curr;

            curr = (char*)pcurrent + sizeof(block_t);
            next_pos = (char*)next;

            available = next_pos - curr;

            if(required <= available)
            {
                char* fences = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + size;
                insert_fences(fences);
                pcurrent->size = (int)size;
                init_control_block_checker(ptr);

                return memblock;
            }
            else
            {
                void* new = heap_malloc(size);
                if(new == NULL)
                    return NULL;

                memcpy(new, memblock, pcurrent->size);
                heap_free(memblock);

                return new;
            }
        }

        // Next block free == 1
        else
        {
            block_t* pcurrent = ptr;
            char* curr = (char*)pcurrent + sizeof(block_t);
            char* next_pos = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + size + FENCE_LEN;
            int required, available;

            required = next_pos - curr;

            curr = (char*)pcurrent + sizeof(block_t);
            next_pos = (char*)next;

            available = next_pos - curr;

            if(required <= available)
            {
                char* fences = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + size;
                insert_fences(fences);
                pcurrent->size = (int)size;
                init_control_block_checker(ptr);

                return memblock;
            }
            else
            {
                int free_len = pcurrent->pnext->size + (int)sizeof(block_t);
                available += free_len;
                if(required <= available)
                {
                    pcurrent->size = (int)size;
                    pcurrent->free = 0;
                    pcurrent->pnext = pcurrent->pnext->pnext;
                    if(pcurrent->pnext->pnext)
                    {
                        pcurrent->pnext->pnext->pprev = pcurrent;
                        init_control_block_checker(pcurrent->pnext->pnext);
                    }
                    init_control_block_checker(pcurrent);

                    char* fences = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + size;
                    insert_fences(fences);

                    return memblock;
                }
                else
                {
                    void* new = heap_malloc(size);
                    if(new == NULL)
                        return NULL;

                    memcpy(new, memblock, pcurrent->size);
                    heap_free(memblock);

                    return new;
                }
            }
        }
    }

    return NULL;
}

void heap_free(void* ptr)
{
    if(!memory_block || !ptr || heap_validate())
        return;

    block_t* pcurrent = (block_t*)memory_block;

    for(;pcurrent != NULL; pcurrent = pcurrent->pnext)
    {
        char* wsk = (char*)pcurrent + sizeof(block_t) + FENCE_LEN;
        if( wsk == (char*)ptr )
            break;
    }

    if(!pcurrent || pcurrent->free == 1)
        return;

    block_t* next = pcurrent->pnext;

    if(!next)
    {
        char* wsk = (char*)pcurrent + sizeof(block_t);

        int len = (char*)custom_sbrk(0) - wsk;
        len = abs(len);
        pcurrent->size = len;
    }
    else
    {
        char* wsk = (char*)pcurrent + sizeof(block_t);
        int len = (char*)next - wsk;
        len = abs(len);
        pcurrent->size = len;
    }

    pcurrent->free = 1;
    init_control_block_checker(pcurrent);

    block_t* test = (block_t*)memory_block;
    while(1)
    {
        if(!test)
            break;
        if(!test->pnext)
            break;

        if(test->free == 1 && test->pnext->free == 1)
        {
            combine_blocks(test);
            continue;
        }

        test = test->pnext;
    }

    block_t* temp = NULL;
    block_t* check = NULL;
    int i=0;

    for(check = (block_t*)memory_block; check != NULL; check = check->pnext)
    {
        temp = check->pnext;
        if(temp == NULL)
            break;
        i++;
    }

    if(check->pnext == NULL && check->free == 1 && i != 0)
    {
        check->pprev->pnext = NULL;
        init_control_block_checker(check->pprev);
    }
}


int heap_validate(void)
{
    if(!memory_block)
        return 2;

    if(check_control_blocks())
        return 3;

    block_t* pcurrent = (block_t*)memory_block;

    for(;pcurrent != NULL; pcurrent = pcurrent->pnext)
    {
        if(pcurrent->free == 1)
            continue;

        char* wsk = (char*)pcurrent + sizeof(block_t);
        for(int i=0; i<FENCE_LEN; i++)
        {
            if(wsk[i] != '#')
                return 1;
        }

        wsk = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + pcurrent->size;
        for(int i=0; i<FENCE_LEN; i++)
        {
            if(wsk[i] != '#')
                return 1;
        }
    }

    return 0;
}

size_t heap_get_largest_used_block_size(void)
{
    if(!memory_block || heap_validate())
        return 0;

    int max = 0;

    block_t* pcurrent = (block_t*)memory_block;
    for(; pcurrent; pcurrent = pcurrent->pnext)
    {
        if(pcurrent->free == 0 && pcurrent->size > max)
            max = pcurrent->size;
    }

    return max;
}

enum pointer_type_t get_pointer_type(const void* ptr)
{
    if(!ptr)
        return pointer_null;

    if(heap_validate())
        return pointer_heap_corrupted;

    char* wsk = (char*)ptr;

    block_t* pcurrent = (block_t*)memory_block;
    for(;pcurrent != NULL; pcurrent = pcurrent->pnext)
    {
        char* temp = (char*)pcurrent;

        for(int i=0; i < (int)sizeof(block_t); i++)
        {
            if(temp == wsk)
                return pointer_control_block;
            temp++;
        }

        if(pcurrent->free == 0)
        {
            temp = (char*)pcurrent + sizeof(block_t) + FENCE_LEN;
            if(temp == wsk)
                return pointer_valid;

            for(int i=0; i<pcurrent->size; i++)
            {
                if(temp == wsk)
                    return pointer_inside_data_block;
                temp++;
            }

            temp = (char*)pcurrent + sizeof(block_t);
            for(int i=0; i<FENCE_LEN; i++)
            {
                if(temp == wsk)
                    return pointer_inside_fences;
                temp++;
            }

            temp = (char*)pcurrent + sizeof(block_t) + FENCE_LEN + pcurrent->size;
            for(int i=0; i<FENCE_LEN; i++)
            {
                if(temp == wsk)
                    return pointer_inside_fences;
                temp++;
            }
        }

        if(pcurrent->free == 1)
        {
            temp = (char*)pcurrent + sizeof(block_t);
            for(int i=0; i<pcurrent->size; i++)
            {
                if(temp == wsk)
                    return pointer_unallocated;
                temp++;
            }
        }
    }

    return pointer_unallocated;
}

