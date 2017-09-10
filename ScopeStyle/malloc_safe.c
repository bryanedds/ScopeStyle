#include "malloc_safe.h"

#include <assert.h>
#include <stdlib.h>

void* malloc_safe(size_t size)
{
    void* memory = malloc(size);
    assert(memory != NULL && "Out of memory.");
    if (memory == NULL) exit(EXIT_FAILURE);
    return memory;
}
