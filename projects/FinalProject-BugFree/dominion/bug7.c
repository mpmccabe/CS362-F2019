/******************************************************************************************
Bug #7

Tribute card bug around line 1075 in dominion.c . The for loop overruns the array. 
The tributeRevealedCards array has two elements and the loop is written to iterate 3 times.

bug7.c 
gcc -o bug7 bug7.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99


**********************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int anotherGame(struct gameState* G)
{
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	

    initializeGame(2, k, 1, G);
    G->hand[0][0] = tribute;
    G->deckCount[1] = 2;
    G->deck[1][0] = mine;
    G->deck[1][1] = baron;
    G->numActions = 0;
}

int main()
{
    struct gameState G;
    anotherGame(&G);
    int* bonus;
    printf("Test Bug #7, case tribute, in cardEffect function \n");
    //int cur_actions = G.numActions;
	int currentActions = G.numActions;
    printf("Expect current player to have 4 actions when tribute's played \n"); //4 actions are 2 iterations
    cardEffect(tribute, -1, -1, -1, &G, 0, bonus);
    if(G.numActions != 4){
        printf("Actions total wrong. Actions = %d\n", G.numActions);  //if 6 then 3 iterations and wrong
    }
    else{
        printf("Test Passes.\n");
    }

    
}


