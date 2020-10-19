/*=============================================================================
|   	Source code:  connect4main.c
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
|		**connect4hdr.h must be included in same directory
|		  as all other program files to compile correctly**
|
|        Language:  c
|     Compile/Run: make build
|					c4.out
|
|	**OR without makefile**
|
|				gcc connect4main.c gameMap.c sequenceChecks.c
|				   ./a.out
| +-----------------------------------------------------------------------------
|
|  Description: game of Connect 4; program allows 2 players (red, yellow) 
|				to play the game by taking turns "dropping their piece" into
|				cells on a 7x6 game board (map); First player to connect
|				4 of their pieces consecitively in a row, column or diagonal line
|				wins the game; Game ends in a draw if all 42 cells are used without
|				either player taking up consecutive 4 cells.
|
|        Input: Every turn of the game a player is required to enter the position
|				(cell number) where they want to drop their piece, which is an
|				integer from 1 to 42 inclusive; player can enter -1 to quit the game. 
|
|       Output: Every turn a game map is printed showing the cells that were taken
|				so far as well as all empty cells; Empty cells show their position numbers,
|				filled cells show the letter corresponding to the color that fills them
|				(R for red, Y for yellow); at the end of the game the result
|				is displayed - whether game ended in a draw, was quit, or had a winner
|				final result also shows how the winning sequence of cells was placed
|				(vertically, horizontally or diagonally)
|
|      Process: the game is initialized by filling each cell with its position number
|				on a 7x6 table (game map); players take turns as long as the game
|				status is "ongoing"; every turn checks whether all cells have been filled
|				(which results in a draw), or the turn resulted in the current player
|				connecting 4 cells, in which case game state changes to one of
|				the following: wonVertical, wonHorizontal, wonDiagonal;
|				at any turn, if -1 is entered, game state changes to quit;
|				Based on the final state of the game, the result is displayed
|
|   Required Features Not Included: all included
|
|
|   Known Bugs: no known bugs
|
|  *===========================================================================*/

#include "connect4hdr.h" //for common macros, included libraries, prototypes

#define QUIT_GAME -1
#define NO_ERROR 0


int main(void)
{
	int gameMap[ROWS + 1][COLUMNS + 1]; gameMap[0][0] = 0;
	initializeGame(gameMap);
	printf("%s\n", "Welcome to Connect 4. Initial game map is empty:");
	printGameMap(gameMap);
	enum gameState state = ongoing;
	enum players player = yellow;
	int turnsTaken = 0;
	do
	{	player = (player == yellow)? red : yellow;
		turnsTaken++;
		int turn = getPlayerInput(gameMap);
		if(turn == QUIT_GAME)
		{
			state = quit;
		}else
		{
			gameMap[((turn - 1) / COLUMNS) + 1][((turn - 1) % COLUMNS) + 1] = player;
			getGameStatus(gameMap, turn, turnsTaken,  &state, &player);
		}
		printGameMap(gameMap);
	}while(state == ongoing);
	showGameResult(&player, &state);
	return NO_ERROR;
}


/*-----------------------------------------------------------------------------
	Determines status of the game - if it's ended in a draw, or the current
	player won by covering consecutive 4 cells vertically, horizontally
	or diagonally; depending on the state, changes currentState
	which is also enum gameState state in the main
	
	@param int currentMap[][] - game map to be checked for winning combinations
	@param int lastTurn - last taken position, starting point of checks
	@param int turnsSum - number of turns taken so far (if 42, might be a draw)
	@param enum gameState *currentState - state of the game (ongoing, draw, etc...)
	@param enum players *currentPlayer - current player, red or yellow
-----------------------------------------------------------------------------*/
void getGameStatus(int currentMap[][COLUMNS + 1], int lastTurn, int turnsSum,
        enum gameState *currentState, enum players *currentPlayer)
{
	if(turnsSum >= ALL_CELLS)
	{
		*currentState = draw;
	}
	else if(has4Vertical(currentMap, lastTurn, currentPlayer))
	{
		*currentState = wonDiagonal;
	}
	else if (has4Horizontal(currentMap[((lastTurn - 1) / COLUMNS) + 1], lastTurn, currentPlayer))
	{
		*currentState = wonHorizontal;
	}
	else if (has4DiagonalDown(currentMap, lastTurn, currentPlayer) ||
			has4DiagonalUp(currentMap, lastTurn, currentPlayer))
	{
		*currentState = wonDiagonal;
	}
}


/*-----------------------------------------------------------------------------
	Input from the player - function gets the integer position of
	where to drop the next piece; non-integer or out-of-bounds
	input is rejected; 
	Position above an empty cell rejected as per rules of the game;
	-1 taken as signal to quit the game.
	
	@int map[][] - current game map to check for positions above empty cells
-----------------------------------------------------------------------------*/
int getPlayerInput(int map[][COLUMNS + 1])
{
	int intInput = 0;
	do
	{
		printf("%s\n", "Enter the position where you want to drop your piece");
		printf("%s\n", "[integer from 1 to 42, inclusive; -1 to quit]");
		char inBuffer[3];
		scanf("%s", inBuffer);
		intInput = atoi(inBuffer);

		int row = ((intInput - 1) / COLUMNS) + 1;
		int col = ((intInput - 1) % COLUMNS) + 1;
		if(intInput != QUIT_GAME && (intInput < 1 || intInput > ALL_CELLS ||
		((row) < ROWS && map[row + 1][col] < red)))
		{
			intInput = 0;
			printf("%s\n", "Position out of range or above a blank spot");
		}
	}while(intInput == 0);
	return intInput;
}


/*-----------------------------------------------------------------------------
	Prints the final result of the game;
	Either a draw, a quit game or a game with a winner (red or yellow)
	and the combination that won the game (4 in a horizontal row,
	4 in a vertical column, or 4 diagonally)
	
	@param enum players *player - the player to take the last turn
	@param enum gameState *state - finishing state of the game
-----------------------------------------------------------------------------*/
void showGameResult(const enum players *player, const enum gameState *state)
{
	char *lastPlayer = (*player == red)?"RED" : "YELLOW";
	if(*state == quit)
	{
		printf("%s\n", "Game quit");
	}
	else if(*state == draw)
	{
		printf("%s\n", "Game ended in a draw");
	}else 
	{
		printf("%s%s", "Game is over - won by: ", lastPlayer);
		if(*state == wonVertical)
		{
			printf("%s\n",  " - Vertical");
		}
		else if(*state == wonHorizontal)
		{
			printf("%s\n", " - Horizontal");
		}
		else if(*state == wonDiagonal)
		{
			printf("%s\n", " - Diagonal");
		}
	}
}









