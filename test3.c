/* 
 * File:   test2.c
 * Author: Tom
 * Checks that the cache support is working
 *
 * Created on September 9, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "memory.h"
#include "trace.h"

/*
 * 
 */
#define N 100

void initMatrix()
{
    for (int i=0; i<N; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            memory_store((i * N + j) * sizeof(int), i*N+j);
        }
    }
}

void checkMatrix()
{
    for (int i=0; i<N; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            int value = memory_load((i * N + j) * sizeof(int));
            if (value != i * N + j)
            {
                printf("expected %d but got %d \n", i * N + j, value);
            }
        }
    }
}

int main(int argc, char** argv) 
{
    bool trace = false;
    if (argc >= 2)
    {
        trace = strcmp(argv[1], "-t") == 0;
        TRACE_ENABLE(trace);
    }

    for (enum cache_type ct = NO_CACHE; ct < MAX_CACHE_TYPES; ++ct)
    {
        printf("\n");
        memory_init(ct);
        printf("initializing memory\n");
	initMatrix();
        memory_flush();
        memory_stats();
        // note that no init is done here
	printf("Checking memory\n");
	checkMatrix();
        memory_flush();
        memory_stats();
    }
    return (EXIT_SUCCESS);
}

