#ifndef __SYNTAX_TREE__
#define __SYNTAX_TREE__

#include "nodeFunctions.h"
/*
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
*/



/* TYPES */
typedef enum {INTEGER_TYPE, DOUBLE_TYPE, STRING_TYPE} typeOp;
/* END TYPES */


typedef struct sentenceNode {
	//algo
	runFn runCode;
} sentenceNode;

/* LIST */
typedef struct sentenceList {
	sentenceNode * sentence;
	struct sentenceList * next;
} sentenceList;
/* END LIST */

typedef struct sentencesNode {
	sentenceList * list;
	runFn runCode;
} sentencesNode;

typedef struct nameNode {
	char * name;
	runFn runCode;
} nameNode;

typedef struct typeNode {
	typeOp type;
	runFn runCode;
} typeNode;

typedef struct functionNode {
	typeNode * type;
	nameNode * name;
	sentencesNode * sentences;
	runFn runCode;
} functionNode;

/* LIST */
typedef struct functionList {
	functionNode * function;
	struct functionList * next;
} functionList;
/* END LIST */

typedef struct functionsNode {
	functionList * list;
	runFn runCode;
} functionsNode;


#endif
