/**
 * @mainpage Lox Interpreter
 * @section Introduction
 *
 * Welcome to clox, a lox interpreter written in c. It is from Robert Nystrom's
 * Book [Crafting Interpreters](https://craftinginterpreters.com/)
 * */

// Std lib includes
#include <stdlib.h> // For EXIT_SUCCESS/EXIT_FAILURE

// Local Includes
#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, char *argv[]) {
  initVM();

  // Manually create and free a chunk to test if it works
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_DIVIDE, 123);

  writeChunk(&chunk, OP_NEGATE, 123);

  writeChunk(&chunk, OP_RETURN, 123);

  dissasembleChunk(&chunk, "test chunk");
  interpret(&chunk);
  freeVM();
  freeChunk(&chunk);

  return EXIT_SUCCESS;
}
