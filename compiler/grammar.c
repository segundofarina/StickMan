#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"


static int_var integer_variables[50];

static int integer_variables_length = 0;
/*
typedef struct double_var 
{
	char * name;
	double value;
} double_var;

typedef struct string_var
{
	char * name;
	char * value;
};
*/

//double_var double_variables[50];
//string_var string_variables[50];


//int double_variables_length = 0;
//int string_variables_length = 0;


void add(char * name, int value){
	int_var * aux = malloc( sizeof(int_var) );
	aux->name = name;
	aux->value = value;
	integer_variables[integer_variables_length] = (*aux);
	integer_variables_length++;
}

int update(char * name, int value){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			integer_variables[i].value = value;
			return 1;
		}
	}
	return 0;
}

int getValue(char * name){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			return integer_variables[i].value;
		}
	}
	return 0;
}

/*
int main(){
	add("martincito", 4);
	add("segundito", 5);
	add("florci", 4);
	printf("%d\n", getValue("florci"));
	printf("%d\n", getValue("martincito"));
	printf("%d\n", getValue("segundito"));
	update("florci", 10)
	printf("%d\n", getValue("florci"));
	return 0;
}
*/
/*

void addDouble(char * name, double * value){
	double_var * aux = malloc( sizeof(double_var) );
	aux->name = name;
	aux->value = value;
	double_variables[double_variables_length] = aux;
	double_variables_length++;
}

void addString(char * name, char * value){
	double_var * aux = malloc( sizeof(double_var) );
	aux->name = name;
	aux->value = value;
	string_variables[string_variables_length] = aux;
	string_variables_length++;
}

int updateDouble(char * name, double value){
	for(int i=0; i< double_variables_length ; i++){
		if(strcmp(double_variables[i]->name,name) == 0){
			double_variables[i]->value = value;
			return 1;
		}
	}
	return 0;
}

int updateString(char * name, char * value){
	for(int i=0; i< string_variables_length ; i++){
		if(strcmp(string_variables[i]->name,name) == 0){
			strcpy(string_variables[i]->value,value);
			return 1;
		}
	}
	return 0;
}

void update( char * name, void * value){
	int is_integer_variable = 0;
	int is_double_variable = 0;
	int is_string_variable = 0;

	is_integer_variable = updateInteger(name, (int)value);

	if(is_integer_variable == 1){
		return;
	}
	is_double_variable = updateDouble(name , (double)value);
	
	if(is_double_variable == 1){
		return;
	}

	is_string_variable = updateString(name , (char * )value);
	
	if(is_string_variable == 1){
		return;
	}
	exit(1);
}

void add( char * type, char * name, void * value){
	switch(type){
		case 'int':
			addInt(name,(int) value); break;
		case 'double':
			addDouble(name,(double) value); break;
		case 'string':
			addString(name,(char *) value); break;
	}
}


*/

