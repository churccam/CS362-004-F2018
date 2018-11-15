//
// Random testing
// Card being tested: village
// Village effect: +2 Actions, +1 Card from deck
//

/*
 * randomtestcard1.c
 *
 * Description: random tests for village card
 *
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c.c dominion.o rngs.o $(CFLAGS)
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

/*
Village
Original card effect found in switch statement
case village:
      //+1 Card
      drawCard(currentPlayer, state);

      //+2 Actions
      state->numActions = state->numActions + 2;

      //discard played card from hand
      discardCard(handPos, currentPlayer, state, 0);

*/
// what is being tested: cardEffect() - village
// village_cardEffect(currentPlayer, state, handPos); - + 1 card, +2 actions
// input parameters that need to be random - currentPlayer, state, handPos
// dependesis - things we need to check after running: deck count, hand count, discard count, actions

int checkVillageCard(int player, struct gameState *post, int *deckCountErrors, int *handCountErrors, int *discardCountErrors, int *actionCountErrors){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    
    int preDeckCount = post->deckCount[player];
    int preHandCount = post->handCount[player];
    int preDiscardCount = post->discardCount[player];
    int preActionCount = post->numActions;

    int cardEffect_check = cardEffect(village, choice1, choice2, choice3, post, handpos, &bonus);


}

int main () {

    int n;
    int p;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState G;

    int deckCountErrors = 0;
    int handCountErrors = 0;
    int discardCountErrors = 0;
    int actionCountErrors = 0;
    initializeGame(numPlayers, k, seed, &G); //initialize default game state
    printf("----------------- Testing Card: %s ----------------\n", TEST_CARD);

    for (n = 0; n < 2000; n++) {
        p = floor(Random() * 2); //randomize player
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);

        checkVillageCard(p, &G, &deckCountErrors, &handCountErrors, &discardCountErrors, &actionCountErrors);
        //checkDrawCard(p, &G);
    }

    return 0;
}




