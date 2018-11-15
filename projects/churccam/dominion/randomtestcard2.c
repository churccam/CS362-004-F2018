
/*
 * randomtestcard2.c
 *
 * Description: random tests for smithy card
 *
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

void checkSmithyCard(int player, struct gameState *post, int *deckCountErrors, int *handCountErrors, int *discardCountErrors, int *cardEffectErrors){
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

    int preDeckCount = post->deckCount[player];
    int preHandCount = post->handCount[player];
    int preDiscardCount = post->discardCount[player];

    //use card - desired card effects: +3 cards to handCount, +1 to discardCount, -3 to deckCount
    int cardEffect_check = cardEffect(smithy, choice1, choice2, choice3, post, handpos, &bonus);

    //check values - increment error count when needed
    if(post->deckCount[player] != preDeckCount-3){
        *deckCountErrors += 1;
    }
    if(post->handCount[player] != preHandCount+3){
        *handCountErrors += 1;
    }
    if(post->discardCount[player] != preDiscardCount+1){
        *discardCountErrors += 1;
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
    int cardEffectErrors = 0;
    initializeGame(numPlayers, k, seed, &G); //initialize default game state
    printf("----------------- Testing Card: %s ----------------\n", TEST_CARD);

    for (n = 0; n < testNumber; n++) {
        p = floor(Random() * 2); //randomize player
        G.deckCount[p] = floor(Random() * MAX_DECK);
        G.discardCount[p] = floor(Random() * MAX_DECK);
        G.handCount[p] = floor(Random() * MAX_HAND);

        checkSmithyCard(p, &G, &deckCountErrors, &handCountErrors, &discardCountErrors, &cardEffectErrors);
    }

    printf("Deck count errors found in %i / %i test cases\n", deckCountErrors, testNumber);
    printf("Hand count errors found in %i / %i test cases\n", handCountErrors, testNumber);
    printf("Discard count errors found in %i / %i test cases\n", discardCountErrors, testNumber);
    printf("Card effect errors found in %i / %i test cases\n", cardEffectErrors, testNumber);
    printf("----------------- Testing Complete -----------------\n\n");



    return 0;
}




