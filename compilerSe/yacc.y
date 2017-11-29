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
%token MAN
%token INTEGER_TYPE
%token STRING_TYPE
%token BOOLEAN_TYPE
%token MOVEMENTS_TYPE
%token INCLUDE
%token FILE_NAME
%token COLON
%token FOR
%token WHILE
%token IF
%token ELSE
%token EQUAL
%token NOT_EQUAL
%token GREATER_THAN
%token EQUAL_GREATER_THAN
%token EQUAL_LESS_THAN
%token LESS_THAN
%token MULTIPLY
%token DIVIDE
%token MODULUS
%token RETURN
%token START
%token AND
%token OR
%token FUNCTION
%token ARROW
%token DOT

%left ADD SUBSTRACT
%left MULTIPLY DIVIDE MODULUS

%left EQUAL NOT_EQUAL
%left EQUAL_LESS_THAN EQUAL_GREATER_THAN LESS_THAN GREATER_THAN
%left OR AND


%start Start


%%

Start: Headers Functions
Headers: /* empty */
 		| Headers Header
Header: INCLUDE FILE_NAME
Functions: Functions Function
		| Function
Function: StartFn
		| FUNCTION VARIABLE OPEN_PARENTHESES CLOSE_PARENTHESES ReturnType OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
		| FUNCTION VARIABLE OPEN_PARENTHESES Paramenters CLOSE_PARENTHESES ReturnType OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
StartFn: START OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
Paramenters: Paramenters COLON Parameter
		| Parameter
Parameter: Type VARIABLE
ReturnType: /* empty */
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
		| ManAction SEMICOLON
Assignment: VARIABLE AssignmentOp Expression
		| VARIABLE IncOp
		| ManAttribute EQUAL Expression
AssignmentOp: EQUAL
		| ADD EQUAL
		| SUBSTRACT EQUAL
		| MULTIPLY EQUAL
		| DIVIDE EQUAL
IncOp: ADD ADD
		| SUBSTRACT SUBSTRACT
Declaration: Type VARIABLE EQUAL Expression
		| Type VARIABLE
Return: RETURN Expression
		| RETURN BOOLEAN
Type: INTEGER_TYPE
	| STRING_TYPE
	| BOOLEAN_TYPE
Expression: INTEGER
	| VARIABLE
	| ManAttribute
	| FunctionCall
 	| Expression ADD Expression
	| Expression SUBSTRACT Expression
	| Expression MULTIPLY Expression
	| Expression DIVIDE Expression
	| Expression MODULUS Expression
If: IF OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET ElseBlock
ElseBlock: /* empty */
		| ELSE If
		| ELSE OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
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

ManAttribute: MAN DOT VARIABLE
ManAction: MAN ARROW VARIABLE ManParams ADD MAN ARROW VARIABLE ManParams
		| MAN ARROW VARIABLE ManParams
ManParams: /* empty */
		| STRING
		| VARIABLE

%%

void yyerror (char *s) {
	printf("%s in line %d, reading %s\n", s, yylineno, yytext);
}
