#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define     TESTCARD    "minion"
#define     NUMTIMES    10000

int test_one(struct gameState G, int choiceOne, int choiceTwo, int handpos);
int test_two(struct gameState G, int choiceOne, int choiceTwo, int handpos);

int main(){
    srand(time(NULL));
    
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall
                };

    printf("----------------- Test: %s ----------------\n", TESTCARD);

    int failedCount = 0;
    int messedUpCount = 0;
    int successCount = 0;

    int n = 0;
    printf("Starting loop\n...");

  while ( n < NUMTIMES){
        
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

        int choiceOne = floor(Random() * 2);
        int choiceTwo = floor(Random() * 2);

        int handpos = -1;

        for (int j = 0; j < numPlayers; j++){
            for(int i = 0; i < G.handCount[j]; i++){
                G.hand[j][i] = rand() % 28;
                if (G.hand[0][i] == minion){
                    handpos = i;
                }
            }
        }
        
        int test_result;

        if (choiceOne == 0){
            test_result = test_one(G, choiceOne, choiceTwo, handpos);
        } else{
            test_result = test_two(G, choiceOne, choiceTwo, handpos);
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

int test_one(struct gameState G, int choiceOne, int choiceTwo, int handpos){
    struct gameState testG;

    // printf("----------------- Test 1: %s ----------------\n", TESTCARD);
    // printf("discard hand\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    if (handpos < 0){
        printf("minion card not found in deck\n");
        return -1;
    }

     if (choiceOne == choiceTwo){
        printf("choices must be mutually exclusive.\n");
        return -1;
    }


    int return_status = minionEffect(&testG, 0, choiceOne, choiceTwo, handpos);
    // int return_status = minionEffect(choiceOne, choiceTwo, &testG, handpos);

    if (return_status < 0){
        printf("Function returned negative.\n");
        return -1;
    }

    printf("----------------- Discard Case ----------------\n");
    printf("choice1 param: %d choice2 param: %d\n", choiceOne, choiceTwo);

    int thisPlayer = 0;

    printf("Current playedCards: %d\n", testG.playedCardCount);
    printf("Current coins: %d\n", testG.coins);

    for (thisPlayer = 0; thisPlayer < testG.numPlayers; thisPlayer++){

        if (testG.handCount[thisPlayer] <= 4 && testG.hand){
            printf("Player %d's handcount <= 4, test passed.\n", thisPlayer);
            return 1;
        }
        else{
            printf("Player %d's handcount is not equal/ to 4 Received %d. Test failed\n", thisPlayer, testG.handCount[thisPlayer]);
            return 0;
        }

    }
}
    

int test_two(struct gameState G, int choiceOne, int choiceTwo, int handpos){
    struct gameState testG;
   
    // printf("----------------- Test 2: %s ----------------\n", TESTCARD);
    // printf("choose coins hand\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    int numCoins =  testG.coins;

    if (handpos < 0){
        printf("minion card not found in deck\n");
        return -1;
    }

    if (choiceOne == choiceTwo){
        printf("choices must be mutually exclusive.\n");
        return -1;
    }

    int return_status = minionEffect(&testG, 0, choiceOne, choiceTwo, handpos);
    // int return_status = minionEffect(choiceOne, choiceTwo, &testG, handpos);

     if (return_status < 0){
        printf("Function returned negative.\n");
        return -1;
    }

    printf("----------------- Choose Coins Case (0 for discard, 1 for coins) ----------------\n");
    printf("choice1 param: %d choice2 param: %d\n", choiceOne, choiceTwo);
  
    printf("Current playedCards: %d\n", testG.playedCardCount);
    printf("Current coins: %d\n", testG.coins);

    if (numCoins + 2 != testG.coins){
        printf("Number of coins incorrectly added. Test failed. Expected :%d Actual: %d\n", numCoins + 2, testG.coins);
        return 0;
    }
    else{
        printf("Number of coins increased successfully. Test passed.\n");
    }

    if (testG.playedCardCount > 1){
        printf("Cards were discarded - test failed.\n");
        return 0;
    }
    else{
        printf("No cards were discarded other than minion. Test passed\n");
    }
    return 1;

}