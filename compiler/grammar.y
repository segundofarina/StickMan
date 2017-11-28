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

%token EQUAL

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


%token INCLUDE
%token RETURN
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
%token GREATER
%token EGUAL_GREATER
%token EQUAL_LESS
%token LESS


%token RETURN

%start Start


%%

<<<<<<< HEAD
Start : Include Body
Start : Body	
											
Include : HASHTAG INCLUDE OPEN_ANGLE_BRACKET Name CLOSE_ANGLE_BRACKET SEMICOLON

Body : Function Body
Body : Function

Function : ReturnType Name OPEN_PARENTHESES Parameters CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentence Return CLOSE_CURLY_BRACKET

ReturnType : Type

Name : VARIABLE

Parameters : Parameter COLON Parameters
Parameters : Parameter
Parameter : Type Name

Sentence : Cicle Sentence COLON
Sentence : Assignment Sentence
Sentence : Declaration Sentence
Sentence : Cicle 
Sentence : Assignment
Sentence : Declaration
Sentence : Run
Sentence : Return

Cicle : FOR OPEN_PARENTHESES Assignment SEMICOLON Condition SEMICOLON Assignment CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentence CLOSE_CURLY_BRACKET
Cicle : WHILE OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentence CLOSE_CURLY_BRACKET

Type : INTEGER_TYPE
Type : DOUBLE_TYPE
Type : ACTION_TYPE
Type : STRING_TYPE
Return : RETURN Name SEMICOLON
Return : RETURN Value SEMICOLON
Run : RUN Variable ON Value SEMICOLON
Variable : Name
Condition : Condition Operator Condition
Condition : Variable Operator Variable
Condition : Var Operator Variable
Condition : Variable Operator Var
Condition : Var Operator Var
Operator : EQUAL
Operator : NOT_EQUAL
Operator : GREATER
Operator : EGUAL_GREATER
Operator : LESS
Operator : EQUAL_LESS

