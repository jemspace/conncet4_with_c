/*=============================================================================
|   	Source code:  sequenceChecks.c
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

#define NEGATE -1 //used to reverse the increment in search loops

/*-----------------------------------------------------------------------------
	Checks whether current player has connected 4 cells in a column; 
	Starting at the cell that was just filled, loop moves down 1 row at a time,
	as long as cell color matches current player;
	cells above startcell assumed empty as per rules of the game, 
	therefore not checked; 
		
	@param int map[][] - game map to be checked
	@param int startcell - cell that was just filled; indicates where to start
	@param const enum players *currentPlayer - color of the current player
	@return true if 4 consecutive cells matched with current player's color, 
			false otherwise
-----------------------------------------------------------------------------*/
int has4Vertical(int map[][COLUMNS + 1], int startcell, const enum players *currentPlayer)
{
	int column = ((startcell - 1) % COLUMNS) + 1;
	int row = ((startcell - 1 ) / COLUMNS) + 1;
	int matchCount = 0;
	while(row <= ROWS && *currentPlayer == map[row][column])
	{
		matchCount++;
		row++;
	}
	return isWinner(matchCount);
}


/*-----------------------------------------------------------------------------
	Checks whether current player has connected 4 cells in a row;
	Starting at last filled cell, loops forward column by column
	until reaches last column or following column is empty/taken 
	by the other color, then switches direction of the search;
	Stops when either beginning of the row or an unmatching cell is reached;
		
	@param int mapRow[] - row of the game map to be checked
	@param int startcell - cell that was just filled; indicates where to start
	@param const enum players *currentPlayer - color of the current player
	@return true if 4 consecutive cells matched with current player's color, 
			false otherwise
-----------------------------------------------------------------------------*/
int has4Horizontal(int mapRow[], int startcell, const enum players *currentPlayer)
{
	int column = ((startcell - 1) % COLUMNS) + 1;
	int matchCount = 0;
	int increment = 1;
	while(column > 0 && *currentPlayer == mapRow[column])
	{
		matchCount++;
		if(column == COLUMNS || mapRow[column + increment] != *currentPlayer)
		{
			increment *= NEGATE; 
			column = ((startcell - 1) % COLUMNS) + 1;
		}
		column += increment;
	}
	return isWinner(matchCount);
}



/*-----------------------------------------------------------------------------
	Checks whether current player has connected 4 cells diagonally down;
	Searches diagonally down, if reaches last column or row, or unmatching cell,
	reverses direction of search; stops at next unmatching cell or when
	row or column = 1;
		
	@param int map[][] - game map to be checked
	@param int startcell - cell that was just filled; indicates where to start
	@param const enum players *currentPlayer - color of the current player
	@return true if 4 consecutive cells matched with current player's color, 
			false otherwise
-----------------------------------------------------------------------------*/
int has4DiagonalDown(int map[][COLUMNS + 1], int startcell, const enum players *currentPlayer)
{
	int column = ((startcell - 1) % COLUMNS) + 1;
	int row = ((startcell - 1 ) / COLUMNS) + 1;
	int matchCount = 0;
	int increment = 1;
	while(column > 0 && row > 0 && *currentPlayer == map[row][column])
	{
		matchCount++;
		if(increment > 0 && (row == ROWS || column == COLUMNS ||
			map[row + increment][column + increment] != *currentPlayer))
		{
			increment *= NEGATE;
			int column = ((startcell - 1) % COLUMNS) + 1;
			int row = ((startcell - 1 ) / COLUMNS) + 1;
		}
		row += increment; column += increment;
	}
	return isWinner(matchCount);
}


/*-----------------------------------------------------------------------------
	Checks whether current player has connected 4 cells diagonally up;
	Searches diagonally up, if reaches last column or first row, 
	or unmatching cell, reverses direction of search; 
	stops at next unmatching cell or when reaches last row or first column;
		
	@param int map[][] - game map to be checked
	@param int startcell - cell that was just filled; indicates where to start
	@param const enum players *currentPlayer - color of the current player
	@return true if 4 consecutive cells matched with current player's color, 
			false otherwise
-----------------------------------------------------------------------------*/
int has4DiagonalUp(int map[][COLUMNS + 1], int startcell, const enum players *currentPlayer)
{
	int column = ((startcell - 1) % COLUMNS) + 1;
	int row = ((startcell - 1 ) / COLUMNS) + 1;
	int matchCount = 0;
	int increment = 1;
	while(column > 0 && row <= ROWS && *currentPlayer == map[row][column])
	{
		matchCount++;
		if(increment > 0 && (row == 1 || column == COLUMNS ||
			map[row - increment][column + increment] != *currentPlayer))
		{
			increment *= NEGATE;
			int column = ((startcell - 1) % COLUMNS) + 1;
			int row = ((startcell - 1 ) / COLUMNS) + 1;
		}
		row -= increment; column += increment;
	}
	return isWinner(matchCount);
}

/*-----------------------------------------------------------------------------
	Returns true if count >= 4
	(if current player fills 4 cells in a line)
	
	@param count - number of consecutive cells after last turn of the game
	@return true if current turn filled 4 consecutive cells
-----------------------------------------------------------------------------*/
int isWinner(int count)
{
	if(count >= WINNING_NUM)
	{
		return true;
	}
	return false;
}



