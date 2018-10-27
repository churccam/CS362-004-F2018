
/*
int handCard(int handNum, struct gameState *state);
enum value of indexed card in player's hand

 int handCard(int handPos, struct gameState *state) {
  int currentPlayer = whoseTurn(state);
  return state->hand[currentPlayer][handPos];
}

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

int main(int arcg, char** argv){
    int seed = 700;
    int numPlayers = 4;
    int currentPlayer = 0;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    int expectedValue;
    int test_passed = 0;
    int countValue;

    //initialize game state
    struct gameState default_GS, test_GS;

    initializeGame(numPlayers, k, seed, &test_GS);

    for(int i = 0; i < numPlayers; i++){

    }
}