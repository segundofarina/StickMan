#include <stdlib.h>
#include <string.h>
#include "declarations.h"

#include <stdio.h>

FunctionList * functionDeclaredList = NULL;
Function * currentFunction;


/* Search for function with name */
Function * searchFunction(char * name) {
	FunctionList * current = functionDeclaredList;
	while(current != NULL) {
		if(strcmp(current->function->name, name) == 0) {
			return current->function;
		}
		current = current->next;
	}
	return NULL;
}

/* Check if function was declared */
int hasFunction(char * name) {
	if(searchFunction(name) == NULL) {
		return 0;
	}
	return 1;
}

/* Check if current function has variable declared */
int hasVariable(char * variable) {
	VarList * list = currentFunction->variables;
	while(list != NULL) {
		if(strcmp(list->variable->name, variable) == 0) {
			return 1;
		}
		list = list->next;
	}
	return 0;
}



/* Add function fn to global list functionList */
FunctionList * addToFunctionList(Function * fn, FunctionList * list) {
	FunctionList * node = (FunctionList *) malloc(sizeof(FunctionList));
	node->function = fn;
	node->next = list;
	return node;
}

/* Initialize variables list as paramlist */
VarList * initVariables(VarList * parameters) {
	if(parameters == NULL) {
		return NULL;
	}
	VarList * node = (VarList *) malloc(sizeof(VarList));
	node->variable = parameters->variable;
	node->next = initVariables(parameters->next);
	return node;
}

/* Create new function declaration */
int createFunction(char * name, typeOp returnType, VarList * parameters) {
	if(hasFunction(name)) {
		return 0;
	}

	Function * fn = (Function *) malloc(sizeof(Function));
	fn->name = malloc(strlen(name)+1);
	strcpy(fn->name, name);
	fn->returnType = returnType;
	fn->parameters = parameters;
	fn->variables = initVariables(parameters);

	functionDeclaredList = addToFunctionList(fn, functionDeclaredList);
	currentFunction = fn;
	return 1;
}

/* Create new variable declaration */
Variable * createVariable(typeOp type, char * name) {
	Variable * var = (Variable *) malloc(sizeof(Variable));
	var->type = type;
	var->name = malloc(strlen(name)+1);
	strcpy(var->name, name);
	return var;
}

/* Create new parameter declaration */
Variable * createParameter(typeOp type, char * name) {
	return createVariable(type, name);
}

/* Check for duplicate parameter names */
int checkParameter(char * name, VarList * paramList) {
	VarList * current = paramList;
	while(current != NULL) {
		if(strcmp(current->variable->name, name) == 0) {
			return 1;
		}
		current = current->next;
	}
	return 0;
}

/* Create list of parameters */
VarList * addToParamList(Variable * param, VarList * paramList) {
	if(checkParameter(param->name, paramList)) {
		return NULL;
	}
	VarList * list = (VarList *) malloc(sizeof(VarList));
	list->variable = param;
	list->next = paramList;
	return list;
}

/* Add variable declaration to current function */
int addVariable(Variable * var) {
	if(hasVariable(var->name)) {
		return 0;
	}
	VarList * list = (VarList *) malloc(sizeof(VarList));
	list->variable = var;
	list->next = currentFunction->variables;
	currentFunction->variables = list;
	return 1;
}

/*
int hasFunctionDeclaration() {

}

int hasVariableWithType() {

}*/

/*
int functionHasParameter() {

}
*/

// paramList = addToParamList(param, NULL)
// paramList = addToParamList(param, paramList)
// createFunction()


// hasFunction()
// hasVariable(Function fn, var)
// hasParameter(Function fn, param)
/*
int main() {
	VarList * paramList = addToParamList(createParameter(ST_INTEGER_TYPE, "hola"), NULL);
	paramList = addToParamList(createParameter(ST_INTEGER_TYPE, "como"), paramList);
	paramList = addToParamList(createParameter(ST_INTEGER_TYPE, "va"), paramList);

	createFunction("pregunta", ST_INTEGER_TYPE, paramList);

	addVariable(createVariable(ST_INTEGER_TYPE,"bien"));

	printf("%d\n", hasVariable("bien"));
	printf("%d\n", hasVariable("pregu"));

	createFunction("pregunta2", ST_INTEGER_TYPE, paramList);

	addVariable(createVariable(ST_INTEGER_TYPE,"bien2"));

	printf("%d\n", hasFunction("pregunta2"));
	printf("%d\n", hasFunction("pregunta0"));
	printf("%d\n", hasFunction("pregunta"));

	return 0;
}*/
