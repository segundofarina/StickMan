#ifndef __NODE_FUNCTIONS__
#define __NODE_FUNCTIONS__

typedef void (*runFn) (void *);


void startNodeFn(void * node);

void headersNodeFn(void * node);

void functionsNodeFn(void * node);

void startFnNodeFn(void * node);

void functionNodeFn(void * node);

void returnTypeNodeFn(void * node);

void typeNodeFn(void * node);

void parametersNodeFn(void * node);

void parameterNodeFn(void * node);

void sentencesNodeFn(void * node);

void sentenceNodeFn(void * node);

void manActionNodeFn(void * node);

void manParamNodeFn(void * node);

void fnFunctionCallFn(void * node);

void fnParametersNodeFn(void * node);

void fnParameterNodeFn(void * node);

void expressionNodeFn(void * node);

void forNodeFn(void * node);

void conditionNodeFn(void * node);

void whileNodeFn(void * node);

void returnNodeFn(void * node);

void declarationNodeFn(void * node);

void ifNodeFn(void * node);

void elseBlockNodeFn(void * node);

void assignmentNodeFn(void * node);

void manAttributeNodeFn(void * node);

void assignmentOpNodeFn(void * node);

void incOpNodeFn(void * node);

#endif
