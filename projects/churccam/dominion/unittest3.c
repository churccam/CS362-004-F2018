/*
 * unittest3.c
 *
 * Description: unit tests for handCard() function
 *
 * Include the following lines in your makefile:
 *
 * unittest3: unittest3.c dominion.o rngs.o
 *      gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define TEST_FUNCTION "handCard()"

int buildHand(int player, struct gameState *test_GS){
    int hSize = rand() % MAX_HAND; //size of hand
    int index = rand() % hSize;
    test_GS->hand[player][index] = copper;
    return index;
}
int main(int argc, char** argv){
    int seed = 700;
    int numPlayers = 4;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int expectedValue;
    int test_passed = 0;
    int countValue;
    int testNumber=0;
    int handSize;
    int randomIndex;
    int returnCard;
    int testCount=0;

    //Intializes random number generator
    time_t t;
    srand((unsigned) time(&t));

    //initialize game state
    struct gameState default_GS, test_GS;

    initializeGame(numPlayers, k, seed, &test_GS);

    printf("\n--------------- Testing Card: %s ---------------\n", TEST_FUNCTION);

    for(int i = 0; i < numPlayers; i++){
        for(int j = 0; j < 5; j++){
            testNumber+=1;
            memcpy(&test_GS, &default_GS, sizeof(struct gameState));
            test_GS.whoseTurn = currentPlayer;
            randomIndex = buildHand(currentPlayer, &test_GS);

            printf("TEST %i: Player %i, Index: %i\n", testNumber, currentPlayer, randomIndex);

            returnCard = handCard(randomIndex, &test_GS);
            if(returnCard == copper){
                printf("RESULT: PASSED!\n");
                test_passed += 1;
            }
            else{
                printf("RESULT: FAILED!\n");
            }
            printf("OUTPUT: Card: %i     expected:%d\n\n", returnCard, copper);
            testCount += 1;
        }
        currentPlayer += 1;
    }

    //TESTING COMPLETE--------------------------------------------------------
    printf("---------------TESTING COMPLETE: %s---------------", TEST_FUNCTION);
    printf("\n---------------RESULTS: %i/%i Tests Passed----------------\n\n", test_passed, testCount);
}

/*
int handCard(int handNum, struct gameState *state);
enum value of indexed card in player's hand

 int handCard(int handPos, struct gameState *state) {
  int currentPlayer = whoseTurn(state);
  return state->hand[currentPlayer][handPos];
}

*/