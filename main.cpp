#define DEFAULT_PITS 6
#define DEFAULT_STONES 4

#include <iostream>
#include <ctime>
#include <cstdlib>
//#include "mancala.h"
#include "MancalaBoard.h"
#include "MancalaPlayer.h"
#include "Human.h"
#include "Computer.h"

using namespace std;

int main() {
	cout << endl << "Mancala" << endl << endl;
	int pits, stones;
	int players;
	int gameChoice; //used to determine Gamemode
	MancalaPlayer::Game game;

	do { //User input for gamemode
		cout << "Enter 1 for Standard or 2 for Avalance: ";
		cin >> gameChoice;
	} while (!((gameChoice == 1) || (gameChoice == 2)));
	switch(gameChoice) {
		case 1:
			game = MancalaPlayer::STANDARD;
			break;
		case 2:
			game = MancalaPlayer::AVALANCHE;
			break;
	}

	do { //user input for how many players
		cout << "How many players? 1/2: ";
		cin >> players;
	} while (!((players == 1) || (players == 2)));

	do {// user input for pit number
		cout << "How many pits p? (choose from 2 to 7)\n(for default type 0 / for random type 1)" << endl;
		cin >> pits;
		if (pits == 0) {
			pits = DEFAULT_PITS;
		}
		else if (pits == 1) {
			srand(time(NULL));
			pits = rand()%6+2;
		}
	} while (!((pits > -1) && (pits < 8)));

	do { //user input for stone number
		cout << "How many stones s? (choose from 2 to 6)\n For default type 0\n For crazy mode type 1\n For mirrored random type 7" << endl;
		cin >> stones;
		if (stones == 0) {
			stones = DEFAULT_STONES;
		}
	} while (!((stones > -1) && (stones < 8)));

	// create a board
	MancalaBoard mancala(pits, stones);
	// create two players and assign them to the board
	Human player1(mancala);
	Human player2(mancala);
	Computer cpuplayer(mancala); //cpu created in case of single player

	if (players == 1) { //notify player if single player
		cout << endl << "** Since you selected singleplayer, Player 2 will be a CPU **" << endl << endl;
	}

	int begin;
	do { //determine which player will start first where player1 is the bottom row and player2 is the top
		cout << "Who may begin? (1=Player1 2=Player2): ";
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
			do { //get user input
				cout << "Player1 sow: " << flush;
				cin >> frompit;

				reply = player1.sow(mancala, MancalaPlayer::HUMAN, frompit, game);
			} while(reply == MancalaPlayer::TRYAGAIN); //if not valid input will error check

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
		} else { //if player 2 turn
			int frompit;

			if (players == 1) { //if singleplayer
				if (game == MancalaPlayer::STANDARD) { //check what gamemode being played and determing cpu behavior
					cpuplayer.chooseMove(frompit, MancalaPlayer::COMPUTER, mancala, MancalaPlayer::LOOKAHEAD, game);
				} else {
					cpuplayer.chooseMove(frompit, MancalaPlayer::COMPUTER, mancala, MancalaPlayer::GREEDY, game);
				}

				cout << "CPU sows " << frompit << endl;

				reply = cpuplayer.sow(mancala, MancalaPlayer::COMPUTER, frompit, game);
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

					reply = player2.sow(mancala, MancalaPlayer::COMPUTER, frompit, game);
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
	} while (mancala.gameOver() == 0); //loop while criteria to win not met

	//Determining winner
	if (mancala.gameOver() == 1) {
		cout << "The winner is: Player1!" << endl;
		return 0;
	} else if (mancala.gameOver() == 2) {
		cout << "The winner is: Player2!" << endl;
		return 0;
	} else {
		cout << "Both players have equal stones: DRAW!" << endl;
		return 0;
	}
	return 0;
}
