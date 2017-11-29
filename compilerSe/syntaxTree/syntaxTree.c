#include <stdlib.h>
#include <string.h>
#include "syntaxTree.h"


/*nameNode * createNameNode(char * str) {
	nameNode * node = malloc(sizeof(nameNode));
	node->str = malloc(strlen(str)+1);
	strcpy(node->str, str);
	node->runCode = nameNodeFn;
	return node;
}

statementNode * createStatementNode(nameNode * child) {
	statementNode * node = malloc(sizeof(statementNode));
	node->child = child;
	node->runCode = statementNodeFn;
	return node;
}

int main() {
	nameNode * nameN = createNameNode("hola");
	statementNode * statementN = createStatementNode(nameN);
	(statementN->runCode)(statementN);
	return 0;
}


functionsNode * createFunctionsNode(functionNode * fn) {
	functionsNode * node = malloc(sizeof(functionsNode));
	functionList * list = malloc(sizeof(functionList));
	list->function = fn;
	list->next = NULL;
	node->list = list;
	node->runCode = functionsNodeFn;
	return node;
}

functionsNode * addToFunctionsNode(functionNode * fn, functionsNode * pNode) {
	functionList * list = malloc(sizeof(functionList));
	list->function = fn;

	functionList * current = pNode->list;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = list;
	return pNode;
}


functionNode * createFunctionNode(typeNode * type, nameNode * name, sentencesNode * sentences) {
	functionNode * node = malloc(sizeof(functionNode));
	node->type = type;
	node ->name = name;
	node->sentences = sentences;
	node->runCode = functionNodeFn;
	return node;
}

typeNode * createTypeNode(typeOp type) {
	typeNode * node = malloc(sizeof(typeNode));
	node->type = type;
	node->runCode = typeNodeFn;
	return node;
}

nameNode * createNameNode(char * name) {
	nameNode * node = malloc(sizeof(nameNode));
	node->name = malloc(strlen(name)+1);
	strcpy(node->name, name);
	node->runCode = nameNodeFn;
	return node;
}

sentencesNode * createSentencesNode(sentenceNode * sentence) {
	sentencesNode * node = malloc(sizeof(sentencesNode));
	sentenceList * list = malloc(sizeof(sentenceList));
	list->sentence = sentence;
	list->next = NULL;
	node->list = list;
	node->runCode = sentencesNodeFn;
	return node;
}

sentencesNode * addToSentencesNode(sentenceNode * sentence, sentencesNode * pNode) {
	sentenceList * list = malloc(sizeof(sentenceList));
	list->sentence = sentence;

	sentenceList * current = pNode->list;
	while(current->next != NULL) {
		current = current->next;
	}
	current->next = list;
	return pNode;
}

sentenceNode * createSentenceNode() {
	sentenceNode * node = malloc(sizeof(sentenceNode));
	node->runCode = sentenceNodeFn;
	return node;
}




*/




manActionNode * createManActionNode(manParamNode * manParam1, manParamNode * manParam2 ){
	manActionNode * node = malloc(sizeof(manActionNode));
	node->manParam1 = manParam1;
	node->manParam2 = manParam2;
	//node->runCode = manActionNodeFn;
	return node;
}

fnParameterNode * createFnParameterNode(expressionNode * expression){
	fnParameterNode * node = malloc(sizeof(fnParameterNode));
	node->expression = expression;
//	node->runCode = fnParameterNodeFn;
	return node;
}


fnParametersNode * createFnParametersNode(fnParameterNode * fnParameter){
	fnParametersNode * node = malloc(sizeof(fnParametersNode));
	fnParameterList * list = malloc(sizeof(fnParameterList));
	list->fnParameter = fnParameter;
	list->next = NULL;
	node->list = list;
	//node->runCode = fnParametersNodeFn;
	return node;
}

functionCallNode * createFunctionCallNode(fnParametersNode * fnParameters){
	functionCallNode * node = malloc(sizeof(functionCallNode));
	node->fnParameters = fnParameters;
	//node->runCode = fnFunctionCallFn;
	return node;
}

expressionNode * createExpressionNode(manAttributeNode * manAttribute, functionCallNode * functionCall, expressionNode * expression1, expressionNode * expression2){
	expressionNode * node = malloc(sizeof(expressionNode));
	node->manAttribute = manAttribute;
	node->functionCall = functionCall;
	node->expression1 = expression1;
	node->expression2 = expression2;
	//node->runCode = expressionNodeFn;
	return node;
}

forNode * createForNode(assignmentNode * assignment1, assignmentNode * assignment2, conditionNode * condition, sentencesNode * sentences){
	forNode * node = malloc(sizeof(forNode));
	node->assignment1 = assignment1;
	node->assignment2 = assignment2;
	node->condition = condition;
	node->sentences = sentences;
	//node->runCode = forNodeFn;
	return node;
}

returnNode * createReturnNode(expressionNode * expression){
	returnNode * node = malloc(sizeof(returnNode));
	node->expression = expression;
	//node->runCode = returnNodeFn;
	return node;
}

whileNode * createWhileNode(conditionNode * condition, sentencesNode * sentences){
	whileNode * node = malloc(sizeof(whileNode));
	node->condition = condition;
	node->sentences = sentences;
	//node->runCode = whileNodeFn;
	return node;
}

declarationNode * createDeclarationNode(typeNode * type, expressionNode * expression){
	declarationNode * node = malloc(sizeof(declarationNode));
	node->type = type;
	node->expression = expression;
	//node->runCode = declarationNodeFn;
	return node;
}

ifNode * createIfNode( conditionNode * condition, sentencesNode * sentences, struct elseBlockNode * elseBlock){
	ifNode * node = malloc(sizeof(ifNode));
	node->condition = condition;
	node->sentences = sentences;
	node->elseBlock = elseBlock;
	//node->runCode = ifNodeFn;
	return node;
}

assignmentNode * createAssignmentNode(assignmentOpNode * assignmentOp, expressionNode * expression, incOpNode * incOp, manAttributeNode * manAttribute){
	assignmentNode * node = malloc(sizeof(assignmentNode));
	node->assignmentOp = assignmentOp;
	node->expression = expression;
	node->incOp = incOp;
	node->manAttribute = manAttribute;
	//node->runCode = assignmentNodeFn;
	return node;
}

struct elseBlockNode * createElseBlockNode(ifNode * elseif, sentencesNode * sentences) {
	struct elseBlockNode * node = malloc(sizeof(struct elseBlockNode));
	node->elseif = elseif;
	node->sentences = sentences;
	//node->runCode = elseBlockNodeFn;
	return node;
}

conditionNode * createConditionNode(conditionNode * condition1, conditionNode * condition2, expressionNode * expression1, expressionNode * expression2, functionCallNode * functionCall){
	conditionNode * node = malloc(sizeof(conditionNode));
	node->condition1 = condition1;
	node->condition2 = condition2;
	node->expression1 = expression1;
	node->expression2 = expression2;
	node->functionCall = functionCall;
	//node->runCode = conditionNodeFn;
	return node;
}



int main() {
	/*
	sentenceNode * sentence = createSentenceNode();
	sentencesNode * sentences = createSentencesNode(sentence);
	typeNode * type = createTypeNode(INTEGER_TYPE);
	nameNode * name = createNameNode("start");
	functionNode * function = createFunctionNode(type, name, sentences);
	functionsNode * functions = createFunctionsNode(function);

	(functions->runCode)(functions);
*/
	return 0;
}


