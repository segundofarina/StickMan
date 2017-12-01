#include <stdio.h>
#include <stdlib.h>
#include "nodeFunctions.h"
#include "syntaxTree.h"
#include <string.h>
#include "../helpers/lib.h"
#include "../helpers/declarations.h"

void checkFunctionCallError(functionCallNode * functionCall, typeOp type);

void typeAllFunction(typeOp type) {
	switch(type) {
		case ST_INTEGER_TYPE:
		case ST_BOOLEAN_TYPE:
			printf("int ");
			break;
		case ST_STRING_TYPE:
			printf("char * ");
			break;
		case ST_VOID_TYPE:
			printf("void ");
			break;
	}
}

void printAllFunctionParams(VarList * params) {
	VarList * current = params;
	while(current != NULL) {
		typeAllFunction(current->variable->type);
		printf("%s ", current->variable->name);
		current = current->next;
	}
}

void printAllFunction() {
	FunctionList * allFunctions = getAllFunctionDeclarations();
	while(allFunctions != NULL) {
		Function * fn = allFunctions->function;
		typeAllFunction(fn->returnType);
		printf("%s( ", fn->name);
		printAllFunctionParams(fn->parameters);
		printf("); ");
		allFunctions = allFunctions->next;
	}
}


void printError(char * message){
	return;
}
void startNodeFn(void * node) {
	startNode * n = (startNode *) node;

	printf("#include <stdio.h>\n");

	printAllFunction();


	(n->headers->runCode)(n->headers);//no hace falta ejecutarlo no hace nada
	//print all functions declarations
	(n->functions->runCode)(n->functions);

}

void headersNodeFn(void * node) {//se puede borrar
	headersNode * n = (headersNode *) node;

	headerList * current = n->list;
	headerNode * header;

	while(current != NULL) {
		header = current->header;
		(header->runCode)(header);
		current = current->next;
	}
}

void headerNodeFn(void * node) {// se puede borrar
	headerNode * n = (headerNode *) node;
	//agregar archivo de libreria
}

void functionsNodeFn(void * node) {
	functionsNode * n = (functionsNode *) node;

	functionList * current = n->list;
	functionNode * function;
	startFnNode * startFn;

	while(current != NULL) {
		if(current->functionType == ST_START_FN) {
			startFn = (startFnNode *) current->function;
			(startFn->runCode)(startFn);
		} else {
			function = (functionNode *) current->function;
			(function->runCode)(function);
		}
		current = current->next;
	}
}

void startFnNodeFn(void * node) {
	startFnNode * n = (startFnNode *) node;
	printf("int main() { ");
	(n->sentences->runCode)(n->sentences);
	printf("return 0; } ");
}

void functionNodeFn(void * node) {
	functionNode * n = (functionNode *) node;
	setCurrentFunction(n->name);
	if(n->returnType != NULL) {
		(n->returnType->runCode)(n->returnType);
	} else {
		printf("void ");
	}
	printf("%s( ", n->name);

	if(n->parameters != NULL) {
		(n->parameters->runCode)(n->parameters);
	}
	printf("){ ");
	(n->sentences->runCode)(n->sentences);
	printf("} ");
}

void returnTypeNodeFn(void * node) {
	returnTypeNode *  n = (returnTypeNode *) node;
	(n->type->runCode)(n->type);
}

void typeNodeFn(void * node) {
	typeNode * n = (typeNode *) node;
	switch(n->type) {
		case ST_INTEGER_TYPE:
		case ST_BOOLEAN_TYPE:
			printf("int ");
			break;
		case ST_STRING_TYPE:
			printf("char * ");
			break;
		case ST_VOID_TYPE:
			break;
	}
}

void parametersNodeFn(void * node) {
	parametersNode * n = (parametersNode *) node;

	parameterList * current = n->list;
	parameterNode * parameter;

	while(current != NULL) {
		parameter = current->parameter;
		(parameter->runCode)(parameter);
		if(current->next != NULL) {
			printf(", ");
		}
		current = current->next;
	}
}

void parameterNodeFn(void * node) {
	parameterNode * n = (parameterNode *) node;
	(n->type->runCode)(n->type);
	printf("%s ", n->name);
}

void sentencesNodeFn(void * node) {
	sentencesNode * n = (sentencesNode *) node;

	sentenceList * current = n->list;
	sentenceNode * sentence;
	while(current != NULL) {
		sentence = current->sentence;
		(sentence->runCode)(sentence);
		current = current->next;
	}
}

void sentenceNodeFn(void * node) {
	sentenceNode * n = (sentenceNode *) node;
	functionCallNode * functionCall;

	switch(n->sentenceType) {
		case ST_ASSIGNMENT:
			(((assignmentNode *)(n->content))->runCode)(n->content);
			printf("; ");
			break;
		case ST_DECLARATION:
			(((declarationNode *)(n->content))->runCode)(n->content);
			printf("; ");
			break;
		case ST_RETURN:
			(((returnNode *)(n->content))->runCode)(n->content);
			printf("; ");
			break;
		case ST_IF:
			(((ifNode *)(n->content))->runCode)(n->content);
			break;
		case ST_FOR:
			(((forNode *)(n->content))->runCode)(n->content);
			break;
		case ST_WHILE:
			(((whileNode *)(n->content))->runCode)(n->content);
			break;
		case ST_FUNCTION_CALL:
			functionCall = (functionCallNode *)(n->content);
			checkFunctionCallError(functionCall, ST_VOID_TYPE);
			(functionCall->runCode)(functionCall);
			printf("; ");
			break;
		case ST_MAN_ACTION:
			(((manActionNode *)(n->content))->runCode)(n->content);
			printf("; ");
			break;
	}
}

void manActionNodeFn(void * node) {

	manActionNode * n = (manActionNode *) node;

	if(n->manActionType == ST_MAN_ACTION_UNARY) {
		//accion n->var1 al man
		//puede tener parametros
		if(strcmp(n->var1, "yield") == 0)
		{
			printf("executeYield(");
			(n->manParam1->runCode)(n->manParam1);
			printf(")");
		}
		else
		{
			if (existsActionNoDir(n->var1) >=0){
				printf("executeAction( \"%s\" )",n->var1);
			}else{
				printError("Fatal Error: %s is not a valid action");//
			}

		}


	} else {
		//accion n->var1 + n->var2 al man
		//puede tener parametros
		char name1 [MAX_LENGTH_NAME] ={0};
		char name2 [MAX_LENGTH_NAME] ={0};
		strcat(name1,n->var1);
		strcat(name1,n->var2);
		strcat(name2, n->var2);
		strcat(name2, n->var1);
		if (existsActionNoDir(name1) >=0 ){
			printf("executeAction( \"%s\" )",name1);
		}else if (existsActionNoDir(name2) >=0 ){
			printf("executeAction( \"%s\" )",name2);
		}else{
			printError("Fatal Error binaryaction does not exsit");
		}
	}
}

void manParamNodeFn(void * node) {
	// implementar
	manParamNode * n = (manParamNode *) node;
	printf("%s",n->param);

}

void fnFunctionCallFn(void * node) {
	functionCallNode * n = (functionCallNode *) node;
	printf("%s( ", n->name);
	if(n->fnParameters != NULL) {
		(n->fnParameters->runCode)(n->fnParameters);
	}
	printf(") ");
}

void fnParametersNodeFn(void * node) {
	fnParametersNode * n = (fnParametersNode *) node;

	fnParameterList * current = n->list;

	while(current != NULL) {
		(current->fnParameter->runCode)(current->fnParameter);
		if(current->next != NULL) {
			printf(", ");
		}
		current = current->next;
	}
}

void fnParameterNodeFn(void * node) {
	fnParameterNode * n = (fnParameterNode *) node;
	if(n->paramType == ST_PARAM_STRING) {
		printf("%s ", n->str);
	} else {
		(n->expression->runCode)(n->expression);
	}
}

void expressionNodeFn(void * node) {
	expressionNode * n = (expressionNode *) node;
	switch(n->expressionType) {
		case ST_EXP_INT:
			printf("%d ", n->value);
			break;
		case ST_EXP_VAR:
			printf("%s ", n->variable);
			break;
		case ST_EXP_MANATTR:
			(n->manAttribute->runCode)(n->manAttribute);
			break;
		case ST_EXP_FUNCTIONCALL:
			//ver que exista y el return type
			checkFunctionCallError(n->functionCall, ST_INTEGER_TYPE);
			(n->functionCall->runCode)(n->functionCall);
			break;
		case ST_EXP_ADD:
			(n->expression1->runCode)(n->expression1);
			printf("+ ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_SUBSTRACT:
			(n->expression1->runCode)(n->expression1);
			printf("- ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_MULTIPLY:
			(n->expression1->runCode)(n->expression1);
			printf("* ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_DIVIDE:
			(n->expression1->runCode)(n->expression1);
			printf("/ ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_MODULUS:
			(n->expression1->runCode)(n->expression1);
			printf("%s ", "%");
			(n->expression2->runCode)(n->expression2);
			break;
	}
}

void forNodeFn(void * node) {
	forNode * n = (forNode *) node;
	printf("for(" );
	(n->assignment1->runCode)(n->assignment1);
	printf("; ");
	(n->condition->runCode)(n->condition);
	printf("; ");
	(n->assignment2->runCode)(n->assignment2);
	printf("){ ");
	(n->sentences->runCode)(n->sentences);
	printf("} ");
}

void conditionNodeFn(void * node) {
	conditionNode * n = (conditionNode *) node;
	switch(n->conditionType) {
		case ST_CONDITION_EXP:
			(n->expression1->runCode)(n->expression1);
			(n->logicalOperator->runCode)(n->logicalOperator);
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_CONDITION_AND:
			(n->condition1->runCode)(n->condition1);
			printf("&& ");
			(n->condition2->runCode)(n->condition2);
			break;
		case ST_CONDITION_OR:
			(n->condition1->runCode)(n->condition1);
			printf("|| ");
			(n->condition2->runCode)(n->condition2);
			break;
		case ST_CONDITION_BOOLEAN:
			printf("%d ", n->boolean);
			break;
		case ST_CONDITION_FN:
			//verifico que exista y el ret type
			checkFunctionCallError(n->functionCall, ST_BOOLEAN_TYPE);
			(n->functionCall->runCode)(n->functionCall);
			break;
	}
}

void whileNodeFn(void * node) {
	whileNode * n = (whileNode *) node;
	printf("while( ");
	(n->condition->runCode)(n->condition);
	printf(") { ");
	(n->sentences->runCode)(n->sentences);
	printf("} ");
}

void returnNodeFn(void * node) {
	returnNode * n = (returnNode *) node;
	//es correcto el tipo de retorno
	printf("return ");
	if(n->returnType == ST_RETURN_EXPRESSION) {
		(n->expression->runCode)(n->expression);
	} else {
		printf("%d ", n->boolean);
	}
}

void declarationNodeFn(void * node) {
	declarationNode * n = (declarationNode *) node;

	/* Set variable as declared */
	if(!addVariable(createVariable(n->type->type, n->variable))) {
		printf("Fatal Error: variable %s is defined more than once in the function.\n", n->variable);
	}

	(n->type->runCode)(n->type);
	printf("%s ", n->variable);
	if(n->declarationType == ST_DECLARATION_ASIGN) {
		printf("= ");
		(n->expression->runCode)(n->expression);
	} else if(n->declarationType == ST_DECLARATION_ASIGN_BOOLEAN) {
		if(n->type->type != ST_BOOLEAN_TYPE) {
			printf("Fatal Error: cannot asign boolean to non boolean variable %s\n", n->variable);
		}
		printf("= %d ", n->boolean);
	} else if(n->declarationType == ST_DECLARATION_ASIGN_STRING) {
		if(n->type->type != ST_STRING_TYPE) {
			printf("Fatal Error: cannot asign string to non string variable %s\n", n->variable);
		}
		printf("= %s ", n->str);
	}
}

void ifNodeFn(void * node) {
	ifNode * n = (ifNode *) node;
	printf("if( ");
	(n->condition->runCode)(n->condition);
	printf("){ ");
	(n->sentences->runCode)(n->sentences);
	printf("} ");
	if(n->elseBlock != NULL) {
		(n->elseBlock->runCode)(n->elseBlock);
	}
}

void elseBlockNodeFn(void * node) {
	elseBlockNode * n = (elseBlockNode *) node;
	if(n->type == ST_ELSE_BLOCK_ELSEIF) {
		(n->elseif->runCode)(n->elseif);
	} else {
		printf("else{ ");
		(n->sentences->runCode)(n->sentences);
		printf("} ");
	}
}

void checkVarAssignError(char * name, typeOp type) {
	switch(hasVariableWithType(createVariable(type, name))) {
		case VAR_NAME_ERROR:
			printf("Fatal Error: variable %s is not declared in the function.\n", name);
			break;
		case VAR_TYPE_ERROR:
			printf("Fatal Error: variable %s cannot be assigned because of a type error.\n", name);
			break;
		case VAR_NO_ERROR:
			break;
	}

}

void assignmentNodeFn(void * node) {
	assignmentNode * n = (assignmentNode *) node;
	switch (n->assignmentType) {
		case ST_ASSIGNMENT_EXPRESSION:
			checkVarAssignError(n->variable, ST_INTEGER_TYPE);
			printf("%s ", n->variable);
			(n->assignmentOp->runCode)(n->assignmentOp);
			(n->expression->runCode)(n->expression);
			break;
		case ST_ASSIGNMENT_INCREMENT:
			checkVarAssignError(n->variable, ST_INTEGER_TYPE);
			printf("%s ", n->variable);
			(n->incOp->runCode)(n->incOp);
			break;
		case ST_ASSIGNMENT_MAN:

			(n->manAttribute->runCode)(n->manAttribute);
			printf(" = ");
			(n->expression->runCode)(n->expression);
			break;
		case ST_ASSIGNMENT_STRING:
			checkVarAssignError(n->variable, ST_STRING_TYPE);
			printf("%s=%s",n->variable, n->str);
			break;
		case ST_ASSIGNMENT_BOOLEAN:
			checkVarAssignError(n->variable, ST_BOOLEAN_TYPE);
			printf("%s=%d\n", n->variable, n->boolean);
			break;
	}
}

void manAttributeNodeFn(void * node) {
	manAttributeNode * n = (manAttributeNode *) node;
	printf("%s ", n->variable);
}

void assignmentOpNodeFn(void * node) {
	assignmentOpNode * n =(assignmentOpNode *) node;
	switch (n->operator) {
		case ST_EQUAL:
			printf("= ");
			break;
		case ST_ADD_EQUAL:
			printf("+= ");
			break;
		case ST_SUBSTRACT_EQUAL:
			printf("-= ");
			break;
		case ST_MULTIPLY_EQUAL:
			printf("*= ");
			break;
		case ST_DIVIDE_EQUAL:
			printf("/= ");
			break;
	}
}

void incOpNodeFn(void * node) {
	incOpNode * n = (incOpNode *) node;
	switch (n->operator) {
		case ST_INCREMENT_ADD:
			printf("++ ");
			break;
		case ST_INCREMENT_SUBSTRACT:
			printf("-- ");
			break;
	}
}

void logicalOpFn(void * node) {
	logicalOperatorNode * n = (logicalOperatorNode *) node;
	switch (n->type) {
		case ST_LOP_EQ:
			printf("== ");
			break;
		case ST_LOP_NE:
			printf("!= ");
			break;
		case ST_LOP_LE:
			printf("<= ");
			break;
		case ST_LOP_GE:
			printf(">= ");
			break;
		case ST_LOP_LT:
			printf("< ");
			break;
		case ST_LOP_GT:
			printf("> ");
			break;
	}



}

VarList * addToParamListFn(Variable * param, VarList * paramList) {
	VarList * list = (VarList *) malloc(sizeof(VarList));
	list->variable = param;
	list->next = paramList;
	return list;
}

VarList * getParametersFn(fnParametersNode * parameters) {
	VarList * paramList = NULL;

	if(parameters == NULL) {
		return NULL;
	}

	fnParameterList * current = parameters->list;
	while(current != NULL) {
		fnParameterNode * parameter = current->fnParameter;
		paramList = addToParamListFn(createParameter(getVarType(parameter->str), parameter->str), paramList);
		current = current->next;
	}

	return paramList;
}

void checkFunctionCallError(functionCallNode * functionCall, typeOp type) {

	switch(hasFunctionWithType(functionCall->name, type, getParametersFn(functionCall->fnParameters))) {
		case FN_NAME_ERROR:
			printf("Fatal error: function %s is not declared.\n", functionCall->name);
			break;
		case FN_RETURN_ERROR:
			printf("Fatal error: return type of function %s does not match it's declaration.\n", functionCall->name);
			break;
		case FN_PARAM_ERROR:
			printf("Fatal error: parameters of function %s don't match it's declaration.\n", functionCall->name);
			break;
		case FN_NO_ERROR:
			break;
	}

}
