#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include <unistd.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#define SLEEP_MS 300


action * actions;
int actionsLen=0;

int position=0;
int direction= FRONT;

int lineno=0;

int isVariable (char * string){
	 	int status;
  	regex_t re;

    if (regcomp(&re, "[a-zA-Z]([a-zA-Z0-9_])*", REG_EXTENDED|REG_NOSUB) != 0) {
        return(0);      /* Report error. */
    }
    status = regexec(&re, string, (size_t) 0, NULL, 0);
    regfree(&re);
    if (status != 0) {
        return(0);      /* Report error. */
    }
    return(1);
}

void printMovement (char movement [ACTION_LENGTH][FRAME_HEIGHT][FRAME_WIDTH], int position, int direction){
	int i,j,k,l;
	int offset = FRAME_WIDTH*(SCREEN_SPACES - position);
	if(position > SCREEN_SPACES){
		printf("Inavlid postion\n");
		return ;
	}


	char * spaces = malloc(position*FRAME_WIDTH+1);
	for(k=0; k<position*FRAME_WIDTH ;k++){
		spaces[k]=' ';
	}
	spaces[k]=0;

	for (i=0; i<ACTION_LENGTH ;i++){
		if( direction == RIGHT ){
			if(i%2){
				strcat(spaces,"  ");
			}else{
				strcat(spaces," ");
			}
		}else if( direction == LEFT && position !=0){
			if(i%2){
				spaces+=1;
			}else{
				spaces+=2;
			}
		}
		for(j=0; j<FRAME_HEIGHT; j++){

			printf("%s", spaces );
			for(int k=0 ; k< FRAME_WIDTH; k++){
				printf("%c",movement[i][j][k]);
			}
			printf("\n");
		}
		sleep_ms(SLEEP_MS);
		system("clear");

	}
}


int getNextLine(FILE * fp, char ** var){
	int c,i=0;
	char * line = malloc(MAX_LENGTH_NAME);

	while( (c= fgetc(fp)) != '\n' && c!=EOF){
		if(i < MAX_LENGTH_NAME*2 ){

			line[i++]=c;

		}
	}
	line[i]=0;
	*var=line;
	lineno++;
	return c;
}



int fillHeader(FILE * fp ,action * a){
	int ans;
	char * var;
	char * attr;
	ans = getNextLine(fp,&var);
	if (strcmp(var, "") == 0){
		printf("There is no header for action\n" );
		return ERROR;
	}
	strtok_r (var, "[", &attr);

	if( isVariable(var) ){
					a->name =malloc(strlen(var));
					strcpy(a->name,var);
	}else {
		printf("Not a valid name for library input: %s . \n",var );
		return ERROR;
	}


	if ( strcmp(attr,"right]" ) == 0){
		a->direction = RIGHT;
	}else if ( strcmp(attr,"left]" ) == 0){
		a->direction = LEFT;
	}else if ( strcmp(attr,"front]" ) == 0){
		a->direction = FRONT;
	}else {
		printf( "Not a valid attrbute for library input: %s in line %d\n",attr,lineno);
		return ERROR;
	}
	return ans;



}


int fillFrames(FILE * fp ,action * a){
	char c;
	int i,j,len,ans;
	for (i = 0; i< ACTION_LENGTH ;i++){
		for(j = 0; j< FRAME_HEIGHT; j++){
			char * line;
			ans=getNextLine(fp,&line);
			len=strlen(line);
			if (len <= FRAME_WIDTH){
				memcpy(a->frames[i][j],line,FRAME_WIDTH);
				//Complete rest of the line with ' '
				while(len!=FRAME_WIDTH ){
					a->frames[i][j][len++]=' ';
				}
			}else{
				printf("Wrong number of characters in line %d. Expected %d but recieved %lu : %s \n",lineno,FRAME_WIDTH, strlen(line),line);
				return ERROR;
			}
			free(line);

		}
	}
	return ans;
}


int openActions(char * fileRoute){
	int ans,quantity,i;
	char * buffer;
	FILE *fp = fopen(fileRoute, "r");
	if(fp == NULL){
		printf("not a valid route\n");
		return ERROR;
	}
	
	getNextLine(fp,&buffer);
	quantity= atoi(buffer);
	if(quantity == 0){
		printf("First line must be a number indicating the number of actions expected a number but recieved %s\n",buffer);
		return ERROR;
	}

	for ( i=0; ans!=EOF && ans!= ERROR && i<quantity ;i++  ){
		action a;
		ans=fillHeader(fp, &a);
		if( ans == ERROR){
			break;
		}
		ans=fillFrames(fp, &a);

		if (ans != ERROR){
			printf("Name: %s direction: %d \n",a.name,a.direction );

			actions= realloc( actions, sizeof(action)*(actionsLen+1) );
			memcpy( &(actions[actionsLen]) , &a , sizeof(action) );
			actionsLen++;
		}
	}
	if( ans == ERROR || i!= quantity){
		printf("ERROR\n");
		return ERROR;
	}
	fclose(fp);
	return 0;
}

int isValidAction(char * name , int dir){
	int i;
	for(i=0 ; i<actionsLen; i++){
		if(strcmp(name, actions[i].name) == 0 && actions[i].direction == dir){
			return i;
		}
	}
	return -1;
}

int getPosition(){
	return position;
}
int getDirection(){
	return direction;
}

void movePosition(int dir ){
	if (dir == RIGHT){
		if(position < SCREEN_SPACES){
			position+=1;
		}
		direction = RIGHT;
	}else if( dir == LEFT){
		if(position > 0){
			position-=1;
		}
		direction = LEFT;
	}else if (dir == FRONT){
		direction = FRONT;
	}
}


int executeaYield(char * string){
 return 1;
}

int executeaction(char * name , int dir){
	int i;
	if((i=isValidAction(name,dir)) >= 0 ) {
		printMovement( actions[i].frames, position ,actions[i].direction);
		movePosition(dir);
		return 0;
	}
	return ERROR;
}
int executeaction2(char * name , int dir , int position){
	int i;
	if((i=isValidAction(name,dir)) >= 0 ) {
		printMovement( actions[i].frames, position ,actions[i].direction);
		movePosition(dir);
		return 0;
	}
	return ERROR;
}


int main(int argc, char const *argv[]){
	
	int error;
	error= openActions("other.stickLib");
		if(error != ERROR){
			 //executeaction("walk", RIGHT);
			 //executeaction("walk", RIGHT);
			 //executeaction("walk", RIGHT);
			 //executeaction("walk", RIGHT);
			 //executeaction("walk", RIGHT);
			 //executeaction("walk", RIGHT);
			 printf("Press 'y' characther to print all actions\n" );
			 int ans =getchar();
			 if(ans == 'y'){
			 for (int i =0 ; i< actionsLen ; i++){
				 executeaction(actions[i].name, actions[i].direction);
			 }
		 }
			// executeaction("walk", LEFT);
			// executeaction("walk", LEFT);
			// executeaction("walk", LEFT);
}



	return 0;
}
