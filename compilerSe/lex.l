%{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include "syntaxTree/syntaxTree.h"
  #include "y.tab.h"
  extern yy_size_t yyleng;
%}

%option noyywrap
%%

"start"						{ return START; }


";"							{ return SEMICOLON; }
","							{ return COLON;}
"{"							{ return OPEN_CURLY_BRACKET; }
"}"							{ return CLOSE_CURLY_BRACKET; }
"<"							{ return LESS_THAN; }
">"							{ return GREATER_THAN; }
"("							{ return OPEN_PARENTHESES; }
")"							{ return CLOSE_PARENTHESES; }
"+"							{ return ADD; }
"-"							{ return SUBSTRACT; }
"="							{ return EQUAL; }
"!="						{ return NOT_EQUAL;}
">="						{ return EQUAL_GREATER_THAN;}
"<="						{ return EQUAL_LESS_THAN;}

"||"						{ return OR; }
"&&"						{ return AND; }

"*"							{ return MULTIPLY;}
"/"							{ return DIVIDE;}
"%"							{ return MODULUS; }
"->"						{ return ARROW; }
"."							{ return DOT; }
"man"						{ return MAN; }
"int"						{ return INTEGER_TYPE; }
"Movements"					{ return MOVEMENTS_TYPE; }
"string"					{ return STRING_TYPE; }
"boolean"					{ return BOOLEAN_TYPE; }
"return"					{ return RETURN; }
"include"					{ return INCLUDE;}
"for"						{ return FOR;}
"while"						{ return WHILE;}
"if"						{ return IF;}
"else"						{ return ELSE;}
"true"|"false"				{ return BOOLEAN; }
"func"						{ return FUNCTION; }
[0-9]+						{ yylval.integer = atoi(yytext) ; return INTEGER; }
[a-zA-Z]([a-zA-Z0-9_])*		{ 	yylval.string = malloc(yyleng+1);
								strcpy(yylval.string,yytext);
								return VARIABLE; }
\"[^\"]*\"					{ 	yylval.string = malloc(yyleng+1);
								strcpy(yylval.string,yytext);
								return STRING; }
[a-zA-Z]([a-zA-Z0-9_])*."stickLib"		{ return FILE_NAME; }
\/\*([^\*\/])*\*\/			;
[ \t]						;


\n							{ yylineno++; }

%%
