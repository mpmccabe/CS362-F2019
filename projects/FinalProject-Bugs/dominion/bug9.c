/******************************************************************************************
Bug #9

Possible bug with the way duplicate "revealed cards" are handled for the Tribute card. If
tributeRevealedCards[0] is the same as tributeRevealedCards[1], the code sets tributeRevealedCards[1]
to -1. The loop that follows expects 2 entries in the array, which is fine - there are still two entries: index 0
contains the card and index 1 contains -1. What isn't fine is there is no condition to catch the -1. On the
trip through the loop it'll (hopefully correctly) identify the card in index 0 as a Treasure, Victory or Action.

bug9.c 
gcc -o bug9 bug9.c -g dominion.o rngs.o -Wall -fpic -coverage -lm -std=c99


**********************************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	//variables
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	int numPlayer = 2;
	int seed = 1000;
	struct gameState G;
	int i;

	//initialize game
	int j = initializeGame(numPlayer, k, seed, &G);

	printf("\n********Begin Test of Bug 9, Test Tribute to see if actions are awarded for duplicates*******\n\n");

	//first card is duchy
	G.handCount[1]= 5;
	for(i=0; i<5; i++){
		G.hand[1][i]=duchy;
}
	//second card is duchy 
	G.deckCount[1]=5;
	for(i=0; i< 5; ++i){
		G.deck[1][i] = duchy;
}


	int actions = G.numActions;
	G.whoseTurn=0;
	//test tribute for duplicate and actions awarded
	printf("*****Test tribute to see if actions are awarded when duplicate cards are shown*****\n");
		cardEffect(tribute,0,0,0,&G, 0, 0);
	if(G.numActions > actions){
		printf("Player awarded 2 actions when opponent shows duplicates: Test Fails  \n");
	}
	else{
		printf("No actions awarded: Test Passes  \n");
	}
	printf("\n");

	return 0;
} 



