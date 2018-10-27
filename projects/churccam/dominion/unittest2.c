/*
 * unittest2.c
 *
 * Description: unit tests for fullDeckCount() function
 *
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
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

#define TEST_FUNCTION "fullDeckCount()"

int buildHand(int player, struct gameState *test_GS, int test_card){
    int testCardCount = 0; //count of target card in hand
    int hSize = rand() % MAX_HAND; //size of hand
    int randCard; //random card
    for (int i = 0; i < hSize; i++){
        randCard = rand() % 10;
        test_GS->hand[player][i] = randCard;
        if(randCard == test_card){
            testCardCount += 1;
        }
    }
    test_GS->handCount[player] = hSize;
    return testCardCount;
}

int buildDeck(int player, struct gameState *test_GS, int test_card){
    int testCardCount = 0; //count of target card in hand
    int dSize = rand() % MAX_DECK; //size of hand
    int randCard; //random card
    for (int i = 0; i < dSize; i++){
        randCard = rand() % 10;
        test_GS->deck[player][i] = randCard;
        if(randCard == test_card){
            testCardCount += 1;
        }
    }
    test_GS->deckCount[player] = dSize;
    return testCardCount;
}

int buildDiscard(int player, struct gameState *test_GS, int test_card){
    int testCardCount = 0; //count of target card in hand
    int dSize = rand() % MAX_DECK; //size of hand
    int randCard; //random card
    for (int i = 0; i < dSize; i++){
        randCard = rand() % 10;
        test_GS->discard[player][i] = randCard;
        if(randCard == test_card){
            testCardCount += 1;
        }
    }
    test_GS->discardCount[player] = dSize;
    return testCardCount;
}

int main(int argc, char** argv) {

    int seed = 500;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int expectedValue;
    int test_passed = 0;
    int countValue;

    //Intializes random number generator
    time_t t;
    srand((unsigned) time(&t));

    //initialize game state
    struct gameState default_GS, test_GS;

    //start game
    initializeGame(numPlayers, k, seed, &test_GS);

    printf("\n--------------- Testing Card: %s ---------------\n", TEST_FUNCTION);

    //--------------- TEST 1: 0 matching cards in hand, discard, and deck ---------------:
    //start game
    initializeGame(numPlayers, k, seed, &test_GS);
    expectedValue = 0;
    int test_card = outpost; // not in k card array
    countValue = fullDeckCount(currentPlayer, test_card, &test_GS);

    printf("TEST 1: 0 matching cards in hand, discard, and deck\n");
    if(countValue == expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: matching cards: %d     expected:%d\n\n", countValue, expectedValue);


    //--------------- TEST 2: 5 matching cards in hand (0 in discard and deck)---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    expectedValue = 5;
    test_card = outpost; // not in k card array
    for(int i = 0; i < expectedValue; i++){
        test_GS.hand[currentPlayer][i] = test_card;
    }
    //make sure hand count is large enough
    if(test_GS.handCount[currentPlayer] < expectedValue){
        test_GS.handCount[currentPlayer] = expectedValue;
    }

    countValue = fullDeckCount(currentPlayer, test_card, &test_GS);

    printf("TEST 2: 5 matching cards in hand (0 in discard and deck)\n");
    if(countValue == expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: matching cards: %d     expected:%d\n\n", countValue, expectedValue);

    //--------------- TEST 3: 5 matching cards in discard (0 in hand and deck)---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    expectedValue = 5;
    test_card = outpost; // not in k card array

    // add five cards to discard
    for(int i = 0; i < expectedValue; i++){
        test_GS.discard[currentPlayer][i] = test_card;
    }

    //make sure hand count is large enough
    if(test_GS.discardCount[currentPlayer] < expectedValue){
        test_GS.discardCount[currentPlayer] = expectedValue;
    }

    countValue = fullDeckCount(currentPlayer, test_card, &test_GS);

    printf("TEST 3: 5 matching cards in discard (0 in hand and deck)\n");
    if(countValue == expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: matching cards: %d     expected:%d\n\n", countValue, expectedValue);

    //--------------- TEST 4: 5 matching cards in deck (0 in hand and discard)---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    expectedValue = 5;
    test_card = outpost; // not in k card array

    // add five cards to discard
    for(int i = 0; i < expectedValue; i++){
        test_GS.deck[currentPlayer][i] = test_card;
    }

    //make sure hand count is large enough
    if(test_GS.deckCount[currentPlayer] < expectedValue){
        test_GS.deckCount[currentPlayer] = expectedValue;
    }

    countValue = fullDeckCount(currentPlayer, test_card, &test_GS);

    printf("TEST 4: 5 matching cards in deck (0 in hand and discard)\n");
    if(countValue == expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: matching cards: %d     expected:%d\n\n", countValue, expectedValue);

    //--------------- TESTS 5-15: GENERATE RANDOM HANDS, DECKS, AND DISCARDS---------------:
    //variables for holding test card counts
    int hand_tc, deck_tc, discard_tc;


    //reset game state
    int testCount = 15;
    for(int i=5; i <= testCount; i++){
        //reset game state
        memcpy(&test_GS, &default_GS, sizeof(struct gameState));

        //random test card
        test_card = rand() % 10;


        //build random hands, decks, discards - function returns count of test_card
        hand_tc = buildHand(currentPlayer, &test_GS, test_card);
        deck_tc = buildDeck(currentPlayer, &test_GS, test_card);
        discard_tc = buildDiscard(currentPlayer, &test_GS, test_card);

        expectedValue = hand_tc + deck_tc + discard_tc;

        countValue = fullDeckCount(currentPlayer, test_card, &test_GS);

        printf("TEST %i: Hand: %i, Deck: %i, Discard: %i \n", i, hand_tc, deck_tc, discard_tc);
        if(countValue == expectedValue){
            printf("RESULT: PASSED!\n");
            test_passed+=1;
        }else{
            printf("RESULT: FAILED!\n");
        }
        printf("OUTPUT: matching cards: %d     expected:%d\n\n", countValue, expectedValue);

    }

    //TESTING COMPLETE--------------------------------------------------------
    printf("\nTESTING COMPLETE: %s", TEST_FUNCTION);
    printf("\nRESULTS: %i/%i Tests Passed\n\n", test_passed, testCount);

}

/*
 * int fullDeckCount(int player, int card, struct gameState *state);
 *      Here deck = hand + discard + deck
 */
/*
 * int fullDeckCount(int player, int card, struct gameState *state) {
    int i;
    int count = 0;

    for (i = 0; i < state->deckCount[player]; i++)
    {
        if (state->deck[player][i] == card) count++;
    }

    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == card) count++;
    }

    for (i = 0; i < state->discardCount[player]; i++)
    {
        if (state->discard[player][i] == card) count++;
    }

    return count;
}
 */