Name: walk direction: 0 
Name: walk direction: 1 
Name: jump direction: 2 
Name: stand direction: 2 
Name: roll direction: 1 
Name: roll direction: 0 
Name: weightLifting direction: 2 
Name: ridingBike direction: 1 
Name: goesArroundComesArround direction: 2 
Name: headsholders direction: 2 
Name: jumpwalk direction: 1 
Name: jumpwalk direction: 0 
Name: squat direction: 2 
Name:   squatwalk direction: 1 
Name: squatwalk direction: 0 
Name: moveleftarm direction: 2 
Name: moverightarm direction: 2 
 #include <stdio.h>
int main() { int repetitions = 0 ; say( "hola!" ) ; while( repetitions < 15 ) { checkEndOfScreen( ) ; if( isPar( ) ){ moveAndJump( ) ; } else{ executeAction( "walk" ); } repetitions ++ ; } say( "chau!" ) ; return 0; } void moveAndJump( ){ FATAL ERROR: Action does not exist walkjumpFATAL ERROR: Action does not exist jumpjump; } int isPar( ){ if( position % 2 == 0 ){ return 0 ; } return 1 ; } void say( char * str ){ executeYield(str); } void checkEndOfScreen( ){ if( position == eosR ){ direction  = left ; } if( position == eosL ){ direction  = right ; } } 