// C program to illustrate the implementation of lexical 
// analyser 

#include <ctype.h> 
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <limits.h>
#define MAX_LENGTH 100
#define MAX_ID_LENGTH 31

// this function check for a delimiter(it is a piece of data 
// that seprated it from other) to peform some specif case 
// on it 
bool isDelimiter(char chr) {
    return strchr(" ;,()+-*/%=<>[]{}", chr) != NULL;
}

// this function check for a valid identifier eg:- +,-* etc 
bool isOperator(char chr) 
{ 
	return (chr == '+' || chr == '-' || chr == '*'
			|| chr == '/' || chr == '>' || chr == '<'
			|| chr == '='); 
} 

// this function check for an valid identifier 
bool isValidIdentifier(char* str) {
    int length = strlen(str);
    if (length > MAX_ID_LENGTH) {
        printf("Error: Identifier exceeds maximum length of %d characters\n", MAX_ID_LENGTH);
        return false;
    }
    if (!isalpha(str[0]) && str[0] != '_') {
        printf("Error: Invalid start of identifier\n");
        return false;
    }
    for (int i = 1; i < length; i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            printf("Error: Invalid character in identifier\n");
            return false;
        }
    }
    return true;
}

bool isInteger(char* str) {
    int length = strlen(str);

    long long value = atoll(str);
    if (value < INT_MIN || value > INT_MAX) {
        printf("Error: Integer constant out of range\n");
        return false;
    }
    for (int i = 0; i < length; i++) {
        if (!isdigit(str[i]) && !(i == 0 && (str[i] == '+' || str[i] == '-'))) { // In most programming languages and numerical representations, a number can optionally start with a + (plus) or - (minus) sign. These signs indicate whether the number is positive or negative, respectively. This convention allows for clear differentiation between positive and negative numbers.
            printf("Error: Invalid integer format\n");
            return false;
        }
    }
    return true;
}

// 32 Keywords are checked in this function and return the 
// result accordingly 
bool isKeyword(char* str) 
{ 
	const char* keywords[] 
		= { "auto",	 "break", "case",	 "char", 
			"const", "continue", "default", "do", 
			"double", "else",	 "enum",	 "extern", 
			"float", "for",	 "goto",	 "if", 
			"int",	 "long",	 "register", "return", 
			"short", "signed", "sizeof", "static", 
			"struct", "switch", "typedef", "union", 
			"unsigned", "void",	 "volatile", "while" }; 
	for (int i = 0; 
		i < sizeof(keywords) / sizeof(keywords[0]); i++) { 
		if (strcmp(str, keywords[i]) == 0) { 
			return true; 
		} 
	} 
	return false; 
} 


// trims a substring from a given string's start and end 
// position 
char* getSubstring(char* str, int start, int end) 
{ 
	int length = strlen(str); 
	int subLength = end - start + 1; 
	char* subStr 
		= (char*)malloc((subLength + 1) * sizeof(char)); 
	strncpy(subStr, str + start, subLength); 
	subStr[subLength] = '\0'; 
	return subStr; 
} 

bool isLegalCharacter(char chr) {
    return isalnum(chr) || isDelimiter(chr) || isOperator(chr) || isspace(chr);
}


// this function parse the input 
int lexicalAnalyzer(char* input) 
{ 
	int left = 0, right = 0; 
	int len = strlen(input); 

	while (right <= len && left <= right) { 

        bool is_right_delimiter = isDelimiter(input[right]);

        bool is_right_minus_one_delimiter = isDelimiter(input[right - 1]);


        if (!isLegalCharacter(input[right]) && input[right] != '\0') { // Check for illegal characters
            printf("Error: Illegal character '%c' found at position %d\n", input[right], right);
            right++;
            left = right;  // Skip over the illegal character
            continue;
        }


		if (!is_right_delimiter) 
			right++; 

		if (is_right_delimiter && left == right) { 
			if (isOperator(input[right])) 
				printf("Token: Operator, Value: %c\n", 
					input[right]); 

			right++; 
			left = right; 
		} 
		else if (is_right_delimiter && left != right 
				|| (right == len && left != right)) { 
			char* subStr 
				= getSubstring(input, left, right - 1); 

            bool is_valid_indentifier_substr = isValidIdentifier(subStr);
            

			if (isKeyword(subStr)) 
				printf("Token: Keyword, Value: %s\n", 
					subStr); 

			else if (isInteger(subStr)) 
				printf("Token: Integer, Value: %s\n", 
					subStr); 

			else if (is_valid_indentifier_substr 
					&& !is_right_minus_one_delimiter) 
				printf("Token: Identifier, Value: %s\n", 
					subStr); 

			else if (!is_valid_indentifier_substr
					&& !is_right_minus_one_delimiter) 
				printf("Token: Unidentified, Value: %s\n", 
					subStr); 
			left = right; 
		} 
	} 
	return 0; 
} 

// main function 
int main() 
{ 
	// Input 01 
	// char lex_input[MAX_LENGTH] = "int a = b + c + 2147483649"; 
    char lex_input[MAX_LENGTH] = "int x = 12$34"; 
	printf("For Expression \"%s\":\n", lex_input); 
	lexicalAnalyzer(lex_input); 
	printf(" \n"); 
	// Input 02 
	char lex_input01[MAX_LENGTH] 
		= "int x=ab+bc+30+switch+ 0y "; 
	printf("For Expression \"%s\":\n", lex_input01); 
	lexicalAnalyzer(lex_input01); 
	return (0); 
}
