#include "lexer.h"

int main() {
    const char *input = "int x = 42; if (x > 10) return \"Hello, World!\";";

    printf("Tokens:\n");
    while (1) {
        Token token = next_token(&input);
        printf("(%s, \"%s\")\n", token_type_to_string(token.type), token.value ? token.value : "NULL");
        if (token.type == END_OF_FILE) {
            free_token(token);
            break;
        }
        free_token(token);
    }

    return 0;
}
