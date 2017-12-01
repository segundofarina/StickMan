#include <stdio.h>
#include"../lib.h"	
extern int yylex();
extern int yyparse();
extern int yylineno;


int main(){
	initLibrary(NULL);
	return yyparse();
}


// c compiled file pointer
