/* 
 *  Performs an array transpose on a M x N matrix
 */

#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "trace.h"
#include <string.h>

// the size of the matrix
#define M 8
#define N 8

int srcAry[M][N];
int dstAry[N][M];

void transpose()
{
    int gap = 8;  // space between source and dest
    int sourceBase = 0;
    int destBase = sourceBase + sizeof(srcAry) + gap;
    for (int i=0; i<M; ++i)
    {
        for (int j=0; j<N; ++j)
        {
            int * srcLoc = &srcAry[i][j];
            int srcOffset = (char *) srcLoc - (char *) &srcAry;
            int tmp = memory_load(sourceBase + srcOffset);
            int * dstLoc = &dstAry[j][i];
            int dstOffset = (char *) dstLoc - (char *) &dstAry;
            memory_store(destBase + dstOffset, tmp);
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
	printf("Transpose\n");
	transpose();
        if (trace) printf("\n");
        memory_stats();
    }
    return (EXIT_SUCCESS);
}

