#include <stdio.h>
#include <stdlib.h>
#include "nodeFunctions.h"
#include "syntaxTree.h"
#include <string.h>
#include "../helpers/lib.h"
#include "../helpers/declarations.h"

FILE *fp;

void checkFunctionCallError(functionCallNode * functionCall, typeOp type);

void typeAllFunction(typeOp type) {
	switch(type) {
		case ST_INTEGER_TYPE:
		case ST_BOOLEAN_TYPE:
			fprintf(fp,"int ");
			break;
		case ST_STRING_TYPE:
			fprintf(fp,"char * ");
			break;
		case ST_VOID_TYPE:
			fprintf(fp,"void ");
			break;
	}
}

void printAllFunctionParams(VarList * params) {
	VarList * current = params;
	while(current != NULL) {
		typeAllFunction(current->variable->type);
		fprintf(fp,"%s ", current->variable->name);
		current = current->next;
	}
}

void printAllFunction() {
	FunctionList * allFunctions = getAllFunctionDeclarations();
	while(allFunctions != NULL) {
		Function * fn = allFunctions->function;
		typeAllFunction(fn->returnType);
		fprintf(fp,"%s( ", fn->name);
		printAllFunctionParams(fn->parameters);
		fprintf(fp,"); ");
		allFunctions = allFunctions->next;
	}
}



void printError(char * message){
	printf("%s",message);
	return;
}
void startNodeFn(void * node) {
	startNode * n = (startNode *) node;
	fp=fopen("./compiled/compiledCode.c", "w+");
	if (fp == NULL)
	{
		printf("Could not open file for output\n");
		return ;
	}

	fprintf(fp,"\n#include <stdio.h>\n");
	fprintf(fp,"#include <stdlib.h>\n");
	fprintf(fp,"#include <string.h>\n");
	fprintf(fp,"#include \"../compiler/helpers/lib.h\"\n");
	fprintf (fp,"extern int manPosition;\n");
	fprintf (fp,"extern direction manDirection;\n");
	fprintf (fp,"#define left LIB_LEFT\n");
	fprintf (fp,"#define right LIB_RIGHT\n");
	fprintf (fp,"#define position manPosition\n");
	fprintf (fp,"#define direction manDirection\n");
	fprintf (fp,"#define eosR SCREEN_SPACES\n");
	fprintf (fp,"#define eosL 0\n");
	fprintf(fp,"\n int main() { ");


	printAllFunction();


	(n->headers->runCode)(n->headers);//no hace falta ejecutarlo no hace nada
	//print all functions declarations
	(n->functions->runCode)(n->functions);
	fclose(fp);
}

void headersNodeFn(void * node) {//se puede borrar
	headersNode * n = (headersNode *) node;

	fprintf(fp,"char * compiler_libraries[50]; int i = 0; ");

	headerList * current = n->list;
	headerNode * header;

	while(current != NULL) {
		header = current->header;
		fprintf(fp,"compiler_libraries[i] = malloc(strlen( \"");
		(header->runCode)(header);

		current = current->next;
	}
}

void headerNodeFn(void * node) {// se puede borrar
	headerNode * n = (headerNode *) node;
	//agregar archivo de libreria
	fprintf(fp,"%s+1\")); strcpy(compiler_libraries[i++],\"%s\");",n->fileName, n->fileName);
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
	setCurrentFunction("start");
	fprintf(fp,"initLibrary(compiler_libraries,0);");
	(n->sentences->runCode)(n->sentences);
	fprintf(fp,"return 0; } ");
}

void functionNodeFn(void * node) {
	functionNode * n = (functionNode *) node;
	setCurrentFunction(n->name);
	if(n->returnType != NULL) {
		(n->returnType->runCode)(n->returnType);
	} else {
		fprintf(fp,"void ");
	}
	fprintf(fp,"%s( ", n->name);

	if(n->parameters != NULL) {
		(n->parameters->runCode)(n->parameters);
	}
	fprintf(fp,"){ ");
	(n->sentences->runCode)(n->sentences);
	fprintf(fp,"} ");
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
			fprintf(fp,"int ");
			break;
		case ST_STRING_TYPE:
			fprintf(fp,"char * ");
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
			fprintf(fp,", ");
		}
		current = current->next;
	}
}

void parameterNodeFn(void * node) {
	parameterNode * n = (parameterNode *) node;
	(n->type->runCode)(n->type);
	fprintf(fp,"%s ", n->name);
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
			fprintf(fp,"; ");
			break;
		case ST_DECLARATION:
			(((declarationNode *)(n->content))->runCode)(n->content);
			fprintf(fp,"; ");
			break;
		case ST_RETURN:
			(((returnNode *)(n->content))->runCode)(n->content);
			fprintf(fp,"; ");
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
			functionCall = (functionCallNode *)(n->content);printf("acaaa\n");
			checkFunctionCallError(functionCall, ST_VOID_TYPE);
			(functionCall->runCode)(functionCall);
			fprintf(fp,"; ");
			break;
		case ST_MAN_ACTION:
			(((manActionNode *)(n->content))->runCode)(n->content);
			fprintf(fp,"; ");
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
			fprintf(fp,"executeYield(");
			(n->manParam1->runCode)(n->manParam1);
			fprintf(fp,")");
		}
		else
		{
			if (existsActionNoDir(n->var1) >=0){
				fprintf(fp,"executeAction( \"%s\" )",n->var1);
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
			fprintf(fp,"executeAction( \"%s\" )",name1);
		}else if (existsActionNoDir(name2) >=0 ){
			fprintf(fp,"executeAction( \"%s\" )",name2);
		}else{
			printError("Fatal Error binary action does not exsit");
		}
	}
}

void manParamNodeFn(void * node) {
	// implementar
	manParamNode * n = (manParamNode *) node;
	fprintf(fp,"%s",n->param);

}

void fnFunctionCallFn(void * node) {
	functionCallNode * n = (functionCallNode *) node;
	fprintf(fp,"%s( ", n->name);
	if(n->fnParameters != NULL) {
		(n->fnParameters->runCode)(n->fnParameters);
	}
	fprintf(fp,") ");
}

void fnParametersNodeFn(void * node) {
	fnParametersNode * n = (fnParametersNode *) node;

	fnParameterList * current = n->list;

	while(current != NULL) {
		(current->fnParameter->runCode)(current->fnParameter);
		if(current->next != NULL) {
			fprintf(fp,", ");
		}
		current = current->next;
	}
}

void fnParameterNodeFn(void * node) {
	fnParameterNode * n = (fnParameterNode *) node;
	if(n->paramType == ST_PARAM_STRING) {
		fprintf(fp,"%s ", n->str);
	} else {
		(n->expression->runCode)(n->expression);
	}
}

void expressionNodeFn(void * node) {
	expressionNode * n = (expressionNode *) node;
	switch(n->expressionType) {
		case ST_EXP_INT:
			fprintf(fp,"%d ", n->value);
			break;
		case ST_EXP_VAR:
			fprintf(fp,"%s ", n->variable);
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
			fprintf(fp,"+ ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_SUBSTRACT:
			(n->expression1->runCode)(n->expression1);
			fprintf(fp,"- ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_MULTIPLY:
			(n->expression1->runCode)(n->expression1);
			fprintf(fp,"* ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_DIVIDE:
			(n->expression1->runCode)(n->expression1);
			fprintf(fp,"/ ");
			(n->expression2->runCode)(n->expression2);
			break;
		case ST_EXP_MODULUS:
			(n->expression1->runCode)(n->expression1);
			fprintf(fp,"%s ", "%");
			(n->expression2->runCode)(n->expression2);
			break;
	}
}

void forNodeFn(void * node) {
	forNode * n = (forNode *) node;
	fprintf(fp,"for(" );
	(n->assignment1->runCode)(n->assignment1);
	fprintf(fp,"; ");
	(n->condition->runCode)(n->condition);
	fprintf(fp,"; ");
	(n->assignment2->runCode)(n->assignment2);
	fprintf(fp,"){ ");
	(n->sentences->runCode)(n->sentences);
	fprintf(fp,"} ");
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
			fprintf(fp,"&& ");
			(n->condition2->runCode)(n->condition2);
			break;
		case ST_CONDITION_OR:
			(n->condition1->runCode)(n->condition1);
			fprintf(fp,"|| ");
			(n->condition2->runCode)(n->condition2);
			break;
		case ST_CONDITION_BOOLEAN:
			fprintf(fp,"%d ", n->boolean);
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
	fprintf(fp,"while( ");
	(n->condition->runCode)(n->condition);
	fprintf(fp,") { ");
	(n->sentences->runCode)(n->sentences);
	fprintf(fp,"} ");
}

void returnNodeFn(void * node) {
	returnNode * n = (returnNode *) node;
	//es correcto el tipo de retorno
	fprintf(fp,"return ");
	if(n->returnType == ST_RETURN_EXPRESSION) {
		(n->expression->runCode)(n->expression);
	} else {
		fprintf(fp,"%d ", n->boolean);
	}
}

void declarationNodeFn(void * node) {
	declarationNode * n = (declarationNode *) node;

	/* Set variable as declared */
	if(!addVariable(createVariable(n->type->type, n->variable))) {
		printf("Fatal Error: variable %s is defined more than once in the function.\n", n->variable);
	}

	(n->type->runCode)(n->type);
	fprintf(fp,"%s ", n->variable);
	if(n->declarationType == ST_DECLARATION_ASIGN) {
		fprintf(fp,"= ");
		(n->expression->runCode)(n->expression);
	} else if(n->declarationType == ST_DECLARATION_ASIGN_BOOLEAN) {
		if(n->type->type != ST_BOOLEAN_TYPE) {
			printf("Fatal Error: cannot asign boolean to non boolean variable %s\n", n->variable);
		}
		fprintf(fp,"= %d ", n->boolean);
	} else if(n->declarationType == ST_DECLARATION_ASIGN_STRING) {
		if(n->type->type != ST_STRING_TYPE) {
			printf("Fatal Error: cannot asign string to non string variable %s\n", n->variable);
		}
		fprintf(fp,"= %s ", n->str);
	}
}

void ifNodeFn(void * node) {
	ifNode * n = (ifNode *) node;
	fprintf(fp,"if( ");
	(n->condition->runCode)(n->condition);
	fprintf(fp,"){ ");
	(n->sentences->runCode)(n->sentences);
	fprintf(fp,"} ");
	if(n->elseBlock != NULL) {
		(n->elseBlock->runCode)(n->elseBlock);
	}
}

void elseBlockNodeFn(void * node) {
	elseBlockNode * n = (elseBlockNode *) node;
	if(n->type == ST_ELSE_BLOCK_ELSEIF) {
		(n->elseif->runCode)(n->elseif);
	} else {
		fprintf(fp,"else{ ");
		(n->sentences->runCode)(n->sentences);
		fprintf(fp,"} ");
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
			fprintf(fp,"%s ", n->variable);
			(n->assignmentOp->runCode)(n->assignmentOp);
			(n->expression->runCode)(n->expression);
			break;
		case ST_ASSIGNMENT_INCREMENT:
			checkVarAssignError(n->variable, ST_INTEGER_TYPE);
			fprintf(fp,"%s ", n->variable);
			(n->incOp->runCode)(n->incOp);
			break;
		case ST_ASSIGNMENT_MAN:

			(n->manAttribute->runCode)(n->manAttribute);
			fprintf(fp," = ");
			(n->expression->runCode)(n->expression);
			break;
		case ST_ASSIGNMENT_STRING:
			checkVarAssignError(n->variable, ST_STRING_TYPE);
			fprintf(fp,"%s=%s",n->variable, n->str);
			break;
		case ST_ASSIGNMENT_BOOLEAN:
			checkVarAssignError(n->variable, ST_BOOLEAN_TYPE);
			fprintf(fp,"%s=%d\n", n->variable, n->boolean);
			break;
	}
}

void manAttributeNodeFn(void * node) {
	manAttributeNode * n = (manAttributeNode *) node;
	fprintf(fp,"%s ", n->variable);
}

void assignmentOpNodeFn(void * node) {
	assignmentOpNode * n =(assignmentOpNode *) node;
	switch (n->operator) {
		case ST_EQUAL:
			fprintf(fp,"= ");
			break;
		case ST_ADD_EQUAL:
			fprintf(fp,"+= ");
			break;
		case ST_SUBSTRACT_EQUAL:
			fprintf(fp,"-= ");
			break;
		case ST_MULTIPLY_EQUAL:
			fprintf(fp,"*= ");
			break;
		case ST_DIVIDE_EQUAL:
			fprintf(fp,"/= ");
			break;
	}
}

void incOpNodeFn(void * node) {
	incOpNode * n = (incOpNode *) node;
	switch (n->operator) {
		case ST_INCREMENT_ADD:
			fprintf(fp,"++ ");
			break;
		case ST_INCREMENT_SUBSTRACT:
			fprintf(fp,"-- ");
			break;
	}
}

void logicalOpFn(void * node) {
	logicalOperatorNode * n = (logicalOperatorNode *) node;
	switch (n->type) {
		case ST_LOP_EQ:
			fprintf(fp,"== ");
			break;
		case ST_LOP_NE:
			fprintf(fp,"!= ");
			break;
		case ST_LOP_LE:
			fprintf(fp,"<= ");
			break;
		case ST_LOP_GE:
			fprintf(fp,">= ");
			break;
		case ST_LOP_LT:
			fprintf(fp,"< ");
			break;
		case ST_LOP_GT:
			fprintf(fp,"> ");
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
