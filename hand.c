#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <string.h>

#include "helper"
#define SUITS 4
#define DECK 6
#define PRINT_DEBUG 1

//creates hand struct and initalizes fields
Hand* createHand(){

        Hand *newHand = malloc(sizeof (Hand*));
        newHand->firstCard = NULL;
        newHand->num_cards_in_hand = 0;
        return newHand;
}
//adds card to hand
void addCardToHand(Card *card, Hand *hand){

        CardNode *cardNode = malloc(sizeof(cardNode));
        cardNode->thisCard = card;

        if (hand->num_cards_in_hand == 0){
        cardNode->nextCard = NULL;
        cardNode->prevCard = NULL;
        hand->firstCard = cardNode;
        }
        else{
        hand->firstCard->prevCard = cardNode;
        cardNode->nextCard = hand->firstCard;
        hand->firstCard = hand->firstCard->prevCard;
        hand->firstCard->prevCard = NULL;
        }
}
//removes a card from hand
Card* removeCardFromHand(Card *card, Hand *hand){


        CardNode* cardToRemove = isCardInHand(card,hand);

        if(cardToRemove == NULL){
                return card;
        }
        if(cardToRemove == hand->firstCard){
                hand->firstCard = cardToRemove->nextCard;
        }
        if(cardToRemove->prevCard != NULL){
                cardToRemove->prevCard->nextCard = cardToRemove->nextCard;
        }
        if(cardToRemove->nextCard != NULL){
                cardToRemove->nextCard->prevCard = cardToRemove->prevCard;
        }
        hand->num_cards_in_hand--;

        free(cardToRemove);
        return card;
}
//checks if deck is empty
int isHandEmpty(Hand* hand){
        if(hand->num_cards_in_hand == 0){
                return 0;
        }
        else{
                return 1;
        }
}
//destroys hand
void destroyHand(Hand* hand){
        CardNode* nodeToDestroy = hand->firstCard;
        CardNode* next = hand->firstCard;
        while(nodeToDestroy != NULL){
                next = nodeToDestroy->nextCard;
                removeCardFromHand(nodeToDestroy->thisCard, hand);
                nodeToDestroy = next;
        }
        free(hand);//frees memory

}
// custom method used to find a cards suit value and see if it compares against the lead card of is legal move function
int handContainsSuit(Hand *hand, Suit suit){
	
	CardNode* node = hand->firstCard;

	for(int i = 0;i<(int)hand->num_cards_in_hand;i++){
		if((int)node->thisCard->suit ==(int)suit){
			return 0;// return 0 if the suit is returned in the hand 0 is false
		}
		else{
			node = node->nextCard;
		}
	}
	return 1;
}
//given lead card, itterate through opposing players hand to see wheather or not they have a matching suit
int isLegalMove(Hand *hand, Card *leadCard, Card *playedCard){

	if(leadCard->suit == playedCard->suit){
		return 1;
	}
	else{
		return handContainsSuit(hand,(Suit)leadCard->suit);
	}

}
//returns 1 if the person who led wins and 0 if the person that follows wins
int whoWon(Card *leadCard, Card *followedCard, Suit trump){

	if(leadCard->suit == followedCard->suit){
		return (leadCard->name > followedCard->name);
	}	
	else{
		if(followedCard->suit == trump){
			return 0;
		}
		else{
			return 1;
		}
	}
}
//takes cards out of hand and puts them back in the deck
void returnHandToDeck(Hand *hand, Deck *deck){
	
  while (hand->num_cards_in_hand != 0){
                deck = pushCardToDeck(hand->firstCard->thisCard, deck);
		hand->firstCard = hand->firstCard->nextCard;
		hand->num_cards_in_hand--;
  }		
}
