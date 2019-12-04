/*********************************************************************************

Bug #4
There is a bug in the isGameOver function. While checking if there are 3
cards with a card count of 0, it only loops through 25 cards.

**********************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main() {

    //variables
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState state, test;
    int currentPlayer = 0;
    int handPos = 2;
    int choice1 = 0;
    int choice2 = copper;
    int choice3 = 0;
    int bonus = 0;
    int numPlayers = 2;

    //initialize game
    initializeGame(numPlayers, k, seed, &state);

    printf("\n**** Begin Test of isGameOver() function ****\n");

    state.hand[currentPlayer][0] = silver;
    state.hand[currentPlayer][1] = silver;
    state.hand[currentPlayer][2] = mine;
    state.handCount[currentPlayer] = 3;

    memcpy(&test, &state, sizeof(struct gameState));

    int output = cardEffect(mine, choice1, choice2, choice3, &test, handPos, &bonus);

    if (output == 0) {
        printf("Test Failed!");
    }
    else if (output == -1) {
        printf("Test Passed!");
    }

    printf("\n******* End Test of isGameOver() function ***********\n");

    return 0;
}