/*
 * cardtest1.c
 *
 * Description: unit tests for SMITHY card
 *
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
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

#define TEST_CARD "smithy"

int main(int argc, char** argv) {
    int seed = 100;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int expectedValue;  // expected player hand size after smithy card is played
    int test_passed = 0;
    int curHandCount;
    int handPos;
    int currentPlayer = 0;
    int deckCard = gardens; // not in k
    int typeMatch = 1;
    int checkCard;

    //initialize game state
    struct gameState default_GS, test_GS;
    test_GS.phase = 0;

    initializeGame(numPlayers, k, seed, &test_GS);


    printf("\n--------------- Testing Card: %s ---------------\n", TEST_CARD);
    //--------------- TEST 1: check player hand count after smithy card is played ---------------:

    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    //add smithy to hand
    handPos = 0;
    test_GS.hand[currentPlayer][handPos] = smithy;
    test_GS.handCount[currentPlayer] = 1;

    //make sure player has cards in deck
    test_GS.deckCount[currentPlayer] = 10;
    for (int i = 0; i < 10; i++) {
        test_GS.deck[currentPlayer][i] = deckCard;
    }

    curHandCount = 0;
    expectedValue = 3;

    //play smith card
    test_GS.numActions = 1;
    playCard(handPos, 0, 0, 0, &test_GS);

    curHandCount = test_GS.handCount[currentPlayer];

    printf("TEST 1: check if smithy is adding correct amount of cards to hand\n");
    if (curHandCount == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Hand count: %d     expected:%d\n\n", curHandCount, expectedValue);

    if (test_GS.hand[currentPlayer][0] != deckCard || test_GS.hand[currentPlayer][1] != deckCard) {
        typeMatch = 0;
    }

    //--------------- TEST 2: check card types in player hand after playing smithy---------------:

    printf("TEST 2: check if smithy add's cards from deck (by checking card type)\n");
    if (typeMatch == 1) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Type match status: %d     expected:%d\n\n", typeMatch, 1);

    //TESTING COMPLETE--------------------------------------------------------
    printf("---------------TESTING COMPLETE: %s---------------", TEST_CARD);
    printf("\n---------------RESULTS: %i/%i Tests Passed----------------\n\n", test_passed, 2);

}


/*
Smithy
Original card effect found in switch statement
case smithy:
      //+3 Cards
      for (i = 0; i < 3; i++)
	{
	  drawCard(currentPlayer, state);
	}

      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);
      return 0;



 void smithy_cardEffect(int handPos, int currentPlayer, struct gameState *state){
	 //should +3 Cards - bug: +2 Cards
      for (int i = 0; i < 2; i++)
	{
	  drawCard(currentPlayer, state);
	}

      //discard card from hand
      discardCard(handPos, currentPlayer, state, 0);

}

 */
