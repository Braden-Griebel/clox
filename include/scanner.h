#ifndef clox_scanner_h
#define clox_scanner_h

/**
 * The possible types of tokens
 * */
typedef enum {
  // Single-character tokens.
  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,
  TOKEN_COMMA,
  TOKEN_DOT,
  TOKEN_MINUS,
  TOKEN_PLUS,
  TOKEN_SEMICOLON,
  TOKEN_SLASH,
  TOKEN_STAR,
  // One or two character tokens.
  TOKEN_BANG,
  TOKEN_BANG_EQUAL,
  TOKEN_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,
  // Literals.
  TOKEN_IDENTIFIER,
  TOKEN_STRING,
  TOKEN_NUMBER,
  // Keywords.
  TOKEN_AND,
  TOKEN_CLASS,
  TOKEN_ELSE,
  TOKEN_FALSE,
  TOKEN_FOR,
  TOKEN_FUN,
  TOKEN_IF,
  TOKEN_NIL,
  TOKEN_OR,
  TOKEN_PRINT,
  TOKEN_RETURN,
  TOKEN_SUPER,
  TOKEN_THIS,
  TOKEN_TRUE,
  TOKEN_VAR,
  TOKEN_WHILE,

  // Errors/EOF
  TOKEN_ERROR,
  TOKEN_EOF
} TokenType;

/**
 * A single Token/Lexeme
 * */
typedef struct {
  TokenType type;    //! The type of the token
  const char *start; //! The start (in the source code string) of the token
  int length;        //! The length of the token
  int line;          //! The line of the source code the token is on
} Token;

/**
 * Initialize the Scanner from a source code string
 *
 * @param source Source code string
 * */
void initScanner(const char *source);

/**
 * Get the next token from the scanner
 *
 * @returns The next token in the source code
 * */
Token scanToken();

#endif // !clox_scanner_h
