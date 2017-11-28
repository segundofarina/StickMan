#ifndef __SYNTAX_TREE__
#define __SYNTAX_TREE__

#include "nodeFunctions.h"

typedef struct nameNode {
	char * str;
	runFn runCode;
} nameNode;

typedef struct statementNode {
	nameNode * child;
	runFn runCode;
} statementNode;

typedef struct statementsNode {
	//nameNode * children;
	//list of statemnt
	runFn runCode;
} statementsNode;


nameNode * createNameNode(char * str);
statementNode * createStatementNode(nameNode * child);

#endif
