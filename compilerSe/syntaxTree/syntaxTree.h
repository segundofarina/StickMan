#ifndef __SYNTAX_TREE__
#define __SYNTAX_TREE__

#include "nodeFunctions.h"


/* TYPES */
typedef enum {INTEGER_TYPE, DOUBLE_TYPE, STRING_TYPE} typeOp;
typedef enum {START_FN, FUNCTION} typeFunction;
typedef enum {ASSIGMENT, DECLARATION, RETURN, IF, WHILE, FOR, FUNCTION_CALL, MAN_ACTION} typeSentence;
typedef enum {ASSIGMENT_EXPRESSION, ASSIGMENT_INCREMENT, ASSIGMENT_MAN} typeAssigment;
typedef enum {EQUAL, ADD_EQUAL, SUBSTRACT_EQUAL, MULTIPLY_EQUAL, DIVIDE_EQUAL} typeAssigmentOp;
typedef enum {INCREMENT_ADD, INCREMENT_SUBSTRACT} typeIncrementOp;
typedef enum {DECLARATION_DEC, DECLARATION_ASIGN} typeDeclaration;
typedef enum {RETURN_BOOLEAN, RETURN_EXPRESSION} typeReturn;
typedef enum {EXP_INT, EXP_VAR, EXP_ADD, EXP_SUBSTRACT, EXP_MULTIPLY, EXP_DIVIDE, EXP_MODULUS} typeExpression;
typedef enum {PARAM_STRING, PARAM_EXP} typeParameter;
typedef enum {ELSE_BLOCK_ELSEIF, ELSE_BLOCK_ELSE} typeElseBlock;
typedef enum {CONDITION_EXP, CONDITION_AND, CONDITION_OR, CONDITION_FN, CONDITION_BOOLEAN} typeCondition;
typedef enum {MAN_ACTION_JOIN, MAN_ACTION_UNARY} typeManAction;
/* END TYPES */

struct expressionNode;
struct sentencesNode;
struct ifNode;
struct functionCallNode;

typedef struct conditionNode {
	typeCondition conditionType;
	int boolean;
	struct conditionNode * condition1;
	struct conditionNode * condition2;
	struct expressionNode * expression1;
	struct expressionNode * expression2;
	struct functionCallNode * functionCall;
	runFn runCode;
} conditionNode;

typedef struct elseBlockNode {
	typeElseBlock type;
	struct ifNode * elseif;
	struct sentencesNode * sentences;
	runFn runCode;
} elseblockNode;

typedef struct fnParameterNode {
	typeParameter paramType;
	char * str;
	struct expressionNode * expression;
} fnParameterNode;

typedef struct fnParameterList {
	fnParameterNode * fnParameter;
	struct fnParameterList * next;
} fnParameterList;

typedef struct fnParametersNode {
	fnParameterList * list;
	runFn runCode;
} fnParametersNode;

typedef struct manAttributeNode {
	char * variable;
	runFn runCode;
} manAttributeNode;

typedef struct expressionNode {
	typeExpression expressionType;
	int value;
	char * variable;
	struct expressionNode * expression1;
	struct expressionNode * expression2;
	struct functionCallNode * functionCall;
	manAttributeNode * manAttribute;
	runFn runCode;
} expressionNode;

typedef struct incOpNode {
	typeIncrementOp operator;
	runFn runCode;
} incOpNode;

typedef struct assigmentOpNode {
	typeAssigmentOp operator;
	runFn runCode;
} assigmentOpNode;

typedef struct typeNode {
	typeOp type;
	runFn runCode;
} typeNode;

typedef struct assigmentNode {
	typeAssigment assigmentType;
	assigmentOpNode * assigmentOp;
	expressionNode * expression;
	incOpNode * incOp;
	manAttributeNode * manAttribute;
	runFn runCode;
} assigmentNode;

typedef struct declarationNode {
	typeDeclaration declarationType;
	typeNode * type;
	expressionNode * expression;
	runFn runCode;
} declarationNode;

typedef struct returnNode {
	typeReturn returnType;
	int boolean;
	expressionNode * expression;
	runFn runCode;
} returnNode;

typedef struct ifNode {
	conditionNode * condition;
	struct sentencesNode * sentences;
	struct elseBlockNode * elseBlock;
	runFn runCode;
} ifNode;

typedef struct whileNode {
	conditionNode * condition;
	struct sentencesNode * sentences;
	runFn runCode;
} whileNode;

typedef struct forNode {
	assigmentNode * assigment1;
	assigmentNode * assigment2;
	conditionNode * condition;
	struct sentencesNode * sentences;
	runFn runCode;
} forNode;

typedef struct functionCallNode {
	fnParametersNode * fnParameter;
	runFn runCode;
} functionCallNode;

typedef struct manParamNode {
	char * param;
	runFn runCode;
} manParamNode;

typedef struct manActionNode {
	typeManAction manActionType;
	manParamNode * manParam1;
	manParamNode * manParam2;
	runFn runCode;
} manActionNode;

typedef struct sentenceNode {
	void * content;
	typeSentence sentenceType;
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


typedef struct parameterNode {
	char * name;
	typeNode * type;
	runFn runCode;
} parameterNode;

typedef struct parameterList {
	parameterNode * parameter;
	struct parameterList * next;
} parameterList;

typedef struct parametersNode {
	parameterList * list;
	runFn runCode;
} parametersNode;


typedef struct returnTypeNode {
	typeNode * type;
	runFn runCode;
} returnTypeNode;

typedef struct functionNode {
	parametersNode * parameters;
	returnTypeNode * returnType;
	sentencesNode * sentences;
	char * name;
	runFn runCode;
} functionNode;

typedef struct startFnNode {
	sentencesNode * sentences;
	runFn runCode;
} startFnNode;

/* LIST */
typedef struct functionList {
	//functionNode * function;
	void * function; // puede ser functionNode o startNode
	typeFunction functionType;
	struct functionList * next;
} functionList;
/* END LIST */

typedef struct functionsNode {
	functionList * list;
	runFn runCode;
} functionsNode;

typedef struct headerNode {
	char * fileName;
	runFn runCode;
} headerNode;

/* LIST */
typedef struct headerList {
	headerNode * header;
	struct headerList * next;
} headerList;
/* END LIST */

typedef struct headersNode {
	headerList * list;
	runFn runCode;
} headersNode;

typedef struct startNode {
	headersNode * headers;
	functionsNode * functions;
	runFn runCode;
} startNode;

#endif
