#ifndef clox_debug_h
#include "chunk.h"

/**
 * Dissasemble a chunk of bytecode.
 *
 * Dissasemble chunk of bytecode and print the
 * instructions.
 *
 * @param chunk Chunk of bytecode to dissasemble
 * @param name Name of the chunk (used for display only)
 */
void dissasembleChunk(Chunk *chunk, const char *name);

/**
 * Dissasemble a single instruction.
 *
 * @param chunk Array of bytecode containing the instruction to dissasemble
 * @param offset Location in the chunk where the instruction to dissasemble is
 *
 * @return Offset of next instruction
 * */
int dissasembleInstruction(Chunk *chunk, int offset);

#endif // !clox_debug_h
