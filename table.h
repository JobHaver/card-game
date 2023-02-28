#ifndef TABLE_H_
#define TABLE_H_

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include "deck.h"
#include "Globals.h"

struct prevAction {
	card* card;
	vector<int> numsUsed;
};

struct tableState {
	vector<int> tableNumbers;
	vector<card*> cardsInHand;

	prevAction* prev;

	int remainingActionPoints;
	int actionsTaken;

	tableState* parentState;
	vector<tableState*> childStates;

	tableState() {}

	//used to make children states with a specific card action
	tableState(tableState* og, card* c) {
		tableNumbers = og->tableNumbers;
		cardsInHand = og->cardsInHand;

		prev = new prevAction();
		prev->card = c;

		remainingActionPoints = og->remainingActionPoints - c->actionCost;
		actionsTaken = og->actionsTaken + 1;

		parentState = og;
		og->childStates.push_back(this);
	}
};

class table {
public:
	tableState* setTable() {
		tableState* startingState = new tableState();

		srand(time(NULL));

		for (int i = 0; i < NUM_VALUES_ON_TABLE; i++) {
			startingState->tableNumbers.push_back(rand() % (TABLE_VALUES_HIGH - TABLE_VALUES_LOW) + TABLE_VALUES_LOW);
		}

		vector<int> randCardNumbers;

		//chosen num cards in hand so that all nums have possibility to be random in hand
		for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
			randCardNumbers.push_back(rand() % (CARD_VALUES_HIGH - CARD_VALUES_LOW) + CARD_VALUES_LOW);
		}

		deck tempDeck = deck(randCardNumbers);

		for (int i = 0; i < NUM_CARDS_IN_HAND; i++) {
			startingState->cardsInHand.push_back(tempDeck.cards[rand() % tempDeck.cards.size()]);
		}

		startingState->remainingActionPoints = ACTION_POINTS_AVALIBLE;
		startingState->actionsTaken = 0;
		startingState->parentState = NULL;
		startingState->prev = NULL;

		return startingState;
	}

	void cleanTable(tableState* startState) {
		//if i cared about dealocating memory it would go here
	}
};

#endif TABLE_H_