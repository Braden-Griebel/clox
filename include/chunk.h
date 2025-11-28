/**
 * @file chunk.h
 * @brief Arrays of opcodes
 * */

#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

/**
 * Define the types of opcode
 * */
typedef enum {
  OP_CONSTANT, //! Get a constant from Constant array
  OP_ADD,      //! Binary addition
  OP_SUBTRACT, //! Binary subtraction
  OP_MULTIPLY, //! Binary multiplication
  OP_DIVIDE,   //! Binary Division
  OP_NEGATE,   //! Unary negate
  OP_RETURN,   //! Return (from function)
} OpCode;

/**
 * A dynamic array of opcodes (which are single bytes).
 * */
typedef struct {
  int count;            //! Current number of elements in array (in bytes)
  int capacity;         //! Current capacity of the array (in bytes)
  uint8_t *code;        //! Pointer to code array
  int *lines;           //! Line numbers of the instructions
  ValueArray constants; //! Array of constant values
} Chunk;

/**
 * Initialize a new chunk.
 *
 * @param chunk Pointer to array to initialize
 */
void initChunk(Chunk *chunk);

/**
 * Free memory of a chunk
 *
 * @param chunk Pointer to array to free
 */
void freeChunk(Chunk *chunk);

/**
 * Write a byte to the chunk
 *
 * @param chunk Pointer to the chunk array being written to
 * @param byte Byte to write to the array
 */
void writeChunk(Chunk *chunk, uint8_t byte, int line);

/**
 * Add a constant to the value array of the chunk.
 *
 * @param chunk Chunk to add the value to
 * @param value Value to add to the constants ValueArray
 * */
int addConstant(Chunk *chunk, Value value);

#endif // !clox_chunk_h
