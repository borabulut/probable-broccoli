#define CPU_WIN 10000 // high value
#define HUMAN_WIN -10000 // low value
#define DRAW -5000 // low value: CPU doesn't want to play draw
#define NO_MOVES -100000
#define MAX_DEPTH 4 // number of moves to lookahead by CPU (when tactic = lookahead)

#include "mancala.h"

using namespace std;

// constructor
MancalaBoard::MancalaBoard(int pits, int stones) : pits(pits), stones(stones) {
	if (pits <= 0) cout << "Number of pits must be > 0" << endl; //error checking just in case
	if (stones <= 0) cout << "Number of stones must be > 0" << endl;
	
	srand(time(NULL));
	
	if (stones == 1) {
		for (int i=0; i<=(2*pits+1); i++) {
			field.push_back(rand()%6+2); //push_back() pushes to vector stack
		}
	} else if (stones == 7) {
		for (int i=0; i<=(pits); i++) {
			field.push_back(rand()%6+2); //push_back() pushes to vector stack
		}
		for (int i=pits+1; i<=(2*pits+1); i++) {
			field.push_back(field[i-pits-1]); //push_back() pushes to vector stack
		}
	} else {
		for (int i=0; i<=(2*pits+1); i++) {
			field.push_back(stones); //push_back() pushes to vector stack
		}
	}
	
	// reset stores to 0
	field[pits] = 0;
	field[2*pits+1] = 0;
}

// Function that prints the board
void MancalaBoard::printBoard(void) const {
	
	// Default board
	// P2: 12|11|10|9 |8 |7 |
	// -------------------------
	// |  |4 |4 |4 |4 |4 |4 |  |
	// |0 |--+--+--+--+--+--|0 |
	// |  |4 |4 |4 |4 |4 |4 |  |
	// -------------------------
	// P1: 0 |1 |2 |3 |4 |5 |
	
	//line 1
	cout << endl;
	cout << " P2: ";
	for(int i=(2*pits); i>pits; i--) {
		if (i < 10) {
			cout <<i<<" |";
		} else {
			cout <<i<<"|";
		}
	}
	cout<<endl;
	//line 2
	cout << " ----";
	for(int i=pits; i>0; i--) {
		cout << "---";
	}
	cout << "---" <<  endl;
	//line 3
	cout << " |  |";
	for(int i=(2*pits); i>pits; i--) {
		cout << field[i];
		if (field[i]<10) {
			cout << " |";
		} else {
			cout << "|";
		}
	} 
	cout << "  |" << endl;
	//line 4
	cout << " |" << field[(2*pits+1)];
	if (field[2*pits+1] < 10) {
		cout << " |";
	} else {
		cout << "|";
	}
	for(int i=pits; i>1; i--) {
		cout << "--+";
	}
	cout << "--|" << field[pits];
	if (field[pits]<10) {
		cout << " |";
	} else {
		cout << "|";
	}
	cout << endl;
	//line 5
	cout << " |  |";for(int i=0; i<pits; i++) {
		cout << field[i];
		if (field[i]<10) {
			cout << " |";
		} else{
			cout << "|";
		}
	}
	cout << "  |" << endl;
	//line 6
	cout << " ----";
	for(int i=pits; i>0; i--) {
		cout << "---";
	}
	cout << "---" << endl;
	//line 7
	cout << " P1: ";
	for(int i=0; i<pits; i++) {
		if (i < 10) {
			cout <<i<<" |";
		} else {
			cout <<i<<"|";
		}
	} cout<<endl;
}

// Function that checks if the game is over. If so, it returns a value of the winner
// values shown at the end of the function
int MancalaBoard::gameOver(void) const {
	if (field[pits] > (stones*pits)) return 1; // more than half of the total number of stones already means a win
	if (field[(2*pits+1)] > (stones*pits)) return 2; // more than half of the total number of stones already means a win
	
	//Another way endgame is determined is checking if either row of pits (not including store) are empty
	int human = 0, cpu = 0, endgame = 0;
	for (int i=0 ; i<pits ; i++) { //checking stones remaning in pits (not including store)
		human += field[i];
	}
	if (human == 0) { //if all pits in player 1 empty
		cpu = 0;
		for (int i=pits+1 ; i<(2*pits+2) ; i++) { //getting total of the row including home pit
			cpu += field[i];
		}
		endgame = 1; //signal conditions met for endgame
		human = field[pits]; //human gets home pit only since the rest of the pits are empty
	}

	for (int i=pits+1 ; i<(2*pits+1) ; i++) {
		cpu += field[i];
	}
	if (cpu == 0) {
		human = 0;
		for (int i=0 ; i<pits+1 ; i++) {
			human += field[i];
		}
		endgame = 1;
		cpu = field[(2*pits+1)];
	}

	if ((human==cpu) && (endgame==1)) return 3; // draw
	if ((cpu>human) && (endgame==1)) return 2; // cpu = winner
	if ((human>cpu) && (endgame==1)) return 1; // human = winner
	return 0; // no winner
}

// returns the number of stones of a pit
int MancalaBoard::getField(int index) const {
	return field[index];
}

// returns a copy of the entire field
MancalaBoard::Field MancalaBoard::getField(void) const {
	return field;
}

// sets the number of stones in a pit
void MancalaBoard::setField(int index, int value) {
	field[index] = value;
}

// increment the value of field[index] with the value of add
void MancalaBoard::addField(int index, int add) {
	int temp = getField(index);
	temp += add;
	setField(index, temp);
}

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


// constructor of Human (creates a MancalaPlayer with Side HUMAN)
Human::Human(MancalaBoard& board) : MancalaPlayer(board, HUMAN), turn(false) {}

// the chooseMove determines the best move, this move (or pit) is stored in bestMove
int Human::chooseMove(int& bestMove, Side side, MancalaBoard board, Tactic tactic, Game game) {
	// not implemented for HUMAN
	return 0;
}

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
