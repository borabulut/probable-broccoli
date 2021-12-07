#ifndef MANCALAPLAYER_H
#define MANCALAPLAYER_H

#include "MancalaBoard.h"

class MancalaPlayer {
public:
	enum Side { HUMAN, COMPUTER };
	enum Lastpit { TRYAGAIN, STORE, EMPTY, PIT };
	enum Tactic { GREEDY, LOOKAHEAD };
	enum Game {STANDARD, AVALANCHE };

	// constructor
	MancalaPlayer(MancalaBoard board, Side side);

	// get status, virtual functions; each player keeps track of the status itself
	virtual bool getTurn() const = 0;
	virtual void setTurn(bool turn) = 0;
	// the chooseMove functions have a different implementation for HUMAN and CPU
	virtual int chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic, Game game) = 0;

	// these functions are the same for every player
	Lastpit sow(MancalaBoard& board, Side side, int frompit, Game game);
	void steal(MancalaBoard& board, Side side, int lastpit);

private:
	Side side;
	MancalaBoard board;
};

#endif
