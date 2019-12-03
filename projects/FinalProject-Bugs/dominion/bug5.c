#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "scoreFor()"

void test_one(struct gameState G, int thisPlayer);

int main(){
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                    sea_hag, tribute, smithy
                };

    int seed = 1100;
    int numPlayer = 2;
    int thisPlayer = 0;

    initializeGame(numPlayer, k, seed, &G);

    /*hard set the player's hand*/
    G.hand[thisPlayer][0] = baron;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    /* view hand */
    printf("----------------- Base Case ----------------\n");
    printf("Current handcount: %d\n", G.handCount[thisPlayer]);
    printf("Current deckcount: %d\n", G.deckCount[thisPlayer]);
    printf("Current discardCount: %d\n", G.discardCount[thisPlayer]);
    printf("Current coins: %d\n", G.coins);

    for (int i = 0; i < G.handCount[thisPlayer]; i++){
        printf("hand card[%d]: %d\n", i, G.hand[thisPlayer][i]);
    }

    for (int i = 0; i < G.deckCount[thisPlayer]; i++){
        printf("deck card[%d]: %d\n", i, G.deck[thisPlayer][i]);
    }

    for (int i = 0; i < G.discardCount[thisPlayer]; i++){
        printf("deck card[%d]: %d\n", i, G.discard[thisPlayer][i]);
    }

    test_one(G, thisPlayer);

    printf("----------------- Modified Case ----------------\n");
    printf("Current handcount: %d\n", G.handCount[thisPlayer]);
    printf("Current deckcount: %d\n", G.deckCount[thisPlayer]);
    printf("Current discardCount: %d\n", G.discardCount[thisPlayer]);
    printf("Current coins: %d\n", G.coins);
    G.hand[thisPlayer][3] = silver;

}

void test_one(struct gameState G, int thisPlayer){
    printf("----------------- Test 1: %s ----------------\n", TESTCARD);
   
}
