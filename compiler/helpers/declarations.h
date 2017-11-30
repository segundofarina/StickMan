#ifndef __DECLARATIONS_H__
#define __DECLARATIONS_H__

#include "../syntaxTree/syntaxTree.h"

typedef struct Variable {
	char * name;
	typeOp type;
} Variable;

typedef struct VarList {
	Variable * variable;
	struct VarList * next;
} VarList;

typedef struct Function {
	char * name;
	VarList * parameters;
	VarList * variables;
	typeOp returnType;
} Function;

typedef struct FunctionList {
	Function * function;
	struct FunctionList * next;
} FunctionList;


int createFunction(char * name, typeOp returnType, VarList * parameters);

Variable * createVariable(typeOp type, char * name);

Variable * createParameter(typeOp type, char * name);

VarList * addToParamList(Variable * param, VarList * paramList);

int addVariable(Variable * var);


#endif
