%{
#include <math.h>
FILE *fp;
%}
whitespace      [ \t\n]+
digit           [0-9]+
header 		"#include<"[a-z]+".h>"
inbuilt         (printf|scanf|clrscr|getch|exit)\(.*\)
comment         "//".*
main_function   "void main\(\)"
function        [a-zA-Z_]+\(.*\)\n
datatype        "int"|"char"|"float"
operator        "+"|"-"|"*"|"/"
terminator      ";"
bracket1        "{"|"("
bracket2        "}"|")"
keywords        "int"|"return"|"if"|"else"
relational      "<"|">"|"<="|">="|"=="|"!="|"%"
logical         "&&"|"||"
word 		[a-z]+[a-z0-9]*
%%
{whitespace}	 { /* Skip whitespace. */ }
{digit}          { printf("\n Numbers: %s", yytext); }
{header}         { printf("\n Header File: %s", yytext); }
{inbuilt}        { printf("\n Function: %s", yytext); }
{comment}        { printf("\n Comment: %s", yytext); }
{main_function}  { printf("\n Main Function: %s", yytext); }
{function}       { printf("\n User function: %s", yytext); }
{datatype}       { printf("\n Datatype: %s", yytext); }
{operator}       { printf("\n Operator: %s", yytext); }
{terminator}     { printf("\n Terminator: %s", yytext); }
{bracket1}       { printf("\n Opening curly bracket: %s", yytext); }
{bracket2}       { printf("\n Closing curly bracket: %s", yytext); }
{relational}     { printf("\n Relational operator: %s", yytext); }
{keywords}           { printf("\n Keywords: %s", yytext); }
{logical}        { printf("\n Logical Operator: %s", yytext); }
{word} 		 {printf("\n Variables:: %s", yytext);}
%%

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    yyin = fp;
    yylex();

    fclose(fp);
    return 0;
}
