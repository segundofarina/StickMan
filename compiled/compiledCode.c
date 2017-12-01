
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
#define eosL 0

 int main() { void workOut( ); void justDance( ); void keepSpinning( ); char * compiler_libraries[50]; int i = 0; compiler_libraries[i] = malloc(strlen( "other.stickLib+1")); strcpy(compiler_libraries[i++],"other.stickLib");compiler_libraries[i] = malloc(strlen( "lib.stickLib+1")); strcpy(compiler_libraries[i++],"lib.stickLib");initLibrary(compiler_libraries,0);int times = 5 ; while( times > 0 ) { if( direction == right ){ justDance( ) ; direction  = left ; } else{ workOut( ) ; } times -- ; } if( direction == right ){ executeAction( "roll" ); direction  = left ; executeAction( "roll" ); } else{ executeAction( "roll" ); } executeYield("I'll be back"); return 0; } void keepSpinning( ){ int spin = 5 ; while( spin > 0 ) { executeAction( "goesArroundComesArround" ); spin -- ; } } void justDance( ){ int spin = 5 ; executeAction( "walk" ); keepSpinning( ) ; executeAction( "jump" ); } void workOut( ){ executeAction( "weightLifting" ); direction  = right ; executeAction( "walk" ); executeAction( "weightLifting" ); } 