#include <stdlib.h>
#include <stdio.h>
#include "lib.h"
#include <unistd.h>
#include <string.h>


char left [5][FRAME_WIDTH][FRAME_HEIGHT];




void printMovement (char movement [5][FRAME_WIDTH][FRAME_HEIGHT], int position){
	int i,j,k,l;

	char spaces[120]={0};
		for(k=0; k<position ;k++){
			strcat(spaces,"          ");
		}

for (l=1 ;l<3 ;l++){

	for (i=0; i<ACTION_LENGTH ;i++){
		char offset[10]={0};
		for(j=0; j<FRAME_HEIGHT; j++){
			printf("%s",spaces+(i+l*ACTION_LENGTH) );
			for(int k=0 ; k< FRAME_WIDTH; k++){
				printf("%c",left[i][j][k]);
			}
			printf("\n");
		}
		sleep(1);
		system("clear");
	
	}
}
}


int main(int argc, char const *argv[])
{
	int i,j,c;
	FILE *fp;
	fp=fopen("lib.stickLib", "r");

	for (i=0; i<5 ;i++){
		for(j=0; j<10; j++){
			for(int k=0 ;(c =fgetc(fp)) != '\n' && k< 10; k++){
				printf("%c",c );
				left[i][j][k]=c;
			}
			printf("\n");
		}
	
	}
		fclose(fp);

		for(i=5; i>0;i--){
		printMovement(left,i);
	}
	return 0;
}



