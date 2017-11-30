
extern int yylex();
extern int yyparse();
extern int yylineno;

int main(){
	return yyparse();
}