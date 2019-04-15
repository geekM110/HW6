/* 
 * Compares the summing of a MxN matrix done in row major vs column major order
 *
 * Created on October 18, 2018, 6:46 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "trace.h"
#include <string.h>

// The size of the matrix
#define M 8
#define N 4

// The following object is used for address calculation only
int ary[M][N];

void sumRowMajor()
{
    int sum = 0;
    for (int i=0; i<M; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            int * loc = &ary[i][j];
            int offset = (char *) loc - (char *) &ary;
            sum += memory_load(offset);
        }
    }
}

void sumColumnMajor()
{
    int sum = 0;
    for (int j=0; j<N; ++j)
    {
        for (int i=0; i<M; ++i)
        {
            int * loc = &ary[i][j];
            int offset = (char *) loc - (char *) &ary;
            sum += memory_load(offset);
        }
    }
}

int main(int argc, char** argv) 
{
    if (argc >= 2)
    {
        TRACE_ENABLE(strcmp(argv[1], "-t") == 0);
    }
    for (enum cache_type ct = NO_CACHE; ct < MAX_CACHE_TYPES; ++ct)
    {
        printf("\n");
        memory_init(ct);
	printf("Row Major Access\n");
	sumRowMajor();
        printf("\n");
        memory_flush();
        memory_stats();
        memory_init(ct);
	printf("Column Major Access\n");
	sumColumnMajor();
        printf("\n");
        memory_flush();
        memory_stats();
    }
    return (EXIT_SUCCESS);
}

