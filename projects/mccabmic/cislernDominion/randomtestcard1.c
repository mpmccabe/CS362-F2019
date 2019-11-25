#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define TESTCARD "tribute"
#define NUMTIMES 2000 

int test_one(struct gameState g);

int main(){

    int k[10] = {adventurer, baron, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    printf("----------------- Test: %s ----------------\n", TESTCARD);

    printf ("RANDOM TESTS.\n");

    int failedCount = 0;
    int messedUpCount = 0;
    int successCount = 0;

    int n = 0;

    printf("Starting loop\n...");
    while ( n < NUMTIMES ){
        
        struct gameState G;
       
        int numPlayers = 2;
        int seed = 10 + (rand() % NUMTIMES);
        initializeGame(numPlayers, k, seed, &G);
    

        G.deckCount[0] = floor(Random() * MAX_DECK);
        G.discardCount[0] = floor(Random() * MAX_DECK);
        G.handCount[0] = floor(Random() * MAX_DECK);

        G.deckCount[1] = floor(Random() * MAX_DECK);
        G.discardCount[1] = floor(Random() * MAX_DECK);
        G.handCount[1] = floor(Random() * MAX_DECK);

        // fill hand
        for (int j = 0; j < numPlayers; j++){
            for(int i = 0; i < G.handCount[j]; i++){
                G.hand[j][i] = rand() % 28;
            }
        }

        // fill deck
         for (int j = 0; j < numPlayers; j++){
            for(int i = 0; i < G.deckCount[j]; i++){
                G.deck[j][i] = rand() % 28;
            }
        }

        // fill discard
         for (int j = 0; j < numPlayers; j++){
            for(int i = 0; i < G.discardCount[j]; i++){
                G.discard[j][i] = rand() % 28;
            }
        }

        int test_result = test_one(G);

        if (test_result < 0){
            messedUpCount++;
        } else if (test_result == 0) {
            failedCount++;
        } else{
            successCount++;
        }
;
        n = n + 1;
    }

   printf("Finished loop. Test results: %d errors, %d failed, %d successes\n...", messedUpCount, failedCount, successCount);

}

int test_one(struct gameState G){

    struct gameState testG;

    
    memcpy(&testG, &G, sizeof(struct gameState));
    int return_status = tributeEffect(&testG);

    if (return_status < 0){
        return -1;
    }




    
    printf("----------------- discard an estate test: %s ----------------\n", TESTCARD);

    /*expectation: estate not in deck, coins are increased by 4*/

}