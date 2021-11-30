#define DEFAULT_PITS 6
#define DEFAULT_STONES 4

#include <iostream>
#include "mancala.h"

using namespace std;

int main() {
	cout << "Mancala" << endl << endl;
	int pits, stones;
	int players;
	do {
		cout << "How many players? 1/2 " << endl;
		cin >> players;
	} while (!((players == 1) || (players == 2)));
	do {
		cout << "How many pits p? 1<p<8 (for default type 0)" << endl;
		cin >> pits;
		if (pits == 0) {
			pits = DEFAULT_PITS;
		}
	} while (!((pits > 1) && (pits < 8)));
	do {
		cout << "How many stones s? 1<s<7 (for default type 0)" << endl;
		cin >> stones;
		if (stones == 0) {
			stones = DEFAULT_STONES;
		}
	} while (!((stones > 1) && (stones < 7)));
	
	
	
	// create a board
	MancalaBoard mancala(pits, stones);
	// create two players and assign them to the board
	Human player1(mancala);
	Computer cpuplayer(mancala);
	Human player2(mancala);
	if (players == 1) {
		cout << endl << "Since you selected singleplayer, Player 2 will be a CPU" << endl << endl;
	}
	
	int begin;
	do {
		cout << "Who may begin? 1=Player1 2=Player2" << endl;
		cin >> begin;
		if (begin == 1) {
			player1.setTurn(true);
		} else if (begin == 2) {
			player2.setTurn(true);
			cpuplayer.setTurn(true);
		} else {
			cout << "Wrong input, type 1 or 2 and press enter" << endl;
		}
	} while (!(begin == 1 || begin == 2));

	// print the board
	mancala.printBoard();

	do {
		MancalaPlayer::Lastpit reply;
		if (player1.getTurn() == true) { //If player 1 turn
			int frompit;
			do {
				cout << "Player1 sow: " << flush;
				cin >> frompit;

				reply = player1.sow(mancala, MancalaPlayer::HUMAN, frompit);
			} while(reply == MancalaPlayer::TRYAGAIN);

			if (reply == MancalaPlayer::STORE) { // LAST SEED IN STORE, GO AGAIN
				cout << "Player1 gets another turn!" << endl;
			} else {
				player1.setTurn(false);
				if(players == 2) { //check if multiplayer
					player2.setTurn(true);
				} else {
					cpuplayer.setTurn(true);
				}
			}

		//} else if (player2.getTurn() == true) {
		} else { //if player 2 turn
			int frompit;
			
			if (players == 1) { //if singleplayer
				// here the you can adjust the tactic (GREEDY / LOOKAHEAD)
				//cpuplayer.chooseMove(frompit, MancalaPlayer::COMPUTER, mancala, MancalaPlayer::GREEDY);
				cpuplayer.chooseMove(frompit, MancalaPlayer::COMPUTER, mancala, MancalaPlayer::LOOKAHEAD);

				cout << "CPU sows " << frompit << endl;

				reply = cpuplayer.sow(mancala, MancalaPlayer::COMPUTER, frompit);
				if (reply == MancalaPlayer::STORE) { // LAST SEED IN STORE, GO AGAIN
					cout << "CPU received another turn!" << endl;
				} else {
					player1.setTurn(true);
					cpuplayer.setTurn(false);
				}
			} else { //if multiplayer
				do {
					cout << "Player2 sow: " << flush;
					cin >> frompit;
	
					reply = player2.sow(mancala, MancalaPlayer::COMPUTER, frompit);
				} while(reply == MancalaPlayer::TRYAGAIN);

				if (reply == MancalaPlayer::STORE) { // LAST SEED IN STORE, GO AGAIN
					cout << "Player2 gets another turn!" << endl;
				} else {
					player1.setTurn(true);
					player2.setTurn(false);
				}
			}
		}
		// print the board
		mancala.printBoard();
	} while (mancala.gameOver() == 0);

	cout << (mancala.gameOver() == 1 ? "The winner is: Player1" : mancala.gameOver() == 2 ? "The winner is: Player2" : "Everyone is a winner!: DRAW") << endl;

	cin.get();
	cin.get();
	return 0;
}
