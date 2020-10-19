/*=============================================================================
|   	Source code:  connect4hdr.h
|           Author:  Darya Chepurna
|     Student ID:  6152714
|    Assignment:  Program #4 connect 4
|
|            Course:  COP4338 (Computer Programming III)
|           Section:  U03
|        Instructor:  William Feild
|          Due Date:  10/29/2019, at the beginning of class
|
|	I hereby certify that this collective work is my own
|	and none of it is the work of any other person or entity.
|	______________________________________ [Signature]
|	
|	  ****connect4hdr.h is not part of the compilation but 
|		  must be included in same directory as
|		  connect4main.c, gameMap.c, turns.c
|		
|      
| +-----------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define ALL_CELLS 42
#define ROWS 6
#define COLUMNS 7
#define WINNING_NUM 4

/*----Enumerations----*/

/*
	Each game has 2 players, red and yellow;
	Int values stand for ascii codes for 'R' and 'Y' respecively
*/
enum players { red = 82, yellow = 89 };

/*
	A value used in methods which check whether
	the player has connected a sequence of 4 cells;
	meant to function like a boolean
*/
enum connected { false, true };

/*
	States of the game; the game is ongoing until either player quits
	or wins in one of the 3 ways (vertical, horizontal, diagonal)
	state becomes a draw if a game ends with no winner
*/
enum gameState { ongoing, quit, draw, wonVertical, wonHorizontal, wonDiagonal };

/*-----Prototypes-----*/
void getGameStatus(int currentMap[][COLUMNS + 1], int lastTurn, int turnsSum,
	enum gameState *currentState, enum players *currentPlayer);
int getPlayerInput(int map[][COLUMNS + 1]);
void showGameResult(const enum players *player, const enum gameState *state);

void initializeGame(int gameMap[][COLUMNS + 1]);
void printGameMap(int gameMap[][COLUMNS + 1]);

int has4Vertical(int map[][COLUMNS + 1], int startcell, const enum players *currentPlayer);
int has4Horizontal(int mapRow[], int startcell, const enum players *currentPlayer);
int has4DiagonalDown(int map[][COLUMNS + 1], int startcell, const enum players *currentPlayer);
int has4DiagonalUp(int map[][COLUMNS + 1], int startcell, const enum players *currentPlayer);
