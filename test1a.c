/* 
 * File:   test1a.c
 * Author: Tom
 * Checks that the cache support is working
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

/*
 *    This test should have 2 cache misses on stores and 2 cache hits on loads.
 */

void doTest()
{
    memory_store(0, 1234);
    memory_store(16, 2345);
    int value = memory_load(0);
    if (value != 1234)
    {
        printf("expected 1234 but got %d\n", value);
    }
    value = memory_load(16);
    if (value != 2345)
    {
        printf("expected 2345 but got %d\n", value);
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

