/**
 * @file value.h
 * @brief Dynamic arrays of values
 * */

#ifndef clox_value_h
#define clox_value_h

#include "common.h"

/**
 * Possible types of values in Lox */
typedef enum {
  VAL_BOOL,   //! A boolean
  VAL_NIL,    //! Nil value
  VAL_NUMBER, //! Floating point number
} ValueType;

/**
 * Values in lox, a tagged union possibly representing bools, numbers, or nil
 * values
 * */
typedef struct {
  ValueType type; //! The type of the value
  union {
    bool boolean;  //! Bool value
    double number; //! Floating point number
  } as;            //! The actual data represented by the value
} Value;

// Macros for converting c values to lox values
#define BOOL_VAL(value) ((Value){VAL_BOOL, {.boolean = value}})
#define NIL_VAL ((Value){VAL_NIL, {.number = 0}})
#define NUMBER_VAL(value) ((Value){VAL_NUMBER, {.number = value}})

// Macros for converting lox values to c values
#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUMBER(value) ((value).as.number)

// Macros for checking the type of a lox value
#define IS_BOOL(value) ((value).type == VAL_BOOL)
#define IS_NIL(value) ((value).type == VAL_NIL)
#define IS_NUMBER(value) ((value.type) == VAL_NUMBER)

/**
 * Array of constant values (associated with a chunk)
 * */
typedef struct {
  int capacity;  //! Current capacity of the array
  int count;     //! Current number of values stored in the array
  Value *values; //! Pointer to the array holding the values
} ValueArray;

/**
 * Check if two values are equal*/
bool valuesEqual(Value a, Value b);

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
