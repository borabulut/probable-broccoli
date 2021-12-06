#include "Computer.h"
#include <iostream>
using namespace std;

#define CPU_WIN 10000 // high value
#define HUMAN_WIN -10000 // low value
#define DRAW -5000 // low value: CPU doesn't want to play draw
#define NO_MOVES -100000
#define MAX_DEPTH 4 // number of moves to lookahead by CPU (when tactic = lookahead)

// constructor of CPU (creates a MancalaPlayer with Side COMPUTER)
Computer::Computer(MancalaBoard& board) : MancalaPlayer(board, COMPUTER), turn(false), depth(0), step(0) {}

// the chooseMove determines the best move, this move (or pit) is stored in bestMove
int Computer::chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic, Game game) {
	//cout << "CPU is in chooseMove" << endl;
	depth++;
	int* a = NULL;
	a = new int[board.getNumberOfPits()];
	MancalaBoard boardcopy = board;
	int dummy; //dummy variable

	//-------------------------------------GREEDY----------------------------------------
	// Finds the maximum number of stones that can be taken in 1 turn
	// The best move will be the move that takes as many as possible stones
	// before it is HUMAN's turn again.
	//-----------------------------------------------------------------------------------
	if (tactic == GREEDY) {
		// apply greedy tactic
		int score = board.getField(2*board.getNumberOfPits()+1); // number of stones in pit
		int computerpits = 0;
		for (int i=board.getNumberOfPits()+1; i<(2*board.getNumberOfPits()+1);i++){ // for each pit determine the movevalue
			int movevalue = score;
			if (board.getField(i) != 0){ // Only sow if there are stones in the pit
				Lastpit reply = sow(boardcopy, side, i, game);
				movevalue = boardcopy.getField(2*board.getNumberOfPits()+1) - score;
				if (reply == STORE) {
					a[computerpits] = movevalue + chooseMove(dummy, side, boardcopy, GREEDY, game); // recursive call to chooseMove
				} else {
					a[computerpits] = movevalue;
				}
			} else { // no stones, no sow action -> low movevalue
				a[computerpits] = NO_MOVES;
			}
			computerpits++;
			boardcopy = board; // put back a copy of the board to its original state
		}

	//-------------------------------------LOOKAHEAD-----------------------------------------
	// This algorithm looks ahead MAX_DEPTH number of turns to determine the maximum score
	// The best move(s) is the one that CPU gains to most points and HUMAN the least.
	//---------------------------------------------------------------------------------------
	} else if (tactic == LOOKAHEAD) {
		if (side == HUMAN) {
			int score = board.getField(board.getNumberOfPits()); // number of stones in a pit
			for (int i=0; i<board.getNumberOfPits(); i++){ // determine the movevalue for each pit
				int movevalue = score;
				if (board.getField(i) != 0) { // only sow if there are stones in the pit
					Lastpit reply = sow(boardcopy, side, i, game);
					movevalue =  boardcopy.getField(board.getNumberOfPits()) - score;
					if (reply == STORE) {
						depth--; // depth (turn) stays the same because we're not switching turns
						step++; // one more step within this turn
						a[i] = movevalue + chooseMove(dummy, HUMAN, boardcopy, LOOKAHEAD, game); // recursive call to chooseMove
						step--;
						depth++;
					} else {
						if (depth <= MAX_DEPTH) {
							a[i] = movevalue - chooseMove(dummy, COMPUTER, boardcopy, LOOKAHEAD, game); // recursive call to chooseMove
						} else {
							a[i] = movevalue;
						}
					}
				} else { // no stones, no sow action -> low movevalue
					a[i] = NO_MOVES;
				}
				boardcopy = board; // put back a copy of the board to its original state
			}
		} else if (side == COMPUTER) {
			int score = board.getField(2*board.getNumberOfPits()+1); // number of stones in pit
			int computerpits = 0;
			for (int i=(board.getNumberOfPits()+1); i<(2*board.getNumberOfPits()+1); i++){ // for each pit determine the movevalue
				int movevalue = score;
				if (board.getField(i) != 0){ // only sow if there are stones in the pit
					Lastpit reply = sow(boardcopy, side, i, game);
					movevalue = boardcopy.getField(2*board.getNumberOfPits()+1) - score;
					if (reply == STORE) {
						depth--; // depth (turn) stays the same because we're not switching turns
						step++; // one more step within this turn
							a[computerpits] = movevalue + chooseMove(dummy, COMPUTER, boardcopy, LOOKAHEAD, game); // recursive call to chooseMove
						step--;
						depth++;
					} else {
						if (depth <= MAX_DEPTH) {
							a[computerpits] = movevalue - chooseMove(dummy, HUMAN, boardcopy, LOOKAHEAD, game); // recursive call to chooseMove
						}
						else{
							a[computerpits] = movevalue;
						}
					}
				}
				else{ // no stones, no sow action -> low movevalue
					a[computerpits] = NO_MOVES;
				}
				computerpits++;
				boardcopy = board; // put back a copy of the board to its original state
			}
		}
	}

	int max = INT_MIN;
	for (int i=0; i<board.getNumberOfPits(); i++) {
		if (a[i] > max) {
			max = a[i];
			bestMove = i+board.getNumberOfPits()+1;
		}
		// print the value of each move
		//if ((depth == 1) && (step == 0)) {cout << "value of pit "; if ((i+board.getNumberOfPits()+1) < 10) {cout <<" ";} cout << i+board.getNumberOfPits()+1 << "= " << a[i] << endl;}
	}

	// give the move that creates no more possible moves a very high or very low value depending on the player
	if (max == NO_MOVES) {
		if (side == COMPUTER) {
			if (boardcopy.getField(2*board.getNumberOfPits()+1) > (board.getNumberOfPits() * board.getNumberOfStones()))
				max = CPU_WIN;
			else if (boardcopy.getField(2*board.getNumberOfPits()+1) == (board.getNumberOfPits() * board.getNumberOfStones()))
				max = DRAW;
			else
				max = HUMAN_WIN;
		} else if (side == HUMAN) {
			if (boardcopy.getField(board.getNumberOfPits()) > (board.getNumberOfPits() * board.getNumberOfStones()))
				max = -HUMAN_WIN;
			else if (boardcopy.getField(board.getNumberOfPits()) == (board.getNumberOfPits() * board.getNumberOfStones()))
				max = -DRAW;
			else
				max = -CPU_WIN;
		}
	}

	depth--;
	delete [] a;
	return max;
}
