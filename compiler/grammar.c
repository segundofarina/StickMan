#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"

static char * movements_files[FILES_QUANTITY];
static function functions_variables[VARIABLES_QUANTITY];

static int movements_files_length = 0;
static int functions_variables_length = 0;

static function * currentfn;


struct parameter * transform(char * parameters){

	int i=0, j=0;
	char name[MAX_FUNCTION_NAME], type[MAX_RETURN_TYPE];
	struct parameter * parameter = malloc(sizeof(struct parameter));

	if(!parameters[i]){
		return NULL;
	}

	while(parameters[i] != ' '&& parameters[i] != 0 ){
		type[j] = parameters[i];
		j++;
		i++;
	}

	if(parameters[i]==' '){
		i++;
	}

	type[j] = 0;
	parameter->type = malloc(strlen(type));
	strcpy(parameter->type,type);

	j = 0;

	while(parameters[i] != ',' && parameters[i] != 0 ){
		name[j] = parameters[i];
		j++;
		i++;
	}

	if(parameters[i]==','){
		i++;
	}

	name[j] = 0;
	parameter->name = malloc(strlen(name));
	strcpy(parameter->name,name);

	parameter->next = transform(parameters+i);
	

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




function * addFunction(char * name, char * returnType, char * parameters){
	if(!existsFunction(name,returnType,parameters)){
		struct parameter * parameter = transform(parameters);
		struct function * function = malloc(sizeof(function));
		function->name = name;
		function->returnType = returnType;
		function->parameters = parameter;
		functions_variables[functions_variables_length] = (*function);
		functions_variables_length++;

		function->integer_variables_length = 0;
		function->string_variables_length = 0;
	 	function->boolean_variables_length = 0;
		return function;
	}
	return NULL;
}

void currentFunction(char * name, char * returnType, char * parameters){
	currentfn = addFunction(name,returnType,parameters);
}

int existsInt(char * name){
	if(!currentfn->integer_variables_length){
		return 0;
	}
	for(int i=0; i < currentfn->integer_variables_length ; i++){
		if(!strcmp(currentfn->integer_variables[i].name,name)){
			return 1;
		}
	}
	return 0;
}

int existsString(char * name){
	if(!currentfn->string_variables_length){
		return 0;
	}
	for(int i=0; i< currentfn->string_variables_length ; i++){
		if(!strcmp(currentfn->string_variables[i].name,name)){
			return 1;
		}
	}
	return 0;
}

int existsBoolean(char * name){
	if(!currentfn->boolean_variables_length){
		return 0;
	}
	for(int i=0; i< currentfn->boolean_variables_length ; i++){
		if(!strcmp(currentfn->boolean_variables[i].name,name)){
			return 1;
		}
	}
	return 0;
}

int existsFile(char * name){
	for(int i=0 ; i < movements_files_length ; i++){
		if(!strcmp(movements_files[i],name)){
			return 1;
		}
	}
	return 0;
}

int addInt(char * name, int value){
	if(existsInt(name)){
		return 1;
	}
	int_var * aux = malloc( sizeof(int_var));
	aux->name = name;
	aux->value = value;
	currentfn->integer_variables[currentfn->integer_variables_length] = (*aux);
	currentfn->integer_variables_length++;
	return 0;
}

int addBoolean(char * name, int value){
	if(!existsBoolean(name) && (value == 0 || value == 1)){
		boolean_var * aux = malloc( sizeof(boolean_var) );
		aux->name = name;
		aux->value = value;
		currentfn->boolean_variables[currentfn->boolean_variables_length] = (*aux);
		currentfn->boolean_variables_length++;
		return 0;
	}
	return 1;
}

int addString(char * name, char * value){
	if(existsString(name)){
		return 1;
	}
	string_var * aux = malloc( sizeof(string_var) );
	aux->name = name;
	aux->value = value;
	currentfn->string_variables[currentfn->string_variables_length] = (*aux);
	currentfn->string_variables_length++;
	return 0;
}



int addFile(char * name){
 if(!existsFile(name)){
 	movements_files[movements_files_length] = name;
 	movements_files_length++;
 	return 0;
 }
 return 1;
}

int updateInt(char * name, int value){
	if(!existsInt(name)){
		return 1;
	}
	for(int i=0; i< currentfn->integer_variables_length ; i++){
		if(!strcmp(currentfn->integer_variables[i].name,name)){
			currentfn->integer_variables[i].value = value;
			return 0;
		}
	}
	return 1;
}

int updateBoolean(char * name, int value){
	if(!existsBoolean(name)){
		return 1;
	}
	if(value == 0 || value == 1){
		for(int i=0; i< currentfn->boolean_variables_length ; i++){
			if(!strcmp(currentfn->boolean_variables[i].name,name)){
				currentfn->boolean_variables[i].value = value;
				return 0;
			}
		}
	}
	return 1;
}

int updateString(char * name, char * value){
	if(!existsString(name)){
		return 1;
	}
	for(int i=0; i< currentfn->string_variables_length ; i++){
		if(!strcmp(currentfn->string_variables[i].name,name)){
			currentfn->string_variables[i].value = value;
			return 0;
		}
	}
	return 1;
}


int main(){
	return 0;
}
