%{
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<alloca.h>
#include<stddef.h>
int yylex(void); // int yylex(void); is the lexical analyzer
int m=0, count; // int m=0; controls whether angles are in degrees (m == 1) or radians (m == 0).
int flag=0;
double sym[52]; // stores values for variables (sym can store values for up to 52 variables).
void yyerror(char *s) // is used for error handling, printing an error message when a syntax error is encountered.		
{      
           printf("%s\n",s);
           flag=1;
}
%}
%union {
double p;
char id;
}
%token OPEN_BRACKET CLOSE_BRACKET ASSIGN PRINT
%token<p>num
%token<id>VARIABLE
%token ADD SUB MUL DIV POW EXP SQRT MOD PI E 
%token COS SIN TAN ASIN ACOS ATAN COT SEC COSEC LOG LN 
%left SUB ADD // SUB ADD are left-associative and have the lowest precedence.
%left MUL DIV MOD // are also left-associative but have higher precedence.
%left POW SQRT // are left-associative with even higher precedence.
%left OPEN_BRACKET CLOSE_BRACKET
%type<p>exp
%type<p>constant
%%
ss : VARIABLE ASSIGN exp { // assigns the result of an expression to a variable
	sym[$1] = $3; 
	}
     |PRINT OPEN_BRACKET VARIABLE CLOSE_BRACKET {  // prints the value of a variable.
	if (flag==0) { 
    	printf("Result: %.10f\n", sym[$3]); 
    	}
    	}
     |exp { if (flag==0) { 
    	printf("Result: %.10f\n",$1); 
    	}
    	}
exp : exp ADD exp {
	$$=$1+$3;
	}
     |exp SUB exp {
     	$$=$1-$3;
     	}
     |exp MUL exp {
     	$$=$1*$3;
     	}
     |exp DIV exp {
     	if ($3!=0) {
     	$$=$1/$3;
     	}
     	else {
     	yyerror("Divide Error:Cannot divide by 0\n");
     	}
     	}
     |SUB exp {
     	$$=-$2; // This is unary '-' which allows -ve numbers
     	}
     |exp POW exp {
     	$$=pow($1,$3);
     	}
     |exp MOD exp {
     	if($3!=0){
     	$$=fmod($1,$3);
     	}
     	else {
     	yyerror("Modulo Error:Cannot divide by 0\n");
     	}
     	}
     |LOG OPEN_BRACKET exp CLOSE_BRACKET {
     	$$=log10($3); // $3: This refers to the third component in the rule (the expression inside the parentheses). For example, in the input LOG(100), $3 would represent 100
     	}
     |LN OPEN_BRACKET exp CLOSE_BRACKET {
     	$$=log($3);
     	}
     |SQRT OPEN_BRACKET exp CLOSE_BRACKET {
     	$$=sqrt($3);
     	}
     |SIN OPEN_BRACKET exp CLOSE_BRACKET {
     	$$= m==1 ? sin($3*M_PI/180) : sin($3); // if m=1 converts the angle from degrees to radians because the standard C sin() function expects the angle to be in radians.
     	}
     |COS OPEN_BRACKET exp CLOSE_BRACKET {
     	$$= m==1 ? cos($3*M_PI/180) : cos($3);
     	}
     |TAN OPEN_BRACKET exp CLOSE_BRACKET {
     	$$= m==1 ? tan($3*M_PI/180) : tan($3);
     	}
     |COSEC OPEN_BRACKET exp CLOSE_BRACKET {
     	$$= m==1 ? 1/sin($3*M_PI/180) : 1/sin($3);
     	}
     |SEC OPEN_BRACKET exp CLOSE_BRACKET {
     	$$= m==1 ? 1/cos($3*M_PI/180) : 1/cos($3);
     	}
     |COT OPEN_BRACKET exp CLOSE_BRACKET {
     	$$= m==1 ? 1/tan($3*M_PI/180) : 1/tan($3);
     	}
     |ASIN OPEN_BRACKET exp CLOSE_BRACKET { // The ASIN function, short for arc sine, is the inverse of the sine function
     	if($3<=1&&$3>=-1) {
     	$$= m==1 ? asin($3)*180/M_PI : asin($3);
     	}
     	else {
     	yyerror("ASIN ERROR: Out of Range\n");
     	}
     	}
     |ACOS OPEN_BRACKET exp CLOSE_BRACKET {
     	if($3<=1&&$3>=-1) {
     	$$= m==1 ? acos($3)*180/M_PI : acos($3);
     	}
     	else {
     	yyerror("ACOS ERROR: Out of Range\n");
     	}
     	}
     |ATAN OPEN_BRACKET exp CLOSE_BRACKET {
     	if($3<=1&&$3>=-1) {
     	$$= m==1 ? atan($3)*180/M_PI : atan($3);
     	}
     	}
     |OPEN_BRACKET exp CLOSE_BRACKET {
     	$$=$2;
     	}
     |num {
     	$$=$1;
     	}
     |constant	
    	;
constant : PI {
	 $$=M_PI;
	 }
	 | E {
	 $$=M_E;
	 };
%%
void main()
{
	printf("Scientific Calculator based on LEX YACC\n");
	do {
	flag=0,count=0;
	printf("Enter Expression: ");
	yyparse();
	if(flag==-1){
	flag=0;
	yyparse();
	}
	}while(1);
}

