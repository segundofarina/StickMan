%{
	#include <stdio.h>
	void yyerror(char *);

%}

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
%token INTEGER
%token DOUBLE
%token VARIABLE
%token STRING

%start start

%%

start:
	VARIABLE OPEN_PARENTHESES STRING CLOSE_PARENTHESES OPEN_CURLY_BRACKET STRING SEMICOLON CLOSE_CURLY_BRACKET



%%

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}
