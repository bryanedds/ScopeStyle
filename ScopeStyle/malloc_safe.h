#ifndef BGE_MALLOC_SAFE_H
#define BGE_MALLOC_SAFE_H

#include <malloc.h>

/// Free memory at a pointer, and set the pointer to NULL.
#define free_safe(ptr) do { free(ptr); ptr = NULL; } while (false)

/// Allocate the given size of memory, asserting successful allocation, exiting upon failure.
#define malloc_safe malloc_safe

/// Allocate the given size of memory, asserting successful allocation, exiting upon failure.
void* malloc_safe(size_t size);

#endif
