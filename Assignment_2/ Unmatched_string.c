
#include <ctype.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <limits.h>
#define MAX_LENGTH 100
int lexicalAnalyzer(char* input) {
    int left = 0, right = 0;
    int len = strlen(input);
    bool inString = false;
    bool inComment = false;

    while (right <= len) {
        if (!inString && !inComment) {
            // Check for the start of a string
            if (input[right] == '"') {
                inString = true;
                right++;
                continue;
            }
            // Check for the start of a block comment
            else if (input[right] == '/' && input[right + 1] == '*') {
                inComment = true;
                right += 2;
                continue;
            }
        }

        // Handling the inside of a string
        if (inString) {
            if (input[right] == '"' && input[right - 1] != '\\') { // Check for closing quote not escaped
                inString = false;
            } else if (input[right] == '\0') { // Check for end of input without closing quote
                printf("Error: Unmatched string starting at position %d\n", left);
                break;
            }
        }

        // Handling the inside of a comment
        if (inComment) {
            if (input[right] == '*' && input[right + 1] == '/') { // Check for end of comment
                inComment = false;
                right += 2;
                continue;
            } else if (input[right] == '\0') { // Check for end of input without closing comment
                printf("Error: Unmatched comment starting at position %d\n", left);
                break;
            }
        }

        right++;
    }
    return 0;
}


int main() {
    char lex_input[MAX_LENGTH] = "int main() {\n/* comment\n\tcout<<\"GFG!\";\n\treturn 0;\n";
    printf("Analyzing code: %s\n", lex_input);
    lexicalAnalyzer(lex_input);
    return 0;
}
