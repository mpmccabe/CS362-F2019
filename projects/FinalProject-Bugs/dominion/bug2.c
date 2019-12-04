/*********************************************************************************

Bug #2
For the Mine switch statement in the cardEffect function (around line 821),
it seems that it checks the cost of the card they trash against the cost of
the card they want to buy incorrectly. It looks like if the cost of the
treasure that they choose to trash plus 3, is greater than the cost of the
card they want to buy, then it will return -1.

**********************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {

    //variables
    int seed = 1000;
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
    struct gameState state, test;
    int currentPlayer = 0;
    int handPos = 2;
    int choice1 = 0;
    int choice2 = 4;
    int choice3 = 0;
    int bonus = 0;
    int numPlayers = 2;

    //initialize game
    initializeGame(numPlayers, k, seed, &state);

    printf("\n**** Begin Test of Mine case ****\n");

    state.hand[currentPlayer][0] = silver;
    state.hand[currentPlayer][1] = silver;
    state.hand[currentPlayer][2] = mine;
    state.handCount[currentPlayer] = 3;

    memcpy(&test, &state, sizeof(struct gameState));

    int output = cardEffect(mine, choice1, choice2, choice3, &test, handPos, &bonus);

   if (output == -1) {
        printf("Test Failed!\n");
    }
    else {
        printf("Test Passed!\n");
    }

    printf("\n******* End Test of Mine case  ***********\n");

    return 0;
}