/*
 * unittest1.c
 *
 * Description: unit tests for updateCoins() function
 *
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>

#define TEST_FUNCTION "updateCoins()"

int main(int argc, char** argv){

    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    //initialize game state
    struct gameState default_GS, test_GS;

    //testing variables
    int expectedValue;
    int testCount = 6;
    int test_passed=0;


    printf("\n--------------- Testing Card: %s ---------------\n", TEST_FUNCTION);

    //--------------- TEST 1: Add 10 Coppers ---------------:
    //start game
    initializeGame(numPlayers, k, seed, &test_GS);

    test_GS.coins = 0;
    test_GS.handCount[currentPlayer] = 0;
    expectedValue = 10;
    //add 10 copper cards to player hand
    for(int i = 0; i<10; i++){
        test_GS.hand[currentPlayer][i] = copper;
        test_GS.handCount[currentPlayer] += 1;
    }

    //updateCoins
    updateCoins(currentPlayer, &test_GS, 0);
    printf("TEST 1: Add 10 Coppers\n");
    if(test_GS.coins==10){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: coins: %d     expected:%d\n\n", test_GS.coins, expectedValue);


    //--------------- TEST 2: Add 10 SILVERS ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    test_GS.coins = 0;
    test_GS.handCount[currentPlayer] = 0;
    expectedValue = 20;
    //add 10 silver cards to player hand
    for(int i = 0; i<10; i++){
        test_GS.hand[currentPlayer][i] = silver;
        test_GS.handCount[currentPlayer] += 1;
    }

    //updateCoins
    updateCoins(currentPlayer, &test_GS, 0);
    printf("TEST 2: Add 10 Silvers\n");
    if(test_GS.coins==20){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: coins: %d     expected:%d\n\n", test_GS.coins, expectedValue);

    //--------------- TEST 3: Add 10 GOLDS ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    test_GS.coins = 0;
    test_GS.handCount[currentPlayer] = 0;
    expectedValue = 30;
    //add 10 gold cards to player hand
    for(int i = 0; i<10; i++){
        test_GS.hand[currentPlayer][i] = gold;
        test_GS.handCount[currentPlayer] += 1;
    }

    //updateCoins
    updateCoins(currentPlayer, &test_GS, 0);
    printf("TEST 3: Add 10 Golds\n");
    if(test_GS.coins==expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: coins: %d     expected:%d\n\n", test_GS.coins, expectedValue);

    //--------------- TEST 4: Add 1 Copper, 1 Silver, 1 Gold ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    test_GS.coins = 0;
    test_GS.handCount[currentPlayer] = 3;
    expectedValue = 6;

    test_GS.hand[currentPlayer][0] = gold;
    test_GS.hand[currentPlayer][1] = silver;
    test_GS.hand[currentPlayer][2] = copper;

    //updateCoins
    updateCoins(currentPlayer, &test_GS, 0);
    printf("TEST 4: Add 1 Copper, 1 Silver, 1 Gold\n");
    if(test_GS.coins==expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: coins: %d     expected:%d\n\n", test_GS.coins, expectedValue);

    //--------------- TEST 5: Add 10 Bonus coins ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    test_GS.coins = 0;
    test_GS.handCount[currentPlayer] = 0;
    expectedValue = 10;
    int bonusC = 10;

    //updateCoins
    updateCoins(currentPlayer, &test_GS, bonusC);
    printf("TEST 5: Add 10 Bonus Coins\n");
    if(test_GS.coins==expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: coins: %d     expected:%d\n\n", test_GS.coins, expectedValue);

    //--------------- TEST 6: Add 10 Cards with no coin value ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    test_GS.coins = 0;
    test_GS.handCount[currentPlayer] = 0;
    expectedValue = 0;
    //add 10 gold cards to player hand
    for(int i = 0; i<10; i++){
        test_GS.hand[currentPlayer][i] = adventurer;
        test_GS.handCount[currentPlayer] += 1;
    }

    //updateCoins
    updateCoins(currentPlayer, &test_GS, 0);
    printf("TEST 6: Add 10 cards with no coin value\n");
    if(test_GS.coins==expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: coins: %d     expected:%d\n\n", test_GS.coins, expectedValue);

    //TESTING COMPLETE--------------------------------------------------------
    printf("---------------TESTING COMPLETE: %s---------------", TEST_FUNCTION);
    printf("\n---------------RESULTS: %i/%i Tests Passed----------------\n\n", test_passed, testCount);





}

/*
 * int updateCoins(int player, struct gameState *state, int bonus)//updateCoinsFind
{
  int i;

  //reset coin count
  state->coins = 0;

  //add coins for each Treasure card in player's hand
  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == copper)
	{
	  state->coins += 1;
	}
      else if (state->hand[player][i] == silver)
	{
	  state->coins += 2;
	}
      else if (state->hand[player][i] == gold)
	{
	  state->coins += 3;
	}
    }

  //add bonus
  state->coins += bonus;

  return 0;
}
 */