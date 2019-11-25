#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "ambassador"

void test_one(struct gameState G);
void test_two(struct gameState G);
void test_three(struct gameState G);
void test_four(struct gameState G);

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
    G.hand[thisPlayer][0] = ambassador;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = estate;
    G.hand[thisPlayer][3] = estate;
    G.hand[thisPlayer][4] = estate;


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
    test_three(G);
    test_four(G);
}

void test_one(struct gameState G){
    struct gameState testG;

    printf("----------------- Test 1: %s ----------------\n", TESTCARD);
    printf("choose 2 cards to return to supply\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    int numPlayer = testG.numPlayers;
    for (int p = 0; p < numPlayer; p++){
        printf("Current handcount for player %d: %d\n", p, testG.handCount[p]);
        printf("Current deckcount: %d\n", testG.deckCount[p]);
          for (int i = 0; i < testG.handCount[p]; i++){
            printf("player: %d, card[%d]: %d\n", p, i, testG.hand[p][i]);
        }
    }
    
    int discardedCard = testG.hand[0][2];
    ambassadorEffect(0, 2, 2, &testG, 0, 0);

    /* choice1 = hand#, choice2 = number to return to supply */
    printf("----------------- Test Results ----------------\n");
    for (int p = 0; p < numPlayer; p++){
        printf("Current handcount for player %d: %d\n", p, testG.handCount[p]);
        printf("Current deckcount: %d\n", testG.deckCount[p]);
        printf("Current discardCount: %d\n", testG.discardCount[p]);
        for (int i = 0; i < testG.handCount[p]; i++){
            printf("player: %d, card[%d]: %d\n", p, i, testG.hand[p][i]);
        }

        for (int i = 0; i < testG.discardCount[p]; i++){
            printf("player: %d, discard card[%d]: %d\n", p, i, testG.discard[p][i]);
        }
    }
    
    int testCount = testG.handCount[0];
    if (testCount == 2){
        printf("Player 0 handcount == 2. Test passed.\n");
    }
    else{
        printf("Player 0 handcount != 2. Expected 2: Actual %d\n", testG.handCount[0]);
    }

    if (testG.discardCount[1] == 0){
        printf("Player 2 never received discarded card. Test failed\n");
    }
    else if (testG.discard[1][0] != discardedCard){
        printf("Player 2 received random discarded card. Test failed.\n");
    }
    else{
        printf("Player 2 received correct discarded card.\n");
    }
}
    
void test_two(struct gameState G){
    struct gameState testG;

    printf("----------------- Test 2: %s ----------------\n", TESTCARD);
    printf("choose 1 cards to return to supply\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    testG.hand[0][2] = copper;

    int numPlayer = testG.numPlayers;
    for (int p = 0; p < numPlayer; p++){
        printf("Current handcount for player %d: %d\n", p, testG.handCount[p]);
        printf("Current deckcount: %d\n", testG.deckCount[p]);
          for (int i = 0; i < testG.handCount[p]; i++){
            printf("player: %d, card[%d]: %d\n", p, i, testG.hand[p][i]);
        }
    }
    
    
    int discardedCard = testG.hand[0][1];
    ambassadorEffect(0, 1, 1, &testG, 0, 0);

    /* choice1 = hand#, choice2 = number to return to supply */
    printf("----------------- Test Results ----------------\n");
    for (int p = 0; p < numPlayer; p++){
        printf("Current handcount for player %d: %d\n", p, testG.handCount[p]);
        printf("Current deckcount: %d\n", testG.deckCount[p]);
        printf("Current discardCount: %d\n", testG.discardCount[p]);
        for (int i = 0; i < testG.handCount[p]; i++){
            printf("player: %d, card[%d]: %d\n", p, i, testG.hand[p][i]);
        }

        for (int i = 0; i < testG.discardCount[p]; i++){
            printf("player: %d, discard card[%d]: %d\n", p, i, testG.discard[p][i]);
        }
    }
    int testCount = testG.handCount[0];
    if (testCount == 3){
        printf("Player 0 handcount == 3. Test passed.\n");
    }
    else{
        printf("Player 0 handcount != 3. Expected 3: Actual %d\n", testG.handCount[0]);
    }

    if (testG.discardCount[1] == 0){
        printf("Player 2 never received discarded card. Test failed\n");
    }
    else if (testG.discard[1][0] != discardedCard){
        printf("Player 2 received random discarded card. Test failed.\n");
    }
    else{
        printf("Player 2 received correct discarded card\n");
    }
}

    
void test_three(struct gameState G){
   struct gameState testG;

    printf("----------------- Test 3: %s ----------------\n", TESTCARD);
    printf("choose 0 cards to return to supply\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    int numPlayer = testG.numPlayers;
    for (int p = 0; p < numPlayer; p++){
        printf("Current handcount for player %d: %d\n", p, testG.handCount[p]);
        printf("Current deckcount: %d\n", testG.deckCount[p]);
          for (int i = 0; i < testG.handCount[p]; i++){
            printf("player: %d, card[%d]: %d\n", p, i, testG.hand[p][i]);
        }

        for (int i = 0; i < testG.discardCount[p]; i++){
            printf("player: %d, discard card[%d]: %d\n", p, i, testG.discard[p][i]);
        }
    }    
    
    int discardedCard = testG.hand[0][1];
    ambassadorEffect(0, 1, 0, &testG, 0, 0);

    /* choice1 = hand#, choice2 = number to return to supply */
    printf("----------------- Test Results ----------------\n");
    for (int p = 0; p < numPlayer; p++){
        printf("Current handcount for player %d: %d\n", p, testG.handCount[p]);
        printf("Current deckcount: %d\n", testG.deckCount[p]);
        printf("Current discardCount: %d\n", testG.discardCount[p]);
        for (int i = 0; i < testG.handCount[p]; i++){
            printf("player: %d, card[%d]: %d\n", p, i, testG.hand[p][i]);
        }

        for (int i = 0; i < testG.discardCount[p]; i++){
            printf("player: %d, discard card[%d]: %d\n", p, i, testG.discard[p][i]);
        }
    }
    int testCount = testG.handCount[0];
    if (testCount == 4){
        printf("Player 0 handcount == 4. Test passed.\n");
    }
    else{
        printf("Player 0 handcount != 4. Expected 4: Actual %d\n", testG.handCount[0]);
    }

    if (testG.discardCount[1] == 0){
        printf("Player 2 never received discarded card. Test failed\n");
    }
    else if (testG.discard[1][0] != discardedCard){
        printf("Player 2 received random discarded card. Test failed.\n");
    }
    else{
        printf("Player 2 received discarded card. Test passed.\n");
    }
}

void test_four(struct gameState G){
    struct gameState testG;

    printf("----------------- Test 4: %s ----------------\n", TESTCARD);
    printf("choose 2 cards to return to supply but only have 1 of them\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    // int return_status = ambassadorEffect(1, 2, &testG, 0);
    int return_status = ambassadorEffect(0, 1, 2, &testG, 0);

    if (return_status < 0){
        printf("function returned -1, test passed\n");
    }
    else{
        printf("function did not return -1. test failed\n");
    }
}