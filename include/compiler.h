#ifndef clox_compiler_h
#define clox_compiler_h

#include "vm.h"

/**
 * Compile the source code string into a chunk of bytecode
 *
 * @param source The source code string
 * @param chunk An initialized chunk of bytecode that will be filled by the
 * compiler
 *
 * @returns True if there was no error, false otherwise*/
bool compile(const char *source, Chunk *chunk);

#endif // !clox_compiler_h
