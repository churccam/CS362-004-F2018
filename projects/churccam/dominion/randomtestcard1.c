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

void checkVillageCard(int player, struct gameState *post, int *deckCountErrors, int *handCountErrors, int *discardCountErrors, int *actionCountErrors, int *cardEffectErrors){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int preDeckCount = post->deckCount[player];
    int preHandCount = post->handCount[player];
    int preDiscardCount = post->discardCount[player];
    int preActionCount = post->numActions;

    //use card - desired card effects: +1 card to handCount, +2 actions to numActions, +1 to discardCount, -1 to deckCount
    int cardEffect_check = cardEffect(village, choice1, choice2, choice3, post, handpos, &bonus);

    //check values - increment error count when needed
    if(post->deckCount[player] != deckCountErrors-1){
        *deckCountErrors += 1;
    }
    if(post->handCount[player] != preHandCount+1){
        *handCountErrors += 1;
    }
    if(post->discardCount[player] != preDiscardCount+1){
        *discardCountErrors += 1;
    }
    if(post->numActions != preActionCount + 2){
        *actionCountErrors += 1;
    }
    if(cardEffect_check != 0){
        *cardEffectErrors += 1;
    }

}

int main () {

    int n;
    int p;
    int testNumber = 5000;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    struct gameState G;

    int deckCountErrors = 0;
    int handCountErrors = 0;
    int discardCountErrors = 0;
    int actionCountErrors = 0;
    int cardEffectErrors = 0;
    initializeGame(numPlayers, k, seed, &G); //initialize default game state
    printf("----------------- Testing Card: %s ----------------\n", TEST_CARD);

    for (n = 0; n < testNumber; n++) {
        p = floor(Random() * 2); //randomize player
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);

        checkVillageCard(p, &G, &deckCountErrors, &handCountErrors, &discardCountErrors, &actionCountErrors, &cardEffectErrors);
        //checkDrawCard(p, &G);
    }

    printf("Deck count errors found in %i / %i test cases\n", deckCountErrors, testNumber);
    printf("Hand count errors found in %i / %i test cases\n", handCountErrors, testNumber);
    printf("Discard count errors found in %i / %i test cases\n", discardCountErrors, testNumber);
    printf("Action count errors found in %i / %i test cases\n", actionCountErrors, testNumber);
    printf("Card effect errors found in %i / %i test cases\n", cardEffectErrors, testNumber);
    printf("----------------- Testing Complete -----------------\n\n");



    return 0;
}




