#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define GROW_ARRAY(type, pointer, oldCount, newCount)                          \
  (type *)reallocate(pointer, sizeof(type) * (oldCount),                       \
                     sizeof(type) * (newCount))

#define FREE_ARRAY(type, pointer, oldCount)                                    \
  reallocate(pointer, sizeof(type) * (oldCount), 0)

/**
 * Reallocate memory for an array (grow, shrink, free, etc.)
 *
 * @param pointer Pointer to the array
 * @param oldSize Size prior to reallocation (in bytes)
 * @param newSize Size after reallocation (in bytes)
 * */
void *reallocate(void *pointer, size_t oldSize, size_t newSize);

#endif // !clox_memory_h
