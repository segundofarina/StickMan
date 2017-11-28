#include <stdlib.h>
#include <string.h>
#include "syntaxTree.h"

nameNode * createNameNode(char * str) {
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
