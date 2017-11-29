#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grammar.h"

static int_var integer_variables[VARIABLES_QUANTITY];
static double_var double_variables[VARIABLES_QUANTITY];
static string_var string_variables[VARIABLES_QUANTITY];

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
	aux->value = value;
	string_variables[string_variables_length] = (*aux);
	string_variables_length++;
}
/*
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
*/

void updateInt(char * name, int value){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			integer_variables[i].value = value;
			return;
		}
	}
	printf("variable undeclared\n");
}

void updateDouble(char * name, double value){
	for(int i=0; i< double_variables_length ; i++){
		if(strcmp(double_variables[i].name,name) == 0){
			double_variables[i].value = value;
			return;
		}
	}
	printf("variable undeclared\n");
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
/*
void update(char * name, void * value){

	if(existsInt(name)){
		updateInt(name,(int) value);
	}else if(existsDouble(name)){
		updateDouble(name, (double)value);
	}else if(existsString(name)){
		updateString(name, (char *)value);
	}else{
		printf("variable undeclared\n");
	}
	
}
*/

int getInt(char * name){
	for(int i=0; i< integer_variables_length ; i++){
		if(strcmp(integer_variables[i].name,name) == 0){
			return integer_variables[i].value;
		}
	}
	return 0;
}

double getDouble( char * name){
	for(int i=0; i< double_variables_length ; i++){
		if(strcmp(double_variables[i].name,name) == 0){
			return double_variables[i].value;
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
/*
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
*/
void testString(){

	printf("TEST STRING\n");

	printf("%d\n", exists("florcilove"));

	addString("florcilove","FLORCI<3");
	printf("%d\n", exists("florcilove"));
	printf("%s\n", getString("florcilove"));

	updateString("florcilove","FLORCI");
	printf("%s\n", getString("florcilove"));

	addString("tincho","TINCHITO");
	printf("%s\n", getString("tincho"));

	updateString("tincho","TINCHO QUIERO COMER CLUB DE LA MILANESA");
	printf("%s\n", getString("tincho"));

	printf("%d\n", exists("tincho"));
	return;
}

void testInteger(){
	printf("TEST INTEGER\n");

	printf("%d\n", exists("florcilove"));

	addInt("florcilove",0);
	printf("%d\n", exists("florcilove"));
	printf("%d\n", getInt("florcilove"));

	updateInt("florcilove",1);
	printf("%d\n", getInt("florcilove"));

	addInt("tincho",4);
	printf("%d\n", getInt("tincho"));

	updateInt("tincho",5);
	printf("%d\n", getInt("tincho"));

	printf("%d\n", exists("tincho"));
	return;
}

void testDouble(){

	printf("TEST DOUBLE\n");

	printf("%d\n", exists("florcilove"));

	addDouble("florcilove",42.5);
	printf("%d\n", exists("florcilove"));
	printf("%g\n", getDouble("florcilove"));

	updateDouble("florcilove",43.0);
	printf("%g\n", getDouble("florcilove"));

	addDouble("tincho",4.0);
	printf("%g\n", getDouble("tincho"));

	updateDouble("tincho",5.5);
	printf("%g\n", getDouble("tincho"));

	printf("%d\n", exists("tincho"));
	return;
}
/*
int main(){

	testInteger();
	testDouble();
	testString();

	return 0;
}

*/
int main(){
	int flor = 1;
	int segundo = 2;
	int martin = flor + segundo;
	printf("%i\n", martin);
	return 0;
}


