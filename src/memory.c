// Std library Includes
#include <stdlib.h>

// Local Includes
#include "memory.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  // If new size is, free the pointer, this can't use realloc with 0 directly
  // as that may not free depending on implementation
  // Also makes detecting error state below easier
  if (newSize == 0) {
    free(pointer);
    return NULL;
  }

  // Use the built in realloc function in the cast where newSize is greater than
  // 0
  void *result = realloc(pointer, newSize);
  if (result == NULL)
    exit(1);
  return result;
}
