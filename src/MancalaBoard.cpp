#include "MancalaBoard.h"
#include <iostream>
using namespace std;

// constructor
MancalaBoard::MancalaBoard(int pits, int stones) : pits(pits), stones(stones) {
	if (pits <= 0) cout << "Number of pits must be > 0" << endl; //error checking just in case
	if (stones <= 0) cout << "Number of stones must be > 0" << endl;//redundancy

	srand(time(NULL));//setting seed
  //crazy mode: random numbers in each pit
	if (stones == 1) {
		for (int i=0; i<=(2*pits+1); i++) {
			field.push_back(rand()%6+2); //push_back() pushes to vector stack
		}
	}
  //mirrored: random on one side and then mirroring on the other side.
  else if (stones == 7) {
		for (int i=0; i<=(pits); i++) {
			field.push_back(rand()%6+2);
		}
		for (int i=pits+1; i<=(2*pits+1); i++) {
			field.push_back(field[i-pits-1]);
		}
	} else {
		for (int i=0; i<=(2*pits+1); i++) {
			field.push_back(stones);
		}
	}

	// reset stores to 0
	field[pits] = 0;
	field[2*pits+1] = 0;
}

// Function that prints the board
void MancalaBoard::printBoard(void) const {

	// Default board example
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
