#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "minion"

void test_one(struct gameState G);
void test_two(struct gameState G);

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
    G.hand[thisPlayer][0] = minion;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = feast;

    /*hard set the other player's hand*/
    G.hand[thisPlayer + 1][0] = minion;
    G.hand[thisPlayer + 1][1] = copper;
    G.hand[thisPlayer + 1][2] = duchy;
    G.hand[thisPlayer + 1][3] = estate;
    G.hand[thisPlayer + 1][4] = feast;
    G.hand[thisPlayer + 1][5] = silver;
    G.hand[thisPlayer + 1][6] = gold;
    G.handCount[thisPlayer + 1] = 7;

    /* view hand */
    printf("----------------- Base Case ----------------\n");
    printf("Current playedCards: %d\n", G.playedCardCount);
    for (int p = 0; p < numPlayer; p++){
        printf("Current handcount for player %d: %d\n", p, G.handCount[p]);
        printf("Current deckcount: %d\n", G.deckCount[p]);
        printf("Current coins: %d\n", G.coins);
          for (int i = 0; i < G.handCount[p]; i++){
            printf("player: %d, card[%d]: %d\n", p, i, G.hand[p][i]);
        }
    }

    test_one(G);
    test_two(G);

}

void test_one(struct gameState G){
    struct gameState testG;

    printf("----------------- Test 1: %s ----------------\n", TESTCARD);
    printf("discard hand\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    minionEffect(0, 1, &testG, 0);

    printf("----------------- Test Case ----------------\n");
    int thisPlayer = 0;
    /*expectation: old hand has been discarded, new hand has been drawn (4 cards), player 2's hand changed to 4 cards */
    
    for (thisPlayer = 0; thisPlayer < testG.numPlayers; thisPlayer++){
        if (testG.handCount[thisPlayer] == 4){
            printf("Player %d's handcount == 4, test passed.\n", thisPlayer);
        }
        else{
            printf("Player %d's handcount is not equal to 4 Received %d. Test failed\n", thisPlayer, testG.handCount[thisPlayer]);
        }

    }
}
    

void test_two(struct gameState G){
    struct gameState testG;
   
    printf("----------------- Test 2: %s ----------------\n", TESTCARD);
    printf("choose coins hand\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    int numCoins =  testG.coins;
    minionEffect(1, 0, &testG, 0);
    
    printf("----------------- Test Case ----------------\n");
    printf("Current playedCards: %d\n", testG.playedCardCount);
    printf("Current coins: %d\n", testG.coins);

    if (numCoins + 2 != testG.coins){
        printf("Number of coins incorrectly added. Test failed. Expected :%d Actual: %d\n", numCoins + 2, testG.coins);
    }
    else{
        printf("Number of coins increased successfully. Test passed.\n");
    }

    if (testG.playedCardCount > 1){
        printf("Cards were discarded - test failed.\n");
    }
    else{
        printf("No cards were discarded other than minion. Test passed\n");
    }

}
