#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <time.h>


//Prototyupe not in dominion.h, included here
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

void randomtestcard1()
{
	
	srand(time(0));
	
	int outpostReturn;
	int bonus;
	int handpos;
	int player;
	int whereCard;
	int cardIncluded = 0;
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
		s1.outpostPlayed = 0; 
		s1.discardCount[player] = 0;//no cards will start in the discard pile
		
		s1.deckCount[player] = deckSize -  handSize;
		s1.handCount[player] = handSize;
		
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
		whereCard = 0;
		while (checkCard == 0){
			if(s1.hand[player][whereCard] == outpost){
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
	
	printf("handcount: %d -- outpostPlayed: %d -- hand: %d \n", s1.handCount[player], s1.outpostPlayed, s1.hand[player][whereCard]);
	//outpost does not have a choice associated with it. Choice 1, 2 and 3 are all default
	outpostReturn = cardEffect(outpost, 1, 1, 1, &s1, handpos, &bonus);
	//outpost calls discardCard which is not tested by this unit test, it should be unit tested separately
	
	printf("handcount: %d -- outpostPlayed: %d -- hand: %d \n", s1.handCount[player], s1.outpostPlayed, s1.hand[player][whereCard]);

	if((outpostReturn == 0) && (s1.outpostPlayed == 1) && (s1.handCount[player] == (handSize - 1))) printf("-----RandomTestCard1 OUTPOST IS SUCCESSFUL-----\n");
	else printf("-----RandomTestCard1-OUTPOST FAILED-----\n");
	
	
}

int main()
{
	printf("\n-----STARTING RandomTestCard1:OUTPOST-----\n");
	randomtestcard1();
	printf("-----Finished RandomTestCard1:OUTPOST-----\n");
}
