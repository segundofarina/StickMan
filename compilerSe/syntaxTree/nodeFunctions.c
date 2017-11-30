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
/*
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
*/



void startNodeFn(void * node){}

void headersNodeFn(void * node){}

void headerNodeFn(void * node){}

void functionsNodeFn(void * node){}

void startFnNodeFn(void * node){}

void functionNodeFn(void * node){}

void returnTypeNodeFn(void * node){}

void typeNodeFn(void * node){}

void parametersNodeFn(void * node){}

void parameterNodeFn(void * node){}

void sentencesNodeFn(void * node){}

void sentenceNodeFn(void * node){}

void manActionNodeFn(void * node){}

void manParamNodeFn(void * node){}

void fnFunctionCallFn(void * node){}

void fnParametersNodeFn(void * node){}

void fnParameterNodeFn(void * node){}

void expressionNodeFn(void * node){}

void forNodeFn(void * node){}

void conditionNodeFn(void * node){}

void whileNodeFn(void * node){}

void returnNodeFn(void * node){}

void declarationNodeFn(void * node){}

void ifNodeFn(void * node){}

void elseBlockNodeFn(void * node){}

void assignmentNodeFn(void * node){}

void manAttributeNodeFn(void * node){}

void assignmentOpNodeFn(void * node){}

void incOpNodeFn(void * node){}

void logicalOpFn(void * node){}
