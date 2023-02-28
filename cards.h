#ifndef CARDS_H_
#define CARDS_H_

#include <string>
#include <vector>

using namespace std;

class card {
	//could make private with getters but lmao who cares
public:
	string name;
	string description;
	string op;
	int actionCost;
	int singleOpNum; //0 if combineing selected numbers
	bool all; //all numbers are selected

	int(*Op)(int, int);//if single op num zero, two or more numbers are consumed to make a single num

	card(string n, string o,  int cost, int opNum, bool a, int(*O)(int, int), string d) {
		name = n;
		description = d;
		op = o;
		actionCost = cost;
		singleOpNum = opNum;
		all = a;
		Op = O;
	}
};

int addNum(int i, int num) { return i + num; }
int subNum(int i, int num) { return i - num; }
int mulNum(int i, int num) { return i * num; }
int divNum(int i, int num) { return i / num; }
int modNum(int i, int num) { return i % num; }
int meanNum(int i, int num) { return (i + num) / 2; }

#endif CARDS_H_
