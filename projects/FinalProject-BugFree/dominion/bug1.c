/*********************************************************************************

Bug #1
The last discardCard function call within the mine case statement of the
cardEffect function are not actually trashing the cards. They are just being
put into the currentPlayers discard pile when the chosen card should be
trashed.

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
    int choice1 = copper;
    int choice2 = silver;
    int choice3 = 0;
    int bonus = 0;
    int numPlayers = 2;

    //initialize game
    initializeGame(numPlayers, k, seed, &state);

    printf("\n**** Begin Test of discardCard() function in mine ****\n");

    state.hand[currentPlayer][0] = silver;
    state.hand[currentPlayer][1] = silver;
    state.hand[currentPlayer][2] = mine;
    state.handCount[currentPlayer] = 3;

    memcpy(&test, &state, sizeof(struct gameState));

    int output = cardEffect(mine, choice1, choice2, choice3, &test, handPos, &bonus);

   if (test.playedCardCount == 0) {
        printf("Test Failed!\n");
    }
    else {
        printf("Test Passed!\n");
    }

    printf("\n******* End Test of discardCard() function in mine ***********\n");

    return 0;

}