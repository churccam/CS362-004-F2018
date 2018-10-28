/*
 * cardtest3.c
 *
 * Description: unit tests for cutpurse card
 *
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

#define TEST_CARD "cutpurse"

int main(int argc, char** argv) {
    int seed = 100;
    int numPlayers = 4;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, gardens,
                 sea_hag, tribute, smithy, council_room};
    int test_passed = 0;
    //initialize game state
    struct gameState default_GS, test_GS;
    int expectedValue;
    int testValue;

    printf("\n--------------- Testing Card: %s ---------------\n", TEST_CARD);
    //--------------- TEST 1: increase player coins by 2 ---------------:
    //reset game state/game
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &test_GS);

    //set up current player
    test_GS.hand[currentPlayer][0] = cutpurse;
    test_GS.handCount[currentPlayer] = 1;
    test_GS.coins = 0;

    //set up other players with copper card in hand
    for(int i = 1; i < numPlayers; i++){
        test_GS.hand[i][0] = copper;
        test_GS.handCount[i] = 1;
    }

    playCard(0,0,0,0, &test_GS);

    testValue = test_GS.coins;
    expectedValue = 2;

    printf("TEST 1: +2 coins\n");
    if (testValue == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Coins: %d     expected:%d\n\n", testValue, expectedValue);

    //--------------- TEST 2: remove coppers from other players ---------------:
    printf("TEST 2: remove coppers\n");
    expectedValue = 0;
    testValue = 0;
    //count coppers in other players hands
    for(int i = 1; i < numPlayers; i++){
        if(test_GS.hand[i][0] == copper){
            testValue++;
        }
    }

    if (testValue == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Coppers: %d     expected:%d\n\n", testValue, expectedValue);

    //--------------- TEST 3: attempt to remove coppers (from players who are not holding any) ---------------:
    //note: test by counting other players hand counts before and after card is played
    //note: since the other players don't have any coppers, the hand count should stay the same

    //reset game state/game
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &test_GS);

    //set up current player
    test_GS.hand[currentPlayer][0] = cutpurse;
    test_GS.handCount[currentPlayer] = 1;
    test_GS.coins = 0;

    expectedValue = 0;
    //set up other players with copper card in hand
    for(int i = 1; i < numPlayers; i++){
        test_GS.hand[i][0] = gardens;
        test_GS.hand[i][1] = smithy;
        test_GS.hand[i][2] = adventurer;
        test_GS.handCount[i] = 3;
        expectedValue += 3;
    }

    playCard(0,0,0,0, &test_GS);

    //count coppers in other players hands
    for(int i = 1; i < numPlayers; i++){
        testValue += test_GS.handCount[i];
    }

    printf("TEST 3: remove 0 cards from other players (no coppers in hand)\n");
    if (testValue == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Total hand count: %d     expected:%d\n\n", testValue, expectedValue);

    //TESTING COMPLETE--------------------------------------------------------
    printf("---------------TESTING COMPLETE: %s---------------", TEST_CARD);
    printf("\n---------------RESULTS: %i/%i Tests Passed----------------\n\n", test_passed, 3);



}