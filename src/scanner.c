#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct {
  const char *start;
  const char *current;
  int line;
} Scanner;

// Use a global scanner variable to avoid need to
// pass it around
Scanner scanner;

void initScanner(const char *source) {
  scanner.start = source;   // Pointer to the start of the stirng
  scanner.current = source; // Current is also just the start
  scanner.line = 1;         // Will increment with new-lines
}

/** Check for a digit */
static bool isDigit(char c) { return c >= '0' && c <= '9'; }

/** Check for an alphabetic character, or an underscore */
static bool isAlpha(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

// NOTE: Don't need to scan entire source, only need single token lookahead
// for compiler

/**
 * Checks if the scanners current character is the null-terminator at the
 * end of the source code string*/
static bool isAtEnd() { return *scanner.current == '\0'; }

/**
 * Step the scanner one step, returning the consumed character
 * */
static char advance() {
  scanner.current++;
  return scanner.current[-1];
}

/** Return the current character without consuming it*/
static char peek() { return *scanner.current; }

/**
 * Return the character after the current without consuming it */
static char peekNext() {
  if (isAtEnd())
    return '\0';
  return scanner.current[1];
}

/**
 * Chack if the next character matches, conditionally advancing the scanner
 * only if the next character is a match for expected
 *
 * @param expected Expected next character
 *
 * @returns True if next character equals expected, otherwise false
 * */
static bool match(char expected) {
  if (isAtEnd())
    return false;
  if (*scanner.current != expected)
    return false;
  // If there is a match, advance
  scanner.current++;
  return true;
}

/**
 * Create a token using the Scanners state
 * */
static Token makeToken(TokenType type) {
  Token token;
  token.type = type;
  token.start = scanner.start;
  token.length = (int)(scanner.current - scanner.start);
  token.line = scanner.line;
  return token;
}

/**
 * Create an error token using the Scanners state
 * */
static Token errorToken(const char *message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;
  return token;
}

/**
 * Skip over any whitespace characters (space, newline, etc), incrementing
 * scanner's line number as needed
 * */
static void skipWhitespace() {
  for (;;) {
    char c = peek();
    switch (c) {
    case '\n':
      scanner.line++;
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;
    case '/':
      if (peekNext() == '/') {
        // Skip to the end of the line
        while (peek() != '\n' && !isAtEnd())
          advance();
      } else {
        return;
      }
      break;
    default:
      return;
    }
  }
}

static TokenType checkKeyword(int start, int length, const char *rest,
                              TokenType type) {
  if (scanner.current - scanner.start == start + length &&
      memcmp(scanner.start + start, rest, length) == 0) {
    return type;
  }

  return TOKEN_IDENTIFIER;
}

static TokenType identifierType() {
  // Basically a hand-made Trie
  switch (scanner.start[0]) {
  case 'a':
    return checkKeyword(1, 2, "nd", TOKEN_AND);
  case 'c':
    return checkKeyword(1, 4, "lass", TOKEN_CLASS);
  case 'e':
    return checkKeyword(1, 3, "lse", TOKEN_ELSE);
  case 'f':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'a':
        return checkKeyword(2, 3, "lse", TOKEN_FALSE);
      case 'o':
        return checkKeyword(2, 1, "r", TOKEN_FOR);
      case 'u':
        return checkKeyword(2, 1, "n", TOKEN_FUN);
      }
    }
    break;
  case 'i':
    return checkKeyword(1, 1, "f", TOKEN_IF);
  case 'n':
    return checkKeyword(1, 2, "il", TOKEN_NIL);
  case 'o':
    return checkKeyword(1, 1, "r", TOKEN_OR);
  case 'p':
    return checkKeyword(1, 4, "rint", TOKEN_PRINT);
  case 'r':
    return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
  case 's':
    return checkKeyword(1, 4, "uper", TOKEN_SUPER);
  case 't':
    if (scanner.current - scanner.start > 1) {
      switch (scanner.start[1]) {
      case 'h':
        return checkKeyword(2, 2, "is", TOKEN_THIS);
      case 'r':
        return checkKeyword(2, 2, "ue", TOKEN_TRUE);
      }
    }
    break;
  case 'v':
    return checkKeyword(1, 2, "ar", TOKEN_VAR);
  case 'w':
    return checkKeyword(1, 4, "hile", TOKEN_WHILE);
  }

  return TOKEN_IDENTIFIER;
}

static Token identifier() {
  while (isAlpha(peek()) || isDigit(peek()))
    advance();
  return makeToken(identifierType());
}

/**
 * Scan a number (digits optionally seperated by, or starting with, a decimal).
 * */
static Token number() {
  while (isDigit(peek()))
    advance();

  // Check for decimal
  if (peek() == '.') {
    advance(); // Consume the decimal

    // Consume the remainder of the number
    while (isDigit(peek()))
      advance();
  }
  return makeToken(TOKEN_NUMBER);
}

/**
 * Scane a double quoted string in the source code*/
static Token string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      scanner.line++;
    advance();
  }

  if (isAtEnd())
    return errorToken("Unterminated string.");

  // Consume the final quote
  advance();
  return makeToken(TOKEN_STRING);
}

Token scanToken() {
  skipWhitespace();
  scanner.start =
      scanner.current; // Set the start to the start of the current token

  if (isAtEnd())
    return makeToken(TOKEN_EOF);

  char c = advance();
  if (isAlpha(c))
    return identifier();
  if (isDigit(c))
    return number();

  switch (c) {
  case '(':
    return makeToken(TOKEN_LEFT_PAREN);
  case ')':
    return makeToken(TOKEN_RIGHT_PAREN);
  case '{':
    return makeToken(TOKEN_LEFT_BRACE);
  case '}':
    return makeToken(TOKEN_RIGHT_BRACE);
  case ';':
    return makeToken(TOKEN_SEMICOLON);
  case ',':
    return makeToken(TOKEN_COMMA);
  case '.':
    return makeToken(TOKEN_DOT);
  case '-':
    return makeToken(TOKEN_MINUS);
  case '+':
    return makeToken(TOKEN_PLUS);
  case '/':
    return makeToken(TOKEN_SLASH);
  case '*':
    return makeToken(TOKEN_STAR);
  case '!':
    makeToken(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
  case '=':
    return makeToken(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
  case '<':
    return makeToken(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
  case '>':
    return makeToken(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
  case '"':
    return string();
  }

  return errorToken("Unexpected character.");
}
