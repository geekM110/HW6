#include <stdio.h>
#include <cache_direct.h>
#include <memory.h>
#include <storage.h>

int matrix[100];
int cacheLoad;
int cacheStore;

void cache_direct_init(){
    cacheLoad = 0;
    cacheStore = 0;
}

int  cache_direct_load(memory_address addr){
    cacheLoad++;
    return matrix[addr];
}

void cache_direct_store(memory_address addr, int value){
    int current = cache_direct_load(addr);
    cacheStore++;

    if (current != NULL)
        printf("Current value is: %d", current);
    else {
        printf("Empty address");
        matrix[addr] = value;
    }
}

void cache_direct_flush(){
    for (int i=0; i<getLength(matrix); i++)
        if (matrix[i] != NULL)
            storage_store(i, matrix[i]);
}

void cache_direct_stats(){
    printf("Cache store calls:%d, Cache load calls:%d", cacheStore, cacheLoad);
}

int* reinit(int* matrix) {
    int len = getLength(matrix);
    int *result[len+100];

    for (int i=0; i<len; i++) {
        result[i] = matrix[i];
    }

    return result;
}

int getLength(int* matrix) {
    return sizeOf(matrix)/4;
}

int needsReinit(int* matrix) {
    return matrix[getLength(matrix)-1] != NULL;
}
