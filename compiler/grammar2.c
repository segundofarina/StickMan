Start : Include Body
Start : Body												
Include : '#' 'include' '<' string '>' ';'
Body : Function Body
Body : Function
Function : Return Name '(' Parameters ')' '{' Sentence '}'
Return : Type
Name : VARIABLE
Parameters : Parameter ',' Parameters
Parameters : Parameter
Parameter : Type Name
Sentence : Cicle Sentence
Sentence : Assignment Sentence
Sentence : Declaration Sentence
Sentence : Cicle 
Sentence : Assignment
Sentence : Declaration
Sentence : Run
Sentence : Return
Cicle : 'for' '(' Assignment ',' Condition ',' Assignment ')' '{' Sentence '}'
Cicle : 'while' '(' Condition ')' '{' Sentence '}'

Type : 'int'
Type : 'double'
Type : 'action'
Type : 'string'
Return : 'return' name ';'
Return : 'return' Value ';'
Run : 'run' Variable 'on' Value ';'
Variable : Name
Condition : Condition Operator Condition
Condition : Variable Operator Variable
Condition : Var Operator Variable
Condition : Variable Operator Var
Condition : Var Operator Var
Operator : 'eq'
Operator : 'neq'
Operator : 'gt'
Operator : 'gteq'
Operator : 'ls'
Operator : 'lseq'



typedef struct var_int {
		char * name;
		int value;
	} var_int;

	typedef struct var_double {
		char * name;
		double value;
	} var_double;

	typedef struct var_string {
		char * name;
		char * value;
	} var_double;

	int var_int[50];
	double var_double[50];
	char var_string[50];