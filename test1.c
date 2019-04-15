/* 
 * File:   test1.c
 * Author: Tom
 * Checks that the cache support is working
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

/*
 *    This test should have 1 cache miss on a store and 1 cache hit on a load.
 */

void doTest()
{
    memory_store(0, 1234);
    int value = memory_load(0);
    if (value != 1234)
    {
        printf("expected 1234 but got %d\n", value);
    }
}


int main(int argc, char** argv) 
{
    for (enum cache_type ct = NO_CACHE; ct < MAX_CACHE_TYPES; ++ct)
    {
        printf("\n");
        memory_init(ct);
        printf("initializing memory\n");
	doTest();
        memory_flush();
        memory_stats();
    }
    return (EXIT_SUCCESS);
}

