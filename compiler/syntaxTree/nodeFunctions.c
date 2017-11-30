#include <stdio.h>
#include "nodeFunctions.h"
#include "syntaxTree.h"


void startNodeFn(void * node) {
	startNode * n = (startNode *) node;

	printf("#include <stdio.h>\n");

	(n->headers->runCode)(n->headers);
	//print all functions declarations
	(n->functions->runCode)(n->functions);

}

void headersNodeFn(void * node) {
	headersNode * n = (headersNode *) node;

	headerList * current = n->list;
	headerNode * header;

	while(current != NULL) {
		header = current->header;
		(header->runCode)(header);
		current = current->next;
	}
}

void headerNodeFn(void * node) {
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
	printf("soy el start\n");
}

void functionNodeFn(void * node) {
	printf("soy una function\n");
}

void returnTypeNodeFn(void * node) {

}

void typeNodeFn(void * node) {

}

void parametersNodeFn(void * node) {

}

void parameterNodeFn(void * node) {

}

void sentencesNodeFn(void * node) {

}

void sentenceNodeFn(void * node) {

}

void manActionNodeFn(void * node) {

}

void manParamNodeFn(void * node) {

}

void fnFunctionCallFn(void * node) {

}

void fnParametersNodeFn(void * node) {

}

void fnParameterNodeFn(void * node) {

}

void expressionNodeFn(void * node) {

}

void forNodeFn(void * node) {

}

void conditionNodeFn(void * node) {

}

void whileNodeFn(void * node) {

}

void returnNodeFn(void * node) {

}

void declarationNodeFn(void * node) {

}

void ifNodeFn(void * node) {

}

void elseBlockNodeFn(void * node) {

}

void assignmentNodeFn(void * node) {

}

void manAttributeNodeFn(void * node) {

}

void assignmentOpNodeFn(void * node) {

}

void incOpNodeFn(void * node) {

}

void logicalOpFn(void * node) {

}
