#ifndef __lib_h__
#define __lib_h__

#define FRAME_WIDTH 12
#define FRAME_HEIGHT 20
#define SCREEN_SPACES 12
#define ACTION_LENGTH 8
#define ERROR -100
#define MAX_LENGTH_NAME 100
#define SLEEP_MS 300
#define YIELD_WIDTH 20


typedef struct action {
	char * name;
	char frames [ACTION_LENGTH][FRAME_HEIGHT][FRAME_WIDTH];
	int direction;
} action;

typedef enum {LIB_LEFT, LIB_RIGHT, LIB_FRONT} direction;




int executeAction(char * name);

int executeYield(char *string);

int initLibrary(char * * fileRoutes, int filesAmount);

int initLibraryCompiler(char * * fileRoutes, int filesAmount);

int existsAction(char * name , direction dir);

int existsActionNoDir(char *name);

int getPosition();

int getDirection();

void setPosition(int pos);

void setDirection(direction dir);

#endif