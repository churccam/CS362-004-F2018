//If the program hangs, there is a known bug. If there are less than 2 treasure cards in the deck, the cardEffect call to adventurer will freeze in a while loop located in the adventurer card code

#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include <time.h>

//Prototyupe not in dominion.h, included here
int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus);

void randomtestadventurer()
{
	srand(time(0));
	
	int bonus;
	int handpos;
	int cardIncluded = 0;
	int i;
	int player;
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
			if(s1.hand[player][whereCard] == adventurer){
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

	//how many treasure cards are in the hand and in the deck
	int treasureCountHand = 0;
	for( i = 0; i < handSize; i++)
	{
		if((s1.hand[player][i] == copper) || (s1.hand[player][i] == silver) || (s1.hand[player][i] == gold))treasureCountHand++;
	}
	int treasureCountDeck = 0;
	for( i = 0; i < deckSize; i++)
	{
		if((s1.deck[player][i] == copper) || (s1.deck[player][i] == silver) || (s1.deck[player][i] == gold))treasureCountDeck++;
	}
	
	printf("hand treasure count %d deck treasure count %d total hand count %d total deck count %d\n", treasureCountHand, treasureCountDeck, s1.handCount[player], s1.deckCount[player]);
	cardEffect(adventurer, 1, 1, 1, &s1, handpos, &bonus);
	
	int treasureCountHandAfter = 0;
	for( i = 0; i < s1.handCount[player]; i++)
	{
		if((s1.hand[player][i] == copper) || (s1.hand[player][i] == silver) || (s1.hand[player][i] == gold))treasureCountHandAfter++;
	}
	int treasureCountDeckAfter = 0;
	for( i = 0; i < s1.deckCount[player]; i++)
	{
		if((s1.deck[player][i] == copper) || (s1.deck[player][i] == silver) || (s1.deck[player][i] == gold))treasureCountDeckAfter++;
	}
	printf("hand treasure count %d deck treasure count %d total hand count %d total deck count %d\n", treasureCountHandAfter, treasureCountDeckAfter, s1.handCount[player], s1.deckCount[player]);

	if(treasureCountDeck == 2)
	{		
		printf("Deck has 2 Treasure Cards. Playing the Adventurer card results in the hand gaining 2 treasure cards and the deck losing 2 treasure cards. Adventurer card is discarded.\n");
		if((treasureCountHand + 2 == treasureCountHandAfter) && (treasureCountDeck - 2 == treasureCountDeckAfter))
		{
			printf("Adventurer Card Random Test ----- SUCCESSFUL\n");
		}
		else printf("Adventurer Card Random Test ----- UNSUCCESSFUL\n");
	}
	else if(treasureCountDeck == 1)
	{
				printf("Deck has 1 Treasure Card. Playing the Adventurer card results in the hand gaining 1 treasure cards and the deck losing 1 treasure cards. Adventurer card is discarded.\n");
		if((treasureCountHand + 1 == treasureCountHandAfter) && (treasureCountDeck - 1 == treasureCountDeckAfter))
		{
			printf("Adventurer Card Random Test ----- SUCCESSFUL\n");
		}
		else printf("Adventurer Card Random Test ----- UNSUCCESSFUL\n");
	}
	else if (treasureCountDeck == 0)
	{
				printf("Deck has 0 Treasure Cards. Playing the Adventurer card results in the hand gaining 0 treasure cards and the deck losing 0 treasure cards. Adventurer card is discarded.\n");
		if((treasureCountHand + 0 == treasureCountHandAfter) && (treasureCountDeck - 0 == treasureCountDeckAfter))
		{
			printf("Adventurer Card Random Test ----- SUCCESSFUL\n");
		}
		else printf("Adventurer Card Random Test ----- UNSUCCESSFUL\n");
	}
	else
	{
		printf("Deck has MORE than 2 Treasure Cards. Playing the Adventurer card results in the hand gaining 2 treasure cards and the deck losing 2 treasure cards. Adventurer card is discarded.\n");
		if((treasureCountHand + 2 == treasureCountHandAfter) && (treasureCountDeck - 2 == treasureCountDeckAfter))
		{
			printf("Adventurer Card Random Test ----- SUCCESSFUL\n");
		}
		else printf("Adventurer Card Random Test ----- UNSUCCESSFUL\n");
	}
	
}

int main()
{
	printf("-----STARTING RANDOM TEST:Adventurer-----\n");
	randomtestadventurer();
	printf("-----Finished RANDOM TEST:Adventurer-----\n");
}
