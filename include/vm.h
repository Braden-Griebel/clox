#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

/**
 * Virtual Machine.
 * */
typedef struct {
  Chunk *chunk;           //! Chunk of bytecode being interpreted
  uint8_t *ip;            //! Pointer to the current instruction
  Value stack[STACK_MAX]; //! Stack of values the VM is operating on
  Value *stackTop;        //! Pointer to the top of the stack
} VM;

/**
 * Result of interpretation.
 * */
typedef enum {
  INTERPRET_OK,            //! No errors
  INTERPRET_COMPILE_ERROR, //! Error occured during compilation
  INTERPRET_RUNTIME_ERROR, //! Error occured during runtime
} InterpretResult;

/**
 * Initialize the VM.
 * */
void initVM();
/**
 * Free VM associated memory.
 * */
void freeVM();

/**
 * Interpret a Chunk of Bytecode
 * */
InterpretResult interpret(const char *source);

/**
 * Push a value onto the VMs stack.
 *
 * @param value Value to push ont the stack*/
void push(Value value);

/**
 * Remove the value on top of the VMs stack and return it.
 *
 * @return The value previously on top of the stack */
Value pop();

#endif // !clox_vm_h
