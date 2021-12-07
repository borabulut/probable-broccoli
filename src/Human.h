#ifndef HUMAN_H
#define HUMAN_H
#include "MancalaPlayer.h"

class Human: public MancalaPlayer {
public:
	// constructor
	Human(MancalaBoard& board);

	// think of a move
	int chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic, Game game);

	// get status of the game (who's turn it is)
	bool getTurn() const { return turn; }
	void setTurn(bool t) { if (t==true) { turn=true; } if (t==false) { turn=false; } return;}

private:
	bool turn; // my turn?
};

#endif
