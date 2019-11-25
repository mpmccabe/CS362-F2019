#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

#define TESTCARD "baron"

void test_one(struct gameState G, int thisPlayer);
void test_two(struct gameState G, int thisPlayer);
void test_three(struct gameState G, int thisPlayer);

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
        printf("card[%d]: %d\n", i, G.hand[thisPlayer][i]);
    }

    test_one(G, thisPlayer);
    test_two(G, thisPlayer);

    printf("----------------- Modified Case ----------------\n");
    printf("Current handcount: %d\n", G.handCount[thisPlayer]);
    printf("Current deckcount: %d\n", G.deckCount[thisPlayer]);
    printf("Current discardCount: %d\n", G.discardCount[thisPlayer]);
    printf("Current coins: %d\n", G.coins);
    G.hand[thisPlayer][3] = silver;
    test_three(G, thisPlayer);

}

void test_one(struct gameState G, int thisPlayer){

    struct gameState testG;
    int found_discarded_estate;
    int found_hand_estate;
    int return_status;
    

    printf("----------------- Test 1: %s ----------------\n", TESTCARD);
    printf("discard an estate\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    return_status = baronEffect(&testG, 0, 1);

    printf("baronEffect return status: %d\n", return_status);
    printf("Current handcount: %d\n", testG.handCount[thisPlayer]);
    printf("Current deckcount: %d\n", testG.deckCount[thisPlayer]);
    printf("Current discardCount: %d\n", testG.discardCount[thisPlayer]);
    printf("Current coins: %d\n", testG.coins);

    /*expectation: estate not in deck, coins are increased by 4*/
    found_discarded_estate = 0;
    for (int i = 0; i < testG.discardCount[thisPlayer]; i++){
        if (testG.discard[thisPlayer][i] == estate){
            found_discarded_estate = 1;
        }
    }

    if (found_discarded_estate){
        printf("estate card found in discard pile: test passed\n");
    }

    else{
        printf("estate card not found in discard pile: test failed\n");
    }

    found_hand_estate = 0;
    for (int i = 0; i < testG.handCount[thisPlayer]; i++){
        if (testG.hand[thisPlayer][i] == estate){
                found_hand_estate = 1;
        }
    }

    if (!found_hand_estate){
        printf("estate card not found in hand pile: test passed\n");
    }
    else{
        printf("estate card found in hand pile: test failed\n");
    }

    if (testG.coins != 7){
        printf("coins added incorrectly. expected 7, received: %d\n", testG.coins);
    }

}

void test_two(struct gameState G, int thisPlayer){

    struct gameState testG;
    int found_discarded_estate;
    int found_hand_estate;
    int return_status;
    printf("----------------- Test 2: %s ----------------\n", TESTCARD);
    printf("don't discard an estate\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    return_status = baronEffect(&testG, 0, 0);
    /*expectation: gained an estate into discard pile, no coins were added, no estates discarded*/
    printf("baronEffect return status: %d\n", return_status);
    printf("Current handcount: %d\n", testG.handCount[thisPlayer]);
    printf("Current deckcount: %d\n", testG.deckCount[thisPlayer]);
    printf("Current discardCount: %d\n", testG.discardCount[thisPlayer]);
    printf("Current coins: %d\n", testG.coins);

    found_discarded_estate = 0;
    for (int i = 0; i < testG.discardCount[thisPlayer]; i++){
        if (testG.discard[thisPlayer][i] == estate){
            found_discarded_estate = 1;
            }
    }

    if (found_discarded_estate){
        printf("estate card found in discard pile: test passed\n");
    }
    else{
        printf("estate card not found in discard pile: test failed\n");
    }

    found_hand_estate = 0;
    for (int i = 0; i < testG.handCount[thisPlayer]; i++){
        if (testG.hand[thisPlayer][i] == estate){
            found_hand_estate = 1;
            }
    }

    if (!found_hand_estate){
        printf("estate card not found in hand pile: test failed\n");
    }
    else{
        printf("estate card found in hand pile: test passed\n");
    }

    if (testG.coins != 3){
        printf("coins added incorrectly. expected 7, received: %d\n", testG.coins);
    } else{
        printf("coins added correctly. expected 3, received: %d\n", testG.coins);
    }
}

void test_three(struct gameState G, int thisPlayer){
    struct gameState testG;
    int found_discarded_estate;
    int found_hand_estate;
    int return_status;
    printf("----------------- Test 3: %s ----------------\n", TESTCARD);
    printf("try to discard estate I don't have\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    return_status = baronEffect(&testG, 0, 1);
    /*expectation: gained an estate into discard pile, no coins were added, no estates discarded*/
    printf("baronEffect return status: %d\n", return_status);
    printf("Current handcount: %d\n", testG.handCount[thisPlayer]);
    printf("Current deckcount: %d\n", testG.deckCount[thisPlayer]);
    printf("Current discardCount: %d\n", testG.discardCount[thisPlayer]);
    printf("Current coins: %d\n", testG.coins);

    found_discarded_estate = 0;
    for (int i = 0; i < testG.discardCount[thisPlayer]; i++){
        if (testG.discard[thisPlayer][i] == estate){
            found_discarded_estate = 1;
            }
    }

    if (found_discarded_estate){
        printf("estate card found in discard pile: test passed\n");
    }
    else{
        printf("estate card not found in discard pile: test failed\n");
    }

    found_hand_estate = 0;
    for (int i = 0; i < testG.handCount[thisPlayer]; i++){
        if (testG.hand[thisPlayer][i] == estate){
            found_hand_estate = 1;
            }
    }

    if (!found_hand_estate){
        printf("estate card not found in hand pile: test passed\n");
    }
    else{
        printf("estate card found in hand pile: test failed\n");
    }

    if (testG.coins != 3){
        printf("coins added incorrectly. expected 7, received: %d\n", testG.coins);
    } else{
        printf("coins added correctly. expected 3, received: %d\n", testG.coins);
    }


}