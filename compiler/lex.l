%{
  #include "y.tab.h"
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  extern yy_size_t yyleng;
%}

%option noyywrap
%%


"\""						{ return QUOTE; }
";"							{ return SEMICOLON; }
","							{ return COLON;}
"{"							{ return OPEN_CURLY_BRACKET; }
"}"							{ return CLOSE_CURLY_BRACKET; }
"#"							{ return HASHTAG; }
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
"*"							{ return MULTIPLY;}
"/"							{ return DIVIDE;}
"int"						{ return INTEGER_TYPE; }
"double"					{ return DOUBLE_TYPE; }
"string"					{ return STRING_TYPE; }
"return"					{ return RETURN; }
"include"					{ return INCLUDE;}
"for"						{ return FOR;}
"while"						{ return WHILE;}
"if"						{ return IF;}
"else"						{ return ELSE;}
"elseif"					{ return ELSEIF;}
"on"						{ return ON;}
"run"						{ return RUN;}
[0-9]+.[0-9]+				{ return DOUBLE; }
[0-9]+						{ yylval.integer = atoi(yytext) ; return INTEGER; }
[a-zA-Z]([a-zA-Z0-9_])*		{ 	yylval.string = malloc(yyleng+1);
								strcpy(yylval.string,yytext);
								return VARIABLE; }
\"[^\"]*\"					{ 	yylval.string = malloc(yyleng+1);
								strcpy(yylval.string,yytext);
								return STRING; }
\/\*([^\*\/])*\*\/			;
[ \t]						;


\n							{ yylineno++; }

%%



