#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "mine"

int main(){
    struct gameState G, testG;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy
                };
    
    int seed = 1100;
    int numPlayer = 2;
    int thisPlayer = 0;

    initializeGame(numPlayer, k, seed, &G);

    /*hard set the player's hand*/
    G.hand[thisPlayer][0] = mine;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    /* view hand */
    printf("----------------- Base Case ----------------\n");
    printf("Current handcount: %d\n", G.handCount[thisPlayer]);
    printf("Current deckcount: %d\n", G.deckCount[thisPlayer]);
    for (int i = 0; i < G.handCount[thisPlayer]; i++){
        printf("card[%d]: %d\n", i, G.hand[thisPlayer][i]);
    }
    
    printf("----------------- Test 1: %s ----------------\n", TESTCARD);
    printf("swap copper for silver\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    int hand_pos = 1;
    int return_status = mineEffect(hand_pos, silver, &testG, hand_pos);
    printf("mineEffect return status: %d\n", return_status);

    if(testG.hand[thisPlayer][1] == silver){
        printf("Copper replaced with silver. Test Pass\n");
    }
    else{
        printf("Copper not replaced, test failed\n");
    }
    
    printf("----------------- Test 2: %s ----------------\n", TESTCARD);
    printf("swap copper for gold\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    hand_pos = 1;
    return_status = mineEffect(hand_pos, gold, &testG, hand_pos);
    printf("mineEffect return status: %d\n", return_status);

    if(testG.hand[thisPlayer][1] == copper){
        printf("Copper not replaced with gold. Test Pass\n");
    }
    else if (testG.hand[thisPlayer][1] == gold){
        printf("Copper replaced with gold, test failed\n");
    }
    else{
        printf("Copper replaced with something else, test failed\n");
    }
 
}