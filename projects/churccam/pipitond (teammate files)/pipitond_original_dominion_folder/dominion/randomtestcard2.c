#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <time.h>

//Prototyupe not in dominion.h, included here
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

void randomtestcard2()
{
	
	srand(time(0));
	
	int smithyReturn;
	int bonus;
	int handpos;
	int cardIncluded = 0;
	int player;
	int discardSize = 0; //the smithy card should be discarded after the call. before the call there is nothing in discard pile. If there was cards before the call the discard pile should be increased by one after the call
	struct gameState s1;
	
	//randomise the size of the deck and hand
	int deckSize = rand() % (MAX_DECK + 1);
	int handSize = rand() % (deckSize + 1);
	
	while(cardIncluded == 0)
	{
		//10 cards that the deck can be comprised of
		int k[10] = {adventurer, outpost, smithy, curse, estate, copper, gold, silver, gardens, village};

		player = rand() % 2;   //randomize player
		s1.whoseTurn = player;
		s1.discardCount[player] = 0;//no cards will start in the discard pile
		
		s1.deckCount[player] = deckSize -  handSize;
		s1.handCount[player] = handSize;
		s1.discardCount[player] = 0;
		
		int i;
		for (i = 0; i < handSize; i++){
			//randomly fill in the hand
			int cardInsert = (rand()  % 10);
			s1.hand[player][i] = k[cardInsert];
		}
		
		for (i = 0; i < deckSize; i++){
			//randomly fill in the deck
			int cardInsert = (rand()  % 10);
			s1.deck[player][i] = k[cardInsert];
		}
		
		//In order to test cardEffect, the card must be in the hand of the user.
		//The first occurance will be used as the handpos for the cardEffect call.
		//If the hand does not contain the desired card, the deck and hand will be randomly assigned again.
		int checkCard = 0;
		int whereCard = 0;
		while (checkCard == 0){
			if(s1.hand[player][whereCard] == smithy){
				handpos = whereCard;
				checkCard = 1;
				cardIncluded = 1;
			}
			else if (whereCard == *s1.handCount){
				//the card is not in the hand
				checkCard = 1;
			}
			else{
				whereCard++;
			}
		}
		
	}//if the card is not found in the hand, randomize the hand and deck again.
	
	printf("handcount: %d -- deckcount %d -- discardcount %d\n", s1.handCount[player], s1.deckCount[player], s1.discardCount[player]);
	
	smithyReturn = cardEffect(smithy, 1, 1, 1, &s1, handpos, &bonus);
	//smithy calls discardCard which is not tested by this unit test, it should be unit tested separately
	
	printf("handcount: %d -- deckcount %d -- discardcount %d\n", s1.handCount[player], s1.deckCount[player], s1.discardCount[player]);

	//originalHandCount is used to make sure that smithy increases hand count. Smithy draws three but discards 2, resulting in net gain of 2.
	//originalHandCount + 2 is currently used to test the netgain of the smithy card 
	if((smithyReturn == 0) && (s1.handCount[player] == handSize + 2) && (s1.deckCount[player] == deckSize - 3) && (s1.discardCount[player] == discardSize + 1)) printf("-----RANDOMTESTCARD2-SMITHY IS SUCCESSFUL-----\n");
	else printf("-----RANDOMTESTCARD2-SMITHY FAILED-----\n");
	
	
}

int main()
{
	printf("\n-----STARTING RANDOMTESTCARD2:SMITHY-----\n");
	randomtestcard2();
	printf("-----Finished RANDOMTESTCARD2:SMITHY-----\n");
}
