#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

// Define the maximum length for tokens
#define MAX_TOKEN_LENGTH 100
#define MAX_IDENTIFIER_LENGTH 64
// Token types
typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_EOF,
    TOKEN_UNKNOWN,
    TOKEN_ERROR
} TokenType;

// Token structure
typedef struct {
    char lexeme[MAX_TOKEN_LENGTH];
    TokenType type;
} Token;

// Keywords array
const char *keywords[] = {"return", "int", "float", "if", "else"};
const int num_keywords = 5;

// Get the string representation of token types
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

// Check if a string is a keyword
bool is_keyword(const char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Get the next token from the input
Token get_token(FILE *fp) {
    Token token;
    int c, peek;
    int i = 0;

    // Skip whitespace
    while ((c = fgetc(fp)) != EOF && isspace(c));

    if (c == EOF) {
        strcpy(token.lexeme, "EOF");
        token.type = TOKEN_EOF;
        return token;
    }

    
    if (isalpha(c)) { // Identifier or keyword
        token.lexeme[i++] = c;
        while (isalnum(c = fgetc(fp)) && i < MAX_IDENTIFIER_LENGTH) { // Read until non-alphanumeric or max length
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetc(c, fp); // Put back the non-alphanumeric character
        if (i >= MAX_IDENTIFIER_LENGTH) {
            token.type = TOKEN_ERROR;
            strcpy(token.lexeme, "Identifier length exceeded");
        } else if (is_keyword(token.lexeme)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
    
    }
    
     else if (isdigit(c) || (c == '-' && isdigit(peek = fgetc(fp)))) { // Number
        ungetc(peek, fp); // Put back the peeked character if it is a digit
        bool isNegative = (c == '-');
        if (isNegative) {
            token.lexeme[i++] = c;
            c = fgetc(fp);  // Next character must be digit, already checked
            token.lexeme[i++] = c;
        }
        
        long num = c - '0';
        while (isdigit(c = fgetc(fp))) {
            token.lexeme[i++] = c;
            if (isNegative) {
                if (num < INT_MIN / 10 || (num == INT_MIN / 10 && -(c - '0') < INT_MIN % 10)) {
                    token.type = TOKEN_ERROR;
                    strcpy(token.lexeme, "Integer underflow");
                    // break;
                }
                num = num * 10 - (c - '0');
            } else {
                if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (c - '0') > INT_MAX % 10)) {
                    token.type = TOKEN_ERROR;
                    strcpy(token.lexeme, "Integer overflow");
                    // break;
                }
                num = num * 10 + (c - '0');
            }
        }

        if (token.type != TOKEN_ERROR) {
            token.lexeme[i] = '\0';
            ungetc(c, fp);
            token.type = TOKEN_NUMBER;
        }
    } else if (c == '+' || c == '-' || c == '*' || c == '/') { // Operator
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_OPERATOR;
    } else {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_UNKNOWN;
        printf("Unknown token detected: %c\n", c); 
    }

    return token;
}

int main() {
    const char *filename = "overflow.txt";
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file\n");
        return 1;
    }

    Token token;
    do {
        token = get_token(fp);
        printf("Token: %-20s Type: %s\n", token.lexeme, get_token_type_string(token.type));
    } while (token.type != TOKEN_EOF && token.type != TOKEN_ERROR);

    fclose(fp);
    return 0;
}
