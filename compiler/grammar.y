%{
	#include "grammar.h"
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
%token INTEGER_TYPE
%token DOUBLE_TYPE
%token STRING_TYPE

%start start

%%

Start : Function										{ printf("Starting..."); }
Function : Type Name '(' ')' '{' Sentence '}'			{ ; }
Name : VARIABLE											{ ; }
Type : INTEGER_TYPE 									{ ; }
Type : DOUBLE_TYPE										{ ; }
Type : STRING_TYPE										{ ; }
Sentence : Assignment ';' Sentence						{ ; }
Sentence : Declaration ';' Sentence						{ ; }
Sentence : Expression ';' Sentence						{ ; }
Sentence : Expression ';' 								{ ; }
Sentence : Assignment ';' 								{ ; }
Sentence : Declaration ';' 								{ ; }
Sentence : Return ';' 									{ ; }
Assignment : VARIABLE '=' Expression					{ update( $1 , $3 ) ; } 
Declaration : Type VARIABLE '=' Expression				{ add( $1 , $2 , $4 ) ; }
Expression : Expression Operator Expression				{ $$ = $1 + $3 ; }
Expression : Value										{ $$ = $1 ; }
Expression : VARIABLE									{ $$ = getValue($1) ; }
Operator : ADD											{ ; }
Operator : SUBSTRACT									{ ; }
Operator : OPEN_ANGLE_BRACKET							{ ; }
Operator : CLOSE_ANGLE_BRACKET							{ ; }
Value : INTEGER											{ ; }
Value : DOUBLE											{ ; }
Value : STRING											{ ; }
Return : 'return' Expression							{ printf("%d\n", $2 ); return 0; }








start:
	VARIABLE OPEN_PARENTHESES STRING CLOSE_PARENTHESES OPEN_CURLY_BRACKET STRING SEMICOLON CLOSE_CURLY_BRACKET



%%

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}
