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
*/

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



int main() {
	sentenceNode * sentence = createSentenceNode();
	sentencesNode * sentences = createSentencesNode(sentence);
	typeNode * type = createTypeNode(INTEGER_TYPE);
	nameNode * name = createNameNode("start");
	functionNode * function = createFunctionNode(type, name, sentences);
	functionsNode * functions = createFunctionsNode(function);

	(functions->runCode)(functions);

	return 0;
}
