#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "value.h"
#include "vm.h"

#define ALLOCATE_OBJ(type, objectType)                                         \
  (type *)allocateObject(sizeof(type), objectType)

// NOTE: The allocateObject function accepts the size parameter
// so that it can allocate additional space beyond what is required by the
// object directly. This is because the "children" of the object type
// are constructed with the object struct as their first field. This
// allows for simple casting between the children and parent types, but requires
// that the allocateObject function can allocate the additional space required
// by the child types.
/**
 * Allocate space for a new Object
 *
 * @param size Size of the object to allocate
 * @param type of Type of the object to allocate
 *
 * @returns Pointer to the newly allocated object */
static Obj *allocateObject(size_t size, ObjType type) {
  Obj *object = (Obj *)reallocate(NULL, 0, size);
  object->type = type;

  // Add the object to the list of objects for memory management
  object->next = vm.objects;
  vm.objects = object;
  return object;
}

/**
 * Allocate memory for a string object
 *
 * @param chars Pointer to characters which the object will reference
 * @param length The length of the string
 *
 * @returns New string object */
static ObjString *allocateString(char *chars, int length) {
  ObjString *string = ALLOCATE_OBJ(ObjString, OBJ_STRING);
  string->length = length;
  string->chars = chars;
  return string;
}

ObjString *takeString(char *chars, int length) {
  return allocateString(chars, length);
}

ObjString *copyString(const char *chars, int length) {
  char *heapChars = ALLOCATE(char, length + 1);
  memcpy(heapChars, chars, length);
  heapChars[length] = '\0';
  return allocateString(heapChars, length);
}

void printObject(Value value) {
  switch (OBJ_TYPE(value)) {
  case OBJ_STRING:
    printf("%s", AS_CSTRING(value));
    break;
  }
}
