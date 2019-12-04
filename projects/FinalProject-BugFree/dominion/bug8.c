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
    state.hand[currentPlayer][2] = copper;
    state.handCount[currentPlayer] = 3;
    updateCoins(currentPlayer, &state, 0);

    // record the coins before
    int before_coins = state.coins;

    // copy state of the game
    struct gameState testG;
    memcpy(&testG, &state, sizeof(struct gameState));

    // play the baron card manually
    //int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
    int return_status = cardEffect(baron, 1, 0, 0, &state, 0, 0);

    if (return_status < 0){
        printf("cardEffect() function failed call - revise logic\n");
        exit(1);
    }

    // get coinCount, save it
    int control_coins = state.coins;

    printf("cardEffect() before_coins: %d control_coins: %d\n", before_coins, control_coins);
    
    // reset game conditions

    // play the baron card through playCard
    //int playCard(int handPos, int choice1, int choice2, int choice3, struct gameState *state)
    return_status = playCard(0, 1, 0, 0, &testG);

     if (return_status < 0){
        printf("playCard() function failed call - revise logic\n");
        exit(1);
    }

    // get coinCount
    int after_coins = testG.coins;

    // compare coinCount and assert if not equal
    printf("playCard() before_coins: %d after_coins: %d\n", before_coins, after_coins);

    if (control_coins != after_coins){
        printf("control coins does not equal after coins. test failed.\n");
    } else{
        printf("control coins equals after coins. test passed\n");
    }

    printf("**** End Test of cardEffect bonus cards function ****\n");

    return 0;
}
