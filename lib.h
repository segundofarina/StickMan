#define FRAME_WIDTH 12
#define FRAME_HEIGHT 10
#define SCREEN_SPACES 12
#define ACTION_LENGTH 4
#define LEFT 1
#define RIGHT -1
#define FRONT 0


int executeaction(char * name , int direction);


typedef struct action {	
	char * name;
	char frames [ACTION_LENGTH][FRAME_HEIGHT][FRAME_WIDTH];
	int direction;
} action; 

