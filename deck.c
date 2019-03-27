#include <stdio.h>
#include <stdlib.h>
#include "helper"
#define PRINT_DEBUG 1
#define FULLDECK 24

//creates deck
Deck* createDeck(){
        
	Deck *newDeck = malloc(sizeof(Deck));
	newDeck->topCard = -1;
	return newDeck;
}
//pushes card to the top of the deck
Deck* pushCardToDeck(Card* card, Deck* deck){

	for(int i =0;i<=NUM_CARDS_IN_DECK;i++){
		
		if (deck->cards[i] == NULL){
			deck->cards[i] = card;
			return deck;
		}
	}	
	return deck;
}
//peeks at top card
Card* peekAtTopCard(Deck* deck){

	return deck->cards[deck->topCard];

}
//pops card from top of deck
Card* popCardFromDeck(Deck* deck){

	if( deck->topCard == -1){
		return NULL;
	}
	else{
	
		Card* cardToBeRemoved = deck->cards[deck->topCard];
		deck->cards[deck->topCard] = NULL; //sets top card to null
		deck->topCard--;
		return cardToBeRemoved;
	}

}
//checks if the deck is empty
int isDeckEmpty(Deck* deck){
	
	if(deck->topCard){
		return 1;
	}
	else{
		return 0;
	}

}
//destroys deck and frees memory
void destroyDeck(Deck* deck){

	for(int i=0;i<=deck->topCard;i++){
		
		free(deck->cards[i]);
	}
	free(deck);
}
//creates card
Card* createCard(Suit suit, Name name){

	Card *newCard = malloc(sizeof(Card));
	newCard->suit = suit;
	newCard->name = name;
	return newCard;	

}
//destroys card
void destroyCard(Card* card){

	free(card);
}

//returns card if it is in the hand, otherwise returns null
CardNode* isCardInHand(Card* card, Hand* hand){

	CardNode* cardNode = hand->firstCard;
		while(cardNode != NULL){
			if(cardNode->thisCard == card){
				return cardNode;
	                      	}
				cardNode = cardNode->nextCard;
		}

		return NULL;
}
//looks through the suits and values until deck is filled
Deck* populateDeck(){
 	
	Deck *newDeck = createDeck();
	int is_deck_populated = 0;
  	int i = 0;	 
	
	Suit s = HEARTS;
	Name n = 9;
	for(; s <= DIAMONDS; s++) {
   		 for(; n <= ACE; n++) {
			 createHand(s,n);
			 newDeck->cards[i] = createCard(s,n);	 
    }			
  }
}
//shuffles deck by placing random cards in different places within the deck
void shuffle(Deck *aDeck)
{
    int i;
    srand(0);
    for (i = 0; i < NUM_CARDS_IN_DECK; i++)
    {
        int randCard = rand() % FULLDECK;
        Card *tmpCard = aDeck->cards[i];
        aDeck[i] = aDeck[randCard];
        aDeck->cards[randCard] = tmpCard;
    }
}
//pops cards from deck alternating from player one to player two until hands are full 
void deal(Deck *aDeck, Hand *p1hand, Hand *p2hand){

        for(int i =0;i<NUM_CARDS_IN_HAND;i++){
                addCardToHand(popCardFromDeck(aDeck), p1hand);
                addCardToHand(popCardFromDeck(aDeck), p2hand);
        }
}
