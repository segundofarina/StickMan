#include <stdio.h>
#include "nodeFunctions.h"
#include "syntaxTree.h"

void nameNodeFn(void * node) {
	printf("%s", ((nameNode *)node)->str);
}

void statementNodeFn(void * node) {
	statementNode * n = (statementNode *) node;
	(n->child->runCode)(n->child);
	printf(";\n");
}
