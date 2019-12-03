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

    int currentPlayer = 0;

	printf("\n**** Begin Test of cardEffect bonus cards function ****\n");

    
    // set a player's hand to have a baron card and an estate card
    state.hand[currentPlayer][0] = baron;
    state.hand[currentPlayer][1] = estate;
    
    int before_coins = state.coins;

    // play the baron card manually
    //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
    int return_status = cardEffect(baron, 1, 0, 0, &state, 0, 0);

    if (return_status < 0){
        printf("function failed call - revise logic\n");
        exit(1);
    }

    // get coinCount, save it
    int control_coins = state.coins;

    printf("before_coins: %d after_coins: %d\n", before_coins, control_coins);
    
    // reset game conditions
    // play the baron card through playCard
    // get coinCount
    // compare coinCount and assert if not equal

    //int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)




    return 0;
}
