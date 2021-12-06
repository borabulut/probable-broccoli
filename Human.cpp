#include "Human.h"
#include <iostream>
using namespace std;

// constructor of Human (creates a MancalaPlayer with Side HUMAN)
Human::Human(MancalaBoard& board) : MancalaPlayer(board, HUMAN), turn(false) {}

// the chooseMove determines the best move, this move (or pit) is stored in bestMove
int Human::chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic, Game game) {
	// not implemented for HUMAN
	return 0;
}
