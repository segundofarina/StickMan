#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"

static int_var integer_variables[50];
static double_var double_variables[50];
static string_var string_variables[50];

static int integer_variables_length = 0;
static int double_variables_length = 0;
static int string_variables_length = 0;



int existsInt(char * name){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			return 1;
		}
	}
	return 0;
}

int existsDouble(char * name){
	for(int i=0; i< double_variables_length ; i++){
		if(strcmp(double_variables[i].name,name) == 0){
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

int exists(char * name){
	if(existsInt(name) || existsDouble(name) || existsString(name)){
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

void addDouble(char * name, double value){
	double_var * aux = malloc( sizeof(double_var) );
	aux->name = name;
	aux->value = value;
	double_variables[double_variables_length] = (*aux);
	double_variables_length++;
}

void addString(char * name, char * value){
	string_var * aux = malloc( sizeof(string_var) );
	aux->name = name;
	strcpy(aux->value,value);
	string_variables[string_variables_length] = (*aux);
	string_variables_length++;
}

void add(char * type, char * name, void * value){
	if(exists(name)){
		printf("That variable already exists\n");
		return;
	}
	if(strcmp(type,"int")){
		addInt(name, (int)value);
	}else if(strcmp(type, "double")){
		//addDouble(name, (double)value);
	}else if(strcmp(type, "string")){
		addString(name, (char *)value);
	}
}


void updateInt(char * name, int value){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			integer_variables[i].value = value;
			return;
		}
	}
}

void updateDouble(char * name, double value){
	for(int i=0; i< double_variables_length ; i++){
		if(strcmp(double_variables[i].name,name) == 0){
			double_variables[i].value = value;
			return;
		}
	}
}

void updateString(char * name, char * value){
	for(int i=0; i< string_variables_length ; i++){
		if(strcmp(string_variables[i].name,name) == 0){
			strcpy(string_variables[i].value,value);
			return;
		}
	}
}

void update(char * name, void * value){

	if(existsInt(name)){
		updateInt(name,(int) value);
	}else if(existsDouble(name)){
		//updateDouble(name, (double)value);
	}else if(existsString(name)){
		updateString(name, (char *)value);
	}else{
		printf("variable undeclared\n");
	}
	
}

int getInt(char * name){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			return integer_variables[i].value;
		}
	}
}

double getDouble( char * name){
	for(int i=0; i< double_variables_length ; i++){
		if(strcmp(double_variables[i].name,name) == 0){
			return double_variables[i].value;
		}
	}
}

char * getString( char * name){
	for(int i=0; i< string_variables_length ; i++){
		if(strcmp(string_variables[i].name,name) == 0){
			return string_variables[i].value;
		}
	}
}

void * getValue(char * name){

	if( existsInt(name)){
		return (void *)getInt(name);
	}else if(existsDouble(name)){
		return (void *)getDouble(name);
	}else if(existsString(name)){
		return (void *)getString(name);
	}else{
		printf("variable undeclared\n");
		return (void *)0;
	}
}

void test(){
	return;
}

int main(){
	test();
	return 0;
}



