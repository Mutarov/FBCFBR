#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    PARENT_LEFT,   
    PARENT_RIGHT,  
    UNKNOWN,
    END_OF_FILE
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token next_token(const char **input);
void free_token(Token token);
const char *token_type_to_string(TokenType type);

#endif
