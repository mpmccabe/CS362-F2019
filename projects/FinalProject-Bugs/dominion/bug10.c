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

int main (int argc, char** argv) 
{
   int player1;
   int seed = 1000;
   int numPlayer = 2;
   int bonus = 0;
   int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
   struct gameState G;

   //initialize the game
   initializeGame(numPlayer, k, seed, &G);
   
   //set current player as player1
   player1 = whoseTurn(&G);

   //give player1 an ambassador card 
   gainCard(ambassador, &G, 2, player1);

   //give player1 2 similar cards
   gainCard(duchy, &G, 2, player1);
   gainCard(duchy, &G, 2, player1);

   //save preSupply total 
   int preSupply = G.supplyCount[duchy];

   //play ambassador card
   cardEffect(ambassador, duchy, 2, 0, &G, 0, &bonus);

   //save postSupply total
   int postSupply = G.supplyCount[duchy];

   if(postSupply == preSupply + 2){
       
       printf("  preSupply total: %d\n", preSupply);
       printf("  postSupply total: %d\n", postSupply);
	   printf("**** Passes**** \n");
   }
   else{
       
       printf("  preSupply total: %d\n", preSupply);
       printf("  postSupply total: %d\n", postSupply);
	   printf("**** Fails**** \n");
   }


   return 0;
}