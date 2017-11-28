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
%token GREATER_THAN
%token EGUAL_GREATER_THAN
%token EQUAL_LESS_THAN
%token LESS_THAN
%token MULTIPLY
%token DIVIDE


%token RETURN

%start Start


%%

Start : Include Body
Start : Body	
											
Include : HASHTAG INCLUDE OPEN_ANGLE_BRACKET Name CLOSE_ANGLE_BRACKET SEMICOLON

Body : Function Body
Body : Function

Function : ReturnType Name OPEN_PARENTHESES Parameters CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET

ReturnType : Type

Name : VARIABLE

Parameters : Parameter COLON Parameters
			| Parameter

Parameter : Type Name

Sentences : Sentence Sentences
			|Sentence

Sentence : Cicle Sentence
			| Assignment Sentence
			| Declaration Sentence
			| Cicle 
			| Assignment
			| Declaration
			| Run
			| Return

Cicle : FOR OPEN_PARENTHESES Assignment SEMICOLON Condition SEMICOLON Assignment CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
Cicle : WHILE OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET

Assignment : VARIABLE EQUAL Expression

Declaration : Type VARIABLE EQUAL Expression																	
		| Type VARIABLE		

ExpressionLevel1 : ExpressionLevel1 ADD ExpressionLevel2 
					| ExpressionLevel2
ExpressionLevel2 : ExpressionLevel2 SUBSTRACT ExpressionLevel3 
					| ExpressionLevel3
ExpressionLevel3 : ExpressionLevel3 MULTIPLY ExpressionLevel4 
					| ExpressionLevel4
ExpressionLevel4 : ExpressionLevel4 DIVIDE ExpressionLevel5 
					| ExpressionLevel5
ExpressionLevel5 : OPEN_PARENTHESES ExpressionLevel5 CLOSE_PARENTHESES 
					| ExpressionLevel6
ExpressionLevel6 : Value 
					| VARIABLE

Value : INTEGER																									
		| DOUBLE																								
		| STRING	

Return : RETURN Expression			

Type : INTEGER_TYPE
Type : DOUBLE_TYPE
Type : ACTION_TYPE
Type : STRING_TYPE

Run : RUN Variable ON Value SEMICOLON


ConditionLevel1 : ConditionLevel1 EQUAL ConditionLevel2 
				| ConditionLevel2
ConditionLevel2 : ConditionLevel2 NOT_EQUAL ConditionLevel3 
				| ConditionLevel3
ConditionLevel3 : ConditionLevel3 GREATER_THAN ConditionLevel4 
				| ConditionLevel4
ConditionLevel4 : ConditionLevel4 EQUAL_GREATER_THAN ConditionLevel5 
				| ConditionLevel5
ConditionLevel5 : ConditionLevel5 LESS_THAN ConditionLevel6 
				| ConditionLevel6
ConditionLevel6 : ConditionLevel6 EQUAL_LESS_THAN ConditionLevel7 
				| ConditionLevel7
ConditionLevel7 : Value 
				|VARIABLE













Expression : Expression Operator Expression																		
		| Value																									
		| VARIABLE	



Operator : ADD																									
		| SUBSTRACT																								
		| MULTIPLY
		| DIVIDE


Condition : Condition ConditionOperator Condition
| Value
| VARIABLE

ConditionOperator : EQUAL
| NOT_EQUAL
| GREATER_THAN
| EGUAL_GREATER_THAN
| LESS_THAN
| EQUAL_LESS_THAN

