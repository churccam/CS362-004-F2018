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

    int newCards = 0;
    int discarded = 1;
    int extraCoins = 0;
    int shuffledCards = 0;

    int i;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int currentPlayer = 0;
    int otherPlayer = 1;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int test_state_value;
    int default_state_value;
    int testPassCount = 0;
    struct gameState default_GS, test_GS;

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &default_GS);
    printf("----------------- Testing Card: %s ----------------\n", TEST_CARD);

    // copy the game state to a test case
    memcpy(&test_GS, &default_GS, sizeof(struct gameState));
    cardEffect(smithy, choice1, choice2, choice3, &test_GS, handpos, &bonus);

    printf("CARD EFFECT: +3 cards to hand (draw), -1 card from hand (discard)\n");
    newCards = 3;
    extraCoins = 0;

    printf("Current player state-check:\n");
    //check player hand count
    test_state_value = test_GS.handCount[currentPlayer];
    default_state_value = default_GS.handCount[currentPlayer] + newCards - discarded;
    printf("hand count: %d  |  expected: %d", test_state_value, default_state_value);
    if(test_state_value == default_state_value){
        printf("   |   PASSED\n");
        testPassCount++;
    }else{
        printf("   |   FAILED\n");
    }

    //check player deck count
    test_state_value = test_GS.deckCount[currentPlayer];
    default_state_value = default_GS.deckCount[currentPlayer] - newCards + shuffledCards;
    printf("deck count: %d  |  expected: %d", test_state_value, default_state_value);
    if(test_state_value == default_state_value){
        printf("   |   PASSED\n");
        testPassCount++;
    }else{
        printf("   |   FAILED\n");
    }

    //check player coins
    test_state_value = test_GS.coins;
    default_state_value = default_GS.coins+extraCoins;
    printf("coin count: %d  |  expected: %d", test_state_value, default_state_value);
    if(test_state_value == default_state_value){
        printf("   |   PASSED\n");
        testPassCount++;
    }else{
        printf("   |   FAILED\n");
    }


    //check other players state ----------------
    printf("\nOther player state-check:\n");
    //check player hand count
    test_state_value = test_GS.handCount[otherPlayer];
    default_state_value = default_GS.handCount[otherPlayer];
    printf("hand count: %d  |  expected: %d", test_state_value, default_state_value);
    if(test_state_value == default_state_value){
        printf("   |   PASSED\n");
        testPassCount++;
    }else{
        printf("   |   FAILED\n");
    }

    //check other player deck count
    test_state_value = test_GS.deckCount[otherPlayer];
    default_state_value = default_GS.deckCount[otherPlayer];
    printf("deck count: %d |  expected: %d", test_state_value, default_state_value);
    if(test_state_value == default_state_value){
        printf("   |   PASSED\n");
        testPassCount++;
    }else{
        printf("   |   FAILED\n");
    }

    printf("\nVictory card state-check:\n");
    //check victory card piles ----------------
    test_state_value = test_GS.supplyCount[estate] +  test_GS.supplyCount[duchy] +  test_GS.supplyCount[province];
    default_state_value = default_GS.supplyCount[estate] +  default_GS.supplyCount[duchy] +  default_GS.supplyCount[province];
    printf("Victory card count: %d  |  expected: %d", test_state_value, default_state_value);
    if(test_state_value == default_state_value){
        printf("   |   PASSED\n");
        testPassCount++;
    }else{
        printf("   |   FAILED\n");
    }
    test_state_value = 0;
    default_state_value = 0;

    //check kingdom card pile
    for(i=0; i<10; i++){
        test_state_value += test_GS.supplyCount[k[i]];
        default_state_value += default_GS.supplyCount[k[i]];
    }

    printf("\nKingdom card state-check:\n");
    printf("kingdom card count: %d  |  expected: %d", test_state_value, default_state_value);
    if(test_state_value == default_state_value){
        printf("   |   PASSED\n");
        testPassCount++;
    }else{
        printf("   |   FAILED\n");
    }


    printf("\n---------------TESTING COMPLETE: %s---------------", TEST_CARD);
    printf("\n---------------RESULTS: %i/%i State-checks Passed----------------\n\n", testPassCount, 7);


}