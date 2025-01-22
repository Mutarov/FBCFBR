#include "lexer.h"

const char *keywords[] = {
    "if", "else", "while", "for", "return", "int", "float", "char", NULL
};

int is_keyword(const char *str) {
    for (int i = 0; keywords[i] != NULL; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

TokenType get_keyword_type(const char *str) {
    if (strcmp(str, "if") == 0) return IF;
    if (strcmp(str, "else") == 0) return ELSE;
    if (strcmp(str, "while") == 0) return WHILE;
    if (strcmp(str, "for") == 0) return FOR;
    if (strcmp(str, "return") == 0) return RETURN;
    if (strcmp(str, "int") == 0) return INT;
    if (strcmp(str, "float") == 0) return FLOAT;
    if (strcmp(str, "char") == 0) return CHAR;
    return UNKNOWN;  
}


const char *token_type_to_string(TokenType type) {
    switch (type) {
        case IDENTIFIER:      return "IDENTIFIER";
        case NUMBER:          return "NUMBER";
        case OPERATOR:        return "OPERATOR";
        case PARENT_LEFT:     return "PARENT_LEFT";
        case PARENT_RIGHT:    return "PARENT_RIGHT";
        case IF:              return "IF";
        case ELSE:            return "ELSE";
        case WHILE:           return "WHILE";
        case FOR:             return "FOR";
        case RETURN:          return "RETURN";
        case INT:             return "INT";
        case FLOAT:           return "FLOAT";
        case CHAR:            return "CHAR";
        case STRING_LITERAL:  return "STRING_LITERAL";
        case CHAR_LITERAL:    return "CHAR_LITERAL";
        case COMMA:           return "COMMA";
        case SEMICOLON:       return "SEMICOLON";
        case UNKNOWN:         return "UNKNOWN";
        case END_OF_FILE:     return "END_OF_FILE";
        default:              return "INVALID";
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

    
    if (**input == '"') {
        (*input)++; 
        const char *start = *input;
        while (**input != '"' && **input != '\0') {
            (*input)++;
        }

        if (**input == '"') {
            size_t length = *input - start;
            char *value = malloc(length + 1);
            strncpy(value, start, length);
            value[length] = '\0';
            (*input)++; 
            return (Token){STRING_LITERAL, value};
        } else {
            return (Token){UNKNOWN, strdup("Unterminated string literal")};
        }
    }

    
    if (**input == '\'') {
        (*input)++; 
        char value[2] = {'\0', '\0'};
        value[0] = **input;
        (*input)++;
        if (**input == '\'') {
            (*input)++; 
            return (Token){CHAR_LITERAL, strdup(value)};
        } else {
            return (Token){UNKNOWN, strdup("Unterminated char literal")};
        }
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

        
        TokenType keyword_type = get_keyword_type(value);
        if (keyword_type != UNKNOWN) {
            free(value);
            return (Token){keyword_type, NULL};  
        } else {
            return (Token){IDENTIFIER, value};  
        }
    }

    
    if (isdigit(**input)) {
        const char *start = *input;
        while (isdigit(**input)) {
            (*input)++;
        }
        size_t length = *input - start;
        char *value = malloc(length + 1);
        strncpy(value, start, length);
        value[length] = '\0';
        return (Token){NUMBER, value};
    }

    
    if (**input == '(') {
        (*input)++;
        return (Token){PARENT_LEFT, strdup("(")};
    }
    if (**input == ')') {
        (*input)++;
        return (Token){PARENT_RIGHT, strdup(")")};
    }

    
    if (**input == ',') {
        (*input)++;
        return (Token){COMMA, strdup(",")};
    }

    
    if (**input == ';') {
        (*input)++;
        return (Token){SEMICOLON, strdup(";")};
    }

    
    if (strchr("+-*/=<>", **input)) {
        char op = **input;
        (*input)++;
        char *value = malloc(2);
        value[0] = op;
        value[1] = '\0';
        return (Token){OPERATOR, value};
    }

    
    char unknown = **input;
    (*input)++;
    char *value = malloc(2);
    value[0] = unknown;
    value[1] = '\0';
    return (Token){UNKNOWN, value};
}
