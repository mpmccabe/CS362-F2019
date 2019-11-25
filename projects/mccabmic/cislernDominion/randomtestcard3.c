#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define     TESTCARD    "baron"
#define     NUMTIMES       2000

int test_one(struct gameState G, int thisPlayer);
int test_two(struct gameState G, int thisPlayer);
int test_three(struct gameState G, int thisPlayer);

int main(){
    srand(time(NULL));
    
    int k[10] = {adventurer, baron, village, minion, mine, estate,
			sea_hag, tribute, smithy, council_room};

    printf("----------------- Test: %s ----------------\n", TESTCARD);

    int failedCount = 0;
    int messedUpCount = 0;
    int successCount = 0;

    int n = 0;

    printf("Starting loop\n...");
    while ( n < NUMTIMES){
        
        struct gameState G;
       
        int p = 0;
        int seed = 10 + (rand() % NUMTIMES);
        initializeGame(p, k, seed, &G);
        
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_DECK);
        G.supplyCount[estate] = floor(Random() * 2);

        int choice = floor(Random() * 2);

        for(int i = 0; i < G.handCount[p]; i++){
			G.hand[p][i] = rand() % 28;
		}

        int test_result;

        if (choice == 0){
            test_result = test_one(G, p);
        } else{
            test_result = test_two(G, p) & test_three(G, p);

        } 
        
        if (test_result < 0){
            messedUpCount++;
        } else if (test_result == 0) {
            failedCount++;
        } else{
            successCount++;
        }

        n = n + 1;
    }
   printf("Finished loop. Test results: %d errors, %d failed, %d successes\n...", messedUpCount, failedCount, successCount);
}

int test_one(struct gameState G, int thisPlayer){

    struct gameState testG;
    int found_discarded_estate;
    int found_hand_estate;
    int return_status;

    
    memcpy(&testG, &G, sizeof(struct gameState));
    return_status = baronEffect(&testG, 0, 1);

    if (return_status < 0){
        return -1;
    }
    
    printf("----------------- discard an estate test: %s ----------------\n", TESTCARD);

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
        return 0;
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
        return 0;
    }

    if (testG.coins != G.coins + 4){
        printf("coins added incorrectly. expected %d, received: %d\n", G.coins + 4, testG.coins);
        return 0;
    }

    return 1;

}

int test_two(struct gameState G, int thisPlayer){

    struct gameState testG;
    int found_discarded_estate;
    int found_hand_estate;
    int return_status;
    printf("----------------- don't discard an estate: %s ----------------\n", TESTCARD);

    memcpy(&testG, &G, sizeof(struct gameState));
    return_status = baronEffect(&testG,0, 0);

     if (return_status < 0){
        return -1;
    }

    /*expectation: gained an estate into discard pile, no coins were added, no estates discarded*/

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
        return 0;
    }

    found_hand_estate = 0;
    for (int i = 0; i < testG.handCount[thisPlayer]; i++){
        if (testG.hand[thisPlayer][i] == estate){
            found_hand_estate = 1;
            }
    }

    if (!found_hand_estate){
        printf("estate card not found in hand pile: test failed\n");
        return 0;
    }
    else{
        printf("estate card found in hand pile: test passed\n");
    }

    if (testG.coins != G.coins){
        printf("coins were incorrectly added. expected %d, received: %d test failed.\n", G.coins, testG.coins);
        return 0;
    } else{
        printf("coins were not changed . expected %d. test passed.\n", testG.coins);
    }

    return 1;
}

int test_three(struct gameState G, int thisPlayer){
    struct gameState testG;
    int found_discarded_estate;
    int found_hand_estate;
    int return_status;
    printf("-----------------try to discard estate I don't have: %s ----------------\n", TESTCARD);

    memcpy(&testG, &G, sizeof(struct gameState));
    return_status = baronEffect(&testG,0, 1);
    
    /*expectation: gained an estate into discard pile, no coins were added, no estates discarded*/

    if (return_status < 0){
        return -1;
    }

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
        return 0;
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
        return 0;
    }

    if (testG.coins != G.coins){
        printf("coins were incorrectly added. expected %d, received: %d test failed.\n", G.coins, testG.coins);
        return 0;
    } else{
        printf("coins were not changed . expected %d. test passed.\n", testG.coins);
    }

    return 1;

}