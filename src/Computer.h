#ifndef COMPUTER_H
#define COMPUTER_H
#include "MancalaPlayer.h"

// class of CPU (derived from MancalaPlayer)
class Computer: public MancalaPlayer {
public:
	// constructor
	Computer(MancalaBoard& board);

	// think of a move...
	int chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic, Game game);

	// get status of the game (who's turn it is)
	bool getTurn() const { return turn; }
	void setTurn(bool t) { if (t==true) { turn=true; } if (t==false) { turn=false; } return;}

private:
	bool turn; // my turn?
	int depth; // number of turns that is looked ahead
	int step; // number of steps within a turn that is tried
};

#endif
