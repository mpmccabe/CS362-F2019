/*********************************************************************************
Bug #8
The number of bonus coins from actions does not appear to be recorded correctly in cardEffect.
bug8.c 
gcc -o bug8 bug8.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99

**********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() 
{

    //variables 
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state;

    //initialize game
    initializeGame(2, k, seed, &state);

	printf("\n**** Begin Test of cardEffect bonus cards function ****\n");
    return 0;
}
