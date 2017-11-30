#define VARIABLES_QUANTITY 50
#define MAX_FUNCTION_NAME 50
#define FILES_QUANTITY 50
#define MAX_RETURN_TYPE 20

typedef struct int_var 
{
	char * name;
	int value;
}int_var; 

typedef struct boolean_var 
{
	char * name;
	int value;
} boolean_var;

typedef struct string_var
{
	char * name;
	char * value;
}string_var;

typedef struct parameter
{
	char * type;
	char * name;
	struct parameter * next;
} parameter;

typedef struct function
{
	char * name;
	char * returnType;
	parameter * parameters;

	int_var integer_variables[VARIABLES_QUANTITY];
	string_var string_variables[VARIABLES_QUANTITY];
	boolean_var boolean_variables[VARIABLES_QUANTITY];
//	struct function functions_variables[VARIABLES_QUANTITY];

	int integer_variables_length;
	int string_variables_length;
	int boolean_variables_length;
} function;

struct parameter * transform(char * parameters);

int cmpParams(parameter * p1, parameter * p2);

int existsFunction(char * name, char * returnType, char * parameters);

function * addFunction(char * name, char * returnType, char * parameters);

void currentFunction(char * name, char * returnType, char * parameters);

int existsInt(char * name);

int existsString(char * name);

int existsBoolean(char * name);

int existsFile(char * name);

int addInt(char * name, int value);

int addBoolean(char * name, int value);

int addString(char * name, char * value);

int addFile(char * name);

int updateInt(char * name, int value);

int updateBoolean(char * name, int value);

int updateString(char * name, char * value);