/*********************************************************************************

Bug #5 
In the scoreFor function, the discardCount is being used for the deck count.
bug5.c 
gcc -o bug5 bug5.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99



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
    int currentScore = 0;
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState state;

    //initialize game
    initializeGame(2, k, seed, &state);

	printf("\n**** Begin Test of scoreFor function ****\n");

    //test variables and cards
    state.handCount[0] = 0;
    state.discardCount[0] = 0;
    state.deckCount[0] = 4;

    state.deck[0][0] = estate;
    state.deck[0][1] = duchy;
    state.deck[0][2] = duchy;
    state.deck[0][3] = province;

    //calculate scoreFor 
    currentScore = scoreFor(0, &state);

    //assert correct victory points score
    
    printf("currentScore: %d\n", currentScore);
    if (currentScore == 13) {
        printf("scoreFor from deck count correct: PASSED\n");
    }
    else {
        printf("scoreFor deck count correct: FAILED\n");
    }

	printf("\n******* End Test of scoreFor function ***********\n");
    return 0;
}
