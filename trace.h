
#ifndef TRACE_H
#define TRACE_H
#include "storage.h"
#include <stdbool.h>

void TRACE_ENABLE(bool on);
void TRACE_ADDR(memory_address a);
void TRACE_HIT();
void TRACE_MISS();
void TRACE_END();

#endif

