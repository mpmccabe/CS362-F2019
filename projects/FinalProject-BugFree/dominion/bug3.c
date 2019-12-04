/*********************************************************************************

Bug #3
In the remodel case within the cardEffect function, the if statement that
compares the two choice statements needs to be switched (around Line #846).

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
    int choice2 = 2;
    int choice3 = 0;
    int bonus = 0;
    int numPlayers = 2;

    //initialize game
    initializeGame(numPlayers, k, seed, &state);

    printf("\n**** Begin Test of Remodel case ****\n");

    state.hand[currentPlayer][0] = silver;
    state.hand[currentPlayer][1] = silver;
    state.hand[currentPlayer][2] = mine;
    state.handCount[currentPlayer] = 3;

    memcpy(&test, &state, sizeof(struct gameState));

    int output = cardEffect(remodel, choice1, choice2, choice3, &test, handPos, &bonus);

   if (output == 0) {
        printf("Test Failed!\n");
    }
    else {
        printf("Test Passed!\n");
    }

    printf("\n******* End Test of Remodel case ***********\n");

    return 0;

}