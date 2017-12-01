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

/* Search for variable */
Variable * searchVariable(char * name, Function * fn) {
	VarList * current = fn->variables;
	while(current != NULL) {
		if(current->variable != NULL && strcmp(current->variable->name, name) == 0) {
			return current->variable;
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

void setCurrentFunction(char * name) {
	currentFunction = searchFunction(name);
}

varError hasVariableWithType(Variable * var) {
	 VarList * current = currentFunction->variables;
	 while(current != NULL) {
		 int nameCmp = strcmp(current->variable->name, var->name);
		 if(nameCmp == 0 && current->variable->type == var->type) {
			 return VAR_NO_ERROR;
		 } else if(nameCmp == 0) {
			 return VAR_TYPE_ERROR;
		 }
		 current = current->next;
	 }
	 return VAR_NAME_ERROR;
}


/* Check for same list */
int checkParamList(VarList * paramList1, VarList * paramList2) {
	/*VarList * current1 = paramList1;
	VarList * current2 = paramList2;
	int found;
	while(current1 != NULL) {
		current2 = paramList2;
		found = 0;
		while(current2 != NULL && !found) {
			if(strcmp(current1->variable->name, current2->variable->name) == 0 && current1->variable->type == current2->variable->type) {
				found = 1;
			}
			current2 = current2->next;
		}
		if(!found) {
			return 0;
		}
		current1 = current1->next;
	}*/
	VarList * current = paramList1;
	int count1 = 0, count2 = 0;
	while(current != NULL) {
		count1++;
		current = current->next;
	}
	current = paramList2;
	while(current != NULL) {
		count2++;
		current = current->next;
	}
	if(count1 != count2) {
		return 0;
	}
	return 1;
}

fnError hasFunctionWithType(char * name, typeOp returnType, VarList * parameters) {
	FunctionList * current = functionDeclaredList;
	while (current != NULL) {
		int nameCmp = strcmp(current->function->name, name);
		if(nameCmp == 0 && current->function->returnType == returnType && checkParamList(current->function->parameters, parameters)) {
			return FN_NO_ERROR;
		} else if(nameCmp == 0 && current->function->returnType == returnType) {
			return FN_PARAM_ERROR;
		} else if(nameCmp == 0) {
			return FN_RETURN_ERROR;
		}
		current = current->next;
	}
	return FN_NO_ERROR;
}

typeOp getVarType(char * name) {
	Variable * var = searchVariable(name, currentFunction);
	if(var == NULL) {
		return ST_VOID_TYPE;
	}
	return var->type;
}

int amountOfFunctions() {
	FunctionList * current = functionDeclaredList;
	int count = 0;
	while(current != NULL) {
		count++;
		current = current->next;
	}
	return count;
}

FunctionList * getAllFunctionDeclarations() {
	return functionDeclaredList;
}
