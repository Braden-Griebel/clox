/**
 * @file value.h
 * @brief Dynamic arrays of values
 * */

#ifndef clox_value_h
#define clox_value_h

#include "common.h"

/**
 * Values in lox
 * */
typedef double Value;

/**
 * Array of constant values (associated with a chunk)
 * */
typedef struct {
  int capacity;  //! Current capacity of the array
  int count;     //! Current number of values stored in the array
  Value *values; //! Pointer to the array holding the values
} ValueArray;

/**
 * Initialize a new value array
 *
 * @param array Pointer to the value array to initialize
 * */
void initValueArray(ValueArray *array);

/**
 * Write a value to the value array
 *
 * @param array Pointer to the value array to write to
 * @param value Value to add to the array
 * */
void writeValueArray(ValueArray *array, Value value);

/**
 * Free the memory associated with a value array
 *
 * @param array Array to be freed
 * */
void freeValueArray(ValueArray *array);

/**
 * Print a value.
 *
 * @param value Value to be printed
 * */
void printValue(Value value);
#endif // !clox_value_h
