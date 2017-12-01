
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../compiler/helpers/lib.h"
extern int manPosition;
extern direction manDirection;
#define left LIB_LEFT
#define right LIB_RIGHT
#define position manPosition
#define direction manDirection
#define eosR SCREEN_SPACES
#define esoL 0

int main()
{
    void checkEndOfScreen();
    void say(char *str);
    int isPar();
    void moveAndJump();
    char *compiler_libraries[50];
    int i = 0;
    compiler_libraries[i] = malloc(strlen("yourFile.stickLib+1"));
    strcpy(compiler_libraries[i++], "yourFile.stickLib");
    initLibrary(compiler_libraries, 0);
    int repetitions = 0;
    say("hola!");
    char *var;
    ;
    while (repetitions < 15)
    {
        checkEndOfScreen();
        if (isPar())
        {
            moveAndJump();
        }
        else
        {
            ;
        }
        repetitions++;
    }
    say("chau!");
    return 0;
}
void moveAndJump() { ; }
int isPar()
{
    if (position % 2 == 0)
    {
        return 0;
    }
    return 1;
}
void say(char *str) { executeYield(str); }
void checkEndOfScreen()
{
    if (position == eosR)
    {
        direction = left;
    }
    if (position == eosL)
    {
        direction = right;
    }
}