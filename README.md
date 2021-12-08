EC327 FINAL PROJECT (Team Probable Broccoli)
Fall 2021

Project Overview: 

The goal for our final project was to make a Mancala game using C++ and to complete several objectives for the final functionalities of the game to provide a unique experience for any user looking to play Mancala directly on their console. As part of our milestones, we were able to implement a different gameplay mode (Avalanche), multiplayer capability of up to 2 players and/or with a competitive AI, player-adjustable game selections, and an option to randomize the number of stones and pits on the board. Along with added functionality, we have implemented more user-friendly interface designs by adding ASCII screens and audio functions that play at key gameplay moments.  

About Mancala/Rules:

Mancala is a turn-based strategy board game with a simple set up of stones and pits on a board and the goal of the game is to capture most stones on the board. Mancala is one of the oldest board games played around the world and some versions have been known to date back to the 7th century - the most popular version played in USA is the Kalah version, which is the default mode of our program. The rules are to take turns choosing pits to sow, which then allocates all the stones in that pit to other pits in counterclockwise direction, depositing 1 stone in each pit. Each player can only choose pits on their side on the board and the goal is to gather as many stones as possible in their main pit, located on the opposite sides of the board. In the case an empty pit is chosen, the stones on the other side is added directly to the player's main pit. If a stone is added to the player's main pit, the player is able to go again before the other player. 

Another mode that was included is known as "Avalanche" mode, in which the regular rules are altered so that the resulting stone movements resemble an avalanche. Instead of having the turn end when a stone is not added to the player's main pit, the turn only ends if the last stone lands in an empty pit. 

How to Build the Game:

To build the Mancala game, the user launches terminal, ensures the terminal directory is set to the directory that contains all of the game files. User then types ‘make’ and the Makefile generates the objects. Then user enters ‘./MancalaGame’, and the game is initialized.

To build the music player, the SFML library needs to be installed ahead of compile. The instructions for Linux OS is included in the folder under "sudo instructions" - detailed instructions for other OS can be found at link: https://www.sfml-dev.org/tutorials/2.5/. After installing the library with provided terminal line, compiling the program is very quickly done with the 3 instruction codes in the file. 

YouTube link: https://www.youtube.com/watch?v=5ZQ8WTBtTb4


Contributors: 

Bora Bulut - Documentation lead @ bbulut@bu.edu

Aryaman Gupta - Specification lead @ aryaman@bu.edu

Fariza Tasnim - Interface lead @ ftasnim@bu.edu

Sally Shin - Project lead @ salshin@bu.edu

Zachary Tan - Technical lead @ zdltan20@bu.edu


Credit for source code: 
boaz001 at https://github.com/boaz001/mancala

Credit for music creators:

JuliusH: https://pixabay.com/users/juliush-3921568/?tab=audio&utm_source=link-attribution&utm_medium=referral&utm_campaign=audio&utm_content=2641

PDillow: https://pixabay.com/users/phill_dillow-16161775/?tab=audio&utm_source=link-attribution&utm_medium=referral&utm_campaign=audio&utm_content=543

audiomirage: https://freesound.org/people/audiomirage/

bloodpixelhero: https://freesound.org/people/BloodPixelHero/

