#define VARIABLES_QUANTITY 50
#define MAX_FUNCTION_NAME 50
#define FILES_QUANTITY 50

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
	char * name;
	struct parameter * next;
} parameter;

typedef struct function
{
	char * name;
	char * returnType;
	parameter * parameters;
} functions;



int existsInt(char * name);

int existsString(char * name);

int existsBoolean(char * name);

int existsVariable(char * name);

int existsFunction(char * name, char * returnType, char * parameters);

void addInt(char * name, int value);

void addBoolean(char * name, int value);

void addString(char * name, char * value);

void addFunction(char * name, char * returnType, char * parameters);

void updateInt(char * name, int value);

void updateBoolean(char * name, int value);

void updateString(char * name, char * value);

int getInt(char * name);

int getBoolean(char * name);

char * getString( char * name);

void testString();

void testInteger();

void testBoolean();
