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

%token OPEN_PARENTHESES
%token CLOSE_PARENTHESES
%token ADD
%token SUBSTRACT
%token <integer> INTEGER
%token <double> DOUBLE
%token <string> VARIABLE
%token <string> STRING
%token INTEGER_TYPE
%token DOUBLE_TYPE
%token STRING_TYPE
%token ACTION_TYPE

%token INCLUDE
%token COLON
%token FOR
%token WHILE
%token IF
%token ELSE
%token ELSEIF
%token ON
%token RUN
%token EQUAL
%token NOT_EQUAL
%token GREATER_THAN
%token EQUAL_GREATER_THAN
%token EQUAL_LESS_THAN
%token LESS_THAN
%token MULTIPLY
%token DIVIDE


%token RETURN

%start Start

%%

Start : Include Body	{;}																												
			| Body	{;}											
Include : HASHTAG INCLUDE LESS_THAN VARIABLE GREATER_THAN SEMICOLON	{;}
Body : Function Body	{;}
			| Function	{;}
Function : Type VARIABLE OPEN_PARENTHESES Parameters CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET	{;}
			| Type VARIABLE OPEN_PARENTHESES CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET	{;}
Parameters : Parameter COLON Parameters	{;}
			| Parameter	{;}
Parameter : Type VARIABLE	{;}
Sentences : Sentences Sentence	{;}
			|Sentence	{;}
Sentence :	| Cicle SEMICOLON	{;}
			| Assignment SEMICOLON	{;}
			| Declaration SEMICOLON	{;}
			| Return SEMICOLON	{;}
			| Expression SEMICOLON													 							{ ; }
Assignment : VARIABLE EQUAL Expression																			{ ; } 
Declaration : Type VARIABLE EQUAL Expression																	{ ; }
		| Type VARIABLE																							{ ; }
Cicle : FOR OPEN_PARENTHESES Assignment SEMICOLON Condition SEMICOLON Assignment CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET	{;}
Cicle : WHILE OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET	{;}
Expression : %prec Expression AritmeticOp Expression 															{ ; }
			| Value																								{ ; }
			| VARIABLE																							{ ; }
AritmeticOp : ADD																									{ ; }
			| SUBSTRACT																							{ ; }
			| MULTIPLY																							{ ; }
			| DIVIDE																							{ ; }
Condition  : %prec Condition LogicOp Condition 																	{ ; }
			| Expression																						{ ; }
			| OPEN_PARENTHESES Condition CLOSE_PARENTHESES														{ ; }
LogicOp : EQUAL EQUAL 																							{ ; }
		| NOT_EQUAL 																							{ ; }
		| EQUAL_LESS_THAN																						{ ; }
		| EQUAL_GREATER_THAN																					{ ; }
		| LESS_THAN 																							{ ; }
		| GREATER_THAN 																							{ ; }

Value : INTEGER																									{ ; }
		| DOUBLE																								{ ; }
		| STRING																								{ ; }
Return : RETURN Expression																						{ ; }
Type : INTEGER_TYPE	{;}
			| DOUBLE_TYPE	{;}
			| ACTION_TYPE	{;}
			| STRING_TYPE	{;}



%%

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}