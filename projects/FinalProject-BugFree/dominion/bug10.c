/******************************************************************************************
Bug #10

In the dominion.c cardEffect function, ambassador case, line 1100 to 1106, the program goes through the
currentPlayer's hand, and tries to find copies of choice1 card. In this loop, if the i-th card is not
"ambassador", the same kind of card as the choice1-th card and "i != choice1", count up "j". But this line
compares the position "i" with the card in choice1-th position. 

bug10.c 
gcc -o bug10 bug10.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99


**********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main () 
{
   int player1 = 0;
   //int player1; no have to set to 0
   int seed = 1000;
   int numPlayer = 2;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;


   printf("*****Begin test for ambassador bug 10 *****\n");
   memset(&G, 23, sizeof(struct gameState));
   //initialize the game
   initializeGame(numPlayer, k, seed, &G);
   
   //set current player as player1
   //player gets 5 cards
    G.handCount[player1] = 5;
    G.hand[player1][0] = copper;
    G.hand[player1][1] = copper;
    G.hand[player1][2] = gold;
    G.hand[player1][3] = gold;
    G.hand[player1][4] = ambassador;

    int result = cardEffect(ambassador, 3, 2, 0, &G, 4, 0);

    if (result == 0)
    {
        printf("**** Expect: 0 , Actual: %d: Passes **** \n", result);
    }
    else
    {
        printf("**** Expect: 0 , Actual: %d:  Fails **** %d\n", result);
    }

    printf("******End Bug 10 Test for ambassador card *********  \n");
}