#define FRAME_WIDTH 12
#define FRAME_HEIGHT 20
#define SCREEN_SPACES 12
#define ACTION_LENGTH 8
#define ERROR -100
#define MAX_LENGTH_NAME 100




#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}

typedef enum {LEFT, RIGHT, FRONT} direction;

int executeaction(char * name , int direction);

int existsAction(char * name , int dir);

typedef struct action {
	char * name;
	char frames [ACTION_LENGTH][FRAME_HEIGHT][FRAME_WIDTH];
	int direction;
} action;
