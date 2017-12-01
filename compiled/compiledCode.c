
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

 int main() { void start( ); char * compiler_libraries[50]; int i = 0; initLibrary(compiler_libraries,0);executeAction( "moveleftarm" ); executeYield("Look at me! I'm Mr Meeseeks"); executeAction( "moverightarm" ); direction  = right ; executeYield("walk with me..."); direction  = right ; while( position != eosR ) { executeAction( "walk" ); } executeYield("how about a little workout??"); int times = 3 ; while( times != 0 ) { executeAction( "weightLifting" ); times = times - 1 ; } executeYield("or some squats"); times = 3 ; while( times != 0 ) { executeAction( "squat" ); times = times - 1 ; } direction  = left ; executeAction( "roll" ); executeYield("like a ride by bike?"); executeAction( "ridingBike" ); executeYield("oh fuck"); executeYield("doesn't matter"); executeAction( "goesArroundComesArround" ); executeYield("do you know this one?"); times = 3 ; while( times != 0 ) { executeAction( "headsholders" ); times = times - 1 ; } executeYield("let's go back"); direction  = left ; times = 3 ; while( times != 0 ) { executeAction( "jumpwalk" ); times = times - 1 ; } executeYield("what a day"); executeYield("Goodbye!!"); executeAction( "moveleftarm" ); executeAction( "moverightarm" ); return 0; } 