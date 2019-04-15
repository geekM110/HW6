/* 
 *  Stores 10 values and then loads them.
 */

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

/*
 * 
 */
int main(int argc, char** argv) 
{
    for (enum cache_type ct = NO_CACHE; ct < MAX_CACHE_TYPES; ++ct)
    {
        printf("\n");
        memory_init(ct);
        for (int i=0; i<10; i++)
        {
            memory_store(i*4, i);
        }
        for (int i=0; i<10; i++)
        {
            int v = memory_load(i*4);
            if (v != i)
            {
                printf("invalid value at address %08x\n", i*4);
            }
        }
        memory_flush();
        memory_stats();
    }
    return (EXIT_SUCCESS);
}

