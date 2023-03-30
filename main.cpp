#include "table.h"
#include "Globals.h"

#include <iostream>
#include <queue>

vector<tableState*> endStates(tableState* startState);

tableState* challengeGenerator(vector<tableState*>& endStates, tableState* startState);

string forCollin(tableState start, tableState end);

int main() {
	table tableSetup = table();
	
	tableState* startState = tableSetup.setTable();
	
	vector<tableState*> vecEndStates = endStates(startState);

	tableState* end = challengeGenerator(vecEndStates, startState);

	string temp = forCollin(*startState, *end);

	cout << temp;
	
	return 0;
}

vector<tableState*> endStates(tableState* startState) {
	vector<tableState*> terminatedStates;
	queue<tableState*> statesToExplore;

	statesToExplore.push(startState);

	while (!statesToExplore.empty()) {
		tableState* cur = statesToExplore.front();
		statesToExplore.pop();
		//if children found false appeneded to end sates
		bool childrenFound = false;

		for (int i = 0; i < cur->cardsInHand.size(); i++) {
			if (cur->cardsInHand[i]->actionCost <= cur->remainingActionPoints) {
				//checks if singlo op or two op equasion
				if (cur->cardsInHand[i]->singleOpNum == 0) {
					//cannot do op on two nums if there is only one
					if (cur->tableNumbers.size() > 1) {
						childrenFound = true;
						//if does not apply to all
						if (!cur->cardsInHand[i]->all) {
							for (int x = 0; x < cur->tableNumbers.size(); x++) {
								for (int y = 0; y < cur->tableNumbers.size(); y++) {
									//cant operate on self
									if (x != y) {
										//prevent devide by 0
										if (cur->tableNumbers[y] != 0 || (cur->cardsInHand[i]->op != "/" && cur->cardsInHand[i]->op != "%")) {
											//saves action, sets parent and child, exc
											tableState* child = new tableState(cur, cur->cardsInHand[i]);
											//saves numbers consumed
											child->prev->numsUsed.push_back(child->tableNumbers[x]);
											child->prev->numsUsed.push_back(child->tableNumbers[y]);

											//table table num = operation (table num op const card num)
											child->tableNumbers[x] = child->cardsInHand[i]->Op(child->tableNumbers[x], child->tableNumbers[y]);
			
											//removes y, as they combine
											child->tableNumbers.erase(child->tableNumbers.begin() + y);
											//removes card from pool
											child->cardsInHand.erase(child->cardsInHand.begin() + i);

											statesToExplore.push(child);
										}
									}
								}
							}
						}
					}
				}
				else {
					childrenFound = true;
					//if does not apply to all
					if (!cur->cardsInHand[i]->all) {
						for (int num = 0; num < cur->tableNumbers.size(); num++) {
							//saves action, sets parent and child, exc
							tableState* child = new tableState(cur, cur->cardsInHand[i]);
							//saves numbers consumed
							child->prev->numsUsed.push_back(child->tableNumbers[num]);
							child->prev->numsUsed.push_back(child->cardsInHand[i]->singleOpNum);
							//table table num = operation (table num op const card num)

							child->tableNumbers[num] = child->cardsInHand[i]->Op(child->tableNumbers[num], child->cardsInHand[i]->singleOpNum);
							
							//removes card from pool
							child->cardsInHand.erase(child->cardsInHand.begin() + i);

							statesToExplore.push(child);
						}
					}
				}
			}
		}

		if (!childrenFound) {
			terminatedStates.push_back(cur);
		}
	}

	return terminatedStates;
}

tableState* challengeGenerator(vector<tableState*>& endStates, tableState* startState) {
	
	tableState* bestEndState = endStates[0];
	float bestHeuristic = 0;

	vector<int> startingTable = startState->tableNumbers;

	int startingTableSize = startingTable.size();

	for (int i = 0; i < endStates.size(); i++){
		//int cardsUsed=startState.cardsInHand.size() - endStates[i].cardsInHand.size();
		int actionPointsExpended=startState->remainingActionPoints - endStates[i]->remainingActionPoints;
		int lengthOfPath=endStates[i]->actionsTaken;

		int heuristicValues = startingTableSize;
		float heuristicPath = lengthOfPath + ((float)actionPointsExpended / lengthOfPath);

		if (heuristicPath != 0){
			for (int x = 0; x < startingTableSize; x++) {
				for (int y = 0; y < endStates[i]->tableNumbers.size(); y++) {
					if (startingTable[x] == endStates[i]->tableNumbers[y] || endStates[i]->tableNumbers[y] == 0) {
						heuristicValues--;
						break;
					}
				}
			}
		}

		if (heuristicPath + heuristicValues > bestHeuristic) {
			bestHeuristic = heuristicPath + heuristicValues;
			bestEndState = endStates[i];
		}
	}

	return bestEndState;
}

string forCollin(tableState start, tableState end) {
	string tableStart;
	string tableEnd;
	string cards;

	for (int i = 0; i < start.tableNumbers.size(); i++) {
		tableStart += to_string(start.tableNumbers[i]);
		if (i + 1 != start.tableNumbers.size()) { tableStart += ","; }
	}

	for (int i = 0; i < end.tableNumbers.size(); i++) {
		tableEnd += to_string(end.tableNumbers[i]);
		if (i + 1 != end.tableNumbers.size()) { tableEnd += ","; }
	}

	for (int i = 0; i < start.cardsInHand.size(); i++) {
		cards += "["
				"\"" + start.cardsInHand[i]->name + "\","
				"\"" + start.cardsInHand[i]->description + "\","
				"\"" + start.cardsInHand[i]->op + "\","
				+ to_string(start.cardsInHand[i]->singleOpNum) + ","
				+ to_string(start.cardsInHand[i]->all) + ","
				+ to_string(start.cardsInHand[i]->actionCost) +
				"]";

		if (i + 1 != start.cardsInHand.size()) { cards += ",\n"; }
				 
	}

	return  "{\n"
			"	\"State\": {\n"
			"		\"Board\": [" + tableStart + "],\n"
			"		\"Hand\":[\n" + cards + "\n],\n"
			"		\"Energy\":" + to_string(start.remainingActionPoints) +
			"	\n},\n"
			"	\"Goal\": [" + tableEnd + "]\n"
			"}";
			
}