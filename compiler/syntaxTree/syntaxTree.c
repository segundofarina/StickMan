#include <stdlib.h>
#include <string.h>
#include "syntaxTree.h"
#include "../helpers/declarations.h"

#include <stdio.h>

startNode * createStartNode(headersNode * headers, functionsNode * functions) {
	startNode * node = malloc(sizeof(startNode));
	node->headers = headers;
	node->functions = functions;
	node->runCode = startNodeFn;
	return node;
}

headersNode * createHeadersNode() {
	headersNode * node = malloc(sizeof(headersNode));
	node->list = NULL;
	node->runCode = headersNodeFn;
	return node;
}

headerList * addToHeaderList(headerList * current, headerNode * header) {
	if(current == NULL) {
		headerList * list = malloc(sizeof(headerList));
		list->header = header;
		list->next = NULL;
		return list;
	}
	current->next = addToHeaderList(current->next, header);
	return current;
}

headersNode * addToHeadersNode(headerNode * header, headersNode * pNode) {
	pNode->list = addToHeaderList(pNode->list, header);
	return pNode;
}

headerNode * createHeaderNode(char * fileName) {
	headerNode * node = malloc(sizeof(headerNode));
	if(fileName != NULL) {
		node->fileName = malloc(strlen(fileName)+1);
		strcpy(node->fileName, fileName);
	}
	node->runCode = headerNodeFn;
	return node;
}

functionsNode * createFunctionsNode(void * fn, typeFunction typeFn) {
	functionsNode * node = malloc(sizeof(functionsNode));
	functionList * list = malloc(sizeof(functionList));
	list->function = fn;
	list->functionType = typeFn;
	list->next = NULL;
	node->list = list;
	node->runCode = functionsNodeFn;
	return node;
}

functionsNode * addToFunctionsNode(void * fn, functionsNode * pNode, typeFunction typeFn) {
	functionList * list = malloc(sizeof(functionList));
	list->function = fn;
	list->functionType = typeFn;
	list->next = NULL;
	functionList * current = pNode->list;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = list;
	return pNode;
}

startFnNode * createStartFnNode(sentencesNode * sentences) {
	startFnNode * node = malloc(sizeof(startFnNode));
	node->sentences = sentences;
	node->functionType = ST_START_FN;
	if(!createFunction("start", ST_VOID_TYPE, NULL)) {
		printf("Fatal Error: function %s() has more than one declaration.\n", "start");
	}
	node->runCode = startFnNodeFn;
	return node;
}

VarList * getParameters(parametersNode * parameters) {
	VarList * paramList = NULL;

	if(parameters == NULL) {
		return NULL;
	}

	parameterList * current = parameters->list;
	while(current != NULL) {
		parameterNode * parameter = current->parameter;
		paramList = addToParamList(createParameter(parameter->type->type, parameter->name), paramList);
		if(paramList == NULL) {
			printf("Fatal Error: parameter %s has more than one declaration in the same function.\n", parameter->name);
			return paramList;
		}
		current = current->next;
	}

	return paramList;
}

functionNode * createFunctionNode(parametersNode * parameters, returnTypeNode * returnType, sentencesNode * sentences, char * name) {
	functionNode * node = malloc(sizeof(functionNode));
	node->parameters = parameters;
	node->returnType = returnType;
	node->sentences = sentences;
	node->functionType = ST_FUNCTION;

	if(name != NULL) {
		node->name = malloc(strlen(name)+1);
		strcpy(node->name, name);
	}

	node->runCode = functionNodeFn;

	/* Add to functions list */
	typeOp retType = ST_VOID_TYPE;
	if(returnType != NULL) {
		retType = returnType->type->type;
	}
	if(!createFunction(name, retType, getParameters(parameters))) {
		printf("Fatal Error: function %s() has more than one declaration.\n", name);
	}

	return node;
}

returnTypeNode * createReturnTypeNode(typeNode * type) {
	returnTypeNode * node = malloc(sizeof(returnTypeNode));
	node->type = type;
	node->runCode = returnTypeNodeFn;
	return node;
}

typeNode * createTypeNode(typeOp type) {
	typeNode * node = malloc(sizeof(typeNode));
	node->type = type;
	node->runCode = typeNodeFn;
	return node;
}

parametersNode * createParametersNode(parameterNode * parameter) {
	parametersNode * node = malloc(sizeof(parametersNode));
	parameterList * list = malloc(sizeof(parameterList));
	list->parameter = parameter;
	list->next = NULL;
	node->list = list;
	node->runCode = parametersNodeFn;
	return node;
}

parametersNode * addToParametersNode(parameterNode * parameter, parametersNode * pNode) {
	parameterList * list = malloc(sizeof(parameterList));
	list->parameter = parameter;
	list->next = NULL;

	parameterList * current = pNode->list;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = list;
	return pNode;
}

parameterNode * createParameterNode(typeNode * type, char * name) {
	parameterNode * node = malloc(sizeof(parameterNode));
	if(name != NULL) {
		node->name = malloc(strlen(name)+1);
		strcpy(node->name, name);
	}
	node->type = type;
	node->runCode = parameterNodeFn;
	return node;
}

sentencesNode * createSentencesNode() {
	sentencesNode * node = malloc(sizeof(sentencesNode));
	node->list = NULL;
	node->runCode = sentencesNodeFn;
	return node;
}

sentenceList * addToSentenceList(sentenceList * current, sentenceNode * sentence) {
	if(current == NULL) {
		sentenceList * list = malloc(sizeof(sentenceList));
		list->sentence = sentence;
		list->next = NULL;
		return list;
	}
	current->next = addToSentenceList(current->next, sentence);
	return current;
}

sentencesNode * addToSentences(sentenceNode * sentence, sentencesNode * pNode) {
	pNode->list = addToSentenceList(pNode->list, sentence);
	return pNode;
}

sentenceNode * createSentenceNode(void * sentence, typeSentence type) {
	sentenceNode * node = malloc(sizeof(sentenceNode));
	node->content = sentence;
	node->sentenceType = type;
	node->runCode = sentenceNodeFn;
	return node;
}

manActionNode * createManActionNode(typeManAction type, char * var1, manParamNode * manParam1, char * var2, manParamNode * manParam2){
	manActionNode * node = malloc(sizeof(manActionNode));
	node->manActionType = type;
	node->manParam1 = manParam1;
	node->manParam2 = manParam2;
	if(var1 != NULL) {
		node->var1 = malloc(strlen(var1)+1);
		strcpy(node->var1, var1);
	}
	if(var2 != NULL) {
		node->var2 = malloc(strlen(var2)+1);
		strcpy(node->var2, var2);
	}
	node->runCode = manActionNodeFn;
	return node;
}

manParamNode * createManParamNode(char * string) {
	//si es un string esta con "", sino es una vaiable
	manParamNode * node = malloc(sizeof(manParamNode));
	if(string != NULL) {
		node->param = malloc(strlen(string)+1);
		strcpy(node->param, string);
	}
	node->runCode = manParamNodeFn;
	return node;
}

functionCallNode * createFunctionCallNode(char * name, fnParametersNode * fnParameters){
	functionCallNode * node = malloc(sizeof(functionCallNode));
	if(name != NULL) {
		node->name = malloc(strlen(name)+1);
		strcpy(node->name, name);
	}
	node->sentenceType = ST_FUNCTION_CALL;
	node->fnParameters = fnParameters;
	node->runCode = fnFunctionCallFn;
	return node;
}

fnParametersNode * createFnParametersNode(fnParameterNode * fnParameter){
	fnParametersNode * node = malloc(sizeof(fnParametersNode));
	fnParameterList * list = malloc(sizeof(fnParameterList));
	list->fnParameter = fnParameter;
	list->next = NULL;
	node->list = list;
	node->runCode = fnParametersNodeFn;
	return node;
}

fnParametersNode * addToFnParametersNode(fnParameterNode * fnParameter, fnParametersNode * pNode){
	fnParameterList * list = malloc(sizeof(fnParameterList));
	list->fnParameter = fnParameter;
	list->next = NULL;

	fnParameterList * current = pNode->list;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = list;

	return pNode;
}

fnParameterNode * createFnParameterNode(typeParameter paramType, expressionNode * expression, char * str){
	fnParameterNode * node = malloc(sizeof(fnParameterNode));
	node->paramType = paramType;
	if(str != NULL) {
		node->str = malloc(strlen(str)+1);
		strcpy(node->str, str);
	}
	node->expression = expression;
	node->runCode = fnParameterNodeFn;
	return node;
}

expressionNode * createExpressionNode(typeExpression expType, int value, char * variable, manAttributeNode * manAttribute, functionCallNode * functionCall, expressionNode * expression1, expressionNode * expression2){
	expressionNode * node = malloc(sizeof(expressionNode));
	node->expressionType = expType;
	node->value = value;
	if(variable != NULL) {
		node->variable = malloc(strlen(variable)+1);
		strcpy(node->variable, variable);
	}
	node->manAttribute = manAttribute;
	node->functionCall = functionCall;
	node->expression1 = expression1;
	node->expression2 = expression2;
	node->runCode = expressionNodeFn;
	return node;
}

forNode * createForNode(assignmentNode * assignment1, assignmentNode * assignment2, conditionNode * condition, sentencesNode * sentences){
	forNode * node = malloc(sizeof(forNode));
	node->assignment1 = assignment1;
	node->assignment2 = assignment2;
	node->condition = condition;
	node->sentences = sentences;
	node->sentenceType = ST_FOR;
	node->runCode = forNodeFn;
	return node;
}

conditionNode * createConditionNode(typeCondition conditionType, logicalOperatorNode * logicalOp, int boolean, conditionNode * condition1, conditionNode * condition2, expressionNode * expression1, expressionNode * expression2, functionCallNode * functionCall){
	conditionNode * node = malloc(sizeof(conditionNode));
	node->conditionType = conditionType;
	node->logicalOperator = logicalOp;
	node->boolean = boolean;
	node->condition1 = condition1;
	node->condition2 = condition2;
	node->expression1 = expression1;
	node->expression2 = expression2;
	node->functionCall = functionCall;
	node->runCode = conditionNodeFn;
	return node;
}

logicalOperatorNode * createLogicalOpNode(typeLogicOp type) {
	logicalOperatorNode * node = malloc(sizeof(logicalOperatorNode));
	node->type = type;
	node->runCode = logicalOpFn;
	return node;
}

whileNode * createWhileNode(conditionNode * condition, sentencesNode * sentences){
	whileNode * node = malloc(sizeof(whileNode));
	node->condition = condition;
	node->sentences = sentences;
	node->sentenceType = ST_WHILE;
	node->runCode = whileNodeFn;
	return node;
}

returnNode * createReturnNode(typeReturn retType, int boolean, expressionNode * expression){
	returnNode * node = malloc(sizeof(returnNode));
	node->returnType = retType;
	node->boolean = boolean;
	node->sentenceType = ST_RETURN;
	node->expression = expression;
	node->runCode = returnNodeFn;
	return node;
}

declarationNode * createDeclarationNode(typeDeclaration declarationType, typeNode * type, expressionNode * expression, char * variable, char * str, int boolean){
	declarationNode * node = malloc(sizeof(declarationNode));
	node->declarationType = declarationType;
	node->type = type;
	node->expression = expression;
	node->boolean = boolean;
	node->sentenceType = ST_DECLARATION;
	if(variable != NULL) {
		node->variable = malloc(strlen(variable)+1);
		strcpy(node->variable, variable);
	}
	if(str != NULL) {
		node->str = malloc(strlen(str)+1);
		strcpy(node->str, str);
	}
	node->runCode = declarationNodeFn;
	return node;
}

ifNode * createIfNode( conditionNode * condition, sentencesNode * sentences, elseBlockNode * elseBlock){
	ifNode * node = malloc(sizeof(ifNode));
	node->condition = condition;
	node->sentences = sentences;
	node->elseBlock = elseBlock;
	node->sentenceType = ST_IF;
	node->runCode = ifNodeFn;
	return node;
}

elseBlockNode * createElseBlockNode(typeElseBlock typeElse, ifNode * elseif, sentencesNode * sentences) {
	elseBlockNode * node = malloc(sizeof(elseBlockNode));
	node->type = typeElse;
	node->elseif = elseif;
	node->sentences = sentences;
	node->runCode = elseBlockNodeFn;
	return node;
}

assignmentNode * createAssignmentNode(typeAssigment assigmentType, assignmentOpNode * assignmentOp, expressionNode * expression, incOpNode * incOp, manAttributeNode * manAttribute, char * variable, char * str, int boolean) {
	assignmentNode * node = malloc(sizeof(assignmentNode));
	node->assignmentType = assigmentType;
	node->assignmentOp = assignmentOp;
	node->expression = expression;
	node->incOp = incOp;
	node->manAttribute = manAttribute;
	node->sentenceType = ST_ASSIGNMENT;
	node->boolean = boolean;
	if(variable != NULL) {
		node->variable = malloc(strlen(variable)+1);
		strcpy(node->variable, variable);
	}
	if(str != NULL) {
		node->str = malloc(strlen(str)+1);
		strcpy(node->str, str);
	}
	node->runCode = assignmentNodeFn;
	return node;
}

manAttributeNode * createManAttributeNode(char * variable) {
	manAttributeNode * node = malloc(sizeof(manAttributeNode));
	if(variable != NULL) {
		node->variable = malloc(strlen(variable)+1);
		strcpy(node->variable, variable);
	}
	node->runCode = manAttributeNodeFn;
	return node;
}

assignmentOpNode * createAssignmentOpNode(typeAssigmentOp operator) {
	assignmentOpNode * node = malloc(sizeof(assignmentOpNode));
	node->operator = operator;
	node->runCode = assignmentOpNodeFn;
	return node;
}

incOpNode * createIncOpNode(typeIncrementOp operator) {
	incOpNode * node = malloc(sizeof(incOpNode));
	node->operator = operator;
	node->runCode = incOpNodeFn;
	return node;
}
