%{
	#include <stdio.h>
	#include <stdlib.h>
	extern void yyerror(char *);
	extern int yylex();
	extern int yylineno;
	extern char * yytext;
%}

%union {char * string ; int integer;}

%token SEMICOLON
%token OPEN_CURLY_BRACKET
%token CLOSE_CURLY_BRACKET
%token OPEN_PARENTHESES
%token CLOSE_PARENTHESES
%token ADD
%token SUBSTRACT
%token <integer> INTEGER
%token <string> VARIABLE
%token <integer> BOOLEAN
%token <string> STRING
%token INTEGER_TYPE
%token STRING_TYPE
%token BOOLEAN_TYPE
%token INCLUDE
%token COLON
%token FOR
%token WHILE
%token IF
%token ELSE
%token ELSEIF
%token EQUAL
%token NOT_EQUAL
%token GREATER_THAN
%token EQUAL_GREATER_THAN
%token EQUAL_LESS_THAN
%token LESS_THAN
%token MULTIPLY
%token DIVIDE
%token RETURN
%token START
%token AND
%token OR
%token FUNCTION
%token ARROW

%left ADD SUBSTRACT
%left MULTIPLY DIVIDE

%left EQUAL NOT_EQUAL
%left EQUAL_LESS_THAN EQUAL_GREATER_THAN LESS_THAN GREATER_THAN
%left OR AND


%start Start


%%

Start: Body
Body: Functions
Functions: Functions Function
		| Function
Function: StartFn
		| FUNCTION VARIABLE OPEN_PARENTHESES CLOSE_PARENTHESES RetrunType OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
		| FUNCTION VARIABLE OPEN_PARENTHESES Paramenters CLOSE_PARENTHESES RetrunType OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
StartFn: START OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
Paramenters: Paramenters COLON Parameter
			| Parameter
Parameter: Type VARIABLE
RetrunType: /* empty */
		| ARROW Type

Sentences: /* empty */
		| Sentences Sentece
Sentece: Assignment SEMICOLON
		| Declaration SEMICOLON
		| Return SEMICOLON
		| If
		| While
		| For
		| FunctionCall SEMICOLON
Assignment: VARIABLE EQUAL Expression
Declaration: Type VARIABLE EQUAL Expression
		| Type VARIABLE
Return: RETURN Expression
Type: INTEGER_TYPE
	| STRING_TYPE
	| BOOLEAN_TYPE
Expression: Value
	| VARIABLE
	| FunctionCall
 	| Expression ADD Expression
	| Expression SUBSTRACT Expression
	| Expression MULTIPLY Expression
	| Expression DIVIDE Expression
Value: INTEGER
If: IF OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
While: WHILE OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
For: FOR OPEN_PARENTHESES Assignment SEMICOLON Condition SEMICOLON Assignment CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
Condition: Expression LogicalOp Expression
 		| Condition OR Condition
		| Condition AND Condition
		| OPEN_PARENTHESES Condition CLOSE_PARENTHESES
		| BOOLEAN
		| FunctionCall
LogicalOp: EQUAL EQUAL
		| NOT_EQUAL
		| EQUAL_LESS_THAN
		| EQUAL_GREATER_THAN
		| LESS_THAN
		| GREATER_THAN
FunctionCall: VARIABLE OPEN_PARENTHESES CLOSE_PARENTHESES
		| VARIABLE OPEN_PARENTHESES FnParameters CLOSE_PARENTHESES
FnParameters: FnParameters COLON FnParameter
		| FnParameter
FnParameter: Expression
		| STRING


%%

void yyerror (char *s) {
	printf("%s in line %d, reading %s\n", s, yylineno, yytext);
}
