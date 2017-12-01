%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "syntaxTree/syntaxTree.h"
	extern void yyerror(char *);
	extern int yylex();
	extern int yylineno;
	extern char * yytext;


%}

%union {
	char * string;
	int integer;

	logicalOperatorNode * logicalOpNode;
	conditionNode * conditionNode;
	elseBlockNode * elseBlockNode;
	fnParameterNode * fnParameterNode;
	fnParametersNode * fnParametersNode;
	manAttributeNode * manAttributeNode;
	expressionNode * expressionNode;
	incOpNode * incOpNode;
	assignmentOpNode * assignmentOpNode;
	typeNode * typeNode;
	assignmentNode * assignmentNode;
	declarationNode * declarationNode;
	returnNode * returnNode;
	ifNode * ifNode;
	whileNode * whileNode;
	forNode * forNode;
	functionCallNode * functionCallNode;
	manParamNode * manParamNode;
	manActionNode * manActionNode;
	sentenceNode * sentenceNode;
	sentencesNode * sentencesNode;
	parameterNode * parameterNode;
	parametersNode * parametersNode;
	returnTypeNode * returnTypeNode;
	functionNode * functionNode;
	startFnNode * startFnNode;
	functionsNode * functionsNode;
	headerNode * headerNode;
	headersNode * headersNode;
	startNode * startNode;
}

%token SEMICOLON
%token OPEN_CURLY_BRACKET
%token CLOSE_CURLY_BRACKET
%token OPEN_PARENTHESES
%token CLOSE_PARENTHESES
%token ADD
%token SUBSTRACT
%token <integer> INTEGER
%token <string> VARIABLE
%token <integer> BOOLEAN
%token <string> STRING
%token MAN
%token INTEGER_TYPE
%token STRING_TYPE
%token BOOLEAN_TYPE
%token INCLUDE
%token <string> FILE_NAME
%token COLON
%token FOR
%token WHILE
%token IF
%token ELSE
%token EQUAL
%token NOT_EQUAL
%token GREATER_THAN
%token EQUAL_GREATER_THAN
%token EQUAL_LESS_THAN
%token LESS_THAN
%token MULTIPLY
%token DIVIDE
%token MODULUS
%token RETURN
%token START
%token AND
%token OR
%token FUNCTION
%token ARROW
%token DOT

%type <startNode> Start
%type <headersNode> Headers
%type <headerNode> Header
%type <functionsNode> Functions
%type <functionNode> Function
%type <startFnNode> StartFn
%type <parametersNode> Paramenters
%type <parameterNode> Parameter
%type <returnTypeNode> ReturnType
%type <sentencesNode> Sentences
%type <sentenceNode> Sentece
%type <assignmentNode> Assignment
%type <assignmentOpNode> AssignmentOp
%type <incOpNode> IncOp
%type <declarationNode> Declaration
%type <returnNode> Return
%type <typeNode> Type
%type <expressionNode> Expression
%type <ifNode> If
%type <elseBlockNode> ElseBlock
%type <whileNode> While
%type <forNode> For
%type <conditionNode> Condition
%type <logicalOpNode> LogicalOp
%type <functionCallNode> FunctionCall
%type <fnParametersNode> FnParameters
%type <fnParameterNode> FnParameter
%type <manAttributeNode> ManAttribute
%type <manActionNode> ManAction
%type <manParamNode> ManParams





%left ADD SUBSTRACT
%left MULTIPLY DIVIDE MODULUS

%left EQUAL NOT_EQUAL
%left EQUAL_LESS_THAN EQUAL_GREATER_THAN LESS_THAN GREATER_THAN
%left OR AND


%start Start


%%

Start: Headers Functions								{ $$ = createStartNode($1,$2); ($$->runCode)($$);}
Headers: /* empty */									{ $$ = createHeadersNode(); }
 		| Headers Header								{ $$ = addToHeadersNode($2,$1); }
Header: INCLUDE FILE_NAME								{ $$ = createHeaderNode($2); }
Functions: Functions Function							{ $$ = addToFunctionsNode($2, $1, $2->functionType); }
		| Function										{ $$ = createFunctionsNode($1, $1->functionType); }
		| StartFn										{ $$ = createFunctionsNode($1, $1->functionType); }
Function: FUNCTION VARIABLE OPEN_PARENTHESES CLOSE_PARENTHESES ReturnType OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET										{ $$ = createFunctionNode(NULL, $5, $7, $2); }
		| FUNCTION VARIABLE OPEN_PARENTHESES Paramenters CLOSE_PARENTHESES ReturnType OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET							{ $$ = createFunctionNode($4, $6, $8, $2); }
StartFn: START OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET										{ $$ = createStartFnNode($3); }
Paramenters: Paramenters COLON Parameter				{ $$ = addToParametersNode($3, $1); }
		| Parameter										{ $$ = createParametersNode($1); }
Parameter: Type VARIABLE								{ $$ = createParameterNode($1,$2); }
ReturnType: /* empty */									{ $$ = NULL; }
		| ARROW Type									{ $$ = createReturnTypeNode($2); }
Sentences: /* empty */									{ $$ = createSentencesNode(); }
		| Sentences Sentece								{ $$ = addToSentences($2, $1); }
Sentece: Assignment SEMICOLON							{ $$ = createSentenceNode($1, ST_ASSIGNMENT); }
		| Declaration SEMICOLON							{ $$ = createSentenceNode($1, ST_DECLARATION); }
		| Return SEMICOLON								{ $$ = createSentenceNode($1, ST_RETURN); }
		| If											{ $$ = createSentenceNode($1, ST_IF); }
		| While											{ $$ = createSentenceNode($1, ST_WHILE); }
		| For											{ $$ = createSentenceNode($1, ST_FOR); }
		| FunctionCall SEMICOLON						{ $$ = createSentenceNode($1, ST_FUNCTION_CALL); }
		| ManAction SEMICOLON							{ $$ = createSentenceNode($1, ST_MAN_ACTION); }
Assignment: VARIABLE EQUAL STRING						{ $$ = createAssignmentNode(ST_ASSIGNMENT_STRING, NULL, NULL, NULL, NULL,$1, $3, 0); }
		| VARIABLE EQUAL BOOLEAN						{ $$ = createAssignmentNode(ST_ASSIGNMENT_BOOLEAN, NULL, NULL, NULL, NULL,$1, NULL, $3); }
		| VARIABLE AssignmentOp Expression				{ $$ = createAssignmentNode(ST_ASSIGNMENT_EXPRESSION, $2, $3, NULL, NULL,$1 , NULL, 0); }
		| VARIABLE IncOp								{ $$ = createAssignmentNode(ST_ASSIGNMENT_INCREMENT, NULL, NULL, $2, NULL,$1, NULL, 0); }
		| ManAttribute EQUAL Expression					{ $$ = createAssignmentNode(ST_ASSIGNMENT_MAN, NULL, $3, NULL, $1, NULL, NULL, 0); }
AssignmentOp: EQUAL										{ $$ = createAssignmentOpNode(ST_EQUAL); }
		| ADD EQUAL										{ $$ = createAssignmentOpNode(ST_ADD_EQUAL); }
		| SUBSTRACT EQUAL								{ $$ = createAssignmentOpNode(ST_SUBSTRACT_EQUAL); }
		| MULTIPLY EQUAL								{ $$ = createAssignmentOpNode(ST_MULTIPLY_EQUAL); }
		| DIVIDE EQUAL									{ $$ = createAssignmentOpNode(ST_DIVIDE_EQUAL); }
IncOp: ADD ADD											{ $$ = createIncOpNode(ST_INCREMENT_ADD); }
		| SUBSTRACT SUBSTRACT							{ $$ = createIncOpNode(ST_INCREMENT_SUBSTRACT); }
Declaration: Type VARIABLE EQUAL Expression				{ $$ = createDeclarationNode(ST_DECLARATION_ASIGN, $1, $4, $2, NULL, 0); }
		| Type VARIABLE EQUAL BOOLEAN					{ $$ = createDeclarationNode(ST_DECLARATION_ASIGN_BOOLEAN, $1, NULL, $2, NULL, $4); }
		| Type VARIABLE EQUAL STRING					{ $$ = createDeclarationNode(ST_DECLARATION_ASIGN_STRING, $1, NULL, $2, $4, 0); }
		| Type VARIABLE									{ $$ = createDeclarationNode(ST_DECLARATION_DEC, $1, NULL, $2, NULL, 0); }
Return: RETURN Expression								{ $$ = createReturnNode(ST_RETURN_EXPRESSION, 0, $2); }
		| RETURN BOOLEAN								{ $$ = createReturnNode(ST_RETURN_BOOLEAN, $2, NULL); }
Type: INTEGER_TYPE										{ $$ = createTypeNode(ST_INTEGER_TYPE); }
	| STRING_TYPE										{ $$ = createTypeNode(ST_STRING_TYPE); }
	| BOOLEAN_TYPE										{ $$ = createTypeNode(ST_BOOLEAN_TYPE); }
Expression: INTEGER										{ $$ = createExpressionNode(ST_EXP_INT, $1, NULL, NULL, NULL, NULL, NULL); }
	| VARIABLE											{ $$ = createExpressionNode(ST_EXP_VAR, 0, $1, NULL, NULL, NULL, NULL); }
	| ManAttribute										{ $$ = createExpressionNode(ST_EXP_MANATTR, 0, NULL, $1, NULL, NULL, NULL); }
	| FunctionCall										{ $$ = createExpressionNode(ST_EXP_FUNCTIONCALL, 0, NULL, NULL, $1, NULL, NULL); }
 	| Expression ADD Expression							{ $$ = createExpressionNode(ST_EXP_ADD, 0, NULL, NULL, NULL, $1, $3); }
	| Expression SUBSTRACT Expression					{ $$ = createExpressionNode(ST_EXP_SUBSTRACT, 0, NULL, NULL, NULL, $1, $3); }
	| Expression MULTIPLY Expression					{ $$ = createExpressionNode(ST_EXP_MULTIPLY, 0, NULL, NULL, NULL, $1, $3); }
	| Expression DIVIDE Expression						{ $$ = createExpressionNode(ST_EXP_DIVIDE, 0, NULL, NULL, NULL, $1, $3); }
	| Expression MODULUS Expression						{ $$ = createExpressionNode(ST_EXP_MODULUS, 0, NULL, NULL, NULL, $1, $3); }
If: IF OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET ElseBlock						{ $$ = createIfNode($3, $6, $8); }
ElseBlock: /* empty */									{ $$ = NULL; }
		| ELSE If										{ $$ = createElseBlockNode(ST_ELSE_BLOCK_ELSEIF, $2, NULL); }
		| ELSE OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET										{ $$ = createElseBlockNode(ST_ELSE_BLOCK_ELSE, NULL, $3); }
While: WHILE OPEN_PARENTHESES Condition CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET										{ $$ = createWhileNode($3, $6); }
For: FOR OPEN_PARENTHESES Assignment SEMICOLON Condition SEMICOLON Assignment CLOSE_PARENTHESES OPEN_CURLY_BRACKET Sentences CLOSE_CURLY_BRACKET										{ $$ = createForNode($3, $7, $5, $10); }
Condition: Expression LogicalOp Expression										{ $$ = createConditionNode(ST_CONDITION_EXP, $2, 0, NULL, NULL, $1, $3, NULL); }
 		| Condition OR Condition												{ $$ = createConditionNode(ST_CONDITION_OR, NULL, 0, $1, $3, NULL, NULL, NULL); }
		| Condition AND Condition												{ $$ = createConditionNode(ST_CONDITION_AND, NULL, 0, $1, $3, NULL, NULL, NULL); }
		| OPEN_PARENTHESES Condition CLOSE_PARENTHESES							{ $$ = $2; }
		| BOOLEAN																{ $$ = createConditionNode(ST_CONDITION_BOOLEAN, NULL, $1, NULL, NULL, NULL, NULL, NULL); }
		| FunctionCall															{ $$ = createConditionNode(ST_CONDITION_FN, NULL, 0, NULL, NULL, NULL, NULL, $1); }
LogicalOp: EQUAL EQUAL															{ $$ = createLogicalOpNode(ST_LOP_EQ); }
		| NOT_EQUAL																{ $$ = createLogicalOpNode(ST_LOP_NE); }
		| EQUAL_LESS_THAN														{ $$ = createLogicalOpNode(ST_LOP_LE); }
		| EQUAL_GREATER_THAN													{ $$ = createLogicalOpNode(ST_LOP_GE); }
		| LESS_THAN																{ $$ = createLogicalOpNode(ST_LOP_LT); }
		| GREATER_THAN															{ $$ = createLogicalOpNode(ST_LOP_GT); }
FunctionCall: VARIABLE OPEN_PARENTHESES CLOSE_PARENTHESES						{ $$ = createFunctionCallNode($1, NULL); }
		| VARIABLE OPEN_PARENTHESES FnParameters CLOSE_PARENTHESES				{ $$ = createFunctionCallNode($1, $3); }
FnParameters: FnParameters COLON FnParameter									{ $$ = addToFnParametersNode($3, $1); }
		| FnParameter															{ $$ = createFnParametersNode($1); }
FnParameter: Expression															{ $$ = createFnParameterNode(ST_PARAM_EXP, $1, NULL); }
		| STRING																{ $$ = createFnParameterNode(ST_PARAM_STRING, NULL, $1); }
ManAttribute: MAN DOT VARIABLE													{ $$ = createManAttributeNode($3); }
ManAction: MAN ARROW VARIABLE ManParams ADD MAN ARROW VARIABLE ManParams		{ $$ = createManActionNode( ST_MAN_ACTION_JOIN,$3, $4, $8, $9); }
		| MAN ARROW VARIABLE ManParams											{ $$ = createManActionNode(ST_MAN_ACTION_UNARY, $3, $4, NULL, NULL); }
ManParams: /* empty */															{ $$ = NULL; }
		| STRING																{ $$ = createManParamNode($1); }
		| VARIABLE																{ $$ = createManParamNode($1); }

%%

void yyerror (char *s) {
	printf("Unexpected token in line %d, while reading %s...\n", yylineno, yytext);
}
