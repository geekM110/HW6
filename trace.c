#include "trace.h"
#include <stdio.h>

static bool enabled = false;
void TRACE_ENABLE(bool on)
{
    enabled = on;
}

void TRACE_ADDR(memory_address a)
{
    if (enabled) printf("%d", a);
}

void TRACE_ACTION(char act)
{
    if (enabled) printf("%c", act);
}

void TRACE_HIT()
{
    TRACE_ACTION('h');
}

void TRACE_MISS()
{
    TRACE_ACTION('M');
}

void TRACE_END()
{
    if (enabled) printf(" ");
}


