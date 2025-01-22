#include "lexer.h"

const char *token_type_to_string(TokenType type) {
    switch (type) {
        case IDENTIFIER:    return "IDENTIFIER";
        case NUMBER:        return "NUMBER";
        case OPERATOR:      return "OPERATOR";
        case PARENT_LEFT:   return "PARENT_LEFT";
        case PARENT_RIGHT:  return "PARENT_RIGHT";
        case UNKNOWN:       return "UNKNOWN";
        case END_OF_FILE:   return "END_OF_FILE";
        default:            return "INVALID";
    }
}

void free_token(Token token) {
    if (token.value) {
        free(token.value);
    }
}

Token next_token(const char **input) {
    while (isspace(**input)) {
        (*input)++;
    }

    if (**input == '\0') {
        return (Token){END_OF_FILE, NULL};
    }

    if (isalpha(**input)) {
        const char *start = *input;
        while (isalnum(**input) || **input == '_') {
            (*input)++;
        }
        size_t length = *input - start;
        char *value = malloc(length + 1);
        strncpy(value, start, length);
        value[length] = '\0';
        return (Token){IDENTIFIER, value};
    } else if (isdigit(**input)) {
        const char *start = *input;
        while (isdigit(**input)) {
            (*input)++;
        }
        size_t length = *input - start;
        char *value = malloc(length + 1);
        strncpy(value, start, length);
        value[length] = '\0';
        return (Token){NUMBER, value};
    } else if (**input == '(') {
        (*input)++;
        return (Token){PARENT_LEFT, strdup("(")};
    } else if (**input == ')') {
        (*input)++;
        return (Token){PARENT_RIGHT, strdup(")")};
    } else if (strchr("+-*/=", **input)) {
        char op = **input;
        (*input)++;
        char *value = malloc(2);
        value[0] = op;
        value[1] = '\0';
        return (Token){OPERATOR, value};
    } else {
        char unknown = **input;
        (*input)++;
        char *value = malloc(2);
        value[0] = unknown;
        value[1] = '\0';
        return (Token){UNKNOWN, value};
    }
}
