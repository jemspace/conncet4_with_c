/*=============================================================================
|   	Source code:  gameMap.c
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
| +-----------------------------------------------------------------------------*/

#include "connect4hdr.h"

/*-----------------------------------------------------------------------------
	Initializes an empty game map;
	Fills a 2d array with position numbers for each cell;
	
	@int gameMap[][] - game map to be initialized
-----------------------------------------------------------------------------*/
void initializeGame(int gameMap[][COLUMNS + 1])
{
	int row, col;
	for(row = 1; row <= ROWS; row++)
	{
		for(col = 1; col <= COLUMNS; col++)
		{
			gameMap[row][col] = (COLUMNS * (row - 1)) + col;
		}
	}
}

/*-----------------------------------------------------------------------------
	Prints the 6x7 game map
	If a cell is filled, prints a character for the cell’s color (R or Y)
	Otherwise prints cell’s position number

	@param int gameMap[][] – map to be printed
-----------------------------------------------------------------------------*/
void printGameMap(int gameMap[][COLUMNS + 1])
{
	int printrow, printcol;
	for(printrow = 1; printrow <= ROWS; printrow++)
	{
		printf("%s", " ----- ----- ----- ----- ----- ----- ----- \n|");
		for(printcol = 1; printcol <= COLUMNS; printcol++)
		{
			if(gameMap[printrow][printcol] == red || gameMap[printrow][printcol] == yellow)
			{
				printf("%3c%3s", gameMap[printrow][printcol], "|");
			}
			else printf("%3d%3s", gameMap[printrow][printcol], "|");
		}
		printf("%s", "\n");
	}
	printf("%s", " ----- ----- ----- ----- ----- ----- ----- \n");
}



