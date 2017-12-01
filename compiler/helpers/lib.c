#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include <unistd.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#include "sleepfn.h"



action *actions;
int actionsLen = 0;

int manPosition = 0;
direction manDirection = LIB_FRONT;

int lineno = 0;

int isVariable(char *string)
{
	int status;
	regex_t re;

	if (regcomp(&re, "[a-zA-Z]([a-zA-Z0-9_])*", REG_EXTENDED | REG_NOSUB) != 0)
	{
		return (0); /* Report error. */
	}
	status = regexec(&re, string, (size_t)0, NULL, 0);
	regfree(&re);
	if (status != 0)
	{
		return (0); /* Report error. */
	}
	return (1);
}

char *getSpaces(int position)
{
	int k;
	char *spaces = malloc(position * FRAME_WIDTH + 1);
	for (k = 0; k < position * FRAME_WIDTH; k++)
	{
		spaces[k] = ' ';
	}
	spaces[k] = 0;
	return spaces;
}

char *editSpaces(char *spaces, direction dir, int position, int it)
{
	if (dir == LIB_RIGHT)
	{
		if (it % 2)
		{
			strcat(spaces, "  ");
		}
		else
		{
			strcat(spaces, " ");
		}
	}
	else if (dir == LIB_LEFT && position != 0)
	{
		if (it % 2)
		{
			spaces += 1;
		}
		else
		{
			spaces += 2;
		}
	}
	return spaces;
}

void printMovement(char movement[ACTION_LENGTH][FRAME_HEIGHT][FRAME_WIDTH], int position, direction dir)
{
	int i, j, k, l;
	char * spaces;

	if (position > SCREEN_SPACES)
	{
		printf("Inavlid postion\n");
		return;
	}
	spaces = getSpaces(position);

	for (i = 0; i < ACTION_LENGTH; i++)
	{
		spaces = editSpaces(spaces, dir,position, i);
		for (j = 0; j < FRAME_HEIGHT; j++)
		{

			printf("%s", spaces);
			for (int k = 0; k < FRAME_WIDTH; k++)
			{
				printf("%c", movement[i][j][k]);
			}
			printf("\n");
		}
		sleep_ms(SLEEP_MS);
		system("clear");
	}
	
	
}

int getNextLine(FILE *fp, char **var)
{
	int c, i = 0;
	char *line = malloc(MAX_LENGTH_NAME);

	while ((c = fgetc(fp)) != '\n' && c != EOF)
	{
		if (i < MAX_LENGTH_NAME * 2)
		{

			line[i++] = c;
		}
	}
	line[i] = 0;
	*var = line;
	lineno++;
	return c;
}

int fillHeader(FILE *fp, action *a)
{
	int ans;
	char *var;
	char *attr;
	ans = getNextLine(fp, &var);
	if (strcmp(var, "") == 0)
	{
		printf("line %d: There is no header for action\n",lineno);
		return ERROR;
	}
	strtok_r(var, "[", &attr);

	if (isVariable(var))
	{
		a->name = malloc(strlen(var));
		strcpy(a->name, var);
	}
	else
	{
		printf("line %d: Not a valid name for library input: %s . \n", lineno, var);
		return ERROR;
	}

	if (strcmp(attr, "right]") == 0)
	{
		a->direction = LIB_RIGHT;
	}
	else if (strcmp(attr, "left]") == 0)
	{
		a->direction = LIB_LEFT;
	}
	else if (strcmp(attr, "front]") == 0)
	{
		a->direction = LIB_FRONT;
	}
	else
	{
		printf("line %d: Not a valid attrbute for library input: %s\n", lineno, attr);
		return ERROR;
	}
	return ans;
}

int fillFrames(FILE *fp, action *a)
{
	char c;
	int i, j, len, ans;
	for (i = 0; i < ACTION_LENGTH; i++)
	{
		for (j = 0; j < FRAME_HEIGHT; j++)
		{
			char *line;
			ans = getNextLine(fp, &line);
			len = strlen(line);
			if (len <= FRAME_WIDTH)
			{
				memcpy(a->frames[i][j], line, FRAME_WIDTH);
				//Complete rest of the line with ' '
				while (len != FRAME_WIDTH)
				{
					a->frames[i][j][len++] = ' ';
				}
			}
			else
			{
				printf("Wrong number of characters in line %d. Expected %d but recieved %lu : %s \n", lineno, FRAME_WIDTH, strlen(line), line);
				return ERROR;
			}
			free(line);
		}
	}
	return ans;
}

int openActions(char *fileRoute)
{
	char dirWo [3][10]={"LEFT", "RIGHT","FRONT"};
	int ans, quantity, i;
	char *buffer;
	FILE *fp = fopen(fileRoute, "r");
	lineno = 0;
	if (fp == NULL)
	{
		printf("not a valid route\n");
		return ERROR;
	}

	getNextLine(fp, &buffer);
	quantity = atoi(buffer);
	if (quantity == 0)
	{
		printf("line %d: First line must be a number indicating the number of actions expected a number but recieved %s\n", lineno, buffer);
		return ERROR;
	}

	for (i = 0; ans != EOF && ans != ERROR && i < quantity; i++)
	{
		action a;
		ans = fillHeader(fp, &a);
		if (ans == ERROR)
		{
			break;
		}
		ans = fillFrames(fp, &a);
		if (ans == ERROR)
		{
			break;
		}
		if (existsAction(a.name, a.direction) >= 0)
		{
			printf("line %d: Action of name: %s and direction %d already exists. \n", lineno, a.name, a.direction);
			return ERROR;
		}

		printf("Succesful retrival Name: %s direction: %s \n", a.name, dirWo[a.direction]);
		actions = realloc(actions, sizeof(action) * (actionsLen + 1));
		memcpy(&(actions[actionsLen]), &a, sizeof(action));
		actionsLen++;
	}
	if (ans == ERROR || i != quantity)
	{
		printf("ERROR\n");
		return ERROR;
	}
	fclose(fp);
	return 0;
}

int existsActionNoDir(char *name)
{
	int i;
	for (i = 0; i < actionsLen; i++)
	{
		if (strcmp(name, actions[i].name) == 0 )
		{
			return i;
		}
	}
	//printf("FATAL ERROR: Action does not exist %s",name);
	return -1;
}

int existsAction(char *name, direction dir)
{
	int i;
	for (i = 0; i < actionsLen; i++)
	{
		if (strcmp(name, actions[i].name) == 0 && actions[i].direction == dir)
		{
			return i;
		}
	}
	return -1;
}

int getPosition()
{
	return manPosition;
}

int getDirection()
{
	return manDirection;
}

void setPosition(int pos)
{
	manPosition = pos;
}

void setDirection(direction dir)
{
	manDirection = dir;
}

void movePosition(int dir)
{
	if (dir == LIB_RIGHT)
	{
		if (manPosition < SCREEN_SPACES)
		{
			manPosition += 1;
		}
		dir = LIB_RIGHT;
	}
	else if (dir == LIB_LEFT)
	{
		if (manPosition > 0)
		{
			manPosition -= 1;
		}
		manDirection = LIB_LEFT;
	}
	else if (dir == LIB_FRONT)
	{
		manDirection = LIB_FRONT;
	}
}



void printYield(char * string, char movement[ACTION_LENGTH][FRAME_HEIGHT][FRAME_WIDTH], int position, direction dir)
{
	int i, j, k, l;
	char * spaces;

	if (position > SCREEN_SPACES)
	{
		printf("Inavlid postion\n");
		return;
	}
	spaces = getSpaces(position);

	for (i = 0; i < ACTION_LENGTH; i++)
	{
		spaces = editSpaces(spaces, dir,position, i);
		for (j = 0; j < FRAME_HEIGHT; j++)
		{

			printf("%s", spaces);
			if(j== 8){
				printf("%s",string);
			}
			for (int k = 0; k < FRAME_WIDTH; k++)
			{
				printf("%c", movement[i][j][k]);
			}
			printf("\n");
		}
		sleep_ms(SLEEP_MS);
		system("clear");
	}
}

int executeYield(char *string)
{	
	int i = existsAction("stand",LIB_FRONT);
	setDirection(LIB_FRONT);
	printYield( string, actions[i].frames, manPosition, manDirection);
	return 1;
}

int executeAction(char *name)
{
	int i;
	if ((i = existsAction(name, manDirection)) >= 0)
	{
		printMovement(actions[i].frames, manPosition, actions[i].direction);
		movePosition(manDirection);
		return 0;
	}
	return ERROR;
}
int executeaction2(char *name, int dir, int position)
{
	int i;
	if ((i = existsAction(name, dir)) >= 0)
	{
		printMovement(actions[i].frames, position, actions[i].direction);
		movePosition(dir);
		return 0;
	}
	return ERROR;
}

int initLibrary(char * * fileRoutes, int filesAmount){
	int error1, error2;
	error1 = openActions("./compiler/helpers/lib.stickLib");
	error2 = openActions("./compiler/helpers/other.stickLib");
	if (error1 == ERROR || error2 == ERROR)
	{
		return ERROR;
	}
	int error;

	for(int i = 0; i< filesAmount; i++){
		error = openActions(fileRoutes[i]);
		if(error == ERROR){
		return ERROR;
		}
	}
	return 0;
}


char ** toMatrix(char * yield){
	int length = strlen(yield);
	int mod;
	if(length < YIELD_WIDTH){
		char ** ans = malloc(sizeof(char *));
		ans[0] = yield;
		return ans;
	}
	mod = length%YIELD_WIDTH;
	if(!mod){
		mod = length/YIELD_WIDTH;
	}else{
		mod = length/YIELD_WIDTH + 1;
	}
	int j,k = 0;
	char ** ans = malloc(mod*sizeof(char *));
	for(int i = 0 ; i < mod ; i++){
		ans[i] = malloc((YIELD_WIDTH+1)*sizeof(char));
		for(j = 0; j < YIELD_WIDTH ; j++){
			ans[i][j] = yield[k++];
		}
		ans[i][j] = 0;
	}
	return ans;
}

int test(int argc, char const *argv[])
{

	int error1, error2;
	error1 = openActions("lib.stickLib");
	error2 = openActions("other.stickLib");
	if (error1 == ERROR || error2 == ERROR)
	{
		return ERROR;
	}

	executeAction("jump");
	//executeaction("walk", RIGHT);
	
	executeYield("HOLA FLORRCI UQUE PASA SI PONGO UN STRING MUY LARGO TIP @USKKDJSJKSD HSDHJS HJSDHJSD SDJH");
	executeYield("COMO ESTAS?");
	printf("Press 'y' characther to print all actions\n");
	int ans = getchar();
	if (ans == 'y')
	{
		for (int i = 0; i < actionsLen; i++)
		{
			executeAction(actions[i].name);
		}

		// executeaction("walk", LEFT);
		// executeaction("walk", LEFT);
		// executeaction("walk", LEFT);
	}

	return 0;
}
