#ifndef __SYNTAX_TREE__
#define __SYNTAX_TREE__

#include "nodeFunctions.h"


/* TYPES */
typedef enum {ST_INTEGER_TYPE, ST_STRING_TYPE, ST_BOOLEAN_TYPE, ST_VOID_TYPE} typeOp;
typedef enum {ST_START_FN, ST_FUNCTION} typeFunction;
typedef enum {ST_ASSIGNMENT, ST_DECLARATION, ST_RETURN, ST_IF, ST_WHILE, ST_FOR, ST_FUNCTION_CALL, ST_MAN_ACTION} typeSentence;
typedef enum {ST_ASSIGNMENT_EXPRESSION, ST_ASSIGNMENT_INCREMENT, ST_ASSIGNMENT_MAN} typeAssigment;
typedef enum {ST_EQUAL, ST_ADD_EQUAL, ST_SUBSTRACT_EQUAL, ST_MULTIPLY_EQUAL, ST_DIVIDE_EQUAL} typeAssigmentOp;
typedef enum {ST_INCREMENT_ADD, ST_INCREMENT_SUBSTRACT} typeIncrementOp;
typedef enum {ST_DECLARATION_DEC, ST_DECLARATION_ASIGN} typeDeclaration;
typedef enum {ST_RETURN_BOOLEAN, ST_RETURN_EXPRESSION} typeReturn;
typedef enum {ST_EXP_INT, ST_EXP_VAR, ST_EXP_ADD, ST_EXP_SUBSTRACT, ST_EXP_MULTIPLY, ST_EXP_DIVIDE, ST_EXP_MODULUS, ST_EXP_MANATTR, ST_EXP_FUNCTIONCALL} typeExpression;
typedef enum {ST_PARAM_STRING, ST_PARAM_EXP} typeParameter;
typedef enum {ST_ELSE_BLOCK_ELSEIF, ST_ELSE_BLOCK_ELSE} typeElseBlock;
typedef enum {ST_CONDITION_EXP, ST_CONDITION_AND, ST_CONDITION_OR, ST_CONDITION_FN, ST_CONDITION_BOOLEAN} typeCondition;
typedef enum {ST_MAN_ACTION_JOIN, ST_MAN_ACTION_UNARY} typeManAction;
typedef enum {ST_LOP_EQ, ST_LOP_NE, ST_LOP_LE, ST_LOP_GE, ST_LOP_LT, ST_LOP_GT} typeLogicOp;
/* END TYPES */

struct expressionNode;
struct sentencesNode;
struct ifNode;
struct functionCallNode;

typedef struct logicalOperatorNode {
	typeLogicOp type;
	runFn runCode;
} logicalOperatorNode;

typedef struct conditionNode {
	int boolean;
	typeCondition conditionType;
	logicalOperatorNode * logicalOperator;
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
} elseBlockNode;

typedef struct fnParameterNode {
	typeParameter paramType;
	char * str;
	struct expressionNode * expression;
	runFn runCode;
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

typedef struct assignmentOpNode {
	typeAssigmentOp operator;
	runFn runCode;
} assignmentOpNode;

typedef struct typeNode {
	typeOp type;
	runFn runCode;
} typeNode;

typedef struct assignmentNode {
	typeAssigment assignmentType;
	assignmentOpNode * assignmentOp;
	expressionNode * expression;
	incOpNode * incOp;
	manAttributeNode * manAttribute;
	typeSentence sentenceType;
	char * variable;
	runFn runCode;
} assignmentNode;

typedef struct declarationNode {
	typeDeclaration declarationType;
	typeNode * type;
	expressionNode * expression;
	typeSentence sentenceType;
	char * variable;
	runFn runCode;
} declarationNode;

typedef struct returnNode {
	typeReturn returnType;
	int boolean;
	expressionNode * expression;
	typeSentence sentenceType;
	runFn runCode;
} returnNode;

typedef struct ifNode {
	conditionNode * condition;
	struct sentencesNode * sentences;
	elseBlockNode * elseBlock;
	typeSentence sentenceType;
	runFn runCode;
} ifNode;

typedef struct whileNode {
	conditionNode * condition;
	struct sentencesNode * sentences;
	typeSentence sentenceType;
	runFn runCode;
} whileNode;

typedef struct forNode {
	assignmentNode * assignment1;
	assignmentNode * assignment2;
	conditionNode * condition;
	struct sentencesNode * sentences;
	typeSentence sentenceType;
	runFn runCode;
} forNode;

typedef struct functionCallNode {
	char * name;
	fnParametersNode * fnParameters;
	typeSentence sentenceType;
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
	char * var1;
	char * var2;
	typeSentence sentenceType;
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
	typeFunction functionType;
	runFn runCode;
} functionNode;

typedef struct startFnNode {
	sentencesNode * sentences;
	typeFunction functionType;
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






startNode * createStartNode(headersNode * headers, functionsNode * functions);
headersNode * createHeadersNode();
headersNode * addToHeadersNode(headerNode * header, headersNode * pNode);
headerNode * createHeaderNode(char * fileName);
functionsNode * createFunctionsNode(void * fn, typeFunction typeFn);
functionsNode * addToFunctionsNode(void * fn, functionsNode * pNode, typeFunction typeFn);
startFnNode * createStartFnNode(sentencesNode * sentences);
functionNode * createFunctionNode(parametersNode * parameters, returnTypeNode * returnType, sentencesNode * sentences, char * name);
returnTypeNode * createReturnTypeNode(typeNode * type);
typeNode * createTypeNode(typeOp type);
parametersNode * createParametersNode(parameterNode * parameter);
parametersNode * addToParametersNode(parameterNode * parameter, parametersNode * pNode);
parameterNode * createParameterNode(typeNode * type, char * name);
sentencesNode * createSentencesNode();
sentencesNode * addToSentences(sentenceNode * sentence, sentencesNode * pNode);
sentenceNode * createSentenceNode(void * sentence, typeSentence type);
manActionNode * createManActionNode(typeManAction type, char * var1, manParamNode * manParam1, char * var2, manParamNode * manParam2);
manParamNode * createManParamNode(char * string);
functionCallNode * createFunctionCallNode(char * name, fnParametersNode * fnParameters);
fnParametersNode * createFnParametersNode(fnParameterNode * fnParameter);
fnParametersNode * addToFnParametersNode(fnParameterNode * fnParameter, fnParametersNode * pNode);
fnParameterNode * createFnParameterNode(typeParameter paramType, expressionNode * expression, char * str);
expressionNode * createExpressionNode(typeExpression expType, int value, char * variable, manAttributeNode * manAttribute, functionCallNode * functionCall, expressionNode * expression1, expressionNode * expression2);
forNode * createForNode(assignmentNode * assignment1, assignmentNode * assignment2, conditionNode * condition, sentencesNode * sentences);
conditionNode * createConditionNode(typeCondition conditionType, logicalOperatorNode * logicalOp, int boolean, conditionNode * condition1, conditionNode * condition2, expressionNode * expression1, expressionNode * expression2, functionCallNode * functionCall);
logicalOperatorNode * createLogicalOpNode(typeLogicOp type);
whileNode * createWhileNode(conditionNode * condition, sentencesNode * sentences);
returnNode * createReturnNode(typeReturn retType, int boolean, expressionNode * expression);
declarationNode * createDeclarationNode(typeDeclaration declarationType, typeNode * type, expressionNode * expression, char * variable);
ifNode * createIfNode( conditionNode * condition, sentencesNode * sentences, elseBlockNode * elseBlock);
elseBlockNode * createElseBlockNode(typeElseBlock typeElse, ifNode * elseif, sentencesNode * sentences);
assignmentNode * createAssignmentNode(typeAssigment assigmentType, assignmentOpNode * assignmentOp, expressionNode * expression, incOpNode * incOp, manAttributeNode * manAttribute, char * variable);
manAttributeNode * createManAttributeNode(char * variable);
assignmentOpNode * createAssignmentOpNode(typeAssigmentOp operator);
incOpNode * createIncOpNode(typeIncrementOp operator);




#endif
