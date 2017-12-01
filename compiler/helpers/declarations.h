#ifndef __DECLARATIONS_H__
#define __DECLARATIONS_H__

#include "../syntaxTree/syntaxTree.h"

typedef enum {VAR_NAME_ERROR, VAR_TYPE_ERROR, VAR_NO_ERROR} varError;
typedef enum {FN_NAME_ERROR, FN_RETURN_ERROR, FN_PARAM_ERROR, FN_NO_ERROR} fnError;

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

void setCurrentFunction(char * name);

varError hasVariableWithType(Variable * var);

fnError hasFunctionWithType(char * name, typeOp returnType, VarList * parameters);

typeOp getVarType(char * name);

FunctionList * getAllFunctionDeclarations();

#endif
