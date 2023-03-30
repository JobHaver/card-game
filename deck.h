#ifndef DECK_H_
#define DECK_H_

#include "cards.h"

class deck {
public:
	vector<card*> cards;

	deck() {}

	deck(vector<int> nums) {
		cards.push_back(new card("add two numbers", "+", 1, 0, false, addNum,
			"This card will take two numbers, add them, and output the sum."));
		cards.push_back(new card("sub two numbers", "-", 1, 0, false, subNum,
			"This card will take two numbers, subtracts the second from the first, and output the difference."));
		cards.push_back(new card("mult two numbers", "*", 1, 0, false, mulNum,
			"This card will take two numbers, multiply them, and output the product."));
		cards.push_back(new card("div two numbers", "/", 1, 0, false, divNum,
			"This card will take two numbers, divides the first by the second, and output the quotient."));
		cards.push_back(new card("mod two numbers", "%", 1, 0, false, modNum,
			"This card will take two numbers, mod the first by the second, and output the remainder."));
		cards.push_back(new card("mean two numbers", "mean", 1, 0, false, meanNum,
			"This card will take two cards, sum them together, divide the sum by two, and output the average."));
		
		for (int i = 0; i < nums.size(); i++) {
			nums[i]; //this is the num
			std::string a= std::to_string(nums[i]);
			cards.push_back(new card("add " + a, "+", 1, nums[i], false, addNum,
				"This card will take an number, add " + a +  " to it, and output the sum."));
			cards.push_back(new card("sub " + a, "-", 1, nums[i], false, subNum,
				"This card will take an number, subtract " + a +  " from it, and output the difference."));
			cards.push_back(new card("mult by " + a, "*", 1, nums[i], false, mulNum,
				"This card will take an number, multiply it by " + a +  ", and output the product."));
			cards.push_back(new card("div by " + a, "/", 1, nums[i], false, divNum,
				"This card will take an number, mod it by " + a +  ", and output the quotient."));
			cards.push_back(new card("mod by " + a, "%", 1, nums[i], false, modNum,
				"This card will take an number, divide it by " + a +  ", and output the remainder."));
			cards.push_back(new card("mean with " + a, "mean", 1, nums[i], false, meanNum,
				"This card will take an number, sum it with " + a +  ", divide the result by two, and output the average."));
		}
	}
};

#endif