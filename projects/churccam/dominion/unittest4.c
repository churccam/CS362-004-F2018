/*
 * unittest4.c
 *
 * Description: unit tests for isGameOver() function
 *
 * Include the following lines in your makefile:
 *
 * unittest2: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define TEST_FUNCTION "isGameOver()"

int main(int argc, char** argv)
{
    int seed = 700;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int expectedValue;
    int test_passed = 0;
    int testValue;
    int cardTypes = treasure_map + 1;

    //initialize game state
    struct gameState default_GS, test_GS;

    initializeGame(numPlayers, k, seed, &test_GS);

    printf("\n--------------- Testing Card: %s ---------------\n", TEST_FUNCTION);


    //--------------- TEST 1: stack of province cards is empty ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    expectedValue = 1;
    test_GS.supplyCount[province] = 0;
    testValue = isGameOver(&test_GS);
    printf("TEST 1: stack of province cards is empty\n");
    if(testValue == expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Game status: %d     expected:%d\n\n", testValue, expectedValue);


    //--------------- TEST : stack of province cards is not empty/three supply piles are empty ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    test_GS.supplyCount[province] = 5;

    //set 3 supply piles to 0
    test_GS.supplyCount[0] = 0;
    test_GS.supplyCount[1] = 0;
    test_GS.supplyCount[2] = 0;
    expectedValue = 1;
    testValue = isGameOver(&test_GS);
    printf("TEST 2: 3 empty supply piles/ Province stack not empty\n");
    if(testValue == expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Game status: %d     expected:%d\n\n", testValue, expectedValue);

    //--------------- TEST : stack of province cards is not empty/less than three supply piles empty ---------------:
    //reset game state
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));

    test_GS.supplyCount[province] = 5;

    //set 2 supply piles to 0
    test_GS.supplyCount[0] = 0;
    test_GS.supplyCount[1] = 0;

    for(int i = 2; i < cardTypes; i++){
        test_GS.supplyCount[i] = gold;
    }
    expectedValue = 0;
    testValue = isGameOver(&test_GS);

    printf("TEST 3: supply pile not empty/ less than 3 supply piles empty\n");
    if(testValue == expectedValue){
        printf("RESULT: PASSED!\n");
        test_passed+=1;
    }else{
        printf("RESULT: FAILED!\n");
    }
    printf("OUTPUT: Game status: %d     expected:%d\n\n", testValue, expectedValue);


    return 0;
}

/*
 * int isGameOver(struct gameState *state) {
  int i;
  int j;

  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
    {
      return 1;
    }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
    {
      if (state->supplyCount[i] == 0)
	{
	  j++;
	}
    }
  if ( j >= 3)
    {
      return 1;
    }

  return 0;
}
 *
 */