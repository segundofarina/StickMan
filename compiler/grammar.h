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

	int integer_variables_length;
	int string_variables_length;
	int boolean_variables_length;
} function;

// Returns 1 if exists and 0 if it doesn't
int existsFunction(char * name, char * returnType, char * parameters);

// Returns a the recently added function or 0 if it already existed
function * addFunction(char * name, char * returnType, char * parameters);


void currentFunction(char * name, char * returnType, char * parameters);

// Returns 0 if it doesn't exists and 1 if it does exists
int existsInt(char * name);

// Returns 0 if it doesn't exists and 1 if it does exists
int existsString(char * name);

// Returns 0 if it doesn't exists and 1 if it does exists
int existsBoolean(char * name);

// Returns 0 if it doesn't exists and 1 if it does exists
int existsFile(char * name);

// Return 0 if it has been added and 1 if it already existed
int addInt(char * name, int value);

// Return 0 if it has been added and 1 if it already existed
int addBoolean(char * name, int value);

// Return 0 if it has been added and 1 if it already existed
int addString(char * name, char * value);

// Return 0 if it has been added and 1 if it already existed
int addFile(char * name);

// Return 0 if it has been updated and 1 if it already existed
int updateInt(char * name, int value);

// Return 0 if it has been updated and 1 if it already existed
int updateBoolean(char * name, int value);

// Return 0 if it has been updated and 1 if it already existed
int updateString(char * name, char * value);