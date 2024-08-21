#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#define MAX_TOKEN_LENGTH 100
#define MAX_IDENTIFIER_LENGTH 64

typedef enum {
    TOKEN_KEYWORD,
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_DOT,
    TOKEN_COLON,
    TOKEN_ESCAPE_CHAR,
    TOKEN_LPAREN,      // '('
    TOKEN_RPAREN,      // ')'
    TOKEN_LBRACE,      // '{'
    TOKEN_RBRACE,      // '}'
    TOKEN_LBRACKET,    // '['
    TOKEN_RBRACKET,    // ']'
    TOKEN_SEMICOLON,   // ';'
    TOKEN_COMMA,       // ','
    TOKEN_AMPERSAND,   // '&'
    TOKEN_PIPE,        // '|'
    TOKEN_EXCLAMATION, // '!'
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
        case TOKEN_DOT: return "Dot";
        case TOKEN_COLON: return "Colon";
        case TOKEN_ESCAPE_CHAR: return "Escape Character";
        case TOKEN_LPAREN: return "Left Parenthesis";
        case TOKEN_RPAREN: return "Right Parenthesis";
        case TOKEN_LBRACE: return "Left Brace";
        case TOKEN_RBRACE: return "Right Brace";
        case TOKEN_LBRACKET: return "Left Bracket";
        case TOKEN_RBRACKET: return "Right Bracket";
        case TOKEN_SEMICOLON: return "Semicolon";
        case TOKEN_COMMA: return "Comma";
        case TOKEN_AMPERSAND: return "Ampersand";
        case TOKEN_PIPE: return "Pipe";
        case TOKEN_EXCLAMATION: return "Exclamation Mark";
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
        peek = fgetc(fp);
        if (isalpha(peek)) {
            ungetc(peek, fp);
            while (isalnum(c = fgetc(fp)) && i < MAX_TOKEN_LENGTH) {
                token.lexeme[i++] = c;
            }
            token.lexeme[i] = '\0';
            token.type = TOKEN_ERROR;
            strcpy(token.lexeme, "Invalid identifier starting with a number");
            return token;
        } else {
            ungetc(peek, fp);
            bool isNegative = (c == '-');
            if (isNegative) {
                token.lexeme[i++] = c;
                c = fgetc(fp);
                token.lexeme[i++] = c;
            }

            long num = c - '0';
            while (isdigit(c = fgetc(fp))) {
                token.lexeme[i++] = c;
                if (isNegative) {
                    if (num < INT_MIN / 10 || (num == INT_MIN / 10 && -(c - '0') < INT_MIN % 10)) {
                        token.type = TOKEN_ERROR;
                        strcpy(token.lexeme, "Integer underflow");
                        break;
                    }
                    num = num * 10 - (c - '0');
                } else {
                    if (num > INT_MAX / 10 || (num == INT_MAX / 10 && (c - '0') > INT_MAX % 10)) {
                        token.type = TOKEN_ERROR;
                        strcpy(token.lexeme, "Integer overflow");
                        break;
                    }
                    num = num * 10 + (c - '0');
                }
            }

            if (token.type != TOKEN_ERROR) {
                token.lexeme[i] = '\0';
                ungetc(c, fp);
                token.type = TOKEN_NUMBER;
            }
            return token;
        }
    } else if (isalpha(c) || c == '_') {
        token.lexeme[i++] = c;
        while (isalnum(c = fgetc(fp)) || (c == '_' && i < MAX_IDENTIFIER_LENGTH)) {
            token.lexeme[i++] = c;
        }
        token.lexeme[i] = '\0';
        ungetc(c, fp);
        if (i >= MAX_IDENTIFIER_LENGTH) {
            token.type = TOKEN_ERROR;
            strcpy(token.lexeme, "Identifier length exceeded");
        } else if (is_keyword(token.lexeme)) {
            token.type = TOKEN_KEYWORD;
        } else {
            token.type = TOKEN_IDENTIFIER;
        }
        return token;
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_OPERATOR;
        return token;
    } else if (c == '.') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_DOT;
        return token;
    } else if (c == ':') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_COLON;
        return token;
    } else if (c == '\\') {
        token.lexeme[0] = c;
        token.lexeme[1] = fgetc(fp); 
        token.lexeme[2] = '\0';
        token.type = TOKEN_ESCAPE_CHAR;
        return token;
    } else if (c == '(') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_LPAREN;
        return token;
    } else if (c == ')') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_RPAREN;
        return token;
    } else if (c == '{') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_LBRACE;
        return token;
    } else if (c == '}') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_RBRACE;
        return token;
    } else if (c == '[') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_LBRACKET;
        return token;
    } else if (c == ']') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_RBRACKET;
        return token;
    } else if (c == ';') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_SEMICOLON;
        return token;
    } else if (c == ',') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_COMMA;
        return token;
    } else if (c == '&') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_AMPERSAND;
        return token;
    } else if (c == '|') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_PIPE;
        return token;
    } else if (c == '!') {
        token.lexeme[0] = c;
        token.lexeme[1] = '\0';
        token.type = TOKEN_EXCLAMATION;
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
