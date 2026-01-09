#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)

/*!
 * Types of heap allocated objects*/
typedef enum {
  OBJ_STRING, //! Sequence of characters
} ObjType;

/*!
 * Represents a heap allocated object */
struct Obj {
  ObjType type;     //! Type of the object
  struct Obj *next; //! Pointer to next object (used for GC)
};

/*!
 * String Object*/
struct ObjString {
  Obj obj;     //! The associated object
  int length;  //! The length of the string
  char *chars; //! Pointer to the string data
};

/**
 * Take a string which has already been allocated and move it
 * into an object.
 *
 * @param chars Pointer to string which is to be taken
 * @param length Length of the string
 *
 * @returns Pointer to the object which now owns the string*/
ObjString *takeString(char *chars, int length);
/**
 * Copy a string from the source code into new memory
 *
 * @param chars Pointer to the string to be copied
 * @param length Length of the string to copy
 *
 * @returns Pointer to an Object which holds the string*/
ObjString *copyString(const char *chars, int length);
/**
 * Print a value of the object type
 *
 * @param value Value to print, which is an object*/
void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
