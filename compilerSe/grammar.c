#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"

static int_var integer_variables[VARIABLES_QUANTITY];
static string_var string_variables[VARIABLES_QUANTITY];
static boolean_var boolean_variables[VARIABLES_QUANTITY];
static functions functions_variables[VARIABLES_QUANTITY];

static int integer_variables_length = 0;
static int string_variables_length = 0;
static int boolean_variables_length = 0;
static int functions_variables_length = 0;


struct parameter * transform(char * parameters){

	int i=0, j=0;
	char name[MAX_FUNCTION_NAME];
	struct parameter * parameter = malloc(sizeof(struct parameter));

	if(parameters[i] == 0){
		return NULL;
	}

	while(parameters[i] != ' ' && parameters[i] != 0 ){
		name[j] = parameters[i];
		j++;
		i++;
	} 

	if(parameters[i]==' '){
		i++;
	}

	name[j] = 0;
	parameter->name = malloc(strlen(name));
	
	parameter->next = transform(parameters+i);
	strcpy(parameter->name,name);
	
	return parameter;
}


int cmpParams(parameter * p1, parameter * p2){
	if(p1 == NULL && p2 == NULL){
		return 1;
	}else if(p1 == NULL || p2 == NULL){
		return 0;
	}
	return !strcmp(p1->name,p2->name) && cmpParams(p1->next,p2->next);
}

int existsFunction(char * name, char * returnType, char * parameters){
	struct parameter * parameter = transform(parameters);
	for(int i=0; i<functions_variables_length; i++){
		if(!strcmp(functions_variables[i].name,name) && !strcmp(functions_variables[i].returnType,returnType) && cmpParams(functions_variables[i].parameters,parameter)){
			return 1;
		}
	}
	return 0;
}



int existsInt(char * name){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			return 1;
		}
	}
	return 0;
}

int existsString(char * name){
	for(int i=0; i< string_variables_length ; i++){
		if(strcmp(string_variables[i].name,name) == 0){
			return 1;
		}
	}
	return 0;
}

int existsBoolean(char * name){
	for(int i=0; i< boolean_variables_length ; i++){
		if(strcmp(boolean_variables[i].name,name) == 0){
			return 1;
		}
	}
	return 0;
}

int existsVariable(char * name){
	if(existsInt(name) || existsBoolean(name) || existsString(name)){
		return 1;
	}
	return 0;
}

void addInt(char * name, int value){
	int_var * aux = malloc( sizeof(int_var) );
	aux->name = name;
	aux->value = value;
	integer_variables[integer_variables_length] = (*aux);
	integer_variables_length++;
}

void addBoolean(char * name, int value){
	if(value == 0 || value == 1){
		boolean_var * aux = malloc( sizeof(boolean_var) );
		aux->name = name;
		aux->value = value;
		boolean_variables[boolean_variables_length] = (*aux);
		boolean_variables_length++;
	}
}

void addString(char * name, char * value){
	string_var * aux = malloc( sizeof(string_var) );
	aux->name = name;
	aux->value = value;
	string_variables[string_variables_length] = (*aux);
	string_variables_length++;
}

void addFunction(char * name, char * returnType, char * parameters){
	if(!existsFunction(name,returnType,parameters)){
		struct parameter * parameter = transform(parameters);
		struct function * function = malloc(sizeof(function));
		function->name = name;
		function->returnType = returnType;
		function->parameters = parameter;
		functions_variables[functions_variables_length] = (*function);
		functions_variables_length++;
	}
}

void updateInt(char * name, int value){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			integer_variables[i].value = value;
			return;
		}
	}
	printf("variable undeclared\n");
}

void updateBoolean(char * name, int value){
	if(value == 0 || value == 1){
		for(int i=0; i< boolean_variables_length ; i++){
			if(strcmp(boolean_variables[i].name,name) == 0){
				boolean_variables[i].value = value;
				return;
			}
		}
		printf("variable undeclared\n");
	}else{
		printf("not a boolean value\n");
	}
}

void updateString(char * name, char * value){
	for(int i=0; i< string_variables_length ; i++){
		if(strcmp(string_variables[i].name,name) == 0){
			string_variables[i].value = value;
			return;
		}
	}
	printf("variable undeclared\n");
}

int getInt(char * name){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			return integer_variables[i].value;
		}
	}
	return 0;
}

int getBoolean(char * name){
	for(int i=0; i< boolean_variables_length ; i++){
		if(strcmp(boolean_variables[i].name,name) == 0){
			return boolean_variables[i].value;
		}
	}
	return 0;
}

char * getString( char * name){
	for(int i=0; i< string_variables_length ; i++){
		if(strcmp(string_variables[i].name,name) == 0){
			return string_variables[i].value;
		}
	}
	return 0;
}


void testString(){

	printf("TEST STRING\n");

	printf("%d\n", existsString("florcilove"));

	addString("florcilove","FLORCI<3");
	printf("%d\n", existsString("florcilove"));
	printf("%s\n", getString("florcilove"));

	updateString("florcilove","FLORCI");
	printf("%s\n", getString("florcilove"));

	addString("tincho","TINCHITO");
	printf("%s\n", getString("tincho"));

	updateString("tincho","TINCHO QUIERO COMER CLUB DE LA MILANESA");
	printf("%s\n", getString("tincho"));

	printf("%d\n", existsString("tincho"));
	return;
}

void testInteger(){
	printf("TEST INTEGER\n");

	printf("%d\n", existsInt("florcilove"));

	addInt("florcilove",0);
	printf("%d\n", existsInt("florcilove"));
	printf("%d\n", getInt("florcilove"));

	updateInt("florcilove",1);
	printf("%d\n", getInt("florcilove"));

	addInt("tincho",4);
	printf("%d\n", getInt("tincho"));

	updateInt("tincho",5);
	printf("%d\n", getInt("tincho"));

	printf("%d\n", existsInt("tincho"));
	return;
}

void testBoolean(){
	printf("TEST BOOLEAN\n");

	printf("%d\n", existsBoolean("florcilove"));

	addInt("florcilove",0);
	printf("%d\n", existsBoolean("florcilove"));
	printf("%d\n", getBoolean("florcilove"));

	updateInt("florcilove",1);
	printf("%d\n", getBoolean("florcilove"));

	addInt("tincho",4);
	printf("%d\n", getBoolean("tincho"));

	updateInt("tincho",1);
	printf("%d\n", getBoolean("tincho"));

	printf("%d\n", existsBoolean("tincho"));
	return;
}

void testFunctions(){
	char name[] = "main";
	char returnType[] = "int";
	char parameters[] = "int int";

	char name2[] = "start";
	char returnType2[] = "int";
	char parameters2[] = "string int";

	printf("%d\n", existsFunction(name,returnType,parameters));
	addFunction(name,returnType,parameters);
	printf("%d\n", existsFunction(name,returnType,parameters));
	
	printf("%d\n", existsFunction(name2,returnType2,parameters2));
	addFunction(name2,returnType2,parameters2);
	printf("%d\n", existsFunction(name2,returnType2,parameters2));
	return;
}


int main(){
	testFunctions();
	return 0;
}



