#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>  // Include for exit function

#define MAX_TOKEN_LENGTH 100
#define MAX_IDENTIFIER_LENGTH 64

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_EOF,
    TOKEN_UNKNOWN,
    TOKEN_ERROR
} TokenType;

typedef struct {
    char lexeme[MAX_TOKEN_LENGTH];
    TokenType type;
} Token;

const char *keywords[] = {"return", "int", "float", "if", "else"};
const int num_keywords = 5;

const char* get_token_type_string(TokenType type) {
    switch (type) {
        case TOKEN_KEYWORD: return "Keyword";
        case TOKEN_IDENTIFIER: return "Identifier";
        case TOKEN_NUMBER: return "Number";
        case TOKEN_OPERATOR: return "Operator";
        case TOKEN_EOF: return "EOF";
        case TOKEN_UNKNOWN: return "Unknown";
        case TOKEN_ERROR: return "Error";
        default: return "Unknown";
    }
}

bool is_keyword(const char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

Token get_token(FILE *fp) {
    Token token;
    int c, peek;
    int i = 0;
    while ((c = fgetc(fp)) != EOF && isspace(c));
    if (c == EOF) {
        strcpy(token.lexeme, "EOF");
        token.type = TOKEN_EOF;
        return token;
    }
    if (isdigit(c)) {
        token.lexeme[i++] = c;
        while (isdigit(c = fgetc(fp)) && i < MAX_TOKEN_LENGTH) {
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetc(c, fp);
        token.type = TOKEN_NUMBER;
        return token;
    } else if (isalpha(c) || c == '_') {
        token.lexeme[i++] = c;
        while ((isalnum(c = fgetc(fp)) || c == '_') && i < MAX_IDENTIFIER_LENGTH) {
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetc(c, fp);
        token.type = is_keyword(token.lexeme) ? TOKEN_KEYWORD : TOKEN_IDENTIFIER;
        return token;
    } else if (strchr("+-*/", c) != NULL) {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_OPERATOR;
        return token;
    } else {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_UNKNOWN;
        return token;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "Error opening file %s\n", argv[1]);
        exit(1);
    }

    Token token;
    do {
        token = get_token(fp);
        printf("Token: %-20s Type: %s\n", token.lexeme, get_token_type_string(token.type));
    } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);

    fclose(fp);
    return 0;
}
