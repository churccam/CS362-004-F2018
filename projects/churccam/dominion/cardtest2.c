/*
 * cardtest2.c
 *
 * Description: unit tests for adventurer card
 *
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
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

#define TEST_CARD "adventurer"
void buildDeck(int player, struct gameState *test_GS, int test_card){
    int testCardCount = 0; //count of target card in hand
    int dSize = 10;

    for (int i = 0; i < dSize; i++){
        test_GS->deck[player][i] = gardens;
    }
    test_GS->deckCount[player] = dSize;
}
int main(int argc, char** argv) {
    int seed = 100;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int test_passed = 0;
    //initialize game state
    struct gameState default_GS, test_GS;
    int expectedValue;


    int testValue;
    printf("\n--------------- Testing Card: %s ---------------\n", TEST_CARD);

    //--------------- TEST 1: + 2 cards, - 1 card (discard) ---------------:
    initializeGame(numPlayers, k, seed, &test_GS);

    test_GS.hand[currentPlayer][0] = adventurer;
    test_GS.handCount[currentPlayer]=1;

    expectedValue = test_GS.handCount[currentPlayer]+1; // -1 adventurer card, + 2 treasure cards
    playCard(0, 0, 0, 0, &test_GS);
    testValue = test_GS.handCount[currentPlayer];

    printf("TEST 1: 2 cards drawn, 1 card discarded\n");
    if (testValue == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Cards in hand: %d     expected:%d\n\n", testValue, expectedValue);




    //--------------- TEST 2: 2 treasure cards in hand ---------------:
    int treasureCount=0;
    for (int i=0; i <testValue; i++){
        if (test_GS.hand[currentPlayer][i] <= gold) {
            if (test_GS.hand[currentPlayer][i] >= copper) {
                treasureCount++;
            }
        }
    }
    printf("TEST 2: 2 treasure cards added to hand\n");
    if (treasureCount == 2) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Treasure cards in hand: %d     expected:%d\n\n", treasureCount, 2);


    //--------------- TEST 3: repeat test 1 with more varied beginner hand ---------------:
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &test_GS);
    buildDeck(currentPlayer, &test_GS, 1);

    int prePlayTreasureCount=0;
    for (int i=0; i <testValue; i++){
        if (test_GS.hand[currentPlayer][i] <= gold) {
            if (test_GS.hand[currentPlayer][i] >= copper) {
                prePlayTreasureCount++;
            }
        }
    }

    expectedValue = test_GS.handCount[currentPlayer] + 1;
    test_GS.hand[currentPlayer][0] = adventurer;
    playCard(0, 0, 0, 0, &test_GS);

    testValue = test_GS.handCount[currentPlayer];

    printf("TEST 3: 2 cards drawn, 1 card discarded (larger starting hand)\n");
    if (testValue == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Hand count: %d     expected:%d\n\n", testValue, expectedValue);

    //--------------- TEST 4: 2 treasure cards in hand (start with no treasure in deck)---------------:

    treasureCount=0;
    for (int i=0; i <testValue; i++){
        if (test_GS.hand[currentPlayer][i] <= gold) {
            if (test_GS.hand[currentPlayer][i] >= copper) {
                treasureCount++;
            }
        }
    }
    expectedValue = prePlayTreasureCount+2;
    printf("TEST 4: 2 treasure cards added to hand (start with no treasure in deck)\n");
    if (treasureCount == expectedValue) {
        printf("RESULT: PASSED!\n");
        test_passed += 1;
    } else {
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Treasure cards in hand: %d     expected:%d\n\n", treasureCount, expectedValue);

    //TESTING COMPLETE--------------------------------------------------------
    printf("---------------TESTING COMPLETE: %s---------------", TEST_CARD);
    printf("\n---------------RESULTS: %i/%i Tests Passed----------------\n\n", test_passed, 4);
}

/*Original adventurer card effect
 * switch( card )
    {
    case adventurer:
      while(drawntreasure<2){
	if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
	  shuffle(currentPlayer, state);
	}
	drawCard(currentPlayer, state);
	cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
	if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  drawntreasure++;
	else{
	  temphand[z]=cardDrawn;
	  state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
	  z++;
	}
      }
      while(z-1>=0){
	state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
	z=z-1;
      }
      return 0;
 */