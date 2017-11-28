

typedef struct int_var 
{
	char * name;
	int value;
}int_var; 


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



void add(char * type, char * name, void * value);

void update(char * name, void * value);

void * getValue(char * name);