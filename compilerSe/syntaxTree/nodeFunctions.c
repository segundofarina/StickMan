#include <stdio.h>
#include "nodeFunctions.h"
#include "syntaxTree.h"

/*
void nameNodeFn(void * node) {
	printf("%s", ((nameNode *)node)->str);
}

void statementNodeFn(void * node) {
	statementNode * n = (statementNode *) node;
	(n->child->runCode)(n->child);
	printf(";\n");
}*/

void functionsNodeFn(void * node) {
	functionsNode * n = (functionsNode *) node;
	functionList * current = n->list;
	functionNode * function;

	while(current != NULL) {
		function = current->function;
		(function->runCode)(function);
		current = current->next;
	}
}

void functionNodeFn(void * node) {
	functionNode * n = (functionNode *) node;
	(n->type->runCode)(n->type);
	(n->name->runCode)(n->name);
	(n->sentences->runCode)(n->sentences);
}

void typeNodeFn(void * node) {
	typeNode * n = (typeNode *) node;
	if(n->type == INTEGER_TYPE) {
		printf(" int");
	}
}

void nameNodeFn(void * node) {
	nameNode * n = (nameNode *) node;
	printf(" %s", n->name);
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
	printf(" LlegueAlSentence\n");
}
