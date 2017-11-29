#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFigure(char * figure[] , int position){
	int j,k;
	for (j = 0; j < 3; ++j)
	{
		char spaces[120]={0};
		for(k=0; k<position ;k++){
			strcat(spaces,"      ");
		}
		printf("%s%s\n",spaces,figure[j]);
	}
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	
	sleep(1);
	system("clear");
}








void barrellroll(void){	

char * barrell[12][3];

barrell[0][0]=" \\ o / " ;  
barrell[0][1]="   |   "  ;
barrell[0][2]="  / \\  " ;

barrell[1][0]=" _ o  " ;  
barrell[1][1]="  /\\"  ;
barrell[1][2]=" | \\" ;

barrell[2][0]="       " ;  
barrell[2][1]="  ___\\o"  ;
barrell[2][2]=" /)  | " ;

barrell[3][0]="__|  " ;  
barrell[3][1]="  \\o "  ;
barrell[3][2]="  ( \\" ;

barrell[4][0]=" \\ / " ;  
barrell[4][1]="  |  "  ;
barrell[4][2]=" /o\\ " ;

barrell[5][0]="  |__";
barrell[5][1]="o/   ";
barrell[5][2]="/ )  ";

barrell[6][0]="     "; 
barrell[6][1]="o/__ "; 
barrell[6][2]="|  (\\";  

barrell[7][0]="o _  ";
barrell[7][1]="/\\   "; 
barrell[7][2]=" / | ";

barrell[8][0]="\\ o /"; 
barrell[8][1]="  |  ";
barrell[8][2]=" / \\ ";

barrell[9][0]="  o  ";
barrell[9][1]=" /|\\ ";
barrell[9][2]=" / \\ ";
int i,j,k;
for (i = 0; i < 10; ++i){
	printFigure(barrell[i], i);
}
}



int main(){
	int i = 0;
	while(i<20) {
		barrellroll();
		i++;
	}
	

	return 0;
	
}
