#include <stdio.h>
#include"./helpers/lib.h"	
extern int yylex();
extern int yyparse();
extern int yylineno;


int main(){
	initLibrary(NULL,0);
	return yyparse();
}


// c compiled file pointer
