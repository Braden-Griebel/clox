/**
 * @mainpage Lox Interpreter
 * @section Introduction
 *
 * Welcome to clox, a lox interpreter written in c. It is from Robert Nystrom's
 * Book [Crafting Interpreters](https://craftinginterpreters.com/)
 * */

// Std lib includes
#include <stddef.h>
#include <stdio.h>  // For printf/fprintf/etc
#include <stdlib.h> // For EXIT_SUCCESS/EXIT_FAILURE
#include <string.h>

// Local Includes
#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

/**
 * Run the repl (Read-Eval-Print-Loop)
 * */
static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

/**
 * Read a file into a string
 *
 * @param char* Path to file to read
 *
 * @return Contents of the file as a null-terminated string
 * */
static char *readFile(const char *path) {
  // Open the file for reading
  FILE *file = fopen(path, "rb");
  // If the file open fails, exit with error
  if (file == NULL) {
    fprintf(stderr, "Could not open file \"%s\".\n", path);
    exit(74);
  }

  // Go to the end of the file to find file size
  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  // Rewind to the start of the file
  rewind(file);

  // Create a buffer large enough to hold the file, and an end file character
  char *buffer = (char *)malloc(fileSize + 1);
  // If the buffer couldn't be allocated, exit with error
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  // Read the file into the buffer
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  // If the read fails exit with error
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n", path);
    exit(74);
  }
  // Add an EOF file
  buffer[bytesRead] = '\0';

  // Make sure to close the file
  fclose(file);
  // Just return the buffer, if must be freed by the caller
  return buffer;
}

/**
 * Run the code in a lox file
 *
 * @param char* Path to file to run
 * */
static void runFile(const char *path) {
  char *source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR)
    exit(65);
  if (result == INTERPRET_RUNTIME_ERROR)
    exit(70);
}

int main(int argc, char *argv[]) {
  initVM();

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
    exit(64);
  }

  freeVM();
  return EXIT_SUCCESS;
}
