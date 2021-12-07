#include "MancalaPlayer.h"
#include <iostream>
using namespace std;

// constructor of MancalaPlayer
MancalaPlayer::MancalaPlayer(MancalaBoard board, Side side) : side(side), board(board) {}

// Function that sows stones, returns the type of the last pit where a stone was sown in
MancalaPlayer::Lastpit MancalaPlayer::sow(MancalaBoard& board, Side side, int frompit, Game game) {
	//error checking and if either is true, return TRYAGAIN to get another input
	if (((side == HUMAN) && (frompit > board.getNumberOfPits())) || ((side == COMPUTER) && (frompit < (board.getNumberOfPits()+1)))) {
		cout << "Illegal move - sow from your own pits" << endl;
		return TRYAGAIN;
	}
	if (frompit < 0) {
		cout << "Illegal move" << endl;
		return TRYAGAIN;
	}
	if ((frompit == board.getNumberOfPits()) || (frompit == (2*board.getNumberOfPits()+1))) {
		cout << "You cannot sow from a store" << endl;
		return TRYAGAIN;
	}
	if (board.getField(frompit) == 0) {
		cout << "You cannot sow from an empty pit" << endl;
		return TRYAGAIN;
	}

	//getting sowstones from chosen pit and clearing it
	int sowstones = board.getField(frompit);
	int pit = frompit;
	int previouspit = frompit;
	board.setField(frompit, 0); // clear pit from where is sown

	while (sowstones > 0) { //loop while sowstones is not 0
		// illegal index -1 is used to see if we're going around the field (from highest index to the beginning of the field) while sowing
		if(pit != -1) { // go the the next field index (normal operation)
			previouspit = pit;
			pit++;
		} else if (pit == -1) { // go back to the beginning of the field (index 0)
			previouspit = (2*board.getNumberOfPits()+1);
			pit = 0;
		} else { // error occured
			cout << "Something went wrong with going back to the beginning of the field while sowing stones" << endl;
		}

		if (sowstones == 1 && game == AVALANCHE) { //check if the gamemode is Avalanche and if there is only 1 stone left
			if (board.getField(pit) > 0) {//if pit is not empty
				if (side == COMPUTER) {//check if player 2
					if (pit == (2*board.getNumberOfPits()+1)) { //deposit stone in store
						board.addField(pit, 1);
						sowstones--;
						pit = -1; // set pit to -1
					} else if (pit == board.getNumberOfPits()) { //ignore other player store
						//do nothing
					} else { //if regular pit, take all stones from that pit (thus setting it to 0), and adding to sowstones and continue
						sowstones += board.getField(pit);
						board.setField(pit, 0);
					}
				} else if (side == HUMAN) { //if player 1
					if (pit == (2*board.getNumberOfPits()+1)) {
						// don't sow in opponents store
						pit = -1; // set pit to -1
					} else if (pit == board.getNumberOfPits()) { //deposit in own pit
						board.addField(pit, 1);
						sowstones--;
					} else {
						sowstones += board.getField(pit);
						board.setField(pit, 0);
					}
				}
			} else { //if pit is empty, treat as regular regardless of gamemode
				if (side == COMPUTER) {
					if (pit == (2*board.getNumberOfPits()+1)) {
						board.addField(pit, 1);
						sowstones--;
						pit = -1; // set pit to -1
					} else if (pit == board.getNumberOfPits()){
						//do nothing
					} else {
						board.setField(pit, 1);
						sowstones--;
					}
				} else if (side == HUMAN) {
					if (pit == (2*board.getNumberOfPits()+1)) {
						// don't sow in opponents store
						pit = -1; // set pit to -1
					} else if (pit == board.getNumberOfPits()) {
						board.addField(pit, 1);
						sowstones--;
					} else {
						board.setField(pit, 1);
						sowstones--;
					}
				}
			}
		} else { //if stones more than 1 or gamemode is standard, treat like regular
			if (side == COMPUTER) {
				if (pit == (2*board.getNumberOfPits()+1)) {
					board.addField(pit, 1); // place stone
					sowstones--; // decrement sowstones
					pit = -1; // set pit to -1
				} else if (pit == board.getNumberOfPits()) {
					//do nothing
				} else {
					board.addField(pit, 1); // place stone
					sowstones--; // decrement sowstones
				}
			} else if (side == HUMAN) {
				if (pit == (2*board.getNumberOfPits()+1)) {
					// don't sow in opponents store
					pit = -1; // set pit to -1
				} else {
					board.addField(pit, 1); // place stone
					sowstones--; // decrement sowstones
				}
			}
		}
	}

	// from this point pit is equal to lastpit (no more sowstones)
	// a fix for ending with invalid pit index -1
	if (pit == -1) {
		pit = (2*board.getNumberOfPits()+1);
	}

	// return value
	// if the last pit is filled with only 1 stone and it was not a store it was EMPTY before the sow action
	if (game == STANDARD) {//steal only permitted in Standard gamemode
		if ((board.getField(pit) == 1) && !((pit == board.getNumberOfPits()) || (pit == (2*board.getNumberOfPits()+1))) ) {
			// steal!
			steal(board, side, pit);
			return EMPTY;
		}
	}
	// if the last pit is a store, return STORE
	if ( ((side == HUMAN) && (pit == board.getNumberOfPits())) || ((side == COMPUTER) && (pit == (2*board.getNumberOfPits()+1))) ) {
		return STORE;
	}
	// else...
	return PIT;
};

// steal function steals from opposite pit and put these stones and the 'steal stone' itself in the store
void MancalaPlayer::steal(MancalaBoard& board, Side side, int lastpit) {
	//if player lands on empty pit not on their side, steal() will do nothing
	int stealpit;
	if (side == COMPUTER) { //if player 2
		if (lastpit > board.getNumberOfPits()) { //check if in player2 side of the board
			stealpit = lastpit - board.getNumberOfPits(); //math to determine opposite pit
			stealpit = board.getNumberOfPits() - stealpit;
			board.addField((2*board.getNumberOfPits()+1), board.getField(stealpit)); //add value ot opposite pit to player2 store
			board.addField((2*board.getNumberOfPits()+1), 1); //add value of empty space landed (will me 1 since you landed with one stone)
			board.setField(lastpit, 0); //set each to 0
			board.setField(stealpit, 0);
		}
	} else if (side == HUMAN) {
		if (lastpit < board.getNumberOfPits()) {//check if on player1 side of board
			stealpit = board.getNumberOfPits() - lastpit;  //math to solve for opposite pit
			stealpit = board.getNumberOfPits() + stealpit;
			board.addField(board.getNumberOfPits(), board.getField(stealpit));
			board.addField(board.getNumberOfPits(), 1);
			board.setField(lastpit, 0);
			board.setField(stealpit, 0);
		}
	}
}
