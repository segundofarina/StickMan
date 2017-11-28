%{
	#include <stdio.h>
	#include <stdlib.h>	
	extern int yytext();
	extern int yylex();
	extern void yyerror(char *);

%}

%union {char * string ; int integer;}
%token QUOTE
%token INIT
%token PRINT
%token SEMICOLON
%token OPEN_CURLY_BRACKET
%token CLOSE_CURLY_BRACKET
%token HASHTAG
%token OPEN_PARENTHESES
%token CLOSE_PARENTHESES
%token OPEN_ANGLE_BRACKET
%token CLOSE_ANGLE_BRACKET
%token ADD
%token SUBSTRACT
%token <integer> INTEGER
%token DOUBLE
%token <string> VARIABLE
%token <string> STRING
%token INTEGER_TYPE
%token DOUBLE_TYPE
%token STRING_TYPE
%start Start


%%

Start : Function													{;}
Function : INIT Sentence CLOSE_CURLY_BRACKET						{ ; }
Sentence : PRINT OPEN_PARENTHESES STRING CLOSE_PARENTHESES SEMICOLON	{ printf("%s\n",$3);}

%%

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}