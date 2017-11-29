

typedef struct int_var 
{
	char * name;
	int value;
}int_var; 
#define VARIABLES_QUANTITY 50

typedef struct double_var 
{
	char * name;
	double value;
} double_var;

typedef struct string_var
{
	char * name;
	char * value;
}string_var;

/*

void add(char * type, char * name, void * value);

void update(char * name, void * value);

void * getValue(char * name);

*/

int existsInt(char * name);

int existsDouble(char * name);

int existsString(char * name);

int exists(char * name);

void addInt(char * name, int value);

void addDouble(char * name, double value);

void addString(char * name, char * value);

void updateInt(char * name, int value);

void updateDouble(char * name, double value);

void updateString(char * name, char * value);

int getInt(char * name);

double getDouble( char * name);

char * getString( char * name);

void testString();

void testInteger();

void testDouble();