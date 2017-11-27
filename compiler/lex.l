%{
  #include "y.tab.h"
%}

%option noyywrap

%%

";"							{ return SEMICOLON; }
"{"							{ return OPEN_CURLY_BRACKET; }
"}"							{ return CLOSE_CURLY_BRACKET; }
"#"							{ return HASHTAG; }
"<"							{ return OPEN_ANGLE_BRACKET; }
">"							{ return CLOSE_ANGLE_BRACKET; }
"("							{ return OPEN_PARENTHESES; }
")"							{ return CLOSE_PARENTHESES; }
"+"							{ return ADD; }
"-"							{ return SUBSTRACT; }

[0-9]+						{ return INTEGER; }
[0-9]+.[0-9]+				{ return DOUBLE; }
[a-zA-Z]([a-zA-Z0-9_])*		{ return VARIABLE; }
\"[^\"]*\"					{ return STRING; }

\/\*([^\*\/])*\*\/			;

[ \t]						;
\n							{ yylineno++; }


%%
