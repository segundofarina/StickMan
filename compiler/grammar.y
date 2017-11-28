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
%token ADD
%token SUBSTRACT
%token <integer> INTEGER
%token DOUBLE
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

Start : Include Body
			| Body											
Include : HASHTAG INCLUDE LESS_THAN Name GREATER_THAN SEMICOLON
Body : Function Body
			| Function
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
			| Cicle COLON
			| Assignment COLON
			| Declaration COLON
			| Run COLON
			| Return COLON
			| ExpressionLevel1 COLON
Cicle : FOR OPEN_PARENTHESES Assignment SEMICOLON ConditionLevel1 SEMICOLON Assignment CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
Cicle : WHILE OPEN_PARENTHESES ConditionLevel1 CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET
Assignment : VARIABLE EQUAL ExpressionLevel1
Declaration : Type VARIABLE EQUAL ExpressionLevel1																	
			| Type VARIABLE		
ExpressionLevel1 : ExpressionLevel1 ADD ExpressionLevel2 
			| ExpressionLevel2
ExpressionLevel2 : ExpressionLevel2 SUBSTRACT ExpressionLevel3 
			| ExpressionLevel3
ExpressionLevel3 : ExpressionLevel3 MULTIPLY ExpressionLevel4 
			| ExpressionLevel4
ExpressionLevel4 : ExpressionLevel4 DIVIDE ExpressionLevel5 
			| ExpressionLevel5
ExpressionLevel5 : OPEN_PARENTHESES ExpressionLevel1 CLOSE_PARENTHESES 
			| ExpressionLevel6
ExpressionLevel6 : Value 
			| VARIABLE
Value : INTEGER																									
			| DOUBLE																								
			| STRING	
Return : RETURN ExpressionLevel1			
Type : INTEGER_TYPE
			| DOUBLE_TYPE
			| ACTION_TYPE
			| STRING_TYPE
Run : RUN VARIABLE ON Value SEMICOLON
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
ConditionLevel7 : OPEN_PARENTHESES ConditionLevel1 CLOSE_PARENTHESES
			| ConditionLevel8
ConditionLevel8 : Value 
			|VARIABLE


%%

void yyerror (char *s) {
	fprintf(stderr, "%s\n", s);
}