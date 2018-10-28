/*
 * cardtest4.c
 *
 * Description: unit tests for village card
 *
 * Include the following lines in your makefile:
 *
 * cardtest4: cardtest4.c dominion.o rngs.o
 *      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <stddef.h>

#define TEST_CARD "village"

int main(int argc, char** argv) {
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, gardens,
                 sea_hag, tribute, smithy, council_room};
    int test_passed = 0;
    //initialize game state
    struct gameState default_GS, test_GS;
    int expectedValue;
    int testValue;
    int bonus = 0;

    printf("\n--------------- Testing Card: %s ---------------\n", TEST_CARD);

    //--------------- TEST 1: + 1 card, -1 card (discard village)---------------:
    //reset game state/game
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &test_GS);

    //set up current player
    test_GS.hand[currentPlayer][0] = village;
    int actions = 1;
    test_GS.handCount[currentPlayer] = actions;

    expectedValue = test_GS.handCount[currentPlayer];
    test_GS.numActions = 1;
    cardEffect(village, 0, 0, 0, &test_GS, 0, &bonus);

    testValue = test_GS.handCount[currentPlayer];
    printf("TEST 1: +1 card, -1 card\n");
    if (testValue == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: cards: %d     expected:%d\n\n", testValue, expectedValue);

    //--------------- TEST 2: +2 Actions ---------------:
    testValue = test_GS.numActions;
    printf("TEST 2: +2 Actions\n");
    if (testValue == actions+2) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Actions: %d     expected:%d\n\n", testValue, actions+2);

    //--------------- TEST 3: discard check - makesure card has been changed ---------------:
    testValue = test_GS.hand[currentPlayer][0];
    int match = 0;
    if(testValue == village){
        match = 1;
    }
    printf("TEST 3: discard check\n");
    if (match == 0) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Card type match status: %d     expected:%d\n\n", match, 0);

    //TESTING COMPLETE--------------------------------------------------------
    printf("---------------TESTING COMPLETE: %s---------------", TEST_CARD);
    printf("\n---------------RESULTS: %i/%i Tests Passed----------------\n\n", test_passed, 3);
}

/*
 *     case village:
      //+1 Card
      drawCard(currentPlayer, state);

      //+2 Actions
      state->numActions = state->numActions + 2;

      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;
 */