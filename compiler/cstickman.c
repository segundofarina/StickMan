#include <stdio.h>
#include"./helpers/lib.h"	
extern int yylex();
extern int yyparse();
extern int yylineno;


int main(){
	initLibrary(NULL);
	return yyparse();
}


// c compiled file pointer
