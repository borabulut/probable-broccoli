#ifndef MANCALABOARD_H
#define MANCALABOARD_H

#include <string>
#include <algorithm>
#include <iterator>
#include <climits>
#include <vector>
#include <ctime>
#include <cstdlib>


using namespace std;

class MancalaBoard {
public:
	typedef vector<int> Field;

	//constructor
	MancalaBoard(int pits, int stones);

	// public member functions (const)
	void printBoard(void) const;
	int gameOver(void) const;
	int getNumberOfPits(void) const { return pits; };
	int getNumberOfStones(void) const { return stones; };
	int getField(int index) const;
	Field getField(void) const;
	// non-const
	void setField(int index, int value);
	void addField(int index, int add);

private:
	Field field; // vector<int>
	int pits; // number of pits per player
	int stones; // number of stones per pit
};

#endif
