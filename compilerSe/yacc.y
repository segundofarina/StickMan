%{
	#include <stdio.h>
	#include <stdlib.h>
	extern void yyerror(char *);	
	extern int yytext();
	extern int yylex();

%}

%union {char * string ; int integer;}
%token QUOTE
%token SEMICOLON
%token OPEN_CURLY_BRACKET
%token CLOSE_CURLY_BRACKET
%token HASHTAG
%token EQUAL
%token OPEN_PARENTHESES
%token CLOSE_PARENTHESES
%token LESS_THAN
%token GREATER_THAN
%token ADD
%token SUBSTRACT
%token <integer> INTEGER
%token DOUBLE
%token <string> VARIABLE
%token <string> STRING
%token INTEGER_TYPE
%token DOUBLE_TYPE
%token STRING_TYPE
%token RETURN
%start Start

%%

Start : Function																								{ ; }
Function : Type Name OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET		{ ; }
Name : VARIABLE																									{ ; }
Type : INTEGER_TYPE 																							{ ; }
		| DOUBLE_TYPE 																							{ ; }
		| STRING_TYPE																							{ ; }
Sentences: Sentences Sentence																					{ ; }
		| Sentence 																								{ ; }
Sentence : Expression SEMICOLON  																				{ ; }
		| Assignment SEMICOLON																					{ ; }
		| Declaration SEMICOLON																					{ ; }
		| Return SEMICOLON															 							{ ; }
Assignment : VARIABLE EQUAL Expression																			{ ; } 
Declaration : Type VARIABLE EQUAL Expression																	{ ; }
		| Type VARIABLE																							{ ; }
Expression : Expression Operator Expression																		{ ; }
		| Value																									{ ; }
		| VARIABLE																								{ ; }
Operator : ADD																									{ ; }
		| SUBSTRACT																								{ ; }
		| LESS_THAN																								{ ; }
		| GREATER_THAN																							{ ; }
Value : INTEGER																									{ ; }
		| DOUBLE																								{ ; }
		| STRING																								{ ; }
Return : RETURN Expression																						{ ; }




%%

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}