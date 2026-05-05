// The Game NAME: TERMINAL TOWER
// This Game PROJECT is Made For Terminal Dimensions 30*120.
// FLOOR 3 0 --> 29
// FLOOR 2 30 --> 59
// FLOOR 1 60 --> 89
// W - UP (LADDER)
// S - DOWN (LADDER) 
// D - RIGHT
// A - LEFT
// J - JUMP
// K - DOUBLE JUMP
// I - JUMP RIGHT (LADDER & ELEVATOR)
// U - JUMP LEFT (LADDER & ELEVATOR)
// N - SINGLE BULLET
// M - MULTIPLE BULLETS


#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
using namespace std;

struct Enemy
{
	int Row;
	int Col;
	int Dir;
	int DirTwo;
	int Health;
	int isAlive;
};

struct Obstacle
{
	int strtRow;
	int strtCol;
	int endCol;
};

struct Bullet
{
	int Row;
	int Col;
	int IsActive;
	char Dir;
};

struct Laser
{
	int Col;
	int Len;
	int Timer;
	int IsActive;
};

void GoBackHomeCursor()
{
	COORD coord = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void dispAscii()
{
	for (int i = 0; i < 256; i++)
	{
		cout << i << ". " << (unsigned char)i << endl;
	}
}

void dispWorld(unsigned char** world, int strtRow, int endRow, int strtCol, int endCol)
{
	for (int r = strtRow; r < endRow; r++)
	{
		for (int c = strtCol; c < endCol; c++)
		{
			cout << world[r][c];
		}
		//cout << endl;
	}
}

void deleteWorld(unsigned char** world)
{
	for (int r = 0; r < 90; r++)
	{
		for (int c = 0; c < 360; c++)
		{
			world[r][c] = ' ';
		}
	}

}

void drawWorldBorders(unsigned char** world, int strtRow, int endRow, int strtCol, int endCol)
{
	for (int r = strtRow; r < endRow; r++)
	{
		for (int c = strtCol; c < endCol; c++)
		{
			if ((r == strtRow || r == endRow - 1) && (c == strtCol || c == endCol - 1))
			{
				world[r][c] = '+';
			}
			else
			{
				if ((r == strtRow || r == endRow - 1) && (c > strtCol && c < endCol - 1))
				{
					world[r][c] = '=';
				}
				else
				{
					if ((r > strtRow && r < endRow - 1) && (c == strtCol || c == endCol - 1))
					{
						world[r][c] = '|';
					}
				}
			}
		}
	}

}

void moveElevator(int& elevatorRow, int& elevatorDir, int& elevatorCurrFloor)
{
	if (elevatorRow >= 38)
	{
		elevatorDir = -1;
	}
	else
	{
		if (elevatorRow <= 3)
		{
			elevatorDir = 1;
		}
	}

	elevatorRow += elevatorDir;


	if (elevatorRow + 20 <= 29)
	{
		elevatorCurrFloor = 3;
	}
	else
	{
		elevatorCurrFloor = 2;
	}

}

void fillElevatorRow(int r, int strtCol, int endCol, char k, unsigned char** world)
{
	for (int c = strtCol; c < endCol; c++)
	{
		world[r][c] = k;
	}
}

void drawBlock(int r, int c, unsigned char** world)
{
	for (int tempR = r; tempR <= r + 3; tempR++)
	{
		for (int tempC = c; tempC <= c + 16; tempC++)
		{
			if (tempR == r)
			{
				world[tempR][tempC] = '_';
			}
			else
			{
				if (tempC == c || tempC == c + 4 || tempC == c + 8 || tempC == c + 12 || tempC == c + 16)
				{
					world[tempR][tempC] = '|';
				}
				else
				{
					world[tempR][tempC] = '_';
				}
			}
		}
	}
}

void drawSpike(int r, int c, unsigned char** world)
{
	world[r][c] = '/';
	world[r][c + 1] = '\\';

	world[r + 1][c - 1] = '/';
	world[r + 1][c + 2] = '\\';

}

void drawWorldStatics(unsigned char** world)
{
	///////////////////////////////
	//// DRAWING DOOR  
	/////////////////////////////


	int r = 70, c = 3;

	for (int tempR = r + 1; tempR < 89; tempR++)
	{
		world[tempR][c - 1] = '|';
	}

	for (int tempR = r + 1; tempR < 89; tempR++)
	{
		world[tempR][c + 44] = '|';
	}

	for (int tempC = 3; tempC < c + 44; tempC++)
	{
		world[r][tempC] = '_';
	}


	for (int tempC = 3; tempC < c + 44; tempC++)
	{
		world[r + 1][tempC] = '_';
	}

	world[r + 2][c] = '_';
	world[r + 2][c + 1] = '_';
	world[r + 2][c + 2] = '|';
	world[r + 2][c + 3] = '|';

	world[r + 2][c + 6] = '|';
	world[r + 2][c + 7] = '|';
	world[r + 2][c + 8] = '_';
	world[r + 2][c + 9] = '_';
	world[r + 2][c + 10] = '_';
	world[r + 2][c + 11] = '|';
	world[r + 2][c + 12] = '|';

	world[r + 2][c + 15] = '|';
	world[r + 2][c + 16] = '_';
	world[r + 2][c + 17] = '|';
	world[r + 2][c + 18] = '_';
	world[r + 2][c + 19] = '_';
	world[r + 2][c + 20] = '_';
	world[r + 2][c + 21] = '|';
	world[r + 2][c + 22] = '_';
	world[r + 2][c + 23] = '_';
	world[r + 2][c + 24] = '_';
	world[r + 2][c + 25] = '|';
	world[r + 2][c + 26] = '_';
	world[r + 2][c + 27] = '_';
	world[r + 2][c + 28] = '|';

	world[r + 2][c + 31] = '|';
	world[r + 2][c + 32] = '|';
	world[r + 2][c + 33] = '_';
	world[r + 2][c + 34] = '_';
	world[r + 2][c + 35] = '_';
	world[r + 2][c + 36] = '|';
	world[r + 2][c + 37] = '|';

	world[r + 2][c + 40] = '|';
	world[r + 2][c + 41] = '|';
	world[r + 2][c + 42] = '_';
	world[r + 2][c + 43] = '_';
	world[r + 2][c + 44] = '|';

	world[r + 3][c] = '|';
	world[r + 3][c + 1] = '_';
	world[r + 3][c + 2] = '_';
	world[r + 3][c + 3] = '|';

	world[r + 3][c + 6] = '|';
	world[r + 3][c + 7] = '_';
	world[r + 3][c + 8] = '_';
	world[r + 3][c + 9] = '|';
	world[r + 3][c + 10] = '_';
	world[r + 3][c + 11] = '_';
	world[r + 3][c + 12] = '|';

	world[r + 3][c + 15] = '|';
	world[r + 3][c + 16] = '_';
	world[r + 3][c + 17] = '_';
	world[r + 3][c + 18] = '_';
	world[r + 3][c + 19] = '|';
	world[r + 3][c + 20] = '_';
	world[r + 3][c + 21] = '_';
	world[r + 3][c + 22] = '_';
	world[r + 3][c + 23] = '|';
	world[r + 3][c + 24] = '_';
	world[r + 3][c + 25] = '_';
	world[r + 3][c + 26] = '_';
	world[r + 3][c + 27] = '|';
	world[r + 3][c + 28] = '|';

	world[r + 3][c + 31] = '|';
	world[r + 3][c + 32] = '_';
	world[r + 3][c + 33] = '_';
	world[r + 3][c + 34] = '|';
	world[r + 3][c + 35] = '_';
	world[r + 3][c + 36] = '_';
	world[r + 3][c + 37] = '|';

	world[r + 3][c + 40] = '|';
	world[r + 3][c + 41] = '_';
	world[r + 3][c + 42] = '_';
	world[r + 3][c + 43] = '|';
	world[r + 3][c + 44] = '|';

	world[r + 4][c] = '_';
	world[r + 4][c + 1] = '_';
	world[r + 4][c + 2] = '|';
	world[r + 4][c + 3] = '|';

	world[r + 4][c + 6] = '|';
	world[r + 4][c + 7] = '|';
	world[r + 4][c + 8] = '_';
	world[r + 4][c + 9] = '_';
	world[r + 4][c + 10] = '_';
	world[r + 4][c + 11] = '|';
	world[r + 4][c + 12] = '|';

	world[r + 4][c + 15] = '|';
	world[r + 4][c + 16] = '_';
	world[r + 4][c + 17] = '|';
	world[r + 4][c + 18] = '_';
	world[r + 4][c + 19] = '_';
	world[r + 4][c + 20] = '_';
	world[r + 4][c + 21] = '|';
	world[r + 4][c + 22] = '_';
	world[r + 4][c + 23] = '_';
	world[r + 4][c + 24] = '_';
	world[r + 4][c + 25] = '|';
	world[r + 4][c + 26] = '_';
	world[r + 4][c + 27] = '_';
	world[r + 4][c + 28] = '|';

	world[r + 4][c + 31] = '|';
	world[r + 4][c + 32] = '|';
	world[r + 4][c + 33] = '_';
	world[r + 4][c + 34] = '_';
	world[r + 4][c + 35] = '_';
	world[r + 4][c + 36] = '|';
	world[r + 4][c + 37] = '|';

	world[r + 4][c + 40] = '|';
	world[r + 4][c + 41] = '|';
	world[r + 4][c + 42] = '_';
	world[r + 4][c + 43] = '_';
	world[r + 4][c + 44] = '|';

	world[r + 5][c] = '|';
	world[r + 5][c + 1] = '_';
	world[r + 5][c + 2] = '_';
	world[r + 5][c + 3] = '|';

	world[r + 5][c + 6] = '|';
	world[r + 5][c + 7] = '_';
	world[r + 5][c + 8] = '_';
	world[r + 5][c + 9] = '|';
	world[r + 5][c + 10] = '_';
	world[r + 5][c + 11] = '_';
	world[r + 5][c + 12] = '|';

	world[r + 5][c + 15] = '|';
	world[r + 5][c + 16] = '_';
	world[r + 5][c + 17] = '_';
	world[r + 5][c + 18] = '_';
	world[r + 5][c + 19] = '|';
	world[r + 5][c + 20] = '_';
	world[r + 5][c + 21] = '_';
	world[r + 5][c + 22] = '_';
	world[r + 5][c + 23] = '|';
	world[r + 5][c + 24] = '_';
	world[r + 5][c + 25] = '_';
	world[r + 5][c + 26] = '_';
	world[r + 5][c + 27] = '|';
	world[r + 5][c + 28] = '|';

	world[r + 5][c + 31] = '|';
	world[r + 5][c + 32] = '_';
	world[r + 5][c + 33] = '_';
	world[r + 5][c + 34] = '|';
	world[r + 5][c + 35] = '_';
	world[r + 5][c + 36] = '_';
	world[r + 5][c + 37] = '|';

	world[r + 5][c + 40] = '|';
	world[r + 5][c + 41] = '_';
	world[r + 5][c + 42] = '_';
	world[r + 5][c + 43] = '|';
	world[r + 5][c + 44] = '|';

	world[r + 6][c] = '_';
	world[r + 6][c + 1] = '_';
	world[r + 6][c + 2] = '|';
	world[r + 6][c + 3] = '|';

	world[r + 6][c + 6] = '|';
	world[r + 6][c + 7] = '|';
	world[r + 6][c + 8] = '_';
	world[r + 6][c + 9] = '_';
	world[r + 6][c + 10] = '_';
	world[r + 6][c + 11] = '|';
	world[r + 6][c + 12] = '|';

	world[r + 6][c + 15] = '|';
	world[r + 6][c + 21] = '|';
	world[r + 6][c + 28] = '|';

	world[r + 6][c + 31] = '|';
	world[r + 6][c + 32] = '|';
	world[r + 6][c + 33] = '_';
	world[r + 6][c + 34] = '_';
	world[r + 6][c + 35] = '_';
	world[r + 6][c + 36] = '|';
	world[r + 6][c + 37] = '|';

	world[r + 6][c + 40] = '|';
	world[r + 6][c + 41] = '|';
	world[r + 6][c + 42] = '_';
	world[r + 6][c + 43] = '_';
	world[r + 6][c + 44] = '|';

	world[r + 7][c] = '|';
	world[r + 7][c + 1] = '_';
	world[r + 7][c + 2] = '_';
	world[r + 7][c + 3] = '|';

	world[r + 7][c + 6] = '|';
	world[r + 7][c + 7] = '_';
	world[r + 7][c + 8] = '_';
	world[r + 7][c + 9] = '|';
	world[r + 7][c + 10] = '_';
	world[r + 7][c + 11] = '_';
	world[r + 7][c + 12] = '|';

	world[r + 7][c + 15] = '|';
	world[r + 7][c + 21] = '|';
	world[r + 7][c + 28] = '|';

	world[r + 7][c + 31] = '|';
	world[r + 7][c + 32] = '_';
	world[r + 7][c + 33] = '_';
	world[r + 7][c + 34] = '|';
	world[r + 7][c + 35] = '_';
	world[r + 7][c + 36] = '_';
	world[r + 7][c + 37] = '|';

	world[r + 7][c + 40] = '|';
	world[r + 7][c + 41] = '_';
	world[r + 7][c + 42] = '_';
	world[r + 7][c + 43] = '|';
	world[r + 7][c + 44] = '|';

	world[r + 8][c] = '_';
	world[r + 8][c + 1] = '_';
	world[r + 8][c + 2] = '|';
	world[r + 8][c + 3] = '|';

	world[r + 8][c + 6] = '|';
	world[r + 8][c + 7] = '|';
	world[r + 8][c + 8] = '_';
	world[r + 8][c + 9] = '_';
	world[r + 8][c + 10] = '_';
	world[r + 8][c + 11] = '|';
	world[r + 8][c + 12] = '|';

	world[r + 8][c + 15] = '|';
	world[r + 8][c + 21] = '|';
	world[r + 8][c + 28] = '|';

	world[r + 8][c + 31] = '|';
	world[r + 8][c + 32] = '|';
	world[r + 8][c + 33] = '_';
	world[r + 8][c + 34] = '_';
	world[r + 8][c + 35] = '_';
	world[r + 8][c + 36] = '|';
	world[r + 8][c + 37] = '|';

	world[r + 8][c + 40] = '|';
	world[r + 8][c + 41] = '|';
	world[r + 8][c + 42] = '_';
	world[r + 8][c + 43] = '_';
	world[r + 8][c + 44] = '|';

	world[r + 9][c] = '|';
	world[r + 9][c + 1] = '_';
	world[r + 9][c + 2] = '_';
	world[r + 9][c + 3] = '|';

	world[r + 9][c + 6] = '|';
	world[r + 9][c + 7] = '_';
	world[r + 9][c + 8] = '_';
	world[r + 9][c + 9] = '|';
	world[r + 9][c + 10] = '_';
	world[r + 9][c + 11] = '_';
	world[r + 9][c + 12] = '|';

	world[r + 9][c + 15] = '|';
	world[r + 9][c + 21] = '|';
	world[r + 9][c + 28] = '|';

	world[r + 9][c + 31] = '|';
	world[r + 9][c + 32] = '_';
	world[r + 9][c + 33] = '_';
	world[r + 9][c + 34] = '|';
	world[r + 9][c + 35] = '_';
	world[r + 9][c + 36] = '_';
	world[r + 9][c + 37] = '|';

	world[r + 9][c + 40] = '|';
	world[r + 9][c + 41] = '_';
	world[r + 9][c + 42] = '_';
	world[r + 9][c + 43] = '|';
	world[r + 9][c + 44] = '|';

	world[r + 10][c] = '_';
	world[r + 10][c + 1] = '_';
	world[r + 10][c + 2] = '|';
	world[r + 10][c + 3] = '|';

	world[r + 10][c + 6] = '|';
	world[r + 10][c + 7] = '|';
	world[r + 10][c + 8] = '_';
	world[r + 10][c + 9] = '_';
	world[r + 10][c + 10] = '_';
	world[r + 10][c + 11] = '|';
	world[r + 10][c + 12] = '|';

	world[r + 10][c + 15] = '|';
	world[r + 10][c + 21] = '|';
	world[r + 10][c + 28] = '|';

	world[r + 10][c + 31] = '|';
	world[r + 10][c + 32] = '|';
	world[r + 10][c + 33] = '_';
	world[r + 10][c + 34] = '_';
	world[r + 10][c + 35] = '_';
	world[r + 10][c + 36] = '|';
	world[r + 10][c + 37] = '|';

	world[r + 10][c + 40] = '|';
	world[r + 10][c + 41] = '|';
	world[r + 10][c + 42] = '_';
	world[r + 10][c + 43] = '_';
	world[r + 10][c + 44] = '|';

	world[r + 11][c] = '|';
	world[r + 11][c + 1] = '_';
	world[r + 11][c + 2] = '_';
	world[r + 11][c + 3] = '|';

	world[r + 11][c + 6] = '|';
	world[r + 11][c + 7] = '_';
	world[r + 11][c + 8] = '_';
	world[r + 11][c + 9] = '|';
	world[r + 11][c + 10] = '_';
	world[r + 11][c + 11] = '_';
	world[r + 11][c + 12] = '|';

	world[r + 11][c + 15] = '|';
	world[r + 11][c + 19] = 'O';
	world[r + 11][c + 21] = '|';
	world[r + 11][c + 23] = 'O';
	world[r + 11][c + 28] = '|';

	world[r + 11][c + 31] = '|';
	world[r + 11][c + 32] = '_';
	world[r + 11][c + 33] = '_';
	world[r + 11][c + 34] = '|';
	world[r + 11][c + 35] = '_';
	world[r + 11][c + 36] = '_';
	world[r + 11][c + 37] = '|';

	world[r + 11][c + 40] = '|';
	world[r + 11][c + 41] = '_';
	world[r + 11][c + 42] = '_';
	world[r + 11][c + 43] = '|';
	world[r + 11][c + 44] = '|';

	world[r + 12][c] = '_';
	world[r + 12][c + 1] = '_';
	world[r + 12][c + 2] = '|';
	world[r + 12][c + 3] = '|';

	world[r + 12][c + 6] = '|';
	world[r + 12][c + 7] = '|';
	world[r + 12][c + 8] = '_';
	world[r + 12][c + 9] = '_';
	world[r + 12][c + 10] = '_';
	world[r + 12][c + 11] = '|';
	world[r + 12][c + 12] = '|';

	world[r + 12][c + 15] = '|';
	world[r + 12][c + 21] = '|';
	world[r + 12][c + 28] = '|';

	world[r + 12][c + 31] = '|';
	world[r + 12][c + 32] = '|';
	world[r + 12][c + 33] = '_';
	world[r + 12][c + 34] = '_';
	world[r + 12][c + 35] = '_';
	world[r + 12][c + 36] = '|';
	world[r + 12][c + 37] = '|';

	world[r + 12][c + 40] = '|';
	world[r + 12][c + 41] = '|';
	world[r + 12][c + 42] = '_';
	world[r + 12][c + 43] = '_';
	world[r + 12][c + 44] = '|';

	world[r + 13][c] = '|';
	world[r + 13][c + 1] = '_';
	world[r + 13][c + 2] = '_';
	world[r + 13][c + 3] = '|';

	world[r + 13][c + 6] = '|';
	world[r + 13][c + 7] = '_';
	world[r + 13][c + 8] = '_';
	world[r + 13][c + 9] = '|';
	world[r + 13][c + 10] = '_';
	world[r + 13][c + 11] = '_';
	world[r + 13][c + 12] = '|';

	world[r + 13][c + 15] = '|';
	world[r + 13][c + 21] = '|';
	world[r + 13][c + 28] = '|';

	world[r + 13][c + 31] = '|';
	world[r + 13][c + 32] = '_';
	world[r + 13][c + 33] = '_';
	world[r + 13][c + 34] = '|';
	world[r + 13][c + 35] = '_';
	world[r + 13][c + 36] = '_';
	world[r + 13][c + 37] = '|';

	world[r + 13][c + 40] = '|';
	world[r + 13][c + 41] = '_';
	world[r + 13][c + 42] = '_';
	world[r + 13][c + 43] = '|';
	world[r + 13][c + 44] = '|';

	world[r + 14][c] = '_';
	world[r + 14][c + 1] = '_';
	world[r + 14][c + 2] = '|';
	world[r + 14][c + 3] = '|';

	world[r + 14][c + 6] = '|';
	world[r + 14][c + 7] = '|';
	world[r + 14][c + 8] = '_';
	world[r + 14][c + 9] = '_';
	world[r + 14][c + 10] = '_';
	world[r + 14][c + 11] = '|';
	world[r + 14][c + 12] = '|';

	world[r + 14][c + 15] = '|';
	world[r + 14][c + 21] = '|';
	world[r + 14][c + 28] = '|';

	world[r + 14][c + 31] = '|';
	world[r + 14][c + 32] = '|';
	world[r + 14][c + 33] = '_';
	world[r + 14][c + 34] = '_';
	world[r + 14][c + 35] = '_';
	world[r + 14][c + 36] = '|';
	world[r + 14][c + 37] = '|';

	world[r + 14][c + 40] = '|';
	world[r + 14][c + 41] = '|';
	world[r + 14][c + 42] = '_';
	world[r + 14][c + 43] = '_';
	world[r + 14][c + 44] = '|';

	world[r + 15][c] = '|';
	world[r + 15][c + 1] = '_';
	world[r + 15][c + 2] = '_';
	world[r + 15][c + 3] = '|';

	world[r + 15][c + 6] = '|';
	world[r + 15][c + 7] = '_';
	world[r + 15][c + 8] = '_';
	world[r + 15][c + 9] = '|';
	world[r + 15][c + 10] = '_';
	world[r + 15][c + 11] = '_';
	world[r + 15][c + 12] = '|';
	world[r + 15][c + 13] = '_';
	world[r + 15][c + 14] = '_';
	world[r + 15][c + 15] = '|';
	world[r + 15][c + 16] = '_';
	world[r + 15][c + 17] = '_';
	world[r + 15][c + 18] = '_';
	world[r + 15][c + 19] = '_';
	world[r + 15][c + 20] = '_';
	world[r + 15][c + 21] = '|';
	world[r + 15][c + 22] = '_';
	world[r + 15][c + 23] = '_';
	world[r + 15][c + 24] = '_';
	world[r + 15][c + 25] = '_';
	world[r + 15][c + 26] = '_';
	world[r + 15][c + 27] = '_';
	world[r + 15][c + 28] = '|';

	world[r + 15][c + 31] = '|';
	world[r + 15][c + 32] = '_';
	world[r + 15][c + 33] = '_';
	world[r + 15][c + 34] = '|';
	world[r + 15][c + 35] = '_';
	world[r + 15][c + 36] = '_';
	world[r + 15][c + 37] = '|';

	world[r + 15][c + 40] = '|';
	world[r + 15][c + 41] = '_';
	world[r + 15][c + 42] = '_';
	world[r + 15][c + 43] = '|';

	for (int tempR = r + 16; tempR <= r + 18; tempR++)
	{
		world[tempR][c] = 'L';
		world[tempR][c + 1] = 'L';
		world[tempR][c + 2] = 'L';
		world[tempR][c + 3] = '|';
	}

	world[r + 16][c + 6] = '|';

	for (int tempC = c + 7; tempC < (c + 7) + 8; tempC++)
	{
		world[r + 16][tempC] = 'L';
	}

	world[r + 16][c + 15] = '|';

	for (int tempC = c + 16; tempC < (c + 16) + 12; tempC++)
	{
		world[r + 16][tempC] = '_';
	}

	world[r + 16][c + 28] = '|';

	world[r + 16][c + 31] = '|';
	world[r + 16][c + 32] = '|';
	world[r + 16][c + 33] = '_';
	world[r + 16][c + 34] = '_';
	world[r + 16][c + 35] = '_';
	world[r + 16][c + 36] = '|';
	world[r + 16][c + 37] = '|';

	world[r + 16][c + 40] = '|';
	world[r + 16][c + 41] = '|';
	world[r + 16][c + 42] = '_';
	world[r + 16][c + 43] = '_';
	world[r + 16][c + 44] = '|';


	world[r + 17][c + 6] = '|';

	for (int tempC = c + 7; tempC < (c + 7) + 9; tempC++)
	{
		world[r + 17][tempC] = 'L';
	}

	world[r + 17][c + 16] = '|';

	for (int tempC = c + 17; tempC < (c + 17) + 12; tempC++)
	{
		world[r + 17][tempC] = '_';
	}

	world[r + 17][c + 29] = '|';

	world[r + 17][c + 33] = '|';
	world[r + 17][c + 34] = '_';
	world[r + 17][c + 35] = '_';
	world[r + 17][c + 36] = '|';
	world[r + 17][c + 37] = '|';

	world[r + 17][c + 40] = '|';
	world[r + 17][c + 41] = '|';
	world[r + 17][c + 42] = '_';
	world[r + 17][c + 43] = '_';

	world[r + 18][c + 6] = '|';

	for (int tempC = c + 7; tempC < (c + 7) + 10; tempC++)
	{
		world[r + 18][tempC] = 'L';
	}

	world[r + 18][c + 17] = '|';

	for (int tempC = c + 18; tempC < (c + 18) + 12; tempC++)
	{
		world[r + 18][tempC] = '_';
	}

	world[r + 18][c + 30] = '|';
	world[r + 18][c + 31] = '_';
	world[r + 18][c + 32] = '_';
	world[r + 18][c + 33] = '_';
	world[r + 18][c + 34] = '_';
	world[r + 18][c + 35] = '_';
	world[r + 18][c + 36] = '|';
	world[r + 18][c + 37] = '|';
	world[r + 18][c + 38] = '_';
	world[r + 18][c + 39] = '_';
	world[r + 18][c + 40] = '|';
	world[r + 18][c + 41] = '|';
	world[r + 18][c + 42] = '_';
	world[r + 18][c + 43] = '_';

	///////////////////////////////


	///////////////////////////////
	//// DRAWING LADDER  
	/////////////////////////////

	for (int r = 45; r < 90; r++)
	{
		if (r % 2 != 0)
		{
			world[r][339] = 205;
			world[r][340] = 206;

			for (int c = 341; c < 350; c++)
			{
				world[r][c] = 205;
			}

		}
		else
		{
			world[r][340] = 186;
		}
	}

	for (int r = 45; r < 90; r++)
	{
		if (r % 2 != 0)
		{
			world[r][350] = 206;
			world[r][351] = 205;
		}
		else
		{
			world[r][350] = 186;
		}
	}

	///////////////////////////////

	///////////////////////////////
	//// DRAWING SPIKES  
	/////////////////////////////

	drawSpike(87, 118, world);
	drawSpike(87, 122, world);
	drawSpike(87, 126, world);
	drawSpike(87, 130, world);
	drawSpike(87, 134, world);
	drawSpike(87, 138, world);

	drawSpike(87, 158, world);
	drawSpike(87, 162, world);
	drawSpike(87, 166, world);
	drawSpike(87, 170, world);
	drawSpike(87, 174, world);
	drawSpike(87, 178, world);

	drawSpike(87, 198, world);
	drawSpike(87, 202, world);
	drawSpike(87, 206, world);
	drawSpike(87, 210, world);
	drawSpike(87, 214, world);
	drawSpike(87, 218, world);

	/////////////////////////////


	///////////////////////////////
	//// DRAWING  BLOCKS FLOOR 1
	//////////////////////////////


	drawBlock(85, 100, world);

	drawBlock(85, 140, world);
	drawBlock(82, 140, world);

	drawBlock(85, 180, world);
	drawBlock(82, 180, world);
	drawBlock(79, 180, world);

	drawBlock(85, 220, world);
	drawBlock(82, 220, world);
	drawBlock(79, 220, world);
	drawBlock(76, 220, world);

	///////////////////////////////


}

void drawDiamond(unsigned char** world)
{
	///////////////////////////////
	//// DRAWING DIAMOND  
	/////////////////////////////

	int r = 13; int c = 335;

	world[r][c] = '.';
	world[r][c + 6] = 39;
	world[r][c + 12] = ',';

	for (int tempC = c + 2; tempC < (c + 2) + 9; tempC++)
	{
		world[r + 1][tempC] = '_';
	}

	world[r + 2][c + 1] = '/';
	world[r + 2][c + 2] = '_';
	world[r + 2][c + 3] = '|';

	for (int tempC = c + 4; tempC < (c + 4) + 5; tempC++)
	{
		world[r + 2][tempC] = '_';
	}

	world[r + 2][c + 9] = '|';
	world[r + 2][c + 10] = '_';
	world[r + 2][c + 11] = '\\';

	world[r + 3][c + 1] = 39;
	world[r + 3][c + 2] = '.';
	world[r + 3][c + 4] = '\\';
	world[r + 3][c + 8] = '/';
	world[r + 3][c + 10] = '.';
	world[r + 3][c + 11] = 39;


	world[r + 4][c + 3] = 39;
	world[r + 4][c + 4] = '.';
	world[r + 4][c + 5] = '\\';
	world[r + 4][c + 7] = '/';
	world[r + 4][c + 8] = '.';
	world[r + 4][c + 9] = 39;

	world[r + 5][c + 5] = 39;
	world[r + 5][c + 6] = '.';
	world[r + 5][c + 7] = 39;

	///////////////////////////////
}

void drawFloorDividers(unsigned char** world)
{
	for (int c = 35; c < 360; c++)
	{
		if (c % 2 == 0)
		{
			world[29][c] = ']';
		}
		else
		{
			world[29][c] = '[';
		}
	}

	for (int c = 0; c < 335; c++)
	{
		if (c % 2 == 0)
		{
			world[60][c] = ']';
		}
		else
		{
			world[60][c] = '[';
		}
	}

}

void moveHero(int& heroRow, int& heroCol, char heroDir, int isHeroOnLadder, int isHeroInElevator, int elevatorDir, int elevatorRow, int& heroCurrFloor, int isHeroJumpingLeft, int strtRow, Obstacle One, Obstacle Two, Obstacle Three, Obstacle Four)
{
	int nextRow = heroRow, nextCol = heroCol;

	if (isHeroInElevator == 1)
	{
		heroRow += elevatorDir;
	}

	if ((heroDir == 'w' || heroDir == 'W') && isHeroOnLadder == 1)
	{
		nextRow--;
	}
	if ((heroDir == 's' || heroDir == 'S') && isHeroOnLadder == 1)
	{
		nextRow++;
	}

	if ((heroDir == 'a' || heroDir == 'A') && isHeroOnLadder == 0)
	{
		nextCol--;
	}

	if ((heroDir == 'd' || heroDir == 'D') && isHeroOnLadder == 0)
	{
		nextCol++;
	}

	int heroL = nextCol - 7, heroR = nextCol + 7;
	int heroT = nextRow, heroB = nextRow + 13;

	/////////////////////////////////////
	//// CHECK COLLISION WITH OBSTACLES  
	///////////////////////////////////
	int move = 1;

	if (heroR >= One.strtCol && heroL <= One.endCol && heroB >= One.strtRow)
	{
		move = 0;
	}

	if (heroR >= Two.strtCol && heroL <= Two.endCol && heroB >= Two.strtRow)
	{
		move = 0;
	}

	if (heroR >= Three.strtCol && heroL <= Three.endCol && heroB >= Three.strtRow)
	{
		move = 0;
	}

	if (heroR >= Four.strtCol && heroL <= Four.endCol && heroB >= Four.strtRow)
	{
		move = 0;
	}

	///////////////////////////////////

	if (move == 1)
	{
		int floorCeiling, floorGround, floorR, floorL;

		if (heroCurrFloor == 1)
		{
			floorCeiling = 61;
			floorGround = 88;
			floorL = 54;
			floorR = 345;
		}

		if (heroCurrFloor == 2)
		{
			floorCeiling = 31;
			floorGround = 58;
			floorL = 40;
			floorR = 345;
		}

		if (heroCurrFloor == 3)
		{
			floorCeiling = 1;
			floorGround = 28;
			floorL = 40;
			floorR = 352;
		}


		if ((heroDir == 'w' || heroDir == 'W') && heroRow - 1 >= 45 && isHeroOnLadder == 1)
		{
			heroRow--;
		}
		if ((heroDir == 's' || heroDir == 'S') && heroRow + 13 + 1 <= 88 && isHeroOnLadder == 1)
		{
			heroRow++;
		}
		if ((heroDir == 'a' || heroDir == 'A') && isHeroOnLadder == 0)
		{
			if ((heroCurrFloor == 1 || heroCurrFloor == 2 || heroCurrFloor == 3) && heroCol - 1 > floorL)
			{
				heroCol--;
			}
			else
			{
				if ((heroCurrFloor == 2 || heroCurrFloor == 3) && heroCol < 43 && elevatorRow > strtRow && heroRow >= elevatorRow && isHeroInElevator == 0 && heroCol - 1 > 8 && isHeroInElevator == 0 && isHeroJumpingLeft == 1)
				{
					heroCol--;
				}
			}
		}
		if ((heroDir == 'd' || heroDir == 'D') && heroCol + 1 < floorR && isHeroOnLadder == 0)
		{
			heroCol++;
		}

	}

	/////////////////////////////////////
	//// DETECT HERO FLOOR 
	///////////////////////////////////

	if (heroRow + 13 < 29)
	{
		heroCurrFloor = 3;
	}
	else
	{
		if (heroRow + 13 < 59)
		{
			heroCurrFloor = 2;
		}
		else
		{
			heroCurrFloor = 1;
		}
	}

	///////////////////////////////////

}

void drawHero(int heroRow, int heroCol, char heroDir, unsigned char** world)
{
	if ((heroDir == 'w' || heroDir == 'W' || heroDir == 's' || heroDir == 'S' || heroDir == ' '))
	{
		// ROW 0
		world[heroRow][heroCol - 1] = '.';
		world[heroRow][heroCol] = '-';
		world[heroRow][heroCol + 1] = '.';
		// ROW 1
		world[heroRow + 1][heroCol - 2] = '(';
		world[heroRow + 1][heroCol - 1] = 'O';
		world[heroRow + 1][heroCol] = '.';
		world[heroRow + 1][heroCol + 1] = 'O';
		world[heroRow + 1][heroCol + 2] = ')';
		// ROW 2
		world[heroRow + 2][heroCol - 1] = '|';
		world[heroRow + 2][heroCol] = '=';
		world[heroRow + 2][heroCol + 1] = '|';
		// ROW 3
		world[heroRow + 3][heroCol - 2] = '_';
		world[heroRow + 3][heroCol - 1] = '_';
		world[heroRow + 3][heroCol] = '|';
		world[heroRow + 3][heroCol + 1] = '_';
		world[heroRow + 3][heroCol + 2] = '_';
		// ROW 4
		world[heroRow + 4][heroCol - 4] = '/';
		world[heroRow + 4][heroCol - 3] = '/';
		world[heroRow + 4][heroCol - 2] = '.';
		world[heroRow + 4][heroCol - 1] = '=';
		world[heroRow + 4][heroCol] = '|';
		world[heroRow + 4][heroCol + 1] = '=';
		world[heroRow + 4][heroCol + 2] = '.';
		world[heroRow + 4][heroCol + 3] = '\\';
		world[heroRow + 4][heroCol + 4] = '\\';
		// ROW 5
		world[heroRow + 5][heroCol - 5] = '/';
		world[heroRow + 5][heroCol - 4] = '/';
		world[heroRow + 5][heroCol - 3] = ' ';
		world[heroRow + 5][heroCol - 2] = '.';
		world[heroRow + 5][heroCol - 1] = '=';
		world[heroRow + 5][heroCol] = '|';
		world[heroRow + 5][heroCol + 1] = '=';
		world[heroRow + 5][heroCol + 2] = '.';
		world[heroRow + 5][heroCol + 3] = ' ';
		world[heroRow + 5][heroCol + 4] = '\\';
		world[heroRow + 5][heroCol + 5] = '\\';
		// ROW 6
		world[heroRow + 6][heroCol - 6] = '/';
		world[heroRow + 6][heroCol - 5] = '/';
		world[heroRow + 6][heroCol - 4] = ' ';
		world[heroRow + 6][heroCol - 3] = ' ';
		world[heroRow + 6][heroCol - 2] = '.';
		world[heroRow + 6][heroCol - 1] = '=';
		world[heroRow + 6][heroCol] = '|';
		world[heroRow + 6][heroCol + 1] = '=';
		world[heroRow + 6][heroCol + 2] = '.';
		world[heroRow + 6][heroCol + 3] = ' ';
		world[heroRow + 6][heroCol + 4] = ' ';
		world[heroRow + 6][heroCol + 5] = '\\';
		world[heroRow + 6][heroCol + 6] = '\\';
		// ROW 7
		world[heroRow + 7][heroCol - 7] = '(';
		world[heroRow + 7][heroCol - 6] = ' ';
		world[heroRow + 7][heroCol - 5] = ')';
		world[heroRow + 7][heroCol - 4] = ' ';
		world[heroRow + 7][heroCol - 3] = ' ';
		world[heroRow + 7][heroCol - 2] = '(';
		world[heroRow + 7][heroCol - 1] = '_';
		world[heroRow + 7][heroCol] = '=';
		world[heroRow + 7][heroCol + 1] = '_';
		world[heroRow + 7][heroCol + 2] = ')';
		world[heroRow + 7][heroCol + 3] = ' ';
		world[heroRow + 7][heroCol + 4] = ' ';
		world[heroRow + 7][heroCol + 5] = '(';
		world[heroRow + 7][heroCol + 6] = ' ';
		world[heroRow + 7][heroCol + 7] = ')';
		//ROW 8
		world[heroRow + 8][heroCol - 2] = '|';
		world[heroRow + 8][heroCol - 1] = '|';
		world[heroRow + 8][heroCol] = ' ';
		world[heroRow + 8][heroCol + 1] = '|';
		world[heroRow + 8][heroCol + 2] = '|';
		//ROW 9
		world[heroRow + 9][heroCol - 2] = '|';
		world[heroRow + 9][heroCol - 1] = '|';
		world[heroRow + 9][heroCol] = ' ';
		world[heroRow + 9][heroCol + 1] = '|';
		world[heroRow + 9][heroCol + 2] = '|';
		// R0W 10
		world[heroRow + 10][heroCol - 2] = '(';
		world[heroRow + 10][heroCol - 1] = ')';
		world[heroRow + 10][heroCol] = ' ';
		world[heroRow + 10][heroCol + 1] = '(';
		world[heroRow + 10][heroCol + 2] = ')';
		// ROW 11
		world[heroRow + 11][heroCol - 2] = '|';
		world[heroRow + 11][heroCol - 1] = '|';
		world[heroRow + 11][heroCol] = ' ';
		world[heroRow + 11][heroCol + 1] = '|';
		world[heroRow + 11][heroCol + 2] = '|';
		// ROW 12
		world[heroRow + 12][heroCol - 2] = '|';
		world[heroRow + 12][heroCol - 1] = '|';
		world[heroRow + 12][heroCol] = ' ';
		world[heroRow + 12][heroCol + 1] = '|';
		world[heroRow + 12][heroCol + 2] = '|';
		// ROW 13
		world[heroRow + 13][heroCol - 3] = '=';
		world[heroRow + 13][heroCol - 2] = '=';
		world[heroRow + 13][heroCol - 1] = 39;
		world[heroRow + 13][heroCol] = ' ';
		world[heroRow + 13][heroCol + 1] = 39;
		world[heroRow + 13][heroCol + 2] = '=';
		world[heroRow + 13][heroCol + 3] = '=';

	}
	if (heroDir == 'a' || heroDir == 'A')
	{
		// ROW 0
		world[heroRow][heroCol - 1] = '.';
		world[heroRow][heroCol] = '-';
		world[heroRow][heroCol + 1] = '.';
		// ROW 1
		world[heroRow + 1][heroCol - 2] = '(';
		world[heroRow + 1][heroCol - 1] = 'O';
		world[heroRow + 1][heroCol] = '.';
		world[heroRow + 1][heroCol + 1] = 'O';
		world[heroRow + 1][heroCol + 2] = ')';
		// ROW 2
		world[heroRow + 2][heroCol - 1] = '|';
		world[heroRow + 2][heroCol] = '=';
		world[heroRow + 2][heroCol + 1] = '|';
		// ROW 3
		world[heroRow + 3][heroCol - 2] = '_';
		world[heroRow + 3][heroCol - 1] = '_';
		world[heroRow + 3][heroCol] = '|';
		world[heroRow + 3][heroCol + 1] = '_';
		world[heroRow + 3][heroCol + 2] = '_';
		// ROW 4
		world[heroRow + 4][heroCol - 4] = '/';
		world[heroRow + 4][heroCol - 3] = '/';
		world[heroRow + 4][heroCol - 2] = '.';
		world[heroRow + 4][heroCol - 1] = '=';
		world[heroRow + 4][heroCol] = '|';
		world[heroRow + 4][heroCol + 1] = '=';
		world[heroRow + 4][heroCol + 2] = '.';
		world[heroRow + 4][heroCol + 3] = '\\';
		world[heroRow + 4][heroCol + 4] = '\\';
		// ROW 5
		world[heroRow + 5][heroCol - 5] = '/';
		world[heroRow + 5][heroCol - 4] = '/';
		world[heroRow + 5][heroCol - 3] = ' ';
		world[heroRow + 5][heroCol - 2] = '.';
		world[heroRow + 5][heroCol - 1] = '=';
		world[heroRow + 5][heroCol] = '|';
		world[heroRow + 5][heroCol + 1] = '=';
		world[heroRow + 5][heroCol + 2] = '.';
		world[heroRow + 5][heroCol + 3] = ' ';
		world[heroRow + 5][heroCol + 4] = '\\';
		world[heroRow + 5][heroCol + 5] = '\\';
		// ROW 6
		world[heroRow + 6][heroCol - 6] = '/';
		world[heroRow + 6][heroCol - 5] = '/';
		world[heroRow + 6][heroCol - 4] = ' ';
		world[heroRow + 6][heroCol - 3] = ' ';
		world[heroRow + 6][heroCol - 2] = '.';
		world[heroRow + 6][heroCol - 1] = '=';
		world[heroRow + 6][heroCol] = '|';
		world[heroRow + 6][heroCol + 1] = '=';
		world[heroRow + 6][heroCol + 2] = '.';
		world[heroRow + 6][heroCol + 3] = ' ';
		world[heroRow + 6][heroCol + 4] = ' ';
		world[heroRow + 6][heroCol + 5] = '\\';
		world[heroRow + 6][heroCol + 6] = '\\';
		// ROW 7
		world[heroRow + 7][heroCol - 7] = '(';
		world[heroRow + 7][heroCol - 6] = ' ';
		world[heroRow + 7][heroCol - 5] = ')';
		world[heroRow + 7][heroCol - 4] = ' ';
		world[heroRow + 7][heroCol - 3] = ' ';
		world[heroRow + 7][heroCol - 2] = '(';
		world[heroRow + 7][heroCol - 1] = '_';
		world[heroRow + 7][heroCol] = '=';
		world[heroRow + 7][heroCol + 1] = '_';
		world[heroRow + 7][heroCol + 2] = ')';
		world[heroRow + 7][heroCol + 3] = ' ';
		world[heroRow + 7][heroCol + 4] = ' ';
		world[heroRow + 7][heroCol + 5] = '(';
		world[heroRow + 7][heroCol + 6] = ' ';
		world[heroRow + 7][heroCol + 7] = ')';
		// ROW 8
		world[heroRow + 8][heroCol - 2] = '|';
		world[heroRow + 8][heroCol - 1] = '|';
		world[heroRow + 8][heroCol] = ' ';
		world[heroRow + 8][heroCol + 1] = '|';
		world[heroRow + 8][heroCol + 2] = '|';
		// ROW 9
		world[heroRow + 9][heroCol - 2] = '|';
		world[heroRow + 9][heroCol - 1] = '|';
		world[heroRow + 9][heroCol] = ' ';
		world[heroRow + 9][heroCol + 1] = '|';
		world[heroRow + 9][heroCol + 2] = '|';
		// R0W 10
		world[heroRow + 10][heroCol - 2] = '(';
		world[heroRow + 10][heroCol - 1] = ')';
		world[heroRow + 10][heroCol] = ' ';
		world[heroRow + 10][heroCol + 1] = '(';
		world[heroRow + 10][heroCol + 2] = ')';
		// ROW 11
		world[heroRow + 11][heroCol - 2] = '|';
		world[heroRow + 11][heroCol - 1] = '|';
		world[heroRow + 11][heroCol] = ' ';
		world[heroRow + 11][heroCol + 1] = '|';
		world[heroRow + 11][heroCol + 2] = '|';
		// ROW 12
		world[heroRow + 12][heroCol - 2] = '|';
		world[heroRow + 12][heroCol - 1] = '|';
		world[heroRow + 12][heroCol] = ' ';
		world[heroRow + 12][heroCol + 1] = '|';
		world[heroRow + 12][heroCol + 2] = '|';
		// ROW 13
		world[heroRow + 13][heroCol - 3] = '=';
		world[heroRow + 13][heroCol - 2] = '=';
		world[heroRow + 13][heroCol - 1] = 39;
		world[heroRow + 13][heroCol] = '=';
		world[heroRow + 13][heroCol + 1] = '=';
		world[heroRow + 13][heroCol + 2] = 39;
	}
	if (heroDir == 'd' || heroDir == 'D')
	{
		// ROW 0
		world[heroRow][heroCol - 1] = '.';
		world[heroRow][heroCol] = '-';
		world[heroRow][heroCol + 1] = '.';
		// ROW 1
		world[heroRow + 1][heroCol - 2] = '(';
		world[heroRow + 1][heroCol - 1] = 'O';
		world[heroRow + 1][heroCol] = '.';
		world[heroRow + 1][heroCol + 1] = 'O';
		world[heroRow + 1][heroCol + 2] = ')';
		// ROW 2
		world[heroRow + 2][heroCol - 1] = '|';
		world[heroRow + 2][heroCol] = '=';
		world[heroRow + 2][heroCol + 1] = '|';
		// ROW 3
		world[heroRow + 3][heroCol - 2] = '_';
		world[heroRow + 3][heroCol - 1] = '_';
		world[heroRow + 3][heroCol] = '|';
		world[heroRow + 3][heroCol + 1] = '_';
		world[heroRow + 3][heroCol + 2] = '_';
		// ROW 4
		world[heroRow + 4][heroCol - 4] = '/';
		world[heroRow + 4][heroCol - 3] = '/';
		world[heroRow + 4][heroCol - 2] = '.';
		world[heroRow + 4][heroCol - 1] = '=';
		world[heroRow + 4][heroCol] = '|';
		world[heroRow + 4][heroCol + 1] = '=';
		world[heroRow + 4][heroCol + 2] = '.';
		world[heroRow + 4][heroCol + 3] = '\\';
		world[heroRow + 4][heroCol + 4] = '\\';
		// ROW 5
		world[heroRow + 5][heroCol - 5] = '/';
		world[heroRow + 5][heroCol - 4] = '/';
		world[heroRow + 5][heroCol - 3] = ' ';
		world[heroRow + 5][heroCol - 2] = '.';
		world[heroRow + 5][heroCol - 1] = '=';
		world[heroRow + 5][heroCol] = '|';
		world[heroRow + 5][heroCol + 1] = '=';
		world[heroRow + 5][heroCol + 2] = '.';
		world[heroRow + 5][heroCol + 3] = ' ';
		world[heroRow + 5][heroCol + 4] = '\\';
		world[heroRow + 5][heroCol + 5] = '\\';
		// ROW 6
		world[heroRow + 6][heroCol - 6] = '/';
		world[heroRow + 6][heroCol - 5] = '/';
		world[heroRow + 6][heroCol - 4] = ' ';
		world[heroRow + 6][heroCol - 3] = ' ';
		world[heroRow + 6][heroCol - 2] = '.';
		world[heroRow + 6][heroCol - 1] = '=';
		world[heroRow + 6][heroCol] = '|';
		world[heroRow + 6][heroCol + 1] = '=';
		world[heroRow + 6][heroCol + 2] = '.';
		world[heroRow + 6][heroCol + 3] = ' ';
		world[heroRow + 6][heroCol + 4] = ' ';
		world[heroRow + 6][heroCol + 5] = '\\';
		world[heroRow + 6][heroCol + 6] = '\\';
		// ROW 7
		world[heroRow + 7][heroCol - 7] = '(';
		world[heroRow + 7][heroCol - 6] = ' ';
		world[heroRow + 7][heroCol - 5] = ')';
		world[heroRow + 7][heroCol - 4] = ' ';
		world[heroRow + 7][heroCol - 3] = ' ';
		world[heroRow + 7][heroCol - 2] = '(';
		world[heroRow + 7][heroCol - 1] = '_';
		world[heroRow + 7][heroCol] = '=';
		world[heroRow + 7][heroCol + 1] = '_';
		world[heroRow + 7][heroCol + 2] = ')';
		world[heroRow + 7][heroCol + 3] = ' ';
		world[heroRow + 7][heroCol + 4] = ' ';
		world[heroRow + 7][heroCol + 5] = '(';
		world[heroRow + 7][heroCol + 6] = ' ';
		world[heroRow + 7][heroCol + 7] = ')';
		// ROW 8
		world[heroRow + 8][heroCol - 2] = '|';
		world[heroRow + 8][heroCol - 1] = '|';
		world[heroRow + 8][heroCol] = ' ';
		world[heroRow + 8][heroCol + 1] = '|';
		world[heroRow + 8][heroCol + 2] = '|';
		// ROW 9
		world[heroRow + 9][heroCol - 2] = '|';
		world[heroRow + 9][heroCol - 1] = '|';
		world[heroRow + 9][heroCol] = ' ';
		world[heroRow + 9][heroCol + 1] = '|';
		world[heroRow + 9][heroCol + 2] = '|';
		// R0W 10
		world[heroRow + 10][heroCol - 2] = '(';
		world[heroRow + 10][heroCol - 1] = ')';
		world[heroRow + 10][heroCol] = ' ';
		world[heroRow + 10][heroCol + 1] = '(';
		world[heroRow + 10][heroCol + 2] = ')';
		// ROW 11
		world[heroRow + 11][heroCol - 2] = '|';
		world[heroRow + 11][heroCol - 1] = '|';
		world[heroRow + 11][heroCol] = ' ';
		world[heroRow + 11][heroCol + 1] = '|';
		world[heroRow + 11][heroCol + 2] = '|';
		// ROW 12
		world[heroRow + 12][heroCol - 2] = '|';
		world[heroRow + 12][heroCol - 1] = '|';
		world[heroRow + 12][heroCol] = ' ';
		world[heroRow + 12][heroCol + 1] = '|';
		world[heroRow + 12][heroCol + 2] = '|';
		// ROW 13
		world[heroRow + 13][heroCol - 2] = 39;
		world[heroRow + 13][heroCol - 1] = '=';
		world[heroRow + 13][heroCol] = '=';
		world[heroRow + 13][heroCol + 1] = 39;
		world[heroRow + 13][heroCol + 2] = '=';
		world[heroRow + 13][heroCol + 3] = '=';

	}
	if (heroDir == 'j' || heroDir == 'J')
	{
		// ROW 0
		world[heroRow][heroCol - 1] = '.';
		world[heroRow][heroCol] = '-';
		world[heroRow][heroCol + 1] = '.';
		// ROW 1
		world[heroRow + 1][heroCol - 2] = '(';
		world[heroRow + 1][heroCol - 1] = 'O';
		world[heroRow + 1][heroCol] = '.';
		world[heroRow + 1][heroCol + 1] = 'O';
		world[heroRow + 1][heroCol + 2] = ')';
		// ROW 2
		world[heroRow + 2][heroCol - 1] = '|';
		world[heroRow + 2][heroCol] = '=';
		world[heroRow + 2][heroCol + 1] = '|';
		// ROW 3
		world[heroRow + 3][heroCol - 2] = '_';
		world[heroRow + 3][heroCol - 1] = '_';
		world[heroRow + 3][heroCol] = '|';
		world[heroRow + 3][heroCol + 1] = '_';
		world[heroRow + 3][heroCol + 2] = '_';
		// ROW 4
		world[heroRow + 4][heroCol - 4] = '/';
		world[heroRow + 4][heroCol - 3] = '/';
		world[heroRow + 4][heroCol - 2] = '.';
		world[heroRow + 4][heroCol - 1] = '=';
		world[heroRow + 4][heroCol] = '|';
		world[heroRow + 4][heroCol + 1] = '=';
		world[heroRow + 4][heroCol + 2] = '.';
		world[heroRow + 4][heroCol + 3] = '\\';
		world[heroRow + 4][heroCol + 4] = '\\';
		// ROW 5
		world[heroRow + 5][heroCol - 5] = '/';
		world[heroRow + 5][heroCol - 4] = '/';
		world[heroRow + 5][heroCol - 3] = ' ';
		world[heroRow + 5][heroCol - 2] = '.';
		world[heroRow + 5][heroCol - 1] = '=';
		world[heroRow + 5][heroCol] = '|';
		world[heroRow + 5][heroCol + 1] = '=';
		world[heroRow + 5][heroCol + 2] = '.';
		world[heroRow + 5][heroCol + 3] = ' ';
		world[heroRow + 5][heroCol + 4] = '\\';
		world[heroRow + 5][heroCol + 5] = '\\';
		// ROW 6
		world[heroRow + 6][heroCol - 6] = '/';
		world[heroRow + 6][heroCol - 5] = '/';
		world[heroRow + 6][heroCol - 4] = ' ';
		world[heroRow + 6][heroCol - 3] = ' ';
		world[heroRow + 6][heroCol - 2] = '.';
		world[heroRow + 6][heroCol - 1] = '=';
		world[heroRow + 6][heroCol] = '|';
		world[heroRow + 6][heroCol + 1] = '=';
		world[heroRow + 6][heroCol + 2] = '.';
		world[heroRow + 6][heroCol + 3] = ' ';
		world[heroRow + 6][heroCol + 4] = ' ';
		world[heroRow + 6][heroCol + 5] = '\\';
		world[heroRow + 6][heroCol + 6] = '\\';
		// ROW 7
		world[heroRow + 7][heroCol - 7] = '(';
		world[heroRow + 7][heroCol - 6] = ' ';
		world[heroRow + 7][heroCol - 5] = ')';
		world[heroRow + 7][heroCol - 4] = ' ';
		world[heroRow + 7][heroCol - 3] = ' ';
		world[heroRow + 7][heroCol - 2] = '(';
		world[heroRow + 7][heroCol - 1] = '_';
		world[heroRow + 7][heroCol] = '=';
		world[heroRow + 7][heroCol + 1] = '_';
		world[heroRow + 7][heroCol + 2] = ')';
		world[heroRow + 7][heroCol + 3] = ' ';
		world[heroRow + 7][heroCol + 4] = ' ';
		world[heroRow + 7][heroCol + 5] = '(';
		world[heroRow + 7][heroCol + 6] = ' ';
		world[heroRow + 7][heroCol + 7] = ')';
		// ROW 8
		world[heroRow + 8][heroCol - 2] = '/';
		world[heroRow + 8][heroCol - 1] = '/';
		world[heroRow + 8][heroCol] = ' ';
		world[heroRow + 8][heroCol + 1] = '\\';
		world[heroRow + 8][heroCol + 2] = '\\';
		// ROW 9
		world[heroRow + 9][heroCol - 3] = '/';
		world[heroRow + 9][heroCol - 2] = '/';
		world[heroRow + 9][heroCol - 1] = ' ';
		world[heroRow + 9][heroCol] = ' ';
		world[heroRow + 9][heroCol + 1] = ' ';
		world[heroRow + 9][heroCol + 2] = '\\';
		world[heroRow + 9][heroCol + 3] = '\\';
		// ROW 10
		world[heroRow + 10][heroCol - 4] = '(';
		world[heroRow + 10][heroCol - 3] = ')';
		world[heroRow + 10][heroCol - 2] = ' ';
		world[heroRow + 10][heroCol - 1] = ' ';
		world[heroRow + 10][heroCol] = ' ';
		world[heroRow + 10][heroCol + 1] = ' ';
		world[heroRow + 10][heroCol + 2] = ' ';
		world[heroRow + 10][heroCol + 3] = '(';
		world[heroRow + 10][heroCol + 4] = ')';
		// ROW 11
		world[heroRow + 11][heroCol - 5] = '/';
		world[heroRow + 11][heroCol - 4] = '/';
		world[heroRow + 11][heroCol - 3] = ' ';
		world[heroRow + 11][heroCol - 2] = ' ';
		world[heroRow + 11][heroCol - 1] = ' ';
		world[heroRow + 11][heroCol] = ' ';
		world[heroRow + 11][heroCol + 1] = ' ';
		world[heroRow + 11][heroCol + 2] = ' ';
		world[heroRow + 11][heroCol + 3] = ' ';
		world[heroRow + 11][heroCol + 4] = '\\';
		world[heroRow + 11][heroCol + 5] = '\\';
		// ROW 12
		world[heroRow + 12][heroCol - 6] = '/';
		world[heroRow + 12][heroCol - 5] = '/';
		world[heroRow + 12][heroCol - 4] = ' ';
		world[heroRow + 12][heroCol - 3] = ' ';
		world[heroRow + 12][heroCol - 2] = ' ';
		world[heroRow + 12][heroCol - 1] = ' ';
		world[heroRow + 12][heroCol] = ' ';
		world[heroRow + 12][heroCol + 1] = ' ';
		world[heroRow + 12][heroCol + 2] = ' ';
		world[heroRow + 12][heroCol + 3] = ' ';
		world[heroRow + 12][heroCol + 4] = ' ';
		world[heroRow + 12][heroCol + 5] = '\\';
		world[heroRow + 12][heroCol + 6] = '\\';
		// ROW 13
		world[heroRow + 13][heroCol - 7] = '=';
		world[heroRow + 13][heroCol - 6] = '=';
		world[heroRow + 13][heroCol - 5] = 39;
		world[heroRow + 13][heroCol - 4] = ' ';
		world[heroRow + 12][heroCol - 3] = ' ';
		world[heroRow + 13][heroCol - 2] = ' ';
		world[heroRow + 13][heroCol - 1] = ' ';
		world[heroRow + 13][heroCol] = ' ';
		world[heroRow + 13][heroCol + 1] = ' ';
		world[heroRow + 13][heroCol + 2] = ' ';
		world[heroRow + 13][heroCol + 3] = ' ';
		world[heroRow + 13][heroCol + 4] = ' ';
		world[heroRow + 13][heroCol + 5] = 39;
		world[heroRow + 13][heroCol + 6] = '=';
		world[heroRow + 13][heroCol + 7] = '=';


	}
}

void drawElevator(int elevatorRow, int isHeroInElevator, unsigned char** world)
{
	int r = elevatorRow;


	for (int k = r; k < r + 15; k++)
	{
		for (int c = 2; c < 33; c++)
		{
			world[k][c] = ' ';
		}
	}

	fillElevatorRow(r++, 2, 33, 219, world);

	fillElevatorRow(r, 2, 10, 219, world);
	fillElevatorRow(r, 13, 16, '.', world);
	world[r][20] = '.';
	fillElevatorRow(r, 25, 33, 219, world);
	r++;

	fillElevatorRow(r, 2, 10, 219, world);
	fillElevatorRow(r, 14, 16, '.', world);
	fillElevatorRow(r, 19, 21, '.', world);
	fillElevatorRow(r, 25, 33, 219, world);
	r++;

	fillElevatorRow(r, 2, 10, 219, world);
	world[r][15] = '.';
	fillElevatorRow(r, 18, 21, '.', world);
	fillElevatorRow(r, 25, 33, 219, world);
	r++;

	fillElevatorRow(r++, 2, 33, 219, world);

	for (; r < elevatorRow + 19; r++)
	{
		fillElevatorRow(r, 2, 6, 219, world);
		world[r][17] = 219;
		fillElevatorRow(r, 29, 33, 219, world);
	}

	fillElevatorRow(r, 2, 33, 219, world);

	if (isHeroInElevator == 1)
	{
		drawHero(elevatorRow + 5, 17, ' ', world);
	}
}

void comeHereGravity(int& heroRow, int& heroCol, int& isHeroGoingDown, int heroCurrFloor, Obstacle One, Obstacle Two, Obstacle Three, Obstacle Four)
{
	int heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;
	int isHeroOnGround = 0;

	if (heroCurrFloor == 1 && heroB == 88)
	{
		isHeroOnGround = 1;
	}

	if (heroCurrFloor == 2 && heroB == 58)
	{
		isHeroOnGround = 1;
	}

	if (heroCurrFloor == 3 && heroB == 28)
	{
		isHeroOnGround = 1;
	}

	if (heroR >= One.strtCol && heroL <= One.endCol && heroB == One.strtRow - 1)
	{
		isHeroOnGround = 1;
	}

	if (heroR >= Two.strtCol && heroL <= Two.endCol && heroB == Two.strtRow - 1)
	{
		isHeroOnGround = 1;
	}

	if (heroR >= Three.strtCol && heroL <= Three.endCol && heroB == Three.strtRow - 1)
	{
		isHeroOnGround = 1;
	}

	if (heroR >= Four.strtCol && heroL <= Four.endCol && heroB == Four.strtRow - 1)
	{
		isHeroOnGround = 1;
	}

	if (isHeroOnGround == 1)
	{
		isHeroGoingDown = 0;
	}
	else
	{
		isHeroGoingDown = 1;
		heroRow++;
	}
}

void drawHeroLives(int strtRow, int strtCol, int heroLives, unsigned char** world)
{
	int r = strtRow + 1;
	int c = strtCol + 50;

	world[r][c - 1] = ' ';
	world[r][c] = 'L';
	world[r][c + 1] = 'I';
	world[r][c + 2] = 'V';
	world[r][c + 3] = 'E';
	world[r][c + 4] = 'S';
	world[r][c + 5] = ':';
	world[r][c + 6] = ' ';

	if (heroLives <= 0)
	{
		world[r][c + 7] = '#';
		world[r][c + 8] = ' ';
	}
	else
	{
		if (heroLives == 1)
		{
			world[r][c + 7] = '$';
			world[r][c + 8] = ' ';
		}
		else
		{
			if (heroLives == 2)
			{
				world[r][c + 7] = '$';
				world[r][c + 8] = ' ';
				world[r][c + 9] = '$';
				world[r][c + 10] = ' ';
			}
			else
			{
				if (heroLives == 3)
				{
					world[r][c + 7] = '$';
					world[r][c + 8] = ' ';
					world[r][c + 9] = '$';
					world[r][c + 10] = ' ';
					world[r][c + 11] = '$';
					world[r][c + 12] = ' ';
				}
			}
		}
	}
}

void checkHeroCollisionWithSpike(int& heroRow, int& heroCol, int& heroLives, int& strtCol, int& endCol, Enemy& FloorOne)
{
	int heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;
	int isCollide = 0;

	if (heroB >= 87)
	{
		if (heroR >= 117 && heroL < 140)
		{
			heroLives--; isCollide = 1;
		}
		else
		{
			if (heroR >= 157 && heroL < 180)
			{
				heroLives--; isCollide = 1;
			}
			else
			{
				if (heroR >= 197 && heroL < 220)
				{
					heroLives--; isCollide = 1;
				}
			}
		}

	}

	if (isCollide == 1)
	{
		strtCol = 0;
		endCol = 120;

		heroRow = 75;
		heroCol = 60;

		FloorOne.isAlive = 1;
		FloorOne.Health = 3;
	}

}

void moveSingleBullet(int& singleBulletRow, int& singleBulletCol, int heroCurrFloor, char prevHeroDir, int& doYouWantSingleBullet, Obstacle One, Obstacle Two, Obstacle Three, Obstacle Four)
{
	if (prevHeroDir == 'd' || prevHeroDir == 'D')
	{
		singleBulletCol += 2;

		if (heroCurrFloor == 1 || heroCurrFloor == 2)
		{
			if (singleBulletCol + 5 >= 338)
			{
				doYouWantSingleBullet = 0;
			}
		}
		else
		{
			if (heroCurrFloor == 3)
			{
				if (singleBulletCol + 5 >= 358)
				{
					doYouWantSingleBullet = 0;
				}
			}
		}
	}
	else
	{
		if (prevHeroDir == 'a' || prevHeroDir == 'A')
		{
			singleBulletCol -= 2;
			if (heroCurrFloor == 1)
			{
				if (singleBulletCol - 5 <= 47)
				{
					doYouWantSingleBullet = 0;
				}
			}
			else
			{
				if (heroCurrFloor == 2 || heroCurrFloor == 3)
				{

					if (singleBulletCol - 5 <= 35)
					{
						doYouWantSingleBullet = 0;
					}
				}
			}
		}
	}

	if (doYouWantSingleBullet == 1)
	{
		int singleBulletL, singleBulletR;

		if (prevHeroDir == 'd' || prevHeroDir == 'D')
		{
			singleBulletL = singleBulletCol;
			singleBulletR = singleBulletCol + 5;
		}
		else
		{
			if (prevHeroDir == 'a' || prevHeroDir == 'A')
			{
				singleBulletL = singleBulletCol - 5;
				singleBulletR = singleBulletCol;
			}
		}

		if (singleBulletR >= One.strtCol && singleBulletL <= One.endCol && singleBulletRow >= One.strtRow)
		{
			doYouWantSingleBullet = 0;
		}

		if (singleBulletR >= Two.strtCol && singleBulletL <= Two.endCol && singleBulletRow >= Two.strtRow)
		{
			doYouWantSingleBullet = 0;
		}

		if (singleBulletR >= Three.strtCol && singleBulletL <= Three.endCol && singleBulletRow >= Three.strtRow)
		{
			doYouWantSingleBullet = 0;
		}

		if (singleBulletR >= Four.strtCol && singleBulletL <= Four.endCol && singleBulletRow >= Four.strtRow)
		{
			doYouWantSingleBullet = 0;
		}


	}
}

void drawSingleBullet(int singleBulletRow, int singleBulletCol, char prevHeroDir, int doYouWantSingleBullet, unsigned char** world)
{
	if (doYouWantSingleBullet == 1)
	{
		if (prevHeroDir == 'd' || prevHeroDir == 'D')
		{
			world[singleBulletRow][singleBulletCol] = '>';
			world[singleBulletRow][singleBulletCol + 1] = '>';
			world[singleBulletRow][singleBulletCol + 2] = '-';
			world[singleBulletRow][singleBulletCol + 3] = '-';
			world[singleBulletRow][singleBulletCol + 4] = '-';
			world[singleBulletRow][singleBulletCol + 5] = '>';
		}
		else
		{
			if (prevHeroDir == 'a' || prevHeroDir == 'A')
			{
				world[singleBulletRow][singleBulletCol] = '<';
				world[singleBulletRow][singleBulletCol - 1] = '<';
				world[singleBulletRow][singleBulletCol - 2] = '-';
				world[singleBulletRow][singleBulletCol - 3] = '-';
				world[singleBulletRow][singleBulletCol - 4] = '-';
				world[singleBulletRow][singleBulletCol - 5] = '<';

			}
		}
	}

}

void activateMultiBullets(int heroRow, int heroCol, char prevHeroDir, Bullet* MultiBullets)
{
	for (int i = 0; i < 5; i++)
	{
		if (MultiBullets[i].IsActive == 0)
		{
			MultiBullets[i].IsActive = 1;
			MultiBullets[i].Dir = prevHeroDir;
			MultiBullets[i].Row = heroRow + 7;

			if (prevHeroDir == 'd' || prevHeroDir == 'D')
			{
				MultiBullets[i].Col = heroCol + 8;
			}
			else
			{
				if (prevHeroDir == 'a' || prevHeroDir == 'A')
				{
					MultiBullets[i].Col = heroCol - 8;
				}
			}

			break;
		}
	}
}

void moveMultiBullets(Bullet* MultiBullets, int heroCurrFloor, Obstacle One, Obstacle Two, Obstacle Three, Obstacle Four)
{
	for (int i = 0; i < 5; i++)
	{
		if (MultiBullets[i].IsActive == 1)
		{
			if (MultiBullets[i].Dir == 'd' || MultiBullets[i].Dir == 'D')
			{
				MultiBullets[i].Col += 2;
			}
			else
			{
				MultiBullets[i].Col -= 2;
			}

			if (MultiBullets[i].Dir == 'd' || MultiBullets[i].Dir == 'D')
			{
				if (heroCurrFloor == 1 || heroCurrFloor == 2)
				{
					if (MultiBullets[i].Col + 5 >= 338)
					{
						MultiBullets[i].IsActive = 0;
					}
				}
				else
				{
					if (heroCurrFloor == 3)
					{
						if (MultiBullets[i].Col + 5 >= 358)
						{
							MultiBullets[i].IsActive = 0;
						}
					}
				}

			}
			else
			{
				if (MultiBullets[i].Dir == 'a' || MultiBullets[i].Dir == 'A')
				{
					if (heroCurrFloor == 1)
					{
						if (MultiBullets[i].Col - 5 <= 47)
						{
							MultiBullets[i].IsActive = 0;
						}
					}
					else
					{
						if (heroCurrFloor == 2 || heroCurrFloor == 3)
						{

							if (MultiBullets[i].Col - 5 <= 35)
							{
								MultiBullets[i].IsActive = 0;
							}
						}

					}

				}
			}

			if (MultiBullets[i].IsActive == 1)
			{
				int MultiBulletL, MultiBulletR;

				if (MultiBullets[i].Dir == 'd' || MultiBullets[i].Dir == 'D')
				{
					MultiBulletL = MultiBullets[i].Col;
					MultiBulletR = MultiBullets[i].Col + 8;
				}
				else
				{
					if (MultiBullets[i].Dir == 'a' || MultiBullets[i].Dir == 'A')
					{
						MultiBulletL = MultiBullets[i].Col - 8;
						MultiBulletR = MultiBullets[i].Col;
					}
				}

				if (MultiBulletR >= One.strtCol && MultiBulletL <= One.endCol && MultiBullets[i].Row >= One.strtRow)
				{
					MultiBullets[i].IsActive = 0;
				}

				if (MultiBulletR >= Two.strtCol && MultiBulletL <= Two.endCol && MultiBullets[i].Row >= Two.strtRow)
				{
					MultiBullets[i].IsActive = 0;
				}

				if (MultiBulletR >= Three.strtCol && MultiBulletL <= Three.endCol && MultiBullets[i].Row >= Three.strtRow)
				{
					MultiBullets[i].IsActive = 0;
				}

				if (MultiBulletR >= Four.strtCol && MultiBulletL <= Four.endCol && MultiBullets[i].Row >= Four.strtRow)
				{
					MultiBullets[i].IsActive = 0;
				}

			}
		}
	}
}

void drawMultiBullets(Bullet* MultiBullets, unsigned char** world)
{
	for (int i = 0; i < 5; i++)
	{
		if (MultiBullets[i].IsActive == 1)
		{
			if (MultiBullets[i].Dir == 'd' || MultiBullets[i].Dir == 'D')
			{
				world[MultiBullets[i].Row][MultiBullets[i].Col] = '>';
				world[MultiBullets[i].Row][MultiBullets[i].Col + 1] = '>';
				world[MultiBullets[i].Row][MultiBullets[i].Col + 2] = '-';
				world[MultiBullets[i].Row][MultiBullets[i].Col + 3] = '-';
				world[MultiBullets[i].Row][MultiBullets[i].Col + 4] = '-';
				world[MultiBullets[i].Row][MultiBullets[i].Col + 5] = '>';
			}
			else
			{
				if (MultiBullets[i].Dir == 'a' || MultiBullets[i].Dir == 'A')
				{
					world[MultiBullets[i].Row][MultiBullets[i].Col] = '<';
					world[MultiBullets[i].Row][MultiBullets[i].Col - 1] = '<';
					world[MultiBullets[i].Row][MultiBullets[i].Col - 2] = '-';
					world[MultiBullets[i].Row][MultiBullets[i].Col - 3] = '-';
					world[MultiBullets[i].Row][MultiBullets[i].Col - 4] = '-';
					world[MultiBullets[i].Row][MultiBullets[i].Col - 5] = '<';

				}
			}
		}
	}
}

void moveFloorOneEnemy(Enemy& FloorOne)
{
	// RIGHT AND LEFT
	if (FloorOne.Col >= 325)
	{
		FloorOne.Dir = -2;
	}
	else
	{
		if (FloorOne.Col <= 255)
		{
			FloorOne.Dir = 2;
		}
	}

	// UP AND DOWN
	if (FloorOne.Row <= 63)
	{
		FloorOne.DirTwo = 2;
	}
	else
	{
		if (FloorOne.Row + 16 >= 88)
		{
			FloorOne.DirTwo = -2;
		}
	}

	FloorOne.Col += FloorOne.Dir;
	FloorOne.Row += FloorOne.DirTwo;
}

void drawFloorOneEnemy(Enemy FloorOne, unsigned char** world)
{
	// ROW 0
	world[FloorOne.Row][FloorOne.Col] = '/';
	world[FloorOne.Row][FloorOne.Col + 1] = '\\';

	//ROW 1
	world[FloorOne.Row + 1][FloorOne.Col - 1] = '/';
	world[FloorOne.Row + 1][FloorOne.Col] = ' ';
	world[FloorOne.Row + 1][FloorOne.Col + 1] = ' ';
	world[FloorOne.Row + 1][FloorOne.Col + 2] = '\\';

	// ROW 2
	world[FloorOne.Row + 2][FloorOne.Col - 2] = '|';
	world[FloorOne.Row + 2][FloorOne.Col - 1] = ' ';
	world[FloorOne.Row + 2][FloorOne.Col] = ' ';
	world[FloorOne.Row + 2][FloorOne.Col + 1] = ' ';
	world[FloorOne.Row + 2][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 2][FloorOne.Col + 3] = '|';

	// ROW 3
	world[FloorOne.Row + 3][FloorOne.Col - 4] = '-';
	world[FloorOne.Row + 3][FloorOne.Col - 3] = '-';
	world[FloorOne.Row + 3][FloorOne.Col - 2] = ':';
	world[FloorOne.Row + 3][FloorOne.Col - 1] = 39;
	world[FloorOne.Row + 3][FloorOne.Col] = 39;
	world[FloorOne.Row + 3][FloorOne.Col + 1] = 39;
	world[FloorOne.Row + 3][FloorOne.Col + 2] = 39;
	world[FloorOne.Row + 3][FloorOne.Col + 3] = ':';
	world[FloorOne.Row + 3][FloorOne.Col + 4] = '-';
	world[FloorOne.Row + 3][FloorOne.Col + 5] = '-';

	// ROW 4
	world[FloorOne.Row + 4][FloorOne.Col - 2] = ':';
	world[FloorOne.Row + 4][FloorOne.Col - 1] = 39;
	world[FloorOne.Row + 4][FloorOne.Col] = '_';
	world[FloorOne.Row + 4][FloorOne.Col + 1] = 39;
	world[FloorOne.Row + 4][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 4][FloorOne.Col + 3] = ':';

	// ROW 5
	world[FloorOne.Row + 5][FloorOne.Col - 2] = '_';
	world[FloorOne.Row + 5][FloorOne.Col - 1] = ':';
	world[FloorOne.Row + 5][FloorOne.Col] = '"';
	world[FloorOne.Row + 5][FloorOne.Col + 1] = '"';
	world[FloorOne.Row + 5][FloorOne.Col + 2] = ':';
	world[FloorOne.Row + 5][FloorOne.Col + 3] = '\\';
	world[FloorOne.Row + 5][FloorOne.Col + 4] = '_';
	world[FloorOne.Row + 5][FloorOne.Col + 5] = '_';
	world[FloorOne.Row + 5][FloorOne.Col + 6] = '_';

	// ROW 6
	world[FloorOne.Row + 6][FloorOne.Col - 17] = 39;
	world[FloorOne.Row + 6][FloorOne.Col - 16] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 15] = 39;
	world[FloorOne.Row + 6][FloorOne.Col - 14] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 13] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 12] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 11] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 10] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 9] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 8] = '_';
	world[FloorOne.Row + 6][FloorOne.Col - 7] = '_';
	world[FloorOne.Row + 6][FloorOne.Col - 6] = '_';
	world[FloorOne.Row + 6][FloorOne.Col - 5] = '_';
	world[FloorOne.Row + 6][FloorOne.Col - 4] = '.';
	world[FloorOne.Row + 6][FloorOne.Col - 3] = 39;
	world[FloorOne.Row + 6][FloorOne.Col - 2] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col - 1] = ':';
	world[FloorOne.Row + 6][FloorOne.Col] = ':';
	world[FloorOne.Row + 6][FloorOne.Col + 1] = ':';
	world[FloorOne.Row + 6][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col + 3] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col + 4] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col + 5] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col + 6] = ' ';
	world[FloorOne.Row + 6][FloorOne.Col + 7] = 39;
	world[FloorOne.Row + 6][FloorOne.Col + 8] = '.';
	world[FloorOne.Row + 6][FloorOne.Col + 9] = '_';

	// ROW 7
	world[FloorOne.Row + 7][FloorOne.Col - 18] = '.';
	world[FloorOne.Row + 7][FloorOne.Col - 17] = ' ';
	world[FloorOne.Row + 7][FloorOne.Col - 16] = '*';
	world[FloorOne.Row + 7][FloorOne.Col - 15] = '=';
	world[FloorOne.Row + 7][FloorOne.Col - 14] = '=';
	world[FloorOne.Row + 7][FloorOne.Col - 13] = '=';
	world[FloorOne.Row + 7][FloorOne.Col - 12] = '=';
	world[FloorOne.Row + 7][FloorOne.Col - 11] = '=';
	world[FloorOne.Row + 7][FloorOne.Col - 10] = '<';
	world[FloorOne.Row + 7][FloorOne.Col - 9] = '<';
	world[FloorOne.Row + 7][FloorOne.Col - 8] = '=';
	world[FloorOne.Row + 7][FloorOne.Col - 7] = ')';

	for (int i = -7; i <= 4; i++)
	{
		world[FloorOne.Row + 7][FloorOne.Col - i] = ' ';
	}

	world[FloorOne.Row + 7][FloorOne.Col + 5] = '\\';
	world[FloorOne.Row + 7][FloorOne.Col + 6] = ' ';
	world[FloorOne.Row + 7][FloorOne.Col + 7] = ' ';
	world[FloorOne.Row + 7][FloorOne.Col + 8] = ' ';
	world[FloorOne.Row + 7][FloorOne.Col + 9] = ' ';
	world[FloorOne.Row + 7][FloorOne.Col + 10] = ':';

	// ROW 8
	world[FloorOne.Row + 8][FloorOne.Col - 17] = '.';
	world[FloorOne.Row + 8][FloorOne.Col - 16] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 15] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 14] = 39;
	world[FloorOne.Row + 8][FloorOne.Col - 13] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 12] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 11] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 10] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 9] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 8] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col - 7] = 39;
	world[FloorOne.Row + 8][FloorOne.Col - 6] = '-';
	world[FloorOne.Row + 8][FloorOne.Col - 5] = 39;
	world[FloorOne.Row + 8][FloorOne.Col - 4] = '-';
	world[FloorOne.Row + 8][FloorOne.Col - 3] = 39;
	world[FloorOne.Row + 8][FloorOne.Col - 2] = '\\';
	world[FloorOne.Row + 8][FloorOne.Col - 1] = '_';
	world[FloorOne.Row + 8][FloorOne.Col] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col + 1] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col + 3] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col + 4] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col + 5] = ' ';
	world[FloorOne.Row + 8][FloorOne.Col + 6] = '/';
	world[FloorOne.Row + 8][FloorOne.Col + 7] = 39;
	world[FloorOne.Row + 8][FloorOne.Col + 8] = '.';
	world[FloorOne.Row + 8][FloorOne.Col + 9] = '_';
	world[FloorOne.Row + 8][FloorOne.Col + 10] = '.';
	world[FloorOne.Row + 8][FloorOne.Col + 11] = 39;

	// ROW 9
	world[FloorOne.Row + 9][FloorOne.Col] = '\\';
	world[FloorOne.Row + 9][FloorOne.Col + 1] = '=';
	world[FloorOne.Row + 9][FloorOne.Col + 2] = '=';
	world[FloorOne.Row + 9][FloorOne.Col + 3] = '=';
	world[FloorOne.Row + 9][FloorOne.Col + 4] = '=';
	world[FloorOne.Row + 9][FloorOne.Col + 5] = ':';
	world[FloorOne.Row + 9][FloorOne.Col + 6] = '_';
	world[FloorOne.Row + 9][FloorOne.Col + 7] = ' ';
	world[FloorOne.Row + 9][FloorOne.Col + 8] = '"';
	world[FloorOne.Row + 9][FloorOne.Col + 9] = '"';

	// ROW 10
	world[FloorOne.Row + 10][FloorOne.Col - 1] = '.';
	world[FloorOne.Row + 10][FloorOne.Col] = 39;
	world[FloorOne.Row + 10][FloorOne.Col + 1] = ' ';
	world[FloorOne.Row + 10][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 10][FloorOne.Col + 3] = ' ';
	world[FloorOne.Row + 10][FloorOne.Col + 4] = ' ';
	world[FloorOne.Row + 10][FloorOne.Col + 5] = ' ';
	world[FloorOne.Row + 10][FloorOne.Col + 6] = '\\';
	world[FloorOne.Row + 10][FloorOne.Col + 7] = '\\';

	// ROW 11
	world[FloorOne.Row + 11][FloorOne.Col - 2] = ':';
	world[FloorOne.Row + 11][FloorOne.Col - 1] = ' ';
	world[FloorOne.Row + 11][FloorOne.Col] = ' ';
	world[FloorOne.Row + 11][FloorOne.Col + 1] = ' ';
	world[FloorOne.Row + 11][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 11][FloorOne.Col + 3] = ' ';
	world[FloorOne.Row + 11][FloorOne.Col + 4] = ' ';
	world[FloorOne.Row + 11][FloorOne.Col + 5] = ' ';
	world[FloorOne.Row + 11][FloorOne.Col + 6] = ':';

	// ROW 12
	world[FloorOne.Row + 12][FloorOne.Col - 3] = '/';
	world[FloorOne.Row + 12][FloorOne.Col - 2] = ' ';
	world[FloorOne.Row + 12][FloorOne.Col - 1] = ' ';
	world[FloorOne.Row + 12][FloorOne.Col] = ' ';
	world[FloorOne.Row + 12][FloorOne.Col + 1] = ':';
	world[FloorOne.Row + 12][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 12][FloorOne.Col + 3] = ' ';
	world[FloorOne.Row + 12][FloorOne.Col + 4] = ' ';
	world[FloorOne.Row + 12][FloorOne.Col + 5] = ' ';
	world[FloorOne.Row + 12][FloorOne.Col + 6] = '\\';

	// ROW 13
	world[FloorOne.Row + 13][FloorOne.Col - 4] = ':';
	world[FloorOne.Row + 13][FloorOne.Col - 3] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col - 2] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col - 1] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col] = '.';
	world[FloorOne.Row + 13][FloorOne.Col + 1] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col + 3] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col + 4] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col + 5] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col + 6] = ' ';
	world[FloorOne.Row + 13][FloorOne.Col + 7] = 39;
	world[FloorOne.Row + 13][FloorOne.Col + 8] = '.';

	// ROW 14
	world[FloorOne.Row + 14][FloorOne.Col - 4] = ':';
	world[FloorOne.Row + 14][FloorOne.Col - 3] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col - 2] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col - 1] = ':';
	world[FloorOne.Row + 14][FloorOne.Col] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col + 1] = ':';
	world[FloorOne.Row + 14][FloorOne.Col + 2] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col + 3] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col + 4] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col + 5] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col + 6] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col + 7] = ' ';
	world[FloorOne.Row + 14][FloorOne.Col + 8] = ':';

	// ROW 15
	world[FloorOne.Row + 15][FloorOne.Col - 4] = ':';
	world[FloorOne.Row + 15][FloorOne.Col - 3] = '_';
	world[FloorOne.Row + 15][FloorOne.Col - 2] = '_';
	world[FloorOne.Row + 15][FloorOne.Col - 1] = ':';
	world[FloorOne.Row + 15][FloorOne.Col] = '_';
	world[FloorOne.Row + 15][FloorOne.Col + 1] = ':';
	world[FloorOne.Row + 15][FloorOne.Col + 2] = '_';
	world[FloorOne.Row + 15][FloorOne.Col + 3] = '_';
	world[FloorOne.Row + 15][FloorOne.Col + 4] = '.';
	world[FloorOne.Row + 15][FloorOne.Col + 5] = ';';
	world[FloorOne.Row + 15][FloorOne.Col + 6] = '-';
	world[FloorOne.Row + 15][FloorOne.Col + 7] = '-';
	world[FloorOne.Row + 15][FloorOne.Col + 8] = 39;

	// ROW 16

	world[FloorOne.Row + 16][FloorOne.Col - 3] = 39;
	world[FloorOne.Row + 16][FloorOne.Col - 2] = '-';
	world[FloorOne.Row + 16][FloorOne.Col - 1] = 39;
	world[FloorOne.Row + 16][FloorOne.Col] = ' ';
	world[FloorOne.Row + 16][FloorOne.Col + 1] = ' ';
	world[FloorOne.Row + 16][FloorOne.Col + 2] = 39;
	world[FloorOne.Row + 16][FloorOne.Col + 2] = '-';
	world[FloorOne.Row + 16][FloorOne.Col + 3] = 39;


}

void checkHeroCollisionEnemyFloorOne(int& heroRow, int& heroCol, Enemy& FloorOne, int& heroLives, int& strtCol, int& endCol)
{
	int heroT = heroRow, heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;
	int enemyT = FloorOne.Row, enemyB = FloorOne.Row + 16, enemyL = FloorOne.Col - 18, enemyR = FloorOne.Col + 11;
	int isCollide = 0;

	if (heroR >= enemyL && heroL <= enemyR && heroB >= enemyT && heroT <= enemyB)
	{
		heroLives--; isCollide = 1;
	}

	if (isCollide == 1)
	{
		strtCol = 0;
		endCol = 120;

		heroRow = 75;
		heroCol = 60;

		FloorOne.isAlive = 1;
		FloorOne.Health = 3;
	}

}

void checkBulletsCollisionEnemyFloorOne(Enemy& FloorOne, int& doYouWantSingleBullet, int singleBulletRow, int singleBulletCol, char prevHeroDir, Bullet* MultiBullets)
{
	int enemyT = FloorOne.Row, enemyB = FloorOne.Row + 16, enemyL = FloorOne.Col - 18, enemyR = FloorOne.Col + 11;

	/////////////////////////////////////
	//// SINGLE BULLET CHECK
	///////////////////////////////////

	if (doYouWantSingleBullet == 1)
	{
		int bulletL, bulletR;

		if (prevHeroDir == 'd' || prevHeroDir == 'D')
		{
			bulletL = singleBulletCol;
			bulletR = singleBulletCol + 5;
		}
		else
		{
			bulletL = singleBulletCol - 5;
			bulletR = singleBulletCol;
		}

		if (bulletR >= enemyL && bulletL <= enemyR && singleBulletRow >= enemyT && singleBulletRow <= enemyB)
		{
			FloorOne.Health--;
			doYouWantSingleBullet = 0;
		}
	}

	///////////////////////////////////

	/////////////////////////////////////
	//// MULTIPLE BULLETS CHECK
	///////////////////////////////////

	for (int i = 0; i < 5; i++)
	{
		if (MultiBullets[i].IsActive == 1)
		{
			int bulletL, bulletR;

			if (MultiBullets[i].Dir == 'd' || MultiBullets[i].Dir == 'D')
			{
				bulletL = MultiBullets[i].Col;
				bulletR = MultiBullets[i].Col + 5;
			}
			else
			{
				bulletL = MultiBullets[i].Col - 5;
				bulletR = MultiBullets[i].Col;
			}

			if (bulletR >= enemyL && bulletL <= enemyR &&
				MultiBullets[i].Row >= enemyT && MultiBullets[i].Row <= enemyB)
			{
				FloorOne.Health--;
				MultiBullets[i].IsActive = 0;
			}
		}

	}

	///////////////////////////////////

	if (FloorOne.Health <= 0)
	{
		FloorOne.isAlive = 0;
	}
}

void drawCaspers(Enemy* Casper, unsigned char** world)
{
	for (int i = 0; i < 3; i++)
	{
		if (Casper[i].isAlive == 1)
		{
			// ROW 0
			world[Casper[i].Row][Casper[i].Col - 3] = '.';
			world[Casper[i].Row][Casper[i].Col - 2] = '-';
			world[Casper[i].Row][Casper[i].Col - 1] = 39;
			world[Casper[i].Row][Casper[i].Col] = 39;
			world[Casper[i].Row][Casper[i].Col + 1] = 39;
			world[Casper[i].Row][Casper[i].Col + 2] = '-';
			world[Casper[i].Row][Casper[i].Col + 3] = '.';

			// ROW 1
			world[Casper[i].Row + 1][Casper[i].Col - 4] = '/';
			world[Casper[i].Row + 1][Casper[i].Col - 3] = ' ';
			world[Casper[i].Row + 1][Casper[i].Col - 2] = '-';
			world[Casper[i].Row + 1][Casper[i].Col - 1] = ' ';
			world[Casper[i].Row + 1][Casper[i].Col] = ' ';
			world[Casper[i].Row + 1][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 1][Casper[i].Col + 2] = '-';
			world[Casper[i].Row + 1][Casper[i].Col + 3] = ' ';
			world[Casper[i].Row + 1][Casper[i].Col + 4] = '\\';

			// ROW 2
			world[Casper[i].Row + 2][Casper[i].Col - 5] = '|';
			world[Casper[i].Row + 2][Casper[i].Col - 4] = ' ';
			world[Casper[i].Row + 2][Casper[i].Col - 3] = ' ';
			world[Casper[i].Row + 2][Casper[i].Col - 2] = '.';
			world[Casper[i].Row + 2][Casper[i].Col - 1] = '-';
			world[Casper[i].Row + 2][Casper[i].Col] = '.';
			world[Casper[i].Row + 2][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 2][Casper[i].Col + 2] = '.';
			world[Casper[i].Row + 2][Casper[i].Col + 3] = '-';
			world[Casper[i].Row + 2][Casper[i].Col + 4] = ' ';
			world[Casper[i].Row + 2][Casper[i].Col + 5] = '|';

			// ROW 3
			world[Casper[i].Row + 3][Casper[i].Col - 5] = '|';
			world[Casper[i].Row + 3][Casper[i].Col - 4] = ' ';
			world[Casper[i].Row + 3][Casper[i].Col - 3] = ' ';
			world[Casper[i].Row + 3][Casper[i].Col - 2] = '\\';
			world[Casper[i].Row + 3][Casper[i].Col - 1] = 'o';
			world[Casper[i].Row + 3][Casper[i].Col] = '|';
			world[Casper[i].Row + 3][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 3][Casper[i].Col + 2] = '|';
			world[Casper[i].Row + 3][Casper[i].Col + 3] = 'o';
			world[Casper[i].Row + 3][Casper[i].Col + 4] = ' ';
			world[Casper[i].Row + 3][Casper[i].Col + 5] = '(';

			// ROW 4
			world[Casper[i].Row + 4][Casper[i].Col - 5] = '\\';
			world[Casper[i].Row + 4][Casper[i].Col - 4] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col - 3] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col - 2] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col - 1] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col + 1] = '^';
			world[Casper[i].Row + 4][Casper[i].Col + 2] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col + 3] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col + 4] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col + 5] = ' ';
			world[Casper[i].Row + 4][Casper[i].Col + 6] = '\\';

			// ROW 5
			world[Casper[i].Row + 5][Casper[i].Col - 5] = '|';
			world[Casper[i].Row + 5][Casper[i].Col - 4] = 39;
			world[Casper[i].Row + 5][Casper[i].Col - 3] = '.';
			world[Casper[i].Row + 5][Casper[i].Col - 2] = ' ';
			world[Casper[i].Row + 5][Casper[i].Col - 1] = ' ';
			world[Casper[i].Row + 5][Casper[i].Col] = ')';
			world[Casper[i].Row + 5][Casper[i].Col + 1] = '-';
			world[Casper[i].Row + 5][Casper[i].Col + 2] = '-';
			world[Casper[i].Row + 5][Casper[i].Col + 3] = 39;
			world[Casper[i].Row + 5][Casper[i].Col + 4] = ' ';
			world[Casper[i].Row + 5][Casper[i].Col + 5] = ' ';
			world[Casper[i].Row + 5][Casper[i].Col + 6] = '/';
			world[Casper[i].Row + 5][Casper[i].Col + 7] = '|';

			// ROW 6
			world[Casper[i].Row + 6][Casper[i].Col - 6] = '/';
			world[Casper[i].Row + 6][Casper[i].Col - 5] = ' ';
			world[Casper[i].Row + 6][Casper[i].Col - 4] = '/';
			world[Casper[i].Row + 6][Casper[i].Col - 3] = ' ';
			world[Casper[i].Row + 6][Casper[i].Col - 2] = 39;
			world[Casper[i].Row + 6][Casper[i].Col - 1] = '-';
			world[Casper[i].Row + 6][Casper[i].Col] = '.';
			world[Casper[i].Row + 6][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 6][Casper[i].Col + 2] = '.';
			world[Casper[i].Row + 6][Casper[i].Col + 3] = '-';
			world[Casper[i].Row + 6][Casper[i].Col + 4] = 39;
			world[Casper[i].Row + 6][Casper[i].Col + 5] = 39;
			world[Casper[i].Row + 6][Casper[i].Col + 6] = '\\';
			world[Casper[i].Row + 6][Casper[i].Col + 7] = ' ';
			world[Casper[i].Row + 6][Casper[i].Col + 8] = '\\';

			// ROW 7
			world[Casper[i].Row + 7][Casper[i].Col - 7] = '/';
			world[Casper[i].Row + 7][Casper[i].Col - 6] = ' ';
			world[Casper[i].Row + 7][Casper[i].Col - 5] = '/';
			world[Casper[i].Row + 7][Casper[i].Col - 4] = 39;
			world[Casper[i].Row + 7][Casper[i].Col - 3] = '-';
			world[Casper[i].Row + 7][Casper[i].Col - 2] = '-';
			world[Casper[i].Row + 7][Casper[i].Col - 1] = '-';
			world[Casper[i].Row + 7][Casper[i].Col] = 39;
			world[Casper[i].Row + 7][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 7][Casper[i].Col + 2] = 39;
			world[Casper[i].Row + 7][Casper[i].Col + 3] = '-';
			world[Casper[i].Row + 7][Casper[i].Col + 4] = '-';
			world[Casper[i].Row + 7][Casper[i].Col + 5] = '-';
			world[Casper[i].Row + 7][Casper[i].Col + 6] = 39;
			world[Casper[i].Row + 7][Casper[i].Col + 7] = '\\';
			world[Casper[i].Row + 7][Casper[i].Col + 8] = ' ';
			world[Casper[i].Row + 7][Casper[i].Col + 9] = '\\';

			// ROW 8
			world[Casper[i].Row + 8][Casper[i].Col - 7] = 39;
			world[Casper[i].Row + 8][Casper[i].Col - 6] = '.';
			world[Casper[i].Row + 8][Casper[i].Col - 5] = '_';
			world[Casper[i].Row + 8][Casper[i].Col - 4] = '_';
			world[Casper[i].Row + 8][Casper[i].Col - 3] = '.';
			world[Casper[i].Row + 8][Casper[i].Col - 2] = ' ';
			world[Casper[i].Row + 8][Casper[i].Col - 1] = ' ';
			world[Casper[i].Row + 8][Casper[i].Col] = ' ';
			world[Casper[i].Row + 8][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 8][Casper[i].Col + 2] = ' ';
			world[Casper[i].Row + 8][Casper[i].Col + 3] = ' ';
			world[Casper[i].Row + 8][Casper[i].Col + 4] = ' ';
			world[Casper[i].Row + 8][Casper[i].Col + 5] = '.';
			world[Casper[i].Row + 8][Casper[i].Col + 6] = '_';
			world[Casper[i].Row + 8][Casper[i].Col + 7] = '_';
			world[Casper[i].Row + 8][Casper[i].Col + 8] = '.';
			world[Casper[i].Row + 8][Casper[i].Col + 9] = 39;

			// ROW 9
			world[Casper[i].Row + 9][Casper[i].Col - 3] = 39;
			world[Casper[i].Row + 9][Casper[i].Col - 2] = '|';
			world[Casper[i].Row + 9][Casper[i].Col - 1] = ' ';
			world[Casper[i].Row + 9][Casper[i].Col] = ' ';
			world[Casper[i].Row + 9][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 9][Casper[i].Col + 2] = ' ';
			world[Casper[i].Row + 9][Casper[i].Col + 3] = ' ';
			world[Casper[i].Row + 9][Casper[i].Col + 4] = '|';
			world[Casper[i].Row + 9][Casper[i].Col + 5] = 39;

			// ROW 10
			world[Casper[i].Row + 10][Casper[i].Col - 2] = '|';
			world[Casper[i].Row + 10][Casper[i].Col - 1] = ' ';
			world[Casper[i].Row + 10][Casper[i].Col] = ' ';
			world[Casper[i].Row + 10][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 10][Casper[i].Col + 2] = ' ';
			world[Casper[i].Row + 10][Casper[i].Col + 3] = ' ';
			world[Casper[i].Row + 10][Casper[i].Col + 4] = '\\';

			// ROW 11
			world[Casper[i].Row + 11][Casper[i].Col - 2] = '\\';
			world[Casper[i].Row + 11][Casper[i].Col - 1] = ' ';
			world[Casper[i].Row + 11][Casper[i].Col] = ' ';
			world[Casper[i].Row + 11][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 11][Casper[i].Col + 2] = ' ';
			world[Casper[i].Row + 11][Casper[i].Col + 3] = ' ';
			world[Casper[i].Row + 11][Casper[i].Col + 4] = ' ';
			world[Casper[i].Row + 11][Casper[i].Col + 5] = 39;
			world[Casper[i].Row + 11][Casper[i].Col + 6] = '-';
			world[Casper[i].Row + 11][Casper[i].Col + 7] = '-';
			world[Casper[i].Row + 11][Casper[i].Col + 8] = '.';

			// ROW 12
			world[Casper[i].Row + 12][Casper[i].Col - 1] = 39;
			world[Casper[i].Row + 12][Casper[i].Col] = '.';
			world[Casper[i].Row + 12][Casper[i].Col + 1] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 2] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 3] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 4] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 5] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 6] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 7] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 8] = ' ';
			world[Casper[i].Row + 12][Casper[i].Col + 9] = 39;
			world[Casper[i].Row + 12][Casper[i].Col + 10] = '\\';

			// ROW 13
			world[Casper[i].Row + 13][Casper[i].Col + 1] = 39;
			world[Casper[i].Row + 13][Casper[i].Col + 2] = 39;
			world[Casper[i].Row + 13][Casper[i].Col + 3] = '-';
			world[Casper[i].Row + 13][Casper[i].Col + 4] = '-';
			world[Casper[i].Row + 13][Casper[i].Col + 5] = '-';
			world[Casper[i].Row + 13][Casper[i].Col + 6] = '.';
			world[Casper[i].Row + 13][Casper[i].Col + 7] = ' ';
			world[Casper[i].Row + 13][Casper[i].Col + 8] = ' ';
			world[Casper[i].Row + 13][Casper[i].Col + 9] = ' ';
			world[Casper[i].Row + 13][Casper[i].Col + 10] = '|';

			// ROW 14
			world[Casper[i].Row + 14][Casper[i].Col + 4] = ',';
			world[Casper[i].Row + 14][Casper[i].Col + 5] = '_';
			world[Casper[i].Row + 14][Casper[i].Col + 6] = '_';
			world[Casper[i].Row + 14][Casper[i].Col + 7] = ')';
			world[Casper[i].Row + 14][Casper[i].Col + 8] = ' ';
			world[Casper[i].Row + 14][Casper[i].Col + 9] = '/';

			// ROW 15
			world[Casper[i].Row + 15][Casper[i].Col + 5] = 39;
			world[Casper[i].Row + 15][Casper[i].Col + 6] = '.';
			world[Casper[i].Row + 15][Casper[i].Col + 7] = '.';
			world[Casper[i].Row + 15][Casper[i].Col + 8] = 39;
		}
	}
}

void moveCaspers(Enemy* Casper)
{
	if (Casper[0].isAlive == 1)
	{
		if (Casper[0].Row <= 32)
		{
			Casper[0].Dir = 2;
		}
		else
		{
			if (Casper[0].Row + 15 >= 58)
			{
				Casper[0].Dir = -2;
			}
		}

		Casper[0].Row += Casper[0].Dir;

	}


	if (Casper[1].isAlive == 1)
	{
		if (Casper[1].Col >= 240)
		{
			Casper[1].Dir = -5;
		}
		else
		{
			if (Casper[1].Col <= 150)
			{
				Casper[1].Dir = 5;
			}
		}

		Casper[1].Col += Casper[1].Dir;
	}

	if (Casper[2].isAlive == 1)
	{
		if (Casper[2].Row <= 32)
		{
			Casper[2].Dir = 1;
		}
		else
		{
			if (Casper[2].Row + 15 >= 58)
			{
				Casper[2].Dir = -2;
			}
		}

		if (Casper[2].Col <= 50)
		{
			Casper[2].DirTwo = 2;
		}
		else
		{
			if (Casper[2].Col >= 110)
			{
				Casper[2].DirTwo = -1;
			}
		}

		Casper[2].Row += Casper[2].Dir;
		Casper[2].Col += Casper[2].DirTwo;
	}

}

void checkHeroCollisionCaspers(int& heroRow, int& heroCol, int& heroLives, int& strtCol, int& endCol, Enemy* Casper, Bullet* MultiBullets)
{
	int heroT = heroRow, heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;

	for (int i = 0; i < 3; i++)
	{
		if (Casper[i].isAlive == 1)
		{
			int enemyT = Casper[i].Row, enemyB = Casper[i].Row + 15, enemyL = Casper[i].Col - 7, enemyR = Casper[i].Col + 10;

			if (heroR >= enemyL && heroL <= enemyR && heroB >= enemyT && heroT <= enemyB)
			{
				heroLives--;

				strtCol = 240;
				endCol = 360;

				heroRow = 45;
				heroCol = 330;

				for (int k = 0; k < 3; k++)
				{
					Casper[k].isAlive = 1;
					Casper[k].Health = 5;
				}

				for (int k = 0; k < 5; k++)
				{
					MultiBullets[k].IsActive = 0;
				}

				break;
			}
		}
	}
}

void checkBulletsCollisionCaspers(Enemy* Casper, int& doYouWantSingleBullet, int singleBulletRow, int singleBulletCol, char prevHeroDir, Bullet* MultiBullets)
{
	for (int i = 0; i < 3; i++)
	{
		if (Casper[i].isAlive == 1)
		{
			int enemyT = Casper[i].Row, enemyB = Casper[i].Row + 15, enemyL = Casper[i].Col - 7, enemyR = Casper[i].Col + 10;

			/////////////////////////////////////
			//// SINGLE BULLET CHECK
			///////////////////////////////////

			if (doYouWantSingleBullet == 1)
			{
				int bulletL, bulletR;

				if (prevHeroDir == 'd' || prevHeroDir == 'D')
				{
					bulletL = singleBulletCol;
					bulletR = singleBulletCol + 5;
				}
				else
				{
					bulletL = singleBulletCol - 5;
					bulletR = singleBulletCol;
				}

				if (bulletR >= enemyL && bulletL <= enemyR && singleBulletRow >= enemyT && singleBulletRow <= enemyB)
				{
					Casper[i].Health--;
					doYouWantSingleBullet = 0;
				}
			}

			///////////////////////////////////

			/////////////////////////////////////
			//// MULTIPLE BULLETS CHECK
			///////////////////////////////////

			for (int k = 0; k < 5; k++)
			{
				if (MultiBullets[k].IsActive == 1)
				{
					int bulletL, bulletR;

					if (MultiBullets[k].Dir == 'd' || MultiBullets[k].Dir == 'D')
					{
						bulletL = MultiBullets[k].Col;
						bulletR = MultiBullets[k].Col + 5;
					}
					else
					{
						bulletL = MultiBullets[k].Col - 5;
						bulletR = MultiBullets[k].Col;
					}

					if (bulletR >= enemyL && bulletL <= enemyR && MultiBullets[k].Row >= enemyT && MultiBullets[k].Row <= enemyB)
					{
						Casper[i].Health--;
						MultiBullets[k].IsActive = 0;
					}
				}

			}

			///////////////////////////////////

			if (Casper[i].Health <= 0)
			{
				Casper[i].isAlive = 0;
			}

		}
	}
}

void activateEnemyFloorOneBullets(Enemy FloorOne, Bullet* EnemyBullets)
{
	for (int i = 0; i < 3; i++)
	{
		if (EnemyBullets[i].IsActive == 0)
		{
			EnemyBullets[i].IsActive = 1;
			EnemyBullets[i].Row = FloorOne.Row + 7;
			EnemyBullets[i].Col = FloorOne.Col - 19;
			break;
		}
	}

}

void moveEnemyFloorOneBullets(Bullet* EnemyBullets, Obstacle One, Obstacle Two, Obstacle Three, Obstacle Four)
{
	for (int i = 0; i < 3; i++)
	{
		if (EnemyBullets[i].IsActive == 1)
		{
			EnemyBullets[i].Col -= 5;

			if (EnemyBullets[i].Col <= 54)
			{
				EnemyBullets[i].IsActive = 0;
			}

			if (EnemyBullets[i].Col >= One.strtCol && EnemyBullets[i].Col <= One.endCol && EnemyBullets[i].Row >= One.strtRow)
			{
				EnemyBullets[i].IsActive = 0;
			}

			if (EnemyBullets[i].Col >= Two.strtCol && EnemyBullets[i].Col <= Two.endCol && EnemyBullets[i].Row >= Two.strtRow)
			{
				EnemyBullets[i].IsActive = 0;
			}

			if (EnemyBullets[i].Col >= Three.strtCol && EnemyBullets[i].Col <= Three.endCol && EnemyBullets[i].Row >= Three.strtRow)
			{
				EnemyBullets[i].IsActive = 0;
			}

			if (EnemyBullets[i].Col >= Four.strtCol && EnemyBullets[i].Col <= Four.endCol && EnemyBullets[i].Row >= Four.strtRow)
			{
				EnemyBullets[i].IsActive = 0;
			}
		}
	}
}

void drawEnemyFloorOneBullets(Bullet* EnemyBullets, unsigned char** world)
{
	for (int i = 0; i < 3; i++)
	{
		if (EnemyBullets[i].IsActive == 1)
		{
			world[EnemyBullets[i].Row][EnemyBullets[i].Col] = 249;
		}
	}
}

void checkEnemyFloorOneBulletsCollisionHero(Bullet* EnemyBullets, int& heroRow, int& heroCol, int& heroLives, int& strtCol, int& endCol, int& heroTakenBulletsInFloorOne, Enemy& FloorOne, Bullet* MultiBullets)
{
	int heroT = heroRow, heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;

	for (int i = 0; i < 3; i++)
	{
		if (EnemyBullets[i].IsActive == 1)
		{
			if (EnemyBullets[i].Col >= heroL && EnemyBullets[i].Col <= heroR && EnemyBullets[i].Row >= heroT && EnemyBullets[i].Row <= heroB)
			{
				heroTakenBulletsInFloorOne++;
				EnemyBullets[i].IsActive = 0;
			}
			if (heroTakenBulletsInFloorOne >= 9)
			{
				heroTakenBulletsInFloorOne = 0;

				heroLives--;

				strtCol = 0;
				endCol = 120;
				heroRow = 75;
				heroCol = 60;
				FloorOne.isAlive = 1;

				for (int k = 0; k < 3; k++)
				{
					EnemyBullets[k].IsActive = 0;
				}

				for (int k = 0; k < 5; k++)
				{
					MultiBullets[k].IsActive = 0;
				}
				break;

			}
		}
	}
}

void drawFinalBoss(Enemy FinalBoss, unsigned char** world)
{

	// ROW 0
	world[FinalBoss.Row + 0][FinalBoss.Col - 3] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col - 2] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col - 1] = '(';
	world[FinalBoss.Row + 0][FinalBoss.Col + 0] = 'W';
	world[FinalBoss.Row + 0][FinalBoss.Col + 1] = '{';
	world[FinalBoss.Row + 0][FinalBoss.Col + 2] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 3] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 4] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 5] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 6] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 7] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 8] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 9] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 10] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 11] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 12] = '-';
	world[FinalBoss.Row + 0][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 0][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 0][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 0][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 0][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 0][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 0][FinalBoss.Col + 19] = '/';
	world[FinalBoss.Row + 0][FinalBoss.Col + 20] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 21] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 22] = '=';
	world[FinalBoss.Row + 0][FinalBoss.Col + 23] = '-';

	// ROW 1
	world[FinalBoss.Row + 1][FinalBoss.Col - 1] = '|';
	world[FinalBoss.Row + 1][FinalBoss.Col + 0] = '|';
	world[FinalBoss.Row + 1][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 2] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 3] = '(';
	world[FinalBoss.Row + 1][FinalBoss.Col + 4] = '.';
	world[FinalBoss.Row + 1][FinalBoss.Col + 5] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 6] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 7] = '.';
	world[FinalBoss.Row + 1][FinalBoss.Col + 8] = ')';
	world[FinalBoss.Row + 1][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 1][FinalBoss.Col + 18] = '/';
	world[FinalBoss.Row + 1][FinalBoss.Col + 19] = '=';
	world[FinalBoss.Row + 1][FinalBoss.Col + 20] = '=';
	world[FinalBoss.Row + 1][FinalBoss.Col + 21] = '=';
	world[FinalBoss.Row + 1][FinalBoss.Col + 22] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 23] = '_';
	world[FinalBoss.Row + 1][FinalBoss.Col + 24] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 25] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 26] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 27] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 28] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 29] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 30] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 31] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 32] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 33] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 34] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 35] = '~';
	world[FinalBoss.Row + 1][FinalBoss.Col + 36] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 37] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 38] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 39] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 40] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 41] = '-';
	world[FinalBoss.Row + 1][FinalBoss.Col + 42] = '_';
	world[FinalBoss.Row + 1][FinalBoss.Col + 43] = '_';
	world[FinalBoss.Row + 1][FinalBoss.Col + 44] = '_';
	world[FinalBoss.Row + 1][FinalBoss.Col + 45] = '_';

	// ROW 2
	world[FinalBoss.Row + 2][FinalBoss.Col - 1] = '|';
	world[FinalBoss.Row + 2][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 1] = '\\';
	world[FinalBoss.Row + 2][FinalBoss.Col + 2] = '_';
	world[FinalBoss.Row + 2][FinalBoss.Col + 3] = ',';
	world[FinalBoss.Row + 2][FinalBoss.Col + 4] = '|';
	world[FinalBoss.Row + 2][FinalBoss.Col + 5] = '*';
	world[FinalBoss.Row + 2][FinalBoss.Col + 6] = '*';
	world[FinalBoss.Row + 2][FinalBoss.Col + 7] = '|';
	world[FinalBoss.Row + 2][FinalBoss.Col + 8] = ',';
	world[FinalBoss.Row + 2][FinalBoss.Col + 9] = '_';
	world[FinalBoss.Row + 2][FinalBoss.Col + 10] = '_';
	world[FinalBoss.Row + 2][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 17] = '|';
	world[FinalBoss.Row + 2][FinalBoss.Col + 18] = '=';
	world[FinalBoss.Row + 2][FinalBoss.Col + 19] = '=';
	world[FinalBoss.Row + 2][FinalBoss.Col + 20] = '=';
	world[FinalBoss.Row + 2][FinalBoss.Col + 21] = '-';
	world[FinalBoss.Row + 2][FinalBoss.Col + 22] = '~';
	world[FinalBoss.Row + 2][FinalBoss.Col + 23] = '_';
	world[FinalBoss.Row + 2][FinalBoss.Col + 24] = '_';
	world[FinalBoss.Row + 2][FinalBoss.Col + 25] = '_';
	world[FinalBoss.Row + 2][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 29] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 30] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 32] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 33] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 34] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 35] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 36] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 37] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 38] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 39] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 40] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 41] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 42] = '_';
	world[FinalBoss.Row + 2][FinalBoss.Col + 43] = ',';
	world[FinalBoss.Row + 2][FinalBoss.Col + 44] = '-';
	world[FinalBoss.Row + 2][FinalBoss.Col + 45] = '\'';
	world[FinalBoss.Row + 2][FinalBoss.Col + 46] = ' ';
	world[FinalBoss.Row + 2][FinalBoss.Col + 47] = '`';

	// ROW 3
	world[FinalBoss.Row + 3][FinalBoss.Col - 14] = '-';
	world[FinalBoss.Row + 3][FinalBoss.Col - 13] = '=';
	world[FinalBoss.Row + 3][FinalBoss.Col - 12] = '=';
	world[FinalBoss.Row + 3][FinalBoss.Col - 11] = '\\';
	world[FinalBoss.Row + 3][FinalBoss.Col - 10] = '\\';
	world[FinalBoss.Row + 3][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col - 1] = '`';
	world[FinalBoss.Row + 3][FinalBoss.Col + 0] = '\\';
	world[FinalBoss.Row + 3][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 2] = '\'';
	world[FinalBoss.Row + 3][FinalBoss.Col + 3] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 4] = '`';
	world[FinalBoss.Row + 3][FinalBoss.Col + 5] = '-';
	world[FinalBoss.Row + 3][FinalBoss.Col + 6] = '-';
	world[FinalBoss.Row + 3][FinalBoss.Col + 7] = '\'';
	world[FinalBoss.Row + 3][FinalBoss.Col + 8] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 11] = ')';
	world[FinalBoss.Row + 3][FinalBoss.Col + 12] = ',';
	world[FinalBoss.Row + 3][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 17] = '`';
	world[FinalBoss.Row + 3][FinalBoss.Col + 18] = '/';
	world[FinalBoss.Row + 3][FinalBoss.Col + 19] = '/';
	world[FinalBoss.Row + 3][FinalBoss.Col + 20] = '~';
	world[FinalBoss.Row + 3][FinalBoss.Col + 21] = '\\';
	world[FinalBoss.Row + 3][FinalBoss.Col + 22] = '\\';
	world[FinalBoss.Row + 3][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 3][FinalBoss.Col + 26] = '~';
	world[FinalBoss.Row + 3][FinalBoss.Col + 27] = '~';
	world[FinalBoss.Row + 3][FinalBoss.Col + 28] = '~';
	world[FinalBoss.Row + 3][FinalBoss.Col + 29] = '~';
	world[FinalBoss.Row + 3][FinalBoss.Col + 30] = '`';
	world[FinalBoss.Row + 3][FinalBoss.Col + 31] = '-';
	world[FinalBoss.Row + 3][FinalBoss.Col + 32] = '-';
	world[FinalBoss.Row + 3][FinalBoss.Col + 33] = '-';
	world[FinalBoss.Row + 3][FinalBoss.Col + 34] = '.';
	world[FinalBoss.Row + 3][FinalBoss.Col + 35] = '_';
	world[FinalBoss.Row + 3][FinalBoss.Col + 36] = '_';
	world[FinalBoss.Row + 3][FinalBoss.Col + 37] = '_';
	world[FinalBoss.Row + 3][FinalBoss.Col + 38] = '.';
	world[FinalBoss.Row + 3][FinalBoss.Col + 39] = '-';
	world[FinalBoss.Row + 3][FinalBoss.Col + 40] = '~';
	world[FinalBoss.Row + 3][FinalBoss.Col + 41] = '~';

	// ROW 4
	world[FinalBoss.Row + 4][FinalBoss.Col - 18] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col - 17] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col - 16] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col - 15] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col - 14] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col - 13] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col - 12] = '-';
	world[FinalBoss.Row + 4][FinalBoss.Col - 11] = '=';
	world[FinalBoss.Row + 4][FinalBoss.Col - 10] = '=';
	world[FinalBoss.Row + 4][FinalBoss.Col - 9] = '|';
	world[FinalBoss.Row + 4][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 0] = '/';
	world[FinalBoss.Row + 4][FinalBoss.Col + 1] = '`';
	world[FinalBoss.Row + 4][FinalBoss.Col + 2] = '\\';
	world[FinalBoss.Row + 4][FinalBoss.Col + 3] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col + 4] = '.';
	world[FinalBoss.Row + 4][FinalBoss.Col + 5] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 6] = '.';
	world[FinalBoss.Row + 4][FinalBoss.Col + 7] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col + 8] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col + 9] = '/';
	world[FinalBoss.Row + 4][FinalBoss.Col + 10] = '\\';
	world[FinalBoss.Row + 4][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 12] = '\\';
	world[FinalBoss.Row + 4][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 17] = '|';
	world[FinalBoss.Row + 4][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 19] = '|';
	world[FinalBoss.Row + 4][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 22] = '\\';
	world[FinalBoss.Row + 4][FinalBoss.Col + 23] = '\\';
	world[FinalBoss.Row + 4][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 29] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 30] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 32] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 33] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 34] = ' ';
	world[FinalBoss.Row + 4][FinalBoss.Col + 35] = '_';
	world[FinalBoss.Row + 4][FinalBoss.Col + 36] = '-';
	world[FinalBoss.Row + 4][FinalBoss.Col + 37] = '~';
	world[FinalBoss.Row + 4][FinalBoss.Col + 38] = '`';

	// ROW 5
	world[FinalBoss.Row + 5][FinalBoss.Col - 24] = '_';
	world[FinalBoss.Row + 5][FinalBoss.Col - 23] = '_';
	world[FinalBoss.Row + 5][FinalBoss.Col - 22] = '-';
	world[FinalBoss.Row + 5][FinalBoss.Col - 21] = '-';
	world[FinalBoss.Row + 5][FinalBoss.Col - 20] = '~';
	world[FinalBoss.Row + 5][FinalBoss.Col - 19] = '~';
	world[FinalBoss.Row + 5][FinalBoss.Col - 18] = '~';
	world[FinalBoss.Row + 5][FinalBoss.Col - 17] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 16] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 15] = ',';
	world[FinalBoss.Row + 5][FinalBoss.Col - 14] = '-';
	world[FinalBoss.Row + 5][FinalBoss.Col - 13] = '/';
	world[FinalBoss.Row + 5][FinalBoss.Col - 12] = '-';
	world[FinalBoss.Row + 5][FinalBoss.Col - 11] = '=';
	world[FinalBoss.Row + 5][FinalBoss.Col - 10] = '=';
	world[FinalBoss.Row + 5][FinalBoss.Col - 9] = '\\';
	world[FinalBoss.Row + 5][FinalBoss.Col - 8] = '\\';
	world[FinalBoss.Row + 5][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col - 1] = '(';
	world[FinalBoss.Row + 5][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 2] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 3] = '|';
	world[FinalBoss.Row + 5][FinalBoss.Col + 4] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 5] = '.';
	world[FinalBoss.Row + 5][FinalBoss.Col + 6] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 7] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 8] = '|';
	world[FinalBoss.Row + 5][FinalBoss.Col + 9] = '~';
	world[FinalBoss.Row + 5][FinalBoss.Col + 10] = '~';
	world[FinalBoss.Row + 5][FinalBoss.Col + 11] = '~';
	world[FinalBoss.Row + 5][FinalBoss.Col + 12] = '~';
	world[FinalBoss.Row + 5][FinalBoss.Col + 13] = '|';
	world[FinalBoss.Row + 5][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 17] = '|';
	world[FinalBoss.Row + 5][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 19] = '|';
	world[FinalBoss.Row + 5][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 23] = '`';
	world[FinalBoss.Row + 5][FinalBoss.Col + 24] = '\\';
	world[FinalBoss.Row + 5][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 29] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 30] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 32] = ' ';
	world[FinalBoss.Row + 5][FinalBoss.Col + 33] = ',';
	world[FinalBoss.Row + 5][FinalBoss.Col + 34] = '\'';

	// ROW 6
	world[FinalBoss.Row + 6][FinalBoss.Col - 27] = '_';
	world[FinalBoss.Row + 6][FinalBoss.Col - 26] = '-';
	world[FinalBoss.Row + 6][FinalBoss.Col - 25] = '~';
	world[FinalBoss.Row + 6][FinalBoss.Col - 24] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 23] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 22] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 21] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 20] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 19] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 18] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 17] = '/';
	world[FinalBoss.Row + 6][FinalBoss.Col - 16] = '\'';
	world[FinalBoss.Row + 6][FinalBoss.Col - 15] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 14] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 13] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 12] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 11] = '|';
	world[FinalBoss.Row + 6][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 8] = '\\';
	world[FinalBoss.Row + 6][FinalBoss.Col - 7] = '\\';
	world[FinalBoss.Row + 6][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col - 1] = ')';
	world[FinalBoss.Row + 6][FinalBoss.Col + 0] = '_';
	world[FinalBoss.Row + 6][FinalBoss.Col + 1] = '_';
	world[FinalBoss.Row + 6][FinalBoss.Col + 2] = '/';
	world[FinalBoss.Row + 6][FinalBoss.Col + 3] = '=';
	world[FinalBoss.Row + 6][FinalBoss.Col + 4] = '=';
	world[FinalBoss.Row + 6][FinalBoss.Col + 5] = '0';
	world[FinalBoss.Row + 6][FinalBoss.Col + 6] = '=';
	world[FinalBoss.Row + 6][FinalBoss.Col + 7] = '=';
	world[FinalBoss.Row + 6][FinalBoss.Col + 8] = '-';
	world[FinalBoss.Row + 6][FinalBoss.Col + 9] = '\\';
	world[FinalBoss.Row + 6][FinalBoss.Col + 10] = '<';
	world[FinalBoss.Row + 6][FinalBoss.Col + 11] = '>';
	world[FinalBoss.Row + 6][FinalBoss.Col + 12] = '/';
	world[FinalBoss.Row + 6][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 16] = '/';
	world[FinalBoss.Row + 6][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 18] = '/';
	world[FinalBoss.Row + 6][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 25] = '\\';
	world[FinalBoss.Row + 6][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 29] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 30] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 6][FinalBoss.Col + 32] = '/';

	// ROW 7
	world[FinalBoss.Row + 7][FinalBoss.Col - 29] = '.';
	world[FinalBoss.Row + 7][FinalBoss.Col - 28] = '\'';
	world[FinalBoss.Row + 7][FinalBoss.Col - 27] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 26] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 25] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 24] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 23] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 22] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 21] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 20] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 19] = '/';
	world[FinalBoss.Row + 7][FinalBoss.Col - 18] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 17] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 16] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 15] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 14] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 13] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 12] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 11] = '|';
	world[FinalBoss.Row + 7][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 7] = '\\';
	world[FinalBoss.Row + 7][FinalBoss.Col - 6] = '\\';
	world[FinalBoss.Row + 7][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 1] = '/';
	world[FinalBoss.Row + 7][FinalBoss.Col + 2] = '~';
	world[FinalBoss.Row + 7][FinalBoss.Col + 3] = '\\';
	world[FinalBoss.Row + 7][FinalBoss.Col + 4] = '_';
	world[FinalBoss.Row + 7][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 7][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 7][FinalBoss.Col + 7] = '/';
	world[FinalBoss.Row + 7][FinalBoss.Col + 8] = '~';
	world[FinalBoss.Row + 7][FinalBoss.Col + 9] = '~';
	world[FinalBoss.Row + 7][FinalBoss.Col + 10] = '\\';
	world[FinalBoss.Row + 7][FinalBoss.Col + 11] = '/';
	world[FinalBoss.Row + 7][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 14] = '/';
	world[FinalBoss.Row + 7][FinalBoss.Col + 15] = '\'';
	world[FinalBoss.Row + 7][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 17] = '/';
	world[FinalBoss.Row + 7][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 26] = '\\';
	world[FinalBoss.Row + 7][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 29] = ' ';
	world[FinalBoss.Row + 7][FinalBoss.Col + 30] = '/';
	world[FinalBoss.Row + 7][FinalBoss.Col + 31] = '\'';

	// ROW 8
	world[FinalBoss.Row + 8][FinalBoss.Col - 30] = '/';
	world[FinalBoss.Row + 8][FinalBoss.Col - 29] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 28] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 27] = '_';
	world[FinalBoss.Row + 8][FinalBoss.Col - 26] = '_';
	world[FinalBoss.Row + 8][FinalBoss.Col - 25] = '_';
	world[FinalBoss.Row + 8][FinalBoss.Col - 24] = '_';
	world[FinalBoss.Row + 8][FinalBoss.Col - 23] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 22] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 21] = '/';
	world[FinalBoss.Row + 8][FinalBoss.Col - 20] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 19] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 18] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 17] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 16] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 15] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 14] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 13] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 12] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 11] = '|';
	world[FinalBoss.Row + 8][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col - 6] = '\\';
	world[FinalBoss.Row + 8][FinalBoss.Col - 5] = '`';
	world[FinalBoss.Row + 8][FinalBoss.Col - 4] = '\\';
	world[FinalBoss.Row + 8][FinalBoss.Col - 3] = '.';
	world[FinalBoss.Row + 8][FinalBoss.Col - 2] = '_';
	world[FinalBoss.Row + 8][FinalBoss.Col - 1] = '_';
	world[FinalBoss.Row + 8][FinalBoss.Col + 0] = '/';
	world[FinalBoss.Row + 8][FinalBoss.Col + 1] = '-';
	world[FinalBoss.Row + 8][FinalBoss.Col + 2] = '~';
	world[FinalBoss.Row + 8][FinalBoss.Col + 3] = '~';
	world[FinalBoss.Row + 8][FinalBoss.Col + 4] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 5] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 6] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 7] = '\\';
	world[FinalBoss.Row + 8][FinalBoss.Col + 8] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 10] = '|';
	world[FinalBoss.Row + 8][FinalBoss.Col + 11] = '_';
	world[FinalBoss.Row + 8][FinalBoss.Col + 12] = '/';
	world[FinalBoss.Row + 8][FinalBoss.Col + 13] = '\'';
	world[FinalBoss.Row + 8][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 16] = '/';
	world[FinalBoss.Row + 8][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 8][FinalBoss.Col + 27] = '\\';
	world[FinalBoss.Row + 8][FinalBoss.Col + 28] = '/';
	world[FinalBoss.Row + 8][FinalBoss.Col + 29] = '\'';

	// ROW 9
	world[FinalBoss.Row + 9][FinalBoss.Col - 31] = '/';
	world[FinalBoss.Row + 9][FinalBoss.Col - 30] = '-';
	world[FinalBoss.Row + 9][FinalBoss.Col - 29] = '\'';
	world[FinalBoss.Row + 9][FinalBoss.Col - 28] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 27] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 26] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 25] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 24] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 23] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 22] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 21] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 20] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 19] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 18] = '-';
	world[FinalBoss.Row + 9][FinalBoss.Col - 17] = '-';
	world[FinalBoss.Row + 9][FinalBoss.Col - 16] = '-';
	world[FinalBoss.Row + 9][FinalBoss.Col - 15] = '_';
	world[FinalBoss.Row + 9][FinalBoss.Col - 14] = '_';
	world[FinalBoss.Row + 9][FinalBoss.Col - 13] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 12] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 11] = '|';
	world[FinalBoss.Row + 9][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col - 5] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 4] = '-';
	world[FinalBoss.Row + 9][FinalBoss.Col - 3] = '/';
	world[FinalBoss.Row + 9][FinalBoss.Col - 2] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 2] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 3] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 4] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 5] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 6] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 7] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 8] = '(';
	world[FinalBoss.Row + 9][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 10] = ')';
	world[FinalBoss.Row + 9][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 14] = '/';
	world[FinalBoss.Row + 9][FinalBoss.Col + 15] = '\'';
	world[FinalBoss.Row + 9][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 9][FinalBoss.Col + 24] = '_';
	world[FinalBoss.Row + 9][FinalBoss.Col + 25] = '-';
	world[FinalBoss.Row + 9][FinalBoss.Col + 26] = '-';
	world[FinalBoss.Row + 9][FinalBoss.Col + 27] = '~';
	world[FinalBoss.Row + 9][FinalBoss.Col + 28] = '`';

	// ROW 10
	world[FinalBoss.Row + 10][FinalBoss.Col - 13] = '\\';
	world[FinalBoss.Row + 10][FinalBoss.Col - 12] = '_';
	world[FinalBoss.Row + 10][FinalBoss.Col - 11] = '|';
	world[FinalBoss.Row + 10][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 4] = '/';
	world[FinalBoss.Row + 10][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 2] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 3] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 4] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 10][FinalBoss.Col + 6] = ')';
	world[FinalBoss.Row + 10][FinalBoss.Col + 7] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 8] = '|';
	world[FinalBoss.Row + 10][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 10] = ';';
	world[FinalBoss.Row + 10][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 13] = ')';
	world[FinalBoss.Row + 10][FinalBoss.Col + 14] = ',';
	world[FinalBoss.Row + 10][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 10][FinalBoss.Col + 18] = '_';
	world[FinalBoss.Row + 10][FinalBoss.Col + 19] = '_';
	world[FinalBoss.Row + 10][FinalBoss.Col + 20] = '-';
	world[FinalBoss.Row + 10][FinalBoss.Col + 21] = '-';
	world[FinalBoss.Row + 10][FinalBoss.Col + 22] = '~';
	world[FinalBoss.Row + 10][FinalBoss.Col + 23] = '~';

	// ROW 11
	world[FinalBoss.Row + 11][FinalBoss.Col - 11] = '\'';
	world[FinalBoss.Row + 11][FinalBoss.Col - 10] = '~';
	world[FinalBoss.Row + 11][FinalBoss.Col - 9] = '~';
	world[FinalBoss.Row + 11][FinalBoss.Col - 8] = '-';
	world[FinalBoss.Row + 11][FinalBoss.Col - 7] = '-';
	world[FinalBoss.Row + 11][FinalBoss.Col - 6] = '_';
	world[FinalBoss.Row + 11][FinalBoss.Col - 5] = '/';
	world[FinalBoss.Row + 11][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 2] = '_';
	world[FinalBoss.Row + 11][FinalBoss.Col + 3] = '-';
	world[FinalBoss.Row + 11][FinalBoss.Col + 4] = '~';
	world[FinalBoss.Row + 11][FinalBoss.Col + 5] = '/';
	world[FinalBoss.Row + 11][FinalBoss.Col + 6] = '-';
	world[FinalBoss.Row + 11][FinalBoss.Col + 7] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 8] = '|';
	world[FinalBoss.Row + 11][FinalBoss.Col + 9] = '/';
	world[FinalBoss.Row + 11][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 11] = '\\';
	world[FinalBoss.Row + 11][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 15] = '\'';
	world[FinalBoss.Row + 11][FinalBoss.Col + 16] = '-';
	world[FinalBoss.Row + 11][FinalBoss.Col + 17] = '~';
	world[FinalBoss.Row + 11][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 11][FinalBoss.Col + 19] = '\\';

	// ROW 12
	world[FinalBoss.Row + 12][FinalBoss.Col - 12] = '{';
	world[FinalBoss.Row + 12][FinalBoss.Col - 11] = '\\';
	world[FinalBoss.Row + 12][FinalBoss.Col - 10] = '_';
	world[FinalBoss.Row + 12][FinalBoss.Col - 9] = '_';
	world[FinalBoss.Row + 12][FinalBoss.Col - 8] = '-';
	world[FinalBoss.Row + 12][FinalBoss.Col - 7] = '-';
	world[FinalBoss.Row + 12][FinalBoss.Col - 6] = '_';
	world[FinalBoss.Row + 12][FinalBoss.Col - 5] = '/';
	world[FinalBoss.Row + 12][FinalBoss.Col - 4] = '}';
	world[FinalBoss.Row + 12][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 1] = '/';
	world[FinalBoss.Row + 12][FinalBoss.Col + 2] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 3] = '\\';
	world[FinalBoss.Row + 12][FinalBoss.Col + 4] = '\\';
	world[FinalBoss.Row + 12][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 12][FinalBoss.Col + 6] = '>';
	world[FinalBoss.Row + 12][FinalBoss.Col + 7] = '-';
	world[FinalBoss.Row + 12][FinalBoss.Col + 8] = '|';
	world[FinalBoss.Row + 12][FinalBoss.Col + 9] = ')';
	world[FinalBoss.Row + 12][FinalBoss.Col + 10] = '<';
	world[FinalBoss.Row + 12][FinalBoss.Col + 11] = '_';
	world[FinalBoss.Row + 12][FinalBoss.Col + 12] = '_';
	world[FinalBoss.Row + 12][FinalBoss.Col + 13] = '\\';
	world[FinalBoss.Row + 12][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 12][FinalBoss.Col + 20] = '\\';

	// ROW 13
	world[FinalBoss.Row + 13][FinalBoss.Col - 12] = '/';
	world[FinalBoss.Row + 13][FinalBoss.Col - 11] = '\'';
	world[FinalBoss.Row + 13][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col - 7] = '(';
	world[FinalBoss.Row + 13][FinalBoss.Col - 6] = '_';
	world[FinalBoss.Row + 13][FinalBoss.Col - 5] = '/';
	world[FinalBoss.Row + 13][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col - 2] = '_';
	world[FinalBoss.Row + 13][FinalBoss.Col - 1] = '-';
	world[FinalBoss.Row + 13][FinalBoss.Col + 0] = '~';
	world[FinalBoss.Row + 13][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 2] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 3] = '|';
	world[FinalBoss.Row + 13][FinalBoss.Col + 4] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 5] = '|';
	world[FinalBoss.Row + 13][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 13][FinalBoss.Col + 7] = '_';
	world[FinalBoss.Row + 13][FinalBoss.Col + 8] = '>';
	world[FinalBoss.Row + 13][FinalBoss.Col + 9] = '-';
	world[FinalBoss.Row + 13][FinalBoss.Col + 10] = '-';
	world[FinalBoss.Row + 13][FinalBoss.Col + 11] = '<';
	world[FinalBoss.Row + 13][FinalBoss.Col + 12] = '_';
	world[FinalBoss.Row + 13][FinalBoss.Col + 13] = '_';
	world[FinalBoss.Row + 13][FinalBoss.Col + 14] = '|';
	world[FinalBoss.Row + 13][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 13][FinalBoss.Col + 21] = '|';

	// ROW 14
	world[FinalBoss.Row + 14][FinalBoss.Col - 13] = '|';
	world[FinalBoss.Row + 14][FinalBoss.Col - 12] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col - 11] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col - 9] = '_';
	world[FinalBoss.Row + 14][FinalBoss.Col - 8] = '/';
	world[FinalBoss.Row + 14][FinalBoss.Col - 7] = ')';
	world[FinalBoss.Row + 14][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col - 5] = ')';
	world[FinalBoss.Row + 14][FinalBoss.Col - 4] = '-';
	world[FinalBoss.Row + 14][FinalBoss.Col - 3] = '~';
	world[FinalBoss.Row + 14][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 2] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 3] = '|';
	world[FinalBoss.Row + 14][FinalBoss.Col + 4] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 5] = '|';
	world[FinalBoss.Row + 14][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 14][FinalBoss.Col + 7] = '_';
	world[FinalBoss.Row + 14][FinalBoss.Col + 8] = '>';
	world[FinalBoss.Row + 14][FinalBoss.Col + 9] = '-';
	world[FinalBoss.Row + 14][FinalBoss.Col + 10] = '-';
	world[FinalBoss.Row + 14][FinalBoss.Col + 11] = '<';
	world[FinalBoss.Row + 14][FinalBoss.Col + 12] = '_';
	world[FinalBoss.Row + 14][FinalBoss.Col + 13] = '_';
	world[FinalBoss.Row + 14][FinalBoss.Col + 14] = '|';
	world[FinalBoss.Row + 14][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 14][FinalBoss.Col + 21] = '|';

	// ROW 15
	world[FinalBoss.Row + 15][FinalBoss.Col - 13] = '/';
	world[FinalBoss.Row + 15][FinalBoss.Col - 12] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col - 11] = '/';
	world[FinalBoss.Row + 15][FinalBoss.Col - 10] = '~';
	world[FinalBoss.Row + 15][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col - 8] = ',';
	world[FinalBoss.Row + 15][FinalBoss.Col - 7] = '_';
	world[FinalBoss.Row + 15][FinalBoss.Col - 6] = '/';
	world[FinalBoss.Row + 15][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 1] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 2] = '/';
	world[FinalBoss.Row + 15][FinalBoss.Col + 3] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 4] = '/';
	world[FinalBoss.Row + 15][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 15][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 15][FinalBoss.Col + 7] = '>';
	world[FinalBoss.Row + 15][FinalBoss.Col + 8] = '-';
	world[FinalBoss.Row + 15][FinalBoss.Col + 9] = '-';
	world[FinalBoss.Row + 15][FinalBoss.Col + 10] = '-';
	world[FinalBoss.Row + 15][FinalBoss.Col + 11] = '<';
	world[FinalBoss.Row + 15][FinalBoss.Col + 12] = '_';
	world[FinalBoss.Row + 15][FinalBoss.Col + 13] = '_';
	world[FinalBoss.Row + 15][FinalBoss.Col + 14] = '/';
	world[FinalBoss.Row + 15][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 15][FinalBoss.Col + 21] = '|';

	// ROW 16
	world[FinalBoss.Row + 16][FinalBoss.Col - 14] = 'o';
	world[FinalBoss.Row + 16][FinalBoss.Col - 13] = '-';
	world[FinalBoss.Row + 16][FinalBoss.Col - 12] = 'o';
	world[FinalBoss.Row + 16][FinalBoss.Col - 11] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col - 10] = '_';
	world[FinalBoss.Row + 16][FinalBoss.Col - 9] = '/';
	world[FinalBoss.Row + 16][FinalBoss.Col - 8] = '/';
	world[FinalBoss.Row + 16][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 0] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 1] = '/';
	world[FinalBoss.Row + 16][FinalBoss.Col + 2] = '-';
	world[FinalBoss.Row + 16][FinalBoss.Col + 3] = '~';
	world[FinalBoss.Row + 16][FinalBoss.Col + 4] = '_';
	world[FinalBoss.Row + 16][FinalBoss.Col + 5] = '>';
	world[FinalBoss.Row + 16][FinalBoss.Col + 6] = '-';
	world[FinalBoss.Row + 16][FinalBoss.Col + 7] = '-';
	world[FinalBoss.Row + 16][FinalBoss.Col + 8] = '-';
	world[FinalBoss.Row + 16][FinalBoss.Col + 9] = '<';
	world[FinalBoss.Row + 16][FinalBoss.Col + 10] = '_';
	world[FinalBoss.Row + 16][FinalBoss.Col + 11] = '_';
	world[FinalBoss.Row + 16][FinalBoss.Col + 12] = '-';
	world[FinalBoss.Row + 16][FinalBoss.Col + 13] = '~';
	world[FinalBoss.Row + 16][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 16][FinalBoss.Col + 20] = '/';

	// ROW 17
	world[FinalBoss.Row + 17][FinalBoss.Col - 14] = '(';
	world[FinalBoss.Row + 17][FinalBoss.Col - 13] = '^';
	world[FinalBoss.Row + 17][FinalBoss.Col - 12] = '(';
	world[FinalBoss.Row + 17][FinalBoss.Col - 11] = '~';
	world[FinalBoss.Row + 17][FinalBoss.Col - 10] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 9] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 8] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 7] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 6] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 5] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 4] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 3] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 2] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col - 1] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col + 0] = '/';
	world[FinalBoss.Row + 17][FinalBoss.Col + 1] = '~';
	world[FinalBoss.Row + 17][FinalBoss.Col + 2] = '_';
	world[FinalBoss.Row + 17][FinalBoss.Col + 3] = '>';
	world[FinalBoss.Row + 17][FinalBoss.Col + 4] = '-';
	world[FinalBoss.Row + 17][FinalBoss.Col + 5] = '-';
	world[FinalBoss.Row + 17][FinalBoss.Col + 6] = '-';
	world[FinalBoss.Row + 17][FinalBoss.Col + 7] = '<';
	world[FinalBoss.Row + 17][FinalBoss.Col + 8] = '_';
	world[FinalBoss.Row + 17][FinalBoss.Col + 9] = '_';
	world[FinalBoss.Row + 17][FinalBoss.Col + 10] = '-';
	world[FinalBoss.Row + 17][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 17][FinalBoss.Col + 17] = '_';
	world[FinalBoss.Row + 17][FinalBoss.Col + 18] = '-';
	world[FinalBoss.Row + 17][FinalBoss.Col + 19] = '~';

	// ROW 18
	world[FinalBoss.Row + 18][FinalBoss.Col - 1] = '/';
	world[FinalBoss.Row + 18][FinalBoss.Col + 0] = '_';
	world[FinalBoss.Row + 18][FinalBoss.Col + 1] = '_';
	world[FinalBoss.Row + 18][FinalBoss.Col + 2] = '>';
	world[FinalBoss.Row + 18][FinalBoss.Col + 3] = '-';
	world[FinalBoss.Row + 18][FinalBoss.Col + 4] = '-';
	world[FinalBoss.Row + 18][FinalBoss.Col + 5] = '<';
	world[FinalBoss.Row + 18][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 18][FinalBoss.Col + 7] = '_';
	world[FinalBoss.Row + 18][FinalBoss.Col + 8] = '/';
	world[FinalBoss.Row + 18][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 18][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 18][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 18][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 18][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 18][FinalBoss.Col + 14] = '_';
	world[FinalBoss.Row + 18][FinalBoss.Col + 15] = '-';
	world[FinalBoss.Row + 18][FinalBoss.Col + 16] = '~';

	// ROW 19
	world[FinalBoss.Row + 19][FinalBoss.Col - 2] = '|';
	world[FinalBoss.Row + 19][FinalBoss.Col - 1] = '_';
	world[FinalBoss.Row + 19][FinalBoss.Col + 0] = '_';
	world[FinalBoss.Row + 19][FinalBoss.Col + 1] = '>';
	world[FinalBoss.Row + 19][FinalBoss.Col + 2] = '-';
	world[FinalBoss.Row + 19][FinalBoss.Col + 3] = '-';
	world[FinalBoss.Row + 19][FinalBoss.Col + 4] = '<';
	world[FinalBoss.Row + 19][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 19][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 19][FinalBoss.Col + 7] = '|';
	world[FinalBoss.Row + 19][FinalBoss.Col + 8] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 13] = '/';
	world[FinalBoss.Row + 19][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 29] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 30] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 32] = ' ';
	world[FinalBoss.Row + 19][FinalBoss.Col + 33] = '.';
	world[FinalBoss.Row + 19][FinalBoss.Col + 34] = '-';
	world[FinalBoss.Row + 19][FinalBoss.Col + 35] = '-';
	world[FinalBoss.Row + 19][FinalBoss.Col + 36] = '-';
	world[FinalBoss.Row + 19][FinalBoss.Col + 37] = '-';
	world[FinalBoss.Row + 19][FinalBoss.Col + 38] = '_';

	// ROW 20
	world[FinalBoss.Row + 20][FinalBoss.Col - 2] = '|';
	world[FinalBoss.Row + 20][FinalBoss.Col - 1] = '_';
	world[FinalBoss.Row + 20][FinalBoss.Col + 0] = '_';
	world[FinalBoss.Row + 20][FinalBoss.Col + 1] = '>';
	world[FinalBoss.Row + 20][FinalBoss.Col + 2] = '-';
	world[FinalBoss.Row + 20][FinalBoss.Col + 3] = '-';
	world[FinalBoss.Row + 20][FinalBoss.Col + 4] = '<';
	world[FinalBoss.Row + 20][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 20][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 20][FinalBoss.Col + 7] = '|';
	world[FinalBoss.Row + 20][FinalBoss.Col + 8] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 12] = '|';
	world[FinalBoss.Row + 20][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 29] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 30] = '/';
	world[FinalBoss.Row + 20][FinalBoss.Col + 31] = '\'';
	world[FinalBoss.Row + 20][FinalBoss.Col + 32] = ' ';
	world[FinalBoss.Row + 20][FinalBoss.Col + 33] = '_';
	world[FinalBoss.Row + 20][FinalBoss.Col + 34] = '-';
	world[FinalBoss.Row + 20][FinalBoss.Col + 35] = '-';
	world[FinalBoss.Row + 20][FinalBoss.Col + 36] = '-';
	world[FinalBoss.Row + 20][FinalBoss.Col + 37] = '_';
	world[FinalBoss.Row + 20][FinalBoss.Col + 38] = '~';
	world[FinalBoss.Row + 20][FinalBoss.Col + 39] = '\\';

	// ROW 21
	world[FinalBoss.Row + 21][FinalBoss.Col - 2] = '|';
	world[FinalBoss.Row + 21][FinalBoss.Col - 1] = '_';
	world[FinalBoss.Row + 21][FinalBoss.Col + 0] = '_';
	world[FinalBoss.Row + 21][FinalBoss.Col + 1] = '>';
	world[FinalBoss.Row + 21][FinalBoss.Col + 2] = '-';
	world[FinalBoss.Row + 21][FinalBoss.Col + 3] = '-';
	world[FinalBoss.Row + 21][FinalBoss.Col + 4] = '<';
	world[FinalBoss.Row + 21][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 21][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 21][FinalBoss.Col + 7] = '|';
	world[FinalBoss.Row + 21][FinalBoss.Col + 8] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 12] = '|';
	world[FinalBoss.Row + 21][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 26] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 28] = '/';
	world[FinalBoss.Row + 21][FinalBoss.Col + 29] = '\'';
	world[FinalBoss.Row + 21][FinalBoss.Col + 30] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 32] = '/';
	world[FinalBoss.Row + 21][FinalBoss.Col + 33] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 34] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 35] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 36] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 37] = ' ';
	world[FinalBoss.Row + 21][FinalBoss.Col + 38] = '~';
	world[FinalBoss.Row + 21][FinalBoss.Col + 39] = '\\';
	world[FinalBoss.Row + 21][FinalBoss.Col + 40] = '`';
	world[FinalBoss.Row + 21][FinalBoss.Col + 41] = '\\';

	// ROW 22
	world[FinalBoss.Row + 22][FinalBoss.Col - 2] = '\\';
	world[FinalBoss.Row + 22][FinalBoss.Col - 1] = '_';
	world[FinalBoss.Row + 22][FinalBoss.Col + 0] = '_';
	world[FinalBoss.Row + 22][FinalBoss.Col + 1] = '>';
	world[FinalBoss.Row + 22][FinalBoss.Col + 2] = '-';
	world[FinalBoss.Row + 22][FinalBoss.Col + 3] = '-';
	world[FinalBoss.Row + 22][FinalBoss.Col + 4] = '<';
	world[FinalBoss.Row + 22][FinalBoss.Col + 5] = '_';
	world[FinalBoss.Row + 22][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 22][FinalBoss.Col + 7] = '\\';
	world[FinalBoss.Row + 22][FinalBoss.Col + 8] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 9] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 12] = '\\';
	world[FinalBoss.Row + 22][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 20] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 21] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 22] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 23] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 25] = '/';
	world[FinalBoss.Row + 22][FinalBoss.Col + 26] = '\'';
	world[FinalBoss.Row + 22][FinalBoss.Col + 27] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 28] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 29] = '/';
	world[FinalBoss.Row + 22][FinalBoss.Col + 30] = '/';
	world[FinalBoss.Row + 22][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 32] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 33] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 34] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 35] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 36] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 37] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 38] = ' ';
	world[FinalBoss.Row + 22][FinalBoss.Col + 39] = '|';
	world[FinalBoss.Row + 22][FinalBoss.Col + 40] = '|';

	// ROW 23
	world[FinalBoss.Row + 23][FinalBoss.Col - 1] = '~';
	world[FinalBoss.Row + 23][FinalBoss.Col + 0] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 1] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 2] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 3] = '>';
	world[FinalBoss.Row + 23][FinalBoss.Col + 4] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 5] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 6] = '<';
	world[FinalBoss.Row + 23][FinalBoss.Col + 7] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 8] = '~';
	world[FinalBoss.Row + 23][FinalBoss.Col + 9] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 10] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 11] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 12] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 13] = '~';
	world[FinalBoss.Row + 23][FinalBoss.Col + 14] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 15] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 16] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 17] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 18] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 19] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 20] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 21] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 22] = '-';
	world[FinalBoss.Row + 23][FinalBoss.Col + 23] = '~';
	world[FinalBoss.Row + 23][FinalBoss.Col + 24] = '\'';
	world[FinalBoss.Row + 23][FinalBoss.Col + 25] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 26] = '_';
	world[FinalBoss.Row + 23][FinalBoss.Col + 27] = '/';
	world[FinalBoss.Row + 23][FinalBoss.Col + 28] = '\'';
	world[FinalBoss.Row + 23][FinalBoss.Col + 29] = '/';
	world[FinalBoss.Row + 23][FinalBoss.Col + 30] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 31] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 32] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 33] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 34] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 35] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 36] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 37] = ' ';
	world[FinalBoss.Row + 23][FinalBoss.Col + 38] = '/';
	world[FinalBoss.Row + 23][FinalBoss.Col + 39] = '\'';

	// ROW 24
	world[FinalBoss.Row + 24][FinalBoss.Col + 0] = '~';
	world[FinalBoss.Row + 24][FinalBoss.Col + 1] = '-';
	world[FinalBoss.Row + 24][FinalBoss.Col + 2] = '_';
	world[FinalBoss.Row + 24][FinalBoss.Col + 3] = '~';
	world[FinalBoss.Row + 24][FinalBoss.Col + 4] = '>';
	world[FinalBoss.Row + 24][FinalBoss.Col + 5] = '-';
	world[FinalBoss.Row + 24][FinalBoss.Col + 6] = '-';
	world[FinalBoss.Row + 24][FinalBoss.Col + 7] = '<';
	world[FinalBoss.Row + 24][FinalBoss.Col + 8] = '_';
	world[FinalBoss.Row + 24][FinalBoss.Col + 9] = '/';
	world[FinalBoss.Row + 24][FinalBoss.Col + 10] = '-';
	world[FinalBoss.Row + 24][FinalBoss.Col + 11] = '_';
	world[FinalBoss.Row + 24][FinalBoss.Col + 12] = '_';
	world[FinalBoss.Row + 24][FinalBoss.Col + 13] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 14] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 15] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 16] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 17] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 18] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 19] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 20] = '_';
	world[FinalBoss.Row + 24][FinalBoss.Col + 21] = '_';
	world[FinalBoss.Row + 24][FinalBoss.Col + 22] = '-';
	world[FinalBoss.Row + 24][FinalBoss.Col + 23] = '~';
	world[FinalBoss.Row + 24][FinalBoss.Col + 24] = ' ';
	world[FinalBoss.Row + 24][FinalBoss.Col + 25] = '_';
	world[FinalBoss.Row + 24][FinalBoss.Col + 26] = '/';

	// ROW 25
	world[FinalBoss.Row + 25][FinalBoss.Col + 2] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 3] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 4] = '-';
	world[FinalBoss.Row + 25][FinalBoss.Col + 5] = '\'';
	world[FinalBoss.Row + 25][FinalBoss.Col + 6] = '_';
	world[FinalBoss.Row + 25][FinalBoss.Col + 7] = '/';
	world[FinalBoss.Row + 25][FinalBoss.Col + 8] = '_';
	world[FinalBoss.Row + 25][FinalBoss.Col + 9] = '/';
	world[FinalBoss.Row + 25][FinalBoss.Col + 10] = ' ';
	world[FinalBoss.Row + 25][FinalBoss.Col + 11] = '/';
	world[FinalBoss.Row + 25][FinalBoss.Col + 12] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 13] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 14] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 15] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 16] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 17] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 18] = '~';
	world[FinalBoss.Row + 25][FinalBoss.Col + 19] = '_';
	world[FinalBoss.Row + 25][FinalBoss.Col + 20] = '_';
	world[FinalBoss.Row + 25][FinalBoss.Col + 21] = '-';
	world[FinalBoss.Row + 25][FinalBoss.Col + 22] = '-';
	world[FinalBoss.Row + 25][FinalBoss.Col + 23] = '~';

}

void moveFinalBoss(Enemy& FinalBoss, int heroRow, int heroCol, int heroCurrFloor)
{

	if (FinalBoss.Col - 31 < 200)
	{
		FinalBoss.Dir = 2;
	}
	else
	{
		if (FinalBoss.Col > 300)
		{
			FinalBoss.Dir = -2;
		}
	}

	if (FinalBoss.Row < 2)
	{
		FinalBoss.DirTwo = 1;
	}
	else
	{
		if (FinalBoss.Row + 25 > 27)
		{
			FinalBoss.DirTwo = -1;
		}
	}

	FinalBoss.Col += FinalBoss.Dir;
	FinalBoss.Row += FinalBoss.DirTwo;

}

void drawDragonFire(int belowMouthRow, int belowMouthCol, int& fireCounter, Enemy FinalBoss, unsigned char** world)
{
	if (fireCounter >= 0)
	{
		world[FinalBoss.Row + belowMouthRow + 0][FinalBoss.Col - belowMouthCol] = '|';
		world[FinalBoss.Row + belowMouthRow + 0][FinalBoss.Col - belowMouthCol - 1] = '/';
		world[FinalBoss.Row + belowMouthRow + 0][FinalBoss.Col - belowMouthCol - 2] = ',';
	}

	if (fireCounter >= 1)
	{
		world[FinalBoss.Row + belowMouthRow + 1][FinalBoss.Col - belowMouthCol] = '(';
		world[FinalBoss.Row + belowMouthRow + 1][FinalBoss.Col - belowMouthCol - 1] = 39;
		world[FinalBoss.Row + belowMouthRow + 1][FinalBoss.Col - belowMouthCol - 2] = '(';
		world[FinalBoss.Row + belowMouthRow + 1][FinalBoss.Col - belowMouthCol - 3] = '/';
		world[FinalBoss.Row + belowMouthRow + 1][FinalBoss.Col - belowMouthCol - 4] = '/';
		world[FinalBoss.Row + belowMouthRow + 1][FinalBoss.Col - belowMouthCol - 5] = ',';
	}

	if (fireCounter >= 2)
	{
		world[FinalBoss.Row + belowMouthRow + 2][FinalBoss.Col - belowMouthCol] = ')';
		world[FinalBoss.Row + belowMouthRow + 2][FinalBoss.Col - belowMouthCol - 1] = ')';
		world[FinalBoss.Row + belowMouthRow + 2][FinalBoss.Col - belowMouthCol - 2] = 39;
		world[FinalBoss.Row + belowMouthRow + 2][FinalBoss.Col - belowMouthCol - 3] = ' ';
		world[FinalBoss.Row + belowMouthRow + 2][FinalBoss.Col - belowMouthCol - 4] = '(';
		world[FinalBoss.Row + belowMouthRow + 2][FinalBoss.Col - belowMouthCol - 5] = ' ';
		world[FinalBoss.Row + belowMouthRow + 2][FinalBoss.Col - belowMouthCol - 6] = '(';
	}

	if (fireCounter >= 3)
	{
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol + 1] = ',';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol] = '/';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 1] = 39;
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 2] = '(';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 3] = ' ';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 4] = '(';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 5] = '(';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 6] = ',';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 7] = ' ';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 8] = ')';
		world[FinalBoss.Row + belowMouthRow + 3][FinalBoss.Col - belowMouthCol - 9] = ')';
	}

	if (fireCounter >= 4)
	{
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 1] = ',';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 2] = '/';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 3] = '(';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 4] = ' ';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 5] = '(';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 6] = '(';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 7] = ',';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 8] = ' ';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 9] = ')';
		world[FinalBoss.Row + belowMouthRow + 4][FinalBoss.Col - belowMouthCol - 10] = ')';
	}

	if (fireCounter >= 5)
	{
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 1] = '~';
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 2] = '/';
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 3] = ' ';
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 4] = ' ';
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 5] = ')';
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 6] = ',';
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 7] = '/';
		world[FinalBoss.Row + belowMouthRow + 5][FinalBoss.Col - belowMouthCol - 8] = '|';
	}

	if (fireCounter >= 6)
	{
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 2] = '.';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 3] = '-';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 4] = '~';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 5] = '/';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 6] = '/';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 7] = '(';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 8] = ' ';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 9] = ')';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 10] = '/';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 11] = ' ';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 12] = ')';
		world[FinalBoss.Row + belowMouthRow + 6][FinalBoss.Col - belowMouthCol - 13] = ')';
	}

	if (fireCounter >= 7)
	{
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 3] = '.';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 4] = '-';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 5] = '~';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 6] = '/';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 7] = '/';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 8] = '(';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 9] = ' ';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 10] = ')';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 11] = '/';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 12] = ' ';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 13] = ')';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 14] = ')';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 15] = ' ';
		world[FinalBoss.Row + belowMouthRow + 7][FinalBoss.Col - belowMouthCol - 16] = '(';
	}


	if (fireCounter < 7)
	{
		fireCounter++;
	}
	else
	{
		fireCounter = 0;
	}
}

void checkHeroCollisionFinalBoss(int& heroRow, int& heroCol, int& heroLives, int& strtCol, int& endCol, Enemy& FinalBoss, Bullet* MultiBullets, int& doYouWantSingleBullet)
{
	int heroT = heroRow, heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;
	int enemyT = FinalBoss.Row, enemyB = FinalBoss.Row + 25, enemyL = FinalBoss.Col - 10, enemyR = FinalBoss.Col + 48;

	if (FinalBoss.isAlive == 1)
	{
		if (heroR >= enemyL && heroL <= enemyR && heroB >= enemyT && heroT <= enemyB)
		{
			heroLives--;
			FinalBoss.Health = 10;

			heroRow = 15;
			heroCol = 45;

			strtCol = 0;
			endCol = 120;

			doYouWantSingleBullet = 0;

			for (int i = 0; i < 5; i++)
			{
				MultiBullets[i].IsActive = 0;
			}
		}
	}
}

void checkHerocollisionFire(int& heroRow, int& heroCol, int& heroLives, Enemy FinalBoss, int isFinalBossFire, int belowMouthRow, int belowMouthCol, int& fireCounter, Bullet* MultiBullets, int& doYouWantSingleBullet)
{
	int heroT = heroRow, heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;
	int fireT = FinalBoss.Row + belowMouthRow, fireB = FinalBoss.Row + belowMouthRow + fireCounter, fireR = FinalBoss.Col - belowMouthCol + 1, fireL = FinalBoss.Col - belowMouthCol - 16;

	if (heroR >= fireL && heroL <= fireR && heroB >= fireT && heroT <= fireB)
	{
		heroLives = 0;
		fireCounter = 0;

		doYouWantSingleBullet = 0;

		for (int i = 0; i < 5; i++)
		{
			MultiBullets[i].IsActive = 0;
		}
	}

}

void checkBulletsCollisionFinalBoss(Enemy& FinalBoss, int& doYouWantSingleBullet, int singleBulletRow, int singleBulletCol, char prevHeroDir, Bullet* MultiBullets)
{
	if (FinalBoss.isAlive == 1)
	{
		int enemyT = FinalBoss.Row, enemyB = FinalBoss.Row + 25;
		int enemyL = FinalBoss.Col - 31, enemyR = FinalBoss.Col + 48;

		/////////////////////////////////////
		//// SINGLE BULLET CHECK
		///////////////////////////////////

		if (doYouWantSingleBullet == 1)
		{
			int bulletL, bulletR;

			if (prevHeroDir == 'd' || prevHeroDir == 'D')
			{
				bulletL = singleBulletCol;
				bulletR = singleBulletCol + 5;
			}
			else
			{
				bulletL = singleBulletCol - 5;
				bulletR = singleBulletCol;
			}

			if (bulletR >= enemyL && bulletL <= enemyR && singleBulletRow >= enemyT && singleBulletRow <= enemyB)
			{
				FinalBoss.Health--;
				doYouWantSingleBullet = 0;
			}
		}

		///////////////////////////////////

		/////////////////////////////////////
		//// MULTIPLE BULLETS CHECK
		///////////////////////////////////

		for (int i = 0; i < 5; i++)
		{
			if (MultiBullets[i].IsActive == 1)
			{
				int bulletL, bulletR;

				if (MultiBullets[i].Dir == 'd' || MultiBullets[i].Dir == 'D')
				{
					bulletL = MultiBullets[i].Col;
					bulletR = MultiBullets[i].Col + 5;
				}
				else
				{
					bulletL = MultiBullets[i].Col - 5;
					bulletR = MultiBullets[i].Col;
				}

				if (bulletR >= enemyL && bulletL <= enemyR &&
					MultiBullets[i].Row >= enemyT && MultiBullets[i].Row <= enemyB)
				{
					FinalBoss.Health--;
					MultiBullets[i].IsActive = 0;
				}
			}
		}
		///////////////////////////////////

		if (FinalBoss.Health <= 0)
		{
			FinalBoss.isAlive = 0;
		}
	}
}

void moveLasers(Laser* Lasers)
{
	for (int i = 0; i < 4; i++)
	{
		if (Lasers[i].IsActive == 1)
		{
			Lasers[i].Timer++;

			if (Lasers[i].Timer >= 3)
			{
				Lasers[i].Timer = 0;

				if (Lasers[i].Len < 28)
				{
					Lasers[i].Len++;
				}
				else
				{
					Lasers[i].Len = 0;
				}
			}
		}
	}
}

void drawLasers(Laser* Lasers, unsigned char** world)
{
	for (int i = 0; i < 4; i++)
	{
		if (Lasers[i].IsActive == 1)
		{
			for (int k = 0; k < Lasers[i].Len; k++)
			{
				world[k][Lasers[i].Col + 0] = 219;
				world[k][Lasers[i].Col + 2] = 219;
				world[k][Lasers[i].Col + 4] = 219;
			}
		}
	}
}

void checkHeroCollisionLasers(Laser* Lasers, int& heroRow, int& heroCol, int& heroLives, int& strtCol, int& endCol, Enemy& FinalBoss, Bullet* MultiBullets, int& doYouWantSingleBullet)
{
	int heroT = heroRow, heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;

	for (int i = 0; i < 4; i++)
	{
		if (Lasers[i].IsActive == 1)
		{
			int LaserT = 0, LaserB = Lasers[i].Len;

			if (heroR >= Lasers[i].Col && heroL <= Lasers[i].Col + 4 && heroB >= LaserT && heroT <= LaserB)
			{
				heroLives--;

				heroRow = 15;
				heroCol = 45;

				strtCol = 0;
				endCol = 120;

				doYouWantSingleBullet = 0;

				for (int k = 0; k < 5; k++)
				{
					MultiBullets[k].IsActive = 0;
				}

				FinalBoss.isAlive = 1;
				FinalBoss.Health = 10;

				break;
			}
		}
	}
}

int checkDiamondCollision(int heroRow, int heroCol, int diamondStrtRow, int diamondEndRow, int diamondStrtCol, int diamondEndCol)
{
	int heroT = heroRow, heroB = heroRow + 13, heroL = heroCol - 7, heroR = heroCol + 7;

	if (heroR >= diamondStrtCol && heroL <= diamondEndCol && heroB >= diamondStrtRow && heroT <= diamondEndRow)
	{
		return 1; // WINNER
	}

	return 0; // NOT WINNER YET
}

void drawGameOver(unsigned char** world)
{
	int r = 17; int c = 11;

	world[r - 5][c + 2] = '_';
	world[r - 5][c + 3] = '_';
	world[r - 5][c + 4] = '_';
	world[r - 5][c + 5] = '_';
	world[r - 5][c + 6] = '_';
	world[r - 5][c + 7] = '_';
	world[r - 5][c + 8] = '_';
	world[r - 5][c + 15] = '_';
	world[r - 5][c + 16] = '_';
	world[r - 5][c + 17] = '_';
	world[r - 5][c + 24] = '.';
	world[r - 5][c + 25] = '_';
	world[r - 5][c + 26] = '_';
	world[r - 5][c + 27] = '_';
	world[r - 5][c + 30] = '_';
	world[r - 5][c + 31] = '_';
	world[r - 5][c + 32] = '_';
	world[r - 5][c + 33] = '.';
	world[r - 5][c + 36] = '_';
	world[r - 5][c + 37] = '_';
	world[r - 5][c + 38] = '_';
	world[r - 5][c + 39] = '_';
	world[r - 5][c + 40] = '_';
	world[r - 5][c + 41] = '_';
	world[r - 5][c + 42] = '_';
	world[r - 5][c + 49] = '_';
	world[r - 5][c + 50] = '_';
	world[r - 5][c + 51] = '_';
	world[r - 5][c + 52] = '_';
	world[r - 5][c + 53] = '_';
	world[r - 5][c + 54] = '_';
	world[r - 5][c + 58] = '_';
	world[r - 5][c + 59] = '_';
	world[r - 5][c + 60] = '_';
	world[r - 5][c + 61] = '_';
	world[r - 5][c + 66] = '_';
	world[r - 5][c + 67] = '_';
	world[r - 5][c + 68] = '_';
	world[r - 5][c + 69] = '_';
	world[r - 5][c + 72] = '_';
	world[r - 5][c + 73] = '_';
	world[r - 5][c + 74] = '_';
	world[r - 5][c + 75] = '_';
	world[r - 5][c + 76] = '_';
	world[r - 5][c + 77] = '_';
	world[r - 5][c + 78] = '_';
	world[r - 5][c + 80] = '.';
	world[r - 5][c + 81] = '_';
	world[r - 5][c + 82] = '_';
	world[r - 5][c + 83] = '_';
	world[r - 5][c + 84] = '_';
	world[r - 5][c + 85] = '_';
	world[r - 5][c + 86] = '_';
	world[r - 5][c + 94] = '_';
	world[r - 5][c + 95] = '_';
	world[r - 4][c + 1] = '/';
	world[r - 4][c + 4] = '_';
	world[r - 4][c + 5] = '_';
	world[r - 4][c + 6] = '_';
	world[r - 4][c + 7] = '_';
	world[r - 4][c + 8] = '_';
	world[r - 4][c + 9] = '|';
	world[r - 4][c + 14] = '/';
	world[r - 4][c + 18] = '\\';
	world[r - 4][c + 24] = '|';
	world[r - 4][c + 28] = '\\';
	world[r - 4][c + 29] = '/';
	world[r - 4][c + 33] = '|';
	world[r - 4][c + 35] = '|';
	world[r - 4][c + 39] = '_';
	world[r - 4][c + 40] = '_';
	world[r - 4][c + 41] = '_';
	world[r - 4][c + 42] = '_';
	world[r - 4][c + 43] = '|';
	world[r - 4][c + 48] = '/';
	world[r - 4][c + 51] = '_';
	world[r - 4][c + 52] = '_';
	world[r - 4][c + 55] = '\\';
	world[r - 4][c + 58] = '\\';
	world[r - 4][c + 62] = '\\';
	world[r - 4][c + 65] = '/';
	world[r - 4][c + 69] = '/';
	world[r - 4][c + 71] = '|';
	world[r - 4][c + 75] = '_';
	world[r - 4][c + 76] = '_';
	world[r - 4][c + 77] = '_';
	world[r - 4][c + 78] = '_';
	world[r - 4][c + 79] = '|';
	world[r - 4][c + 80] = '|';
	world[r - 4][c + 84] = '_';
	world[r - 4][c + 87] = '\\';
	world[r - 4][c + 93] = '|';
	world[r - 4][c + 96] = '|';
	world[r - 3][c + 0] = '|';
	world[r - 3][c + 3] = '|';
	world[r - 3][c + 6] = '_';
	world[r - 3][c + 7] = '_';
	world[r - 3][c + 13] = '/';
	world[r - 3][c + 16] = '^';
	world[r - 3][c + 19] = '\\';
	world[r - 3][c + 24] = '|';
	world[r - 3][c + 27] = '\\';
	world[r - 3][c + 30] = '/';
	world[r - 3][c + 33] = '|';
	world[r - 3][c + 35] = '|';
	world[r - 3][c + 38] = '|';
	world[r - 3][c + 39] = '_';
	world[r - 3][c + 40] = '_';
	world[r - 3][c + 47] = '|';
	world[r - 3][c + 50] = '|';
	world[r - 3][c + 53] = '|';
	world[r - 3][c + 56] = '|';
	world[r - 3][c + 59] = '\\';
	world[r - 3][c + 63] = '\\';
	world[r - 3][c + 64] = '/';
	world[r - 3][c + 68] = '/';
	world[r - 3][c + 71] = '|';
	world[r - 3][c + 74] = '|';
	world[r - 3][c + 75] = '_';
	world[r - 3][c + 76] = '_';
	world[r - 3][c + 80] = '|';
	world[r - 3][c + 83] = '|';
	world[r - 3][c + 84] = '_';
	world[r - 3][c + 85] = ')';
	world[r - 3][c + 88] = '|';
	world[r - 3][c + 93] = '|';
	world[r - 3][c + 96] = '|';
	world[r - 2][c + 0] = '|';
	world[r - 2][c + 3] = '|';
	world[r - 2][c + 5] = '|';
	world[r - 2][c + 6] = '_';
	world[r - 2][c + 8] = '|';
	world[r - 2][c + 12] = '/';
	world[r - 2][c + 15] = '/';
	world[r - 2][c + 16] = '_';
	world[r - 2][c + 17] = '\\';
	world[r - 2][c + 20] = '\\';
	world[r - 2][c + 24] = '|';
	world[r - 2][c + 27] = '|';
	world[r - 2][c + 28] = '\\';
	world[r - 2][c + 29] = '/';
	world[r - 2][c + 30] = '|';
	world[r - 2][c + 33] = '|';
	world[r - 2][c + 35] = '|';
	world[r - 2][c + 39] = '_';
	world[r - 2][c + 40] = '_';
	world[r - 2][c + 41] = '|';
	world[r - 2][c + 47] = '|';
	world[r - 2][c + 50] = '|';
	world[r - 2][c + 53] = '|';
	world[r - 2][c + 56] = '|';
	world[r - 2][c + 60] = '\\';
	world[r - 2][c + 67] = '/';
	world[r - 2][c + 71] = '|';
	world[r - 2][c + 75] = '_';
	world[r - 2][c + 76] = '_';
	world[r - 2][c + 77] = '|';
	world[r - 2][c + 80] = '|';
	world[r - 2][c + 87] = '/';
	world[r - 2][c + 93] = '|';
	world[r - 2][c + 96] = '|';
	world[r - 1][c + 0] = '|';
	world[r - 1][c + 3] = '|';
	world[r - 1][c + 4] = '_';
	world[r - 1][c + 5] = '_';
	world[r - 1][c + 6] = '|';
	world[r - 1][c + 8] = '|';
	world[r - 1][c + 11] = '/';
	world[r - 1][c + 14] = '_';
	world[r - 1][c + 15] = '_';
	world[r - 1][c + 16] = '_';
	world[r - 1][c + 17] = '_';
	world[r - 1][c + 18] = '_';
	world[r - 1][c + 21] = '\\';
	world[r - 1][c + 24] = '|';
	world[r - 1][c + 27] = '|';
	world[r - 1][c + 30] = '|';
	world[r - 1][c + 33] = '|';
	world[r - 1][c + 35] = '|';
	world[r - 1][c + 38] = '|';
	world[r - 1][c + 39] = '_';
	world[r - 1][c + 40] = '_';
	world[r - 1][c + 41] = '_';
	world[r - 1][c + 42] = '_';
	world[r - 1][c + 47] = '|';
	world[r - 1][c + 50] = '`';
	world[r - 1][c + 51] = '-';
	world[r - 1][c + 52] = '-';
	world[r - 1][c + 53] = '\'';
	world[r - 1][c + 56] = '|';
	world[r - 1][c + 61] = '\\';
	world[r - 1][c + 66] = '/';
	world[r - 1][c + 71] = '|';
	world[r - 1][c + 74] = '|';
	world[r - 1][c + 75] = '_';
	world[r - 1][c + 76] = '_';
	world[r - 1][c + 77] = '_';
	world[r - 1][c + 78] = '_';
	world[r - 1][c + 80] = '|';
	world[r - 1][c + 83] = '|';
	world[r - 1][c + 84] = '\\';
	world[r - 1][c + 87] = '\\';
	world[r - 1][c + 88] = '-';
	world[r - 1][c + 89] = '-';
	world[r - 1][c + 90] = '-';
	world[r - 1][c + 91] = '-';
	world[r - 1][c + 92] = '.';
	world[r - 1][c + 93] = '|';
	world[r - 1][c + 94] = '_';
	world[r - 1][c + 95] = '_';
	world[r - 1][c + 96] = '|';
	world[r - 0][c + 1] = '\\';
	world[r - 0][c + 2] = '_';
	world[r - 0][c + 3] = '_';
	world[r - 0][c + 4] = '_';
	world[r - 0][c + 5] = '_';
	world[r - 0][c + 6] = '_';
	world[r - 0][c + 7] = '_';
	world[r - 0][c + 8] = '|';
	world[r - 0][c + 10] = '/';
	world[r - 0][c + 11] = '_';
	world[r - 0][c + 12] = '_';
	world[r - 0][c + 13] = '/';
	world[r - 0][c + 19] = '\\';
	world[r - 0][c + 20] = '_';
	world[r - 0][c + 21] = '_';
	world[r - 0][c + 22] = '\\';
	world[r - 0][c + 24] = '|';
	world[r - 0][c + 25] = '_';
	world[r - 0][c + 26] = '_';
	world[r - 0][c + 27] = '|';
	world[r - 0][c + 30] = '|';
	world[r - 0][c + 31] = '_';
	world[r - 0][c + 32] = '_';
	world[r - 0][c + 33] = '|';
	world[r - 0][c + 35] = '|';
	world[r - 0][c + 36] = '_';
	world[r - 0][c + 37] = '_';
	world[r - 0][c + 38] = '_';
	world[r - 0][c + 39] = '_';
	world[r - 0][c + 40] = '_';
	world[r - 0][c + 41] = '_';
	world[r - 0][c + 42] = '_';
	world[r - 0][c + 43] = '|';
	world[r - 0][c + 48] = '\\';
	world[r - 0][c + 49] = '_';
	world[r - 0][c + 50] = '_';
	world[r - 0][c + 51] = '_';
	world[r - 0][c + 52] = '_';
	world[r - 0][c + 53] = '_';
	world[r - 0][c + 54] = '_';
	world[r - 0][c + 55] = '/';
	world[r - 0][c + 62] = '\\';
	world[r - 0][c + 63] = '_';
	world[r - 0][c + 64] = '_';
	world[r - 0][c + 65] = '/';
	world[r - 0][c + 71] = '|';
	world[r - 0][c + 72] = '_';
	world[r - 0][c + 73] = '_';
	world[r - 0][c + 74] = '_';
	world[r - 0][c + 75] = '_';
	world[r - 0][c + 76] = '_';
	world[r - 0][c + 77] = '_';
	world[r - 0][c + 78] = '_';
	world[r - 0][c + 79] = '|';
	world[r - 0][c + 80] = '|';
	world[r - 0][c + 82] = '_';
	world[r - 0][c + 83] = '|';
	world[r - 0][c + 85] = '`';
	world[r - 0][c + 86] = '.';
	world[r - 0][c + 87] = '_';
	world[r - 0][c + 88] = '_';
	world[r - 0][c + 89] = '_';
	world[r - 0][c + 90] = '_';
	world[r - 0][c + 91] = '_';
	world[r - 0][c + 92] = '|';
	world[r - 0][c + 93] = '(';
	world[r - 0][c + 94] = '_';
	world[r - 0][c + 95] = '_';
	world[r - 0][c + 96] = ')';

}

void drawWinner(unsigned char** world)
{
	int r = 17; int c = 20;

	world[r - 5][c + 0] = '_';
	world[r - 5][c + 1] = '_';
	world[r - 5][c + 2] = '_';
	world[r - 5][c + 3] = '_';
	world[r - 5][c + 8] = '_';
	world[r - 5][c + 9] = '_';
	world[r - 5][c + 10] = '_';
	world[r - 5][c + 11] = '_';
	world[r - 5][c + 14] = '_';
	world[r - 5][c + 15] = '_';
	world[r - 5][c + 16] = '_';
	world[r - 5][c + 17] = '_';
	world[r - 5][c + 18] = '_';
	world[r - 5][c + 19] = '_';
	world[r - 5][c + 24] = '_';
	world[r - 5][c + 25] = '_';
	world[r - 5][c + 30] = '_';
	world[r - 5][c + 31] = '_';
	world[r - 5][c + 37] = '_';
	world[r - 5][c + 38] = '_';
	world[r - 5][c + 39] = '_';
	world[r - 5][c + 40] = '_';
	world[r - 5][c + 45] = '_';
	world[r - 5][c + 46] = '_';
	world[r - 5][c + 51] = '_';
	world[r - 5][c + 52] = '_';
	world[r - 5][c + 53] = '_';
	world[r - 5][c + 54] = '_';
	world[r - 5][c + 57] = '_';
	world[r - 5][c + 58] = '_';
	world[r - 5][c + 59] = '_';
	world[r - 5][c + 60] = '_';
	world[r - 5][c + 61] = '_';
	world[r - 5][c + 62] = '_';
	world[r - 5][c + 66] = '.';
	world[r - 5][c + 67] = '_';
	world[r - 5][c + 68] = '_';
	world[r - 5][c + 72] = '_';
	world[r - 5][c + 73] = '_';
	world[r - 5][c + 74] = '.';
	world[r - 5][c + 77] = '_';
	world[r - 5][c + 78] = '_';
	world[r - 4][c + 0] = '\\';
	world[r - 4][c + 4] = '\\';
	world[r - 4][c + 7] = '/';
	world[r - 4][c + 11] = '/';
	world[r - 4][c + 13] = '/';
	world[r - 4][c + 16] = '_';
	world[r - 4][c + 17] = '_';
	world[r - 4][c + 20] = '\\';
	world[r - 4][c + 23] = '|';
	world[r - 4][c + 26] = '|';
	world[r - 4][c + 29] = '|';
	world[r - 4][c + 32] = '|';
	world[r - 4][c + 37] = '\\';
	world[r - 4][c + 41] = '\\';
	world[r - 4][c + 44] = '/';
	world[r - 4][c + 47] = '\\';
	world[r - 4][c + 50] = '/';
	world[r - 4][c + 54] = '/';
	world[r - 4][c + 56] = '/';
	world[r - 4][c + 59] = '_';
	world[r - 4][c + 60] = '_';
	world[r - 4][c + 63] = '\\';
	world[r - 4][c + 66] = '|';
	world[r - 4][c + 69] = '\\';
	world[r - 4][c + 71] = '|';
	world[r - 4][c + 74] = '|';
	world[r - 4][c + 76] = '|';
	world[r - 4][c + 79] = '|';
	world[r - 3][c + 1] = '\\';
	world[r - 3][c + 5] = '\\';
	world[r - 3][c + 6] = '/';
	world[r - 3][c + 10] = '/';
	world[r - 3][c + 12] = '|';
	world[r - 3][c + 15] = '|';
	world[r - 3][c + 18] = '|';
	world[r - 3][c + 21] = '|';
	world[r - 3][c + 23] = '|';
	world[r - 3][c + 26] = '|';
	world[r - 3][c + 29] = '|';
	world[r - 3][c + 32] = '|';
	world[r - 3][c + 38] = '\\';
	world[r - 3][c + 42] = '\\';
	world[r - 3][c + 43] = '/';
	world[r - 3][c + 48] = '\\';
	world[r - 3][c + 49] = '/';
	world[r - 3][c + 53] = '/';
	world[r - 3][c + 55] = '|';
	world[r - 3][c + 58] = '|';
	world[r - 3][c + 61] = '|';
	world[r - 3][c + 64] = '|';
	world[r - 3][c + 66] = '|';
	world[r - 3][c + 70] = '\\';
	world[r - 3][c + 71] = '|';
	world[r - 3][c + 74] = '|';
	world[r - 3][c + 76] = '|';
	world[r - 3][c + 79] = '|';
	world[r - 2][c + 2] = '\\';
	world[r - 2][c + 3] = '_';
	world[r - 2][c + 8] = '_';
	world[r - 2][c + 9] = '/';
	world[r - 2][c + 12] = '|';
	world[r - 2][c + 15] = '|';
	world[r - 2][c + 18] = '|';
	world[r - 2][c + 21] = '|';
	world[r - 2][c + 23] = '|';
	world[r - 2][c + 26] = '|';
	world[r - 2][c + 29] = '|';
	world[r - 2][c + 32] = '|';
	world[r - 2][c + 39] = '\\';
	world[r - 2][c + 52] = '/';
	world[r - 2][c + 55] = '|';
	world[r - 2][c + 58] = '|';
	world[r - 2][c + 61] = '|';
	world[r - 2][c + 64] = '|';
	world[r - 2][c + 66] = '|';
	world[r - 2][c + 69] = '.';
	world[r - 2][c + 71] = '`';
	world[r - 2][c + 74] = '|';
	world[r - 2][c + 76] = '|';
	world[r - 2][c + 79] = '|';
	world[r - 1][c + 4] = '|';
	world[r - 1][c + 7] = '|';
	world[r - 1][c + 12] = '|';
	world[r - 1][c + 15] = '`';
	world[r - 1][c + 16] = '-';
	world[r - 1][c + 17] = '-';
	world[r - 1][c + 18] = '\'';
	world[r - 1][c + 21] = '|';
	world[r - 1][c + 23] = '|';
	world[r - 1][c + 26] = '`';
	world[r - 1][c + 27] = '-';
	world[r - 1][c + 28] = '-';
	world[r - 1][c + 29] = '\'';
	world[r - 1][c + 32] = '|';
	world[r - 1][c + 40] = '\\';
	world[r - 1][c + 45] = '/';
	world[r - 1][c + 46] = '\\';
	world[r - 1][c + 51] = '/';
	world[r - 1][c + 55] = '|';
	world[r - 1][c + 58] = '`';
	world[r - 1][c + 59] = '-';
	world[r - 1][c + 60] = '-';
	world[r - 1][c + 61] = '\'';
	world[r - 1][c + 64] = '|';
	world[r - 1][c + 66] = '|';
	world[r - 1][c + 69] = '|';
	world[r - 1][c + 70] = '\\';
	world[r - 1][c + 74] = '|';
	world[r - 1][c + 76] = '|';
	world[r - 1][c + 77] = '_';
	world[r - 1][c + 78] = '_';
	world[r - 1][c + 79] = '|';
	world[r - 0][c + 4] = '|';
	world[r - 0][c + 5] = '_';
	world[r - 0][c + 6] = '_';
	world[r - 0][c + 7] = '|';
	world[r - 0][c + 13] = '\\';
	world[r - 0][c + 14] = '_';
	world[r - 0][c + 15] = '_';
	world[r - 0][c + 16] = '_';
	world[r - 0][c + 17] = '_';
	world[r - 0][c + 18] = '_';
	world[r - 0][c + 19] = '_';
	world[r - 0][c + 20] = '/';
	world[r - 0][c + 24] = '\\';
	world[r - 0][c + 25] = '_';
	world[r - 0][c + 26] = '_';
	world[r - 0][c + 27] = '_';
	world[r - 0][c + 28] = '_';
	world[r - 0][c + 29] = '_';
	world[r - 0][c + 30] = '_';
	world[r - 0][c + 31] = '/';
	world[r - 0][c + 41] = '\\';
	world[r - 0][c + 42] = '_';
	world[r - 0][c + 43] = '_';
	world[r - 0][c + 44] = '/';
	world[r - 0][c + 47] = '\\';
	world[r - 0][c + 48] = '_';
	world[r - 0][c + 49] = '_';
	world[r - 0][c + 50] = '/';
	world[r - 0][c + 56] = '\\';
	world[r - 0][c + 57] = '_';
	world[r - 0][c + 58] = '_';
	world[r - 0][c + 59] = '_';
	world[r - 0][c + 60] = '_';
	world[r - 0][c + 61] = '_';
	world[r - 0][c + 62] = '_';
	world[r - 0][c + 63] = '/';
	world[r - 0][c + 66] = '|';
	world[r - 0][c + 67] = '_';
	world[r - 0][c + 68] = '_';
	world[r - 0][c + 69] = '|';
	world[r - 0][c + 71] = '\\';
	world[r - 0][c + 72] = '_';
	world[r - 0][c + 73] = '_';
	world[r - 0][c + 74] = '|';
	world[r - 0][c + 76] = '(';
	world[r - 0][c + 77] = '_';
	world[r - 0][c + 78] = '_';
	world[r - 0][c + 79] = ')';
}

void drawOpenScreen(unsigned char** world)
{
	int r = 20; int c = 18;

	world[r - 12][c + 0] = '.';
	world[r - 12][c + 1] = '_';
	world[r - 12][c + 2] = '_';
	world[r - 12][c + 3] = '_';
	world[r - 12][c + 4] = '_';
	world[r - 12][c + 5] = '_';
	world[r - 12][c + 6] = '_';
	world[r - 12][c + 7] = '_';
	world[r - 12][c + 8] = '_';
	world[r - 12][c + 9] = '_';
	world[r - 12][c + 10] = '_';
	world[r - 12][c + 11] = '_';
	world[r - 12][c + 12] = '.';
	world[r - 12][c + 14] = '_';
	world[r - 12][c + 15] = '_';
	world[r - 12][c + 16] = '_';
	world[r - 12][c + 17] = '_';
	world[r - 12][c + 18] = '_';
	world[r - 12][c + 19] = '_';
	world[r - 12][c + 20] = '_';
	world[r - 12][c + 22] = '.';
	world[r - 12][c + 23] = '_';
	world[r - 12][c + 24] = '_';
	world[r - 12][c + 25] = '_';
	world[r - 12][c + 26] = '_';
	world[r - 12][c + 27] = '_';
	world[r - 12][c + 28] = '_';
	world[r - 12][c + 35] = '.';
	world[r - 12][c + 36] = '_';
	world[r - 12][c + 37] = '_';
	world[r - 12][c + 38] = '_';
	world[r - 12][c + 41] = '_';
	world[r - 12][c + 42] = '_';
	world[r - 12][c + 43] = '_';
	world[r - 12][c + 44] = '.';
	world[r - 12][c + 47] = '_';
	world[r - 12][c + 48] = '_';
	world[r - 12][c + 51] = '.';
	world[r - 12][c + 52] = '_';
	world[r - 12][c + 53] = '_';
	world[r - 12][c + 57] = '_';
	world[r - 12][c + 58] = '_';
	world[r - 12][c + 59] = '.';
	world[r - 12][c + 66] = '_';
	world[r - 12][c + 67] = '_';
	world[r - 12][c + 68] = '_';
	world[r - 12][c + 76] = '_';
	world[r - 12][c + 77] = '_';
	world[r - 11][c + 0] = '|';
	world[r - 11][c + 12] = '|';
	world[r - 11][c + 13] = '|';
	world[r - 11][c + 17] = '_';
	world[r - 11][c + 18] = '_';
	world[r - 11][c + 19] = '_';
	world[r - 11][c + 20] = '_';
	world[r - 11][c + 21] = '|';
	world[r - 11][c + 22] = '|';
	world[r - 11][c + 26] = '_';
	world[r - 11][c + 29] = '\\';
	world[r - 11][c + 35] = '|';
	world[r - 11][c + 39] = '\\';
	world[r - 11][c + 40] = '/';
	world[r - 11][c + 44] = '|';
	world[r - 11][c + 46] = '|';
	world[r - 11][c + 49] = '|';
	world[r - 11][c + 51] = '|';
	world[r - 11][c + 54] = '\\';
	world[r - 11][c + 56] = '|';
	world[r - 11][c + 59] = '|';
	world[r - 11][c + 65] = '/';
	world[r - 11][c + 69] = '\\';
	world[r - 11][c + 75] = '|';
	world[r - 11][c + 78] = '|';
	world[r - 10][c + 0] = '`';
	world[r - 10][c + 1] = '-';
	world[r - 10][c + 2] = '-';
	world[r - 10][c + 3] = '-';
	world[r - 10][c + 4] = '|';
	world[r - 10][c + 7] = '|';
	world[r - 10][c + 8] = '-';
	world[r - 10][c + 9] = '-';
	world[r - 10][c + 10] = '-';
	world[r - 10][c + 11] = '-';
	world[r - 10][c + 12] = '`';
	world[r - 10][c + 13] = '|';
	world[r - 10][c + 16] = '|';
	world[r - 10][c + 17] = '_';
	world[r - 10][c + 18] = '_';
	world[r - 10][c + 22] = '|';
	world[r - 10][c + 25] = '|';
	world[r - 10][c + 26] = '_';
	world[r - 10][c + 27] = ')';
	world[r - 10][c + 30] = '|';
	world[r - 10][c + 35] = '|';
	world[r - 10][c + 38] = '\\';
	world[r - 10][c + 41] = '/';
	world[r - 10][c + 44] = '|';
	world[r - 10][c + 46] = '|';
	world[r - 10][c + 49] = '|';
	world[r - 10][c + 51] = '|';
	world[r - 10][c + 55] = '\\';
	world[r - 10][c + 56] = '|';
	world[r - 10][c + 59] = '|';
	world[r - 10][c + 64] = '/';
	world[r - 10][c + 67] = '^';
	world[r - 10][c + 70] = '\\';
	world[r - 10][c + 75] = '|';
	world[r - 10][c + 78] = '|';
	world[r - 9][c + 4] = '|';
	world[r - 9][c + 7] = '|';
	world[r - 9][c + 13] = '|';
	world[r - 9][c + 17] = '_';
	world[r - 9][c + 18] = '_';
	world[r - 9][c + 19] = '|';
	world[r - 9][c + 22] = '|';
	world[r - 9][c + 29] = '/';
	world[r - 9][c + 35] = '|';
	world[r - 9][c + 38] = '|';
	world[r - 9][c + 39] = '\\';
	world[r - 9][c + 40] = '/';
	world[r - 9][c + 41] = '|';
	world[r - 9][c + 44] = '|';
	world[r - 9][c + 46] = '|';
	world[r - 9][c + 49] = '|';
	world[r - 9][c + 51] = '|';
	world[r - 9][c + 54] = '.';
	world[r - 9][c + 56] = '`';
	world[r - 9][c + 59] = '|';
	world[r - 9][c + 63] = '/';
	world[r - 9][c + 66] = '/';
	world[r - 9][c + 67] = '_';
	world[r - 9][c + 68] = '\\';
	world[r - 9][c + 71] = '\\';
	world[r - 9][c + 75] = '|';
	world[r - 9][c + 78] = '|';
	world[r - 8][c + 4] = '|';
	world[r - 8][c + 7] = '|';
	world[r - 8][c + 13] = '|';
	world[r - 8][c + 16] = '|';
	world[r - 8][c + 17] = '_';
	world[r - 8][c + 18] = '_';
	world[r - 8][c + 19] = '_';
	world[r - 8][c + 20] = '_';
	world[r - 8][c + 22] = '|';
	world[r - 8][c + 25] = '|';
	world[r - 8][c + 26] = '\\';
	world[r - 8][c + 29] = '\\';
	world[r - 8][c + 30] = '-';
	world[r - 8][c + 31] = '-';
	world[r - 8][c + 32] = '-';
	world[r - 8][c + 33] = '-';
	world[r - 8][c + 34] = '.';
	world[r - 8][c + 35] = '|';
	world[r - 8][c + 38] = '|';
	world[r - 8][c + 41] = '|';
	world[r - 8][c + 44] = '|';
	world[r - 8][c + 46] = '|';
	world[r - 8][c + 49] = '|';
	world[r - 8][c + 51] = '|';
	world[r - 8][c + 54] = '|';
	world[r - 8][c + 55] = '\\';
	world[r - 8][c + 59] = '|';
	world[r - 8][c + 62] = '/';
	world[r - 8][c + 65] = '_';
	world[r - 8][c + 66] = '_';
	world[r - 8][c + 67] = '_';
	world[r - 8][c + 68] = '_';
	world[r - 8][c + 69] = '_';
	world[r - 8][c + 72] = '\\';
	world[r - 8][c + 75] = '|';
	world[r - 8][c + 78] = '`';
	world[r - 8][c + 79] = '-';
	world[r - 8][c + 80] = '-';
	world[r - 8][c + 81] = '-';
	world[r - 8][c + 82] = '-';
	world[r - 8][c + 83] = '.';
	world[r - 7][c + 4] = '|';
	world[r - 7][c + 5] = '_';
	world[r - 7][c + 6] = '_';
	world[r - 7][c + 7] = '|';
	world[r - 7][c + 13] = '|';
	world[r - 7][c + 14] = '_';
	world[r - 7][c + 15] = '_';
	world[r - 7][c + 16] = '_';
	world[r - 7][c + 17] = '_';
	world[r - 7][c + 18] = '_';
	world[r - 7][c + 19] = '_';
	world[r - 7][c + 20] = '_';
	world[r - 7][c + 21] = '|';
	world[r - 7][c + 22] = '|';
	world[r - 7][c + 24] = '_';
	world[r - 7][c + 25] = '|';
	world[r - 7][c + 27] = '`';
	world[r - 7][c + 28] = '.';
	world[r - 7][c + 29] = '_';
	world[r - 7][c + 30] = '_';
	world[r - 7][c + 31] = '_';
	world[r - 7][c + 32] = '_';
	world[r - 7][c + 33] = '_';
	world[r - 7][c + 34] = '|';
	world[r - 7][c + 35] = '|';
	world[r - 7][c + 36] = '_';
	world[r - 7][c + 37] = '_';
	world[r - 7][c + 38] = '|';
	world[r - 7][c + 41] = '|';
	world[r - 7][c + 42] = '_';
	world[r - 7][c + 43] = '_';
	world[r - 7][c + 44] = '|';
	world[r - 7][c + 46] = '|';
	world[r - 7][c + 47] = '_';
	world[r - 7][c + 48] = '_';
	world[r - 7][c + 49] = '|';
	world[r - 7][c + 51] = '|';
	world[r - 7][c + 52] = '_';
	world[r - 7][c + 53] = '_';
	world[r - 7][c + 54] = '|';
	world[r - 7][c + 56] = '\\';
	world[r - 7][c + 57] = '_';
	world[r - 7][c + 58] = '_';
	world[r - 7][c + 59] = '|';
	world[r - 7][c + 61] = '/';
	world[r - 7][c + 62] = '_';
	world[r - 7][c + 63] = '_';
	world[r - 7][c + 64] = '/';
	world[r - 7][c + 70] = '\\';
	world[r - 7][c + 71] = '_';
	world[r - 7][c + 72] = '_';
	world[r - 7][c + 73] = '\\';
	world[r - 7][c + 75] = '|';
	world[r - 7][c + 76] = '_';
	world[r - 7][c + 77] = '_';
	world[r - 7][c + 78] = '_';
	world[r - 7][c + 79] = '_';
	world[r - 7][c + 80] = '_';
	world[r - 7][c + 81] = '_';
	world[r - 7][c + 82] = '_';
	world[r - 7][c + 83] = '|';
	world[r - 5][c + 9] = '.';
	world[r - 5][c + 10] = '_';
	world[r - 5][c + 11] = '_';
	world[r - 5][c + 12] = '_';
	world[r - 5][c + 13] = '_';
	world[r - 5][c + 14] = '_';
	world[r - 5][c + 15] = '_';
	world[r - 5][c + 16] = '_';
	world[r - 5][c + 17] = '_';
	world[r - 5][c + 18] = '_';
	world[r - 5][c + 19] = '_';
	world[r - 5][c + 20] = '_';
	world[r - 5][c + 21] = '.';
	world[r - 5][c + 24] = '_';
	world[r - 5][c + 25] = '_';
	world[r - 5][c + 26] = '_';
	world[r - 5][c + 27] = '_';
	world[r - 5][c + 28] = '_';
	world[r - 5][c + 29] = '_';
	world[r - 5][c + 33] = '_';
	world[r - 5][c + 34] = '_';
	world[r - 5][c + 35] = '_';
	world[r - 5][c + 36] = '_';
	world[r - 5][c + 41] = '_';
	world[r - 5][c + 42] = '_';
	world[r - 5][c + 47] = '_';
	world[r - 5][c + 48] = '_';
	world[r - 5][c + 49] = '_';
	world[r - 5][c + 50] = '_';
	world[r - 5][c + 53] = '_';
	world[r - 5][c + 54] = '_';
	world[r - 5][c + 55] = '_';
	world[r - 5][c + 56] = '_';
	world[r - 5][c + 57] = '_';
	world[r - 5][c + 58] = '_';
	world[r - 5][c + 59] = '_';
	world[r - 5][c + 61] = '.';
	world[r - 5][c + 62] = '_';
	world[r - 5][c + 63] = '_';
	world[r - 5][c + 64] = '_';
	world[r - 5][c + 65] = '_';
	world[r - 5][c + 66] = '_';
	world[r - 5][c + 67] = '_';
	world[r - 4][c + 9] = '|';
	world[r - 4][c + 21] = '|';
	world[r - 4][c + 23] = '/';
	world[r - 4][c + 26] = '_';
	world[r - 4][c + 27] = '_';
	world[r - 4][c + 30] = '\\';
	world[r - 4][c + 33] = '\\';
	world[r - 4][c + 37] = '\\';
	world[r - 4][c + 40] = '/';
	world[r - 4][c + 43] = '\\';
	world[r - 4][c + 46] = '/';
	world[r - 4][c + 50] = '/';
	world[r - 4][c + 52] = '|';
	world[r - 4][c + 56] = '_';
	world[r - 4][c + 57] = '_';
	world[r - 4][c + 58] = '_';
	world[r - 4][c + 59] = '_';
	world[r - 4][c + 60] = '|';
	world[r - 4][c + 61] = '|';
	world[r - 4][c + 65] = '_';
	world[r - 4][c + 68] = '\\';
	world[r - 3][c + 9] = '`';
	world[r - 3][c + 10] = '-';
	world[r - 3][c + 11] = '-';
	world[r - 3][c + 12] = '-';
	world[r - 3][c + 13] = '|';
	world[r - 3][c + 16] = '|';
	world[r - 3][c + 17] = '-';
	world[r - 3][c + 18] = '-';
	world[r - 3][c + 19] = '-';
	world[r - 3][c + 20] = '-';
	world[r - 3][c + 21] = '`';
	world[r - 3][c + 22] = '|';
	world[r - 3][c + 25] = '|';
	world[r - 3][c + 28] = '|';
	world[r - 3][c + 31] = '|';
	world[r - 3][c + 34] = '\\';
	world[r - 3][c + 38] = '\\';
	world[r - 3][c + 39] = '/';
	world[r - 3][c + 44] = '\\';
	world[r - 3][c + 45] = '/';
	world[r - 3][c + 49] = '/';
	world[r - 3][c + 52] = '|';
	world[r - 3][c + 55] = '|';
	world[r - 3][c + 56] = '_';
	world[r - 3][c + 57] = '_';
	world[r - 3][c + 61] = '|';
	world[r - 3][c + 64] = '|';
	world[r - 3][c + 65] = '_';
	world[r - 3][c + 66] = ')';
	world[r - 3][c + 69] = '|';
	world[r - 2][c + 13] = '|';
	world[r - 2][c + 16] = '|';
	world[r - 2][c + 22] = '|';
	world[r - 2][c + 25] = '|';
	world[r - 2][c + 28] = '|';
	world[r - 2][c + 31] = '|';
	world[r - 2][c + 35] = '\\';
	world[r - 2][c + 48] = '/';
	world[r - 2][c + 52] = '|';
	world[r - 2][c + 56] = '_';
	world[r - 2][c + 57] = '_';
	world[r - 2][c + 58] = '|';
	world[r - 2][c + 61] = '|';
	world[r - 2][c + 68] = '/';
	world[r - 1][c + 13] = '|';
	world[r - 1][c + 16] = '|';
	world[r - 1][c + 22] = '|';
	world[r - 1][c + 25] = '`';
	world[r - 1][c + 26] = '-';
	world[r - 1][c + 27] = '-';
	world[r - 1][c + 28] = '\'';
	world[r - 1][c + 31] = '|';
	world[r - 1][c + 36] = '\\';
	world[r - 1][c + 41] = '/';
	world[r - 1][c + 42] = '\\';
	world[r - 1][c + 47] = '/';
	world[r - 1][c + 52] = '|';
	world[r - 1][c + 55] = '|';
	world[r - 1][c + 56] = '_';
	world[r - 1][c + 57] = '_';
	world[r - 1][c + 58] = '_';
	world[r - 1][c + 59] = '_';
	world[r - 1][c + 61] = '|';
	world[r - 1][c + 64] = '|';
	world[r - 1][c + 65] = '\\';
	world[r - 1][c + 68] = '\\';
	world[r - 1][c + 69] = '-';
	world[r - 1][c + 70] = '-';
	world[r - 1][c + 71] = '-';
	world[r - 1][c + 72] = '-';
	world[r - 1][c + 73] = '.';
	world[r - 0][c + 13] = '|';
	world[r - 0][c + 14] = '_';
	world[r - 0][c + 15] = '_';
	world[r - 0][c + 16] = '|';
	world[r - 0][c + 23] = '\\';
	world[r - 0][c + 24] = '_';
	world[r - 0][c + 25] = '_';
	world[r - 0][c + 26] = '_';
	world[r - 0][c + 27] = '_';
	world[r - 0][c + 28] = '_';
	world[r - 0][c + 29] = '_';
	world[r - 0][c + 30] = '/';
	world[r - 0][c + 37] = '\\';
	world[r - 0][c + 38] = '_';
	world[r - 0][c + 39] = '_';
	world[r - 0][c + 40] = '/';
	world[r - 0][c + 43] = '\\';
	world[r - 0][c + 44] = '_';
	world[r - 0][c + 45] = '_';
	world[r - 0][c + 46] = '/';
	world[r - 0][c + 52] = '|';
	world[r - 0][c + 53] = '_';
	world[r - 0][c + 54] = '_';
	world[r - 0][c + 55] = '_';
	world[r - 0][c + 56] = '_';
	world[r - 0][c + 57] = '_';
	world[r - 0][c + 58] = '_';
	world[r - 0][c + 59] = '_';
	world[r - 0][c + 60] = '|';
	world[r - 0][c + 61] = '|';
	world[r - 0][c + 63] = '_';
	world[r - 0][c + 64] = '|';
	world[r - 0][c + 66] = '`';
	world[r - 0][c + 67] = '.';
	world[r - 0][c + 68] = '_';
	world[r - 0][c + 69] = '_';
	world[r - 0][c + 70] = '_';
	world[r - 0][c + 71] = '_';
	world[r - 0][c + 72] = '_';
	world[r - 0][c + 73] = '|';

	//////////////////////////

	world[r + 4][c + 18 + 2] = 'P';
	world[r + 4][c + 20 + 2] = 'R';
	world[r + 4][c + 22 + 2] = 'E';
	world[r + 4][c + 24 + 2] = 'S';
	world[r + 4][c + 26 + 2] = 'S';

	world[r + 4][c + 30 + 2] = 'S';
	world[r + 4][c + 32 + 2] = 'P';
	world[r + 4][c + 34 + 2] = 'A';
	world[r + 4][c + 36 + 2] = 'C';
	world[r + 4][c + 38 + 2] = 'E';

	world[r + 4][c + 42 + 2] = 'T';
	world[r + 4][c + 44 + 2] = 'O';

	world[r + 4][c + 48 + 2] = 'S';
	world[r + 4][c + 50 + 2] = 'T';
	world[r + 4][c + 52 + 2] = 'A';
	world[r + 4][c + 54 + 2] = 'R';
	world[r + 4][c + 56 + 2] = 'T';

	//////////////////////////

	world[r - 15][c + 20 + 2] = 'B';
	world[r - 15][c + 22 + 2] = 'Y';

	world[r - 15][c + 26 + 2] = 'H';
	world[r - 15][c + 28 + 2] = 'A';
	world[r - 15][c + 30 + 2] = 'M';
	world[r - 15][c + 32 + 2] = 'Z';
	world[r - 15][c + 34 + 2] = 'A';

	world[r - 15][c + 38 + 2] = 'E';
	world[r - 15][c + 40 + 2] = 'L';

	world[r - 15][c + 44 + 2] = 'H';
	world[r - 15][c + 46 + 2] = 'E';
	world[r - 15][c + 48 + 2] = 'N';
	world[r - 15][c + 50 + 2] = 'N';
	world[r - 15][c + 52 + 2] = 'A';
	world[r - 15][c + 54 + 2] = 'W';
	world[r - 15][c + 56 + 2] = 'Y';

}

int main()
{
	unsigned char** world = new unsigned char* [90];

	for (int i = 0; i < 90; i++)
	{
		world[i] = new unsigned char[360];
	}


	int heroRow = 75, heroCol = 60, heroCurrFloor = 1, heroTakenBulletsInFloorOne = 0;
	int elevatorRow = 38, elevatorRangeCol = 34, elevatorDir = 0, elevatorCurrFloor = 2; // 2 OR 3
	int strtRow = 60, endRow = 90;
	int strtCol = 0, endCol = 120;
	char heroDir = ' '; // INITIAL HERO SHAPE
	char prevHeroDir = 'D'; // INITIAL BULLET DIRECTION
	int heroLives = 3;
	int isHeroGoingDown = 0;
	int isHeroJumping = 0, ctJump = 0;
	int isHeroDoubleJumping = 0, ctDoubleJump = 0;
	int isHeroJumpingRight = 0, ctRightJump = 0;
	int isHeroJumpingLeft = 0, ctLeftJump = 0;
	int isHeroOnLadder = 0; // TO ALLOW USAGE OF UP & DOWN MOVEMENTS & USAGE OF LADDER
	int isHeroInElevator = 0; // TO CHANGE ELEVATOR DRAWING AND SCROLLING
	int doYouWantSingleBullet = 0, singleBulletRow = 0, singleBulletCol = 0;
	int isMultiBulletsActive = 0;

	/////////////////////////////////////
	//// MULTIPLE BULLETS DECLARATION
	///////////////////////////////////

	Bullet* MultiBullets = new Bullet[5];

	for (int i = 0; i < 5; i++)
	{
		MultiBullets[i].IsActive = 0;
		MultiBullets[i].Row = 0;
		MultiBullets[i].Col = 0;
		MultiBullets[i].Dir = 'D';
	}

	///////////////////////////////////

	/////////////////////////////////////
	//// DIAMOND DECLARATION
	///////////////////////////////////

	int diamondStrtRow = 13;
	int diamondEndRow = 18;
	int diamondStrtCol = 335;
	int diamondEndCol = 347;

	///////////////////////////////////

	/////////////////////////////////////
	//// OBSTACLES DECLARATION
	///////////////////////////////////

	Obstacle One, Two, Three, Four;

	One.strtCol = 100; One.endCol = 116; One.strtRow = 85;
	Two.strtCol = 140; Two.endCol = 156; Two.strtRow = 82;
	Three.strtCol = 180; Three.endCol = 196; Three.strtRow = 79;
	Four.strtCol = 220; Four.endCol = 236; Four.strtRow = 76;

	///////////////////////////////////

	/////////////////////////////////////
	//// ENEMY FLOOR 1 DECLARATION
	///////////////////////////////////

	Enemy FloorOne;

	FloorOne.Row = 63; FloorOne.Col = 325; FloorOne.isAlive = 1; FloorOne.Dir = -2; FloorOne.DirTwo = -2; FloorOne.Health = 3;

	Bullet* EnemyBullets = new Bullet[3];

	for (int i = 0; i < 3; i++)
	{
		EnemyBullets[i].IsActive = 0;
		EnemyBullets[i].Row = 0;
		EnemyBullets[i].Col = 0;
		EnemyBullets[i].Dir = 'A';
	}

	///////////////////////////////////

	/////////////////////////////////////
	//// ENEMIES FLOOR 2 DECLARATION
	///////////////////////////////////

	Enemy* Casper = new Enemy[3];

	Casper[0].Row = 32; Casper[0].Col = 300; Casper[0].isAlive = 1; Casper[0].DirTwo = 0; Casper[0].Dir = -2; Casper[0].Health = 5;
	Casper[1].Row = 40; Casper[1].Col = 280; Casper[1].isAlive = 1; Casper[1].DirTwo = 0; Casper[1].Dir = -5; Casper[1].Health = 5;
	Casper[2].Row = 35; Casper[2].Col = 50; Casper[2].isAlive = 1; Casper[2].DirTwo = 2; Casper[2].Dir = 2;  Casper[2].Health = 5;

	///////////////////////////////////

	/////////////////////////////////////
	//// FINAL BOSS 
	///////////////////////////////////

	Enemy FinalBoss;

	FinalBoss.Row = 2; FinalBoss.Col = 300; FinalBoss.isAlive = 1; FinalBoss.Dir = -2; FinalBoss.DirTwo = -1; FinalBoss.Health = 10;
	int isFinalBossFire = 1;
	int belowMouthRow = 18;
	int belowMouthCol = 13;
	int fireCounter = 0;

	/////////////////////////////////////

	/////////////////////////////////////
	//// LASER DECLARATION 
	///////////////////////////////////

	Laser* Lasers = new Laser[4];

	Lasers[0].Col = 70;  Lasers[0].Len = 0; Lasers[0].IsActive = 1; Lasers[0].Timer = 0;
	Lasers[1].Col = 100; Lasers[1].Len = 0; Lasers[1].IsActive = 1; Lasers[1].Timer = 1;
	Lasers[2].Col = 130; Lasers[2].Len = 0; Lasers[2].IsActive = 1; Lasers[2].Timer = 2;
	Lasers[3].Col = 160; Lasers[3].Len = 0; Lasers[3].IsActive = 1; Lasers[3].Timer = 3;

	///////////////////////////////////

	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);

	////////////////////////////////////
	//// START SCREEN
	///////////////////////////////////

	for (;;)
	{
		while (!_kbhit())
		{
			GoBackHomeCursor();

			deleteWorld(world);
			drawOpenScreen(world);
			drawWorldBorders(world, 0, 30, 0, 120);
			dispWorld(world, 0, 30, 0, 120);
		}

		char keyPressed = _getch();

		if (keyPressed == ' ')
		{
			break;
		}
	}

	///////////////////////////////////

	/////////////////////////////////////
	//// GAME LOOP 
	///////////////////////////////////

	for (;;)
	{
		while (!_kbhit())
		{
			GoBackHomeCursor();

			////////////////////////////////////
			//// LOSE SCREEN
			///////////////////////////////////

			if (heroLives <= 0)
			{
				while (!_kbhit())
				{
					GoBackHomeCursor();

					deleteWorld(world);
					drawGameOver(world);
					drawWorldBorders(world, 0, 30, 0, 120);
					dispWorld(world, 0, 30, 0, 120);
				}
				return 0;

			}

			///////////////////////////////////

			deleteWorld(world);
			drawWorldStatics(world);
			drawDiamond(world);

			/////////////////////////////////////
			//// WINNER SCREEN
			///////////////////////////////////

			if (checkDiamondCollision(heroRow, heroCol, diamondStrtRow, diamondEndRow, diamondStrtCol, diamondEndCol) && FinalBoss.isAlive == 0)
			{
				while (!_kbhit())
				{
					GoBackHomeCursor();

					deleteWorld(world);
					drawWinner(world);
					drawWorldBorders(world, 0, 30, 0, 120);
					dispWorld(world, 0, 30, 0, 120);
				}
				return 0;
			}

			///////////////////////////////////

			moveElevator(elevatorRow, elevatorDir, elevatorCurrFloor);
			drawFloorDividers(world);
			drawElevator(elevatorRow, isHeroInElevator, world);

			/////////////////////////////////////
			//// FLOOR 1 ENEMY
			///////////////////////////////////

			if (FloorOne.isAlive == 1)
			{
				moveFloorOneEnemy(FloorOne);
				drawFloorOneEnemy(FloorOne, world);
				checkHeroCollisionEnemyFloorOne(heroRow, heroCol, FloorOne, heroLives, strtCol, endCol);

				if (heroCol > 190)
				{
					activateEnemyFloorOneBullets(FloorOne, EnemyBullets);
					moveEnemyFloorOneBullets(EnemyBullets, One, Two, Three, Four);
					drawEnemyFloorOneBullets(EnemyBullets, world);
					checkEnemyFloorOneBulletsCollisionHero(EnemyBullets, heroRow, heroCol, heroLives, strtCol, endCol, heroTakenBulletsInFloorOne, FloorOne, MultiBullets);
				}

				checkBulletsCollisionEnemyFloorOne(FloorOne, doYouWantSingleBullet, singleBulletRow, singleBulletCol, prevHeroDir, MultiBullets);

			}

			///////////////////////////////////

			/////////////////////////////////////
			//// FLOOR 2 ENEMIES
			///////////////////////////////////

			moveCaspers(Casper);
			drawCaspers(Casper, world);
			checkHeroCollisionCaspers(heroRow, heroCol, heroLives, strtCol, endCol, Casper, MultiBullets);

			///////////////////////////////////

			/////////////////////////////////////
			//// FINAL BOSS
			///////////////////////////////////

			if (FinalBoss.isAlive == 1)
			{
				moveFinalBoss(FinalBoss, heroRow, heroCol, heroCurrFloor);
				drawFinalBoss(FinalBoss, world);
				checkBulletsCollisionFinalBoss(FinalBoss, doYouWantSingleBullet, singleBulletRow, singleBulletCol, prevHeroDir, MultiBullets);

				if (isFinalBossFire == 1 && ((FinalBoss.Col - 31) - (heroCol + 14) < 20) && heroCurrFloor == 3)
				{
					drawDragonFire(belowMouthRow, belowMouthCol, fireCounter, FinalBoss, world);
					checkHerocollisionFire(heroRow, heroCol, heroLives, FinalBoss, isFinalBossFire, belowMouthRow, belowMouthCol, fireCounter, MultiBullets, doYouWantSingleBullet);
				}

				checkHeroCollisionFinalBoss(heroRow, heroCol, heroLives, strtCol, endCol, FinalBoss, MultiBullets, doYouWantSingleBullet);
			}

			///////////////////////////////////

			/////////////////////////////////////
			//// LASER LOGIC
			///////////////////////////////////

			moveLasers(Lasers);
			drawLasers(Lasers, world);
			checkHeroCollisionLasers(Lasers, heroRow, heroCol, heroLives, strtCol, endCol, FinalBoss, MultiBullets, doYouWantSingleBullet);

			///////////////////////////////////

			/////////////////////////////////////
			//// SINGLE BULLET
			///////////////////////////////////

			if (doYouWantSingleBullet == 1)
			{
				moveSingleBullet(singleBulletRow, singleBulletCol, heroCurrFloor, prevHeroDir, doYouWantSingleBullet, One, Two, Three, Four);
				drawSingleBullet(singleBulletRow, singleBulletCol, prevHeroDir, doYouWantSingleBullet, world);
			}

			///////////////////////////////////


			////////////////////////////
			//// MULTIPLE BULLETS
			//////////////////////////

			if (doYouWantSingleBullet == 0)
			{
				moveMultiBullets(MultiBullets, heroCurrFloor, One, Two, Three, Four);
				drawMultiBullets(MultiBullets, world);
			}

			///////////////////////////////////

			//////////////////////////////////////////////
			//// CHECKING BULLETS COLLISION ENEMIES
			/////////////////////////////////////////////


			checkBulletsCollisionCaspers(Casper, doYouWantSingleBullet, singleBulletRow, singleBulletCol, prevHeroDir, MultiBullets);

			/////////////////////////////////////////////

			/////////////////////////////////////
			//// CALLING GRAVITY 
			///////////////////////////////////

			if (isHeroJumping == 0 && isHeroDoubleJumping == 0 && isHeroJumpingRight == 0 && isHeroJumpingLeft == 0 && isHeroOnLadder == 0 && isHeroInElevator == 0)
			{
				comeHereGravity(heroRow, heroCol, isHeroGoingDown, heroCurrFloor, One, Two, Three, Four);

				int maxEndRow;
				if (heroCurrFloor == 1)
				{
					maxEndRow = 90;
				}
				else
				{
					if (heroCurrFloor == 2)
					{
						maxEndRow = 60;
					}
					else
					{
						if (heroCurrFloor == 3)
						{
							maxEndRow = 30;
						}
					}
				}


				if (heroRow > strtRow + 10 && endRow < maxEndRow)
				{
					strtRow++;
					endRow++;
				}

			}

			///////////////////////////////////

			////////////////////////////////////
			//// SINGLE JUMP  
			///////////////////////////////////

			if (isHeroJumping == 1 && isHeroGoingDown == 0)
			{
				if (ctJump < 3)
				{
					heroDir = 'J'; // TO IGNORE ANY KEY IS PRESSED DURING JUMPING (SHAPE)

					if (world[heroRow - 1][heroCol] == ' ')
					{
						heroRow--;
					}
					else
					{
						ctJump = 3;
					}
				}
				else
				{
					if (ctJump < 6)
					{
						if (world[heroRow + 14][heroCol] == ' ' && world[heroRow + 14][heroCol - 7] == ' ' && world[heroRow + 14][heroCol + 7] == ' ' && heroRow + 14 < 89 && heroRow + 14 < 59)
						{
							heroRow++;
						}

						heroDir = ' '; // TO DRAW THE STANDING SHAPE WHILE GOING DOWN
					}
					else
					{
						isHeroJumping = 0;
						ctJump = 0;
						isHeroGoingDown = 1; // TO PREVENT MULTIPLE JUMPS (ComeHereGravity WILL RESET IT TO 0 AGAIN)
					}
				}

				ctJump++;
			}

			///////////////////////////////////

			/////////////////////////////////////
			//// DOUBLE JUMP  
			///////////////////////////////////

			if (isHeroDoubleJumping == 1 && isHeroGoingDown == 0)
			{
				if (ctDoubleJump < 6)
				{
					heroDir = 'J'; // TO IGNORE ANY KEY IS PRESSED DURING JUMPING (SHAPE)

					if (world[heroRow - 1][heroCol] == ' ')
					{
						heroRow--;
					}
					else
					{
						ctDoubleJump = 6;
					}
				}
				else
				{
					if (ctDoubleJump < 12)
					{
						if (world[heroRow + 14][heroCol] == ' ' && world[heroRow + 14][heroCol - 7] == ' ' && world[heroRow + 14][heroCol + 7] == ' ' && heroRow + 14 < 89 && heroRow + 14 < 59)
						{
							heroRow++;
						}

						heroDir = ' '; // TO DRAW THE STANDING SHAPE WHILE GOING DOWN
					}
					else
					{
						isHeroDoubleJumping = 0;
						ctDoubleJump = 0;
						isHeroGoingDown = 1; // TO PREVENT MULTIPLE JUMPS (ComeHereGravity WILL RESET IT TO 0 AGAIN)
					}
				}

				ctDoubleJump++;
			}

			///////////////////////////////////

			/////////////////////////////////////
			////  JUMP  RIGHT
			///////////////////////////////////

			if (isHeroJumpingRight == 1 && isHeroGoingDown == 0)
			{
				if (ctRightJump < 4)
				{
					heroDir = 'J'; // TO IGNORE ANY KEY IS PRESSED DURING JUMPING (SHAPE) 

					if (world[heroRow - 1][heroCol] == ' ')
					{
						heroRow--;
					}

					moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol > strtCol + 60 && endCol < 360)
					{
						strtCol++;
						endCol++;
					}

					moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol > strtCol + 60 && endCol < 360)
					{
						strtCol++;
						endCol++;
					}

					moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol > strtCol + 60 && endCol < 360)
					{
						strtCol++;
						endCol++;
					}

					moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol > strtCol + 60 && endCol < 360)
					{
						strtCol++;
						endCol++;
					}

					moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol > strtCol + 60 && endCol < 360)
					{
						strtCol++;
						endCol++;
					}

				}
				else
				{
					if (ctRightJump < 8)
					{
						heroDir = 'D';

						if (world[heroRow + 14][heroCol] == ' ' && world[heroRow + 14][heroCol + 7] == ' ' && world[heroRow + 14][heroCol - 7] == ' ' && heroRow + 14 < 89 && heroRow + 14 < 59)
						{
							heroRow++;
						}

						moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

						if (heroCol > strtCol + 60 && endCol < 360)
						{
							strtCol++;
							endCol++;
						}

						moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

						if (heroCol > strtCol + 60 && endCol < 360)
						{
							strtCol++;
							endCol++;
						}

						moveHero(heroRow, heroCol, 'D', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

						if (heroCol > strtCol + 60 && endCol < 360)
						{
							strtCol++;
							endCol++;
						}


					}
					else
					{
						isHeroJumpingRight = 0;
						ctRightJump = 0;
						isHeroGoingDown = 1; // TO PREVENT MULTIPLE JUMPS (ComeHereGravity WILL RESET IT TO 0 AGAIN)
						heroDir = ' ';
					}
				}

				ctRightJump++;
			}

			///////////////////////////////////

			/////////////////////////////////////
			////  JUMP  LEFT
			///////////////////////////////////

			if (isHeroJumpingLeft == 1 && isHeroGoingDown == 0)
			{
				if (ctLeftJump < 4)
				{
					heroDir = 'J'; // TO IGNORE ANY KEY IS PRESSED DURING JUMPING (SHAPE)

					if (world[heroRow - 1][heroCol] == ' ')
					{
						heroRow--;
					}

					moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol < strtCol + 60 && strtCol > 0)
					{
						strtCol--;
						endCol--;
					}

					moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol < strtCol + 60 && strtCol > 0)
					{
						strtCol--;
						endCol--;
					}

					moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol < strtCol + 60 && strtCol > 0)
					{
						strtCol--;
						endCol--;
					}

					moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol < strtCol + 60 && strtCol > 0)
					{
						strtCol--;
						endCol--;
					}

					moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

					if (heroCol < strtCol + 60 && strtCol > 0)
					{
						strtCol--;
						endCol--;
					}

				}
				else
				{
					if (ctLeftJump < 8)
					{
						heroDir = 'A';

						if (world[heroRow + 14][heroCol] == ' ' && world[heroRow + 14][heroCol + 7] == ' ' && world[heroRow + 14][heroCol - 7] == ' ' && heroRow + 14 < 89 && heroRow + 14 < 59)
						{
							heroRow++;
						}

						moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

						if (heroCol < strtCol + 60 && strtCol > 0)
						{
							strtCol--;
							endCol--;
						}

						moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

						if (heroCol < strtCol + 60 && strtCol > 0)
						{
							strtCol--;
							endCol--;
						}

						moveHero(heroRow, heroCol, 'A', isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

						if (heroCol < strtCol + 60 && strtCol > 0)
						{
							strtCol--;
							endCol--;
						}


					}
					else
					{
						isHeroJumpingLeft = 0;
						ctLeftJump = 0;
						isHeroGoingDown = 1; // TO PREVENT MULTIPLE JUMPS (ComeHereGravity WILL RESET IT TO 0 AGAIN)
						heroDir = ' ';
					}
				}

				/////////////////////////////////////
				////  ELEVATOR ENTER LOGIC
				///////////////////////////////////

				if ((heroCurrFloor == 2 || heroCurrFloor == 3) && heroCol < 43 && elevatorRow > strtRow && heroRow >= elevatorRow && isHeroInElevator == 0 && ctLeftJump > 4)
				{
					if (heroCurrFloor == 2 && elevatorCurrFloor == 2)
					{
						isHeroInElevator = 1;
						heroCol = 17;
						heroRow = elevatorRow + 5;
						heroDir = ' ';
						isHeroJumpingLeft = 0;
						ctLeftJump = 0;

					}
					else
					{
						if (heroCurrFloor == 3 && elevatorCurrFloor == 3)
						{
							isHeroInElevator = 1;
							heroCol = 17;
							heroRow = elevatorRow + 5;
							heroDir = ' ';
							isHeroJumpingLeft = 0;
							ctLeftJump = 0;

						}
					}

				}

				///////////////////////////////////

				ctLeftJump++;
			}

			///////////////////////////////////

			if (isHeroOnLadder == 1)
			{
				heroDir = ' ';
			}

			if (isHeroInElevator == 1)
			{
				heroDir = ' ';

				moveHero(heroRow, heroCol, heroDir, isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRangeCol, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

				// SCROLLING

				if (heroRow < strtRow + 10 && strtRow > 0)
				{
					strtRow--;
					endRow--;
				}
				if (heroRow > strtRow + 10 && endRow < 60)
				{
					strtRow++;
					endRow++;
				}
			}

			/////////////////////////////////////
			////  LADDER ENTER LOGIC
			///////////////////////////////////

			if (isHeroOnLadder == 0 && heroCol > 330 && heroRow + 13 >= 45)
			{
				isHeroOnLadder = 1;
				heroCol = 345;

				if (heroRow < 45)
				{
					heroRow = 45;
				}
			}

			///////////////////////////////////

			if (isHeroInElevator == 0)
			{
				drawHero(heroRow, heroCol, heroDir, world);
			}

			drawWorldBorders(world, strtRow, endRow, strtCol, endCol);
			checkHeroCollisionWithSpike(heroRow, heroCol, heroLives, strtCol, endCol, FloorOne);
			drawHeroLives(strtRow, strtCol, heroLives, world);
			dispWorld(world, strtRow, endRow, strtCol, endCol);

			//Sleep(100);
		}


		heroDir = _getch();

		if ((heroDir == 'j' || heroDir == 'J') && isHeroJumping == 0 && isHeroDoubleJumping == 0 && isHeroJumpingRight == 0 && isHeroJumpingLeft == 0 && isHeroOnLadder == 0 && isHeroGoingDown == 0 && isHeroInElevator == 0)
		{
			isHeroJumping = 1;
			ctJump = 0;
		}

		if ((heroDir == 'k' || heroDir == 'K') && isHeroJumping == 0 && isHeroDoubleJumping == 0 && isHeroJumpingRight == 0 && isHeroJumpingLeft == 0 && isHeroOnLadder == 0 && isHeroGoingDown == 0 && isHeroInElevator == 0)
		{
			isHeroDoubleJumping = 1;
			ctDoubleJump = 0;
		}

		if ((heroDir == 'i' || heroDir == 'I') && isHeroJumping == 0 && isHeroDoubleJumping == 0 && isHeroJumpingRight == 0 && isHeroJumpingLeft == 0 && isHeroOnLadder == 0 && isHeroGoingDown == 0)
		{
			/////////////////////////////////////
			////  ELEVATOR EXIT LOGIC
			///////////////////////////////////

			if (isHeroInElevator == 1 && ((heroRow + 13 < 29 && heroRow > 0) || (heroRow + 13 < 59 && heroRow > 30)))
			{
				isHeroInElevator = 0;
				isHeroJumpingRight = 1;
				ctRightJump = 0;

				if (heroCurrFloor == 2)
				{
					strtRow = 30;
					endRow = 60;
				}
				if (heroCurrFloor == 3)
				{
					strtRow = 0;
					endRow = 30;
				}

				///////////////////////////////////
			}
			else
			{
				if (isHeroInElevator == 0)
				{
					isHeroJumpingRight = 1;
					ctRightJump = 0;
				}
			}
		}

		if ((heroDir == 'u' || heroDir == 'U') && isHeroJumping == 0 && isHeroDoubleJumping == 0 && isHeroJumpingRight == 0 && isHeroJumpingLeft == 0 && isHeroOnLadder == 0 && isHeroGoingDown == 0 && isHeroInElevator == 0)
		{
			isHeroJumpingLeft = 1;
			ctLeftJump = 0;
		}

		/////////////////////////////////////
		////  LADDER EXIT LOGIC
		///////////////////////////////////

		if ((heroDir == 'a' || heroDir == 'A' || heroDir == 'u' || heroDir == 'U') && isHeroOnLadder == 1 && ((heroRow > 60) || (heroRow <= 45 && heroRow + 13 <= 59)))
		{
			isHeroOnLadder = 0;

			if (heroRow >= 60)
			{
				heroCol = 330;

			}
			if (heroRow + 13 <= 59)
			{
				strtRow = 30;
				endRow = 60;

				heroCol = 330;
			}

			// AIM ASSIST FOR THE HERO
			prevHeroDir = 'A';

		}

		///////////////////////////////////

		if ((heroDir == 'n' || heroDir == 'N') && doYouWantSingleBullet == 0 && isHeroOnLadder == 0 && isHeroInElevator == 0)
		{
			isMultiBulletsActive = 0;
			for (int i = 0; i < 5; i++)
			{
				if (MultiBullets[i].IsActive == 1)
				{
					isMultiBulletsActive = 1;
				}
			}

			if (isMultiBulletsActive == 0)
			{
				doYouWantSingleBullet = 1;

				if (prevHeroDir == 'd' || prevHeroDir == 'D')
				{
					singleBulletCol = heroCol + 8;
					singleBulletRow = heroRow + 7;
				}
				else
				{
					if (prevHeroDir == 'a' || prevHeroDir == 'A')
					{
						singleBulletCol = heroCol - 8;
						singleBulletRow = heroRow + 7;
					}
				}
			}
		}


		if ((heroDir == 'm' || heroDir == 'M') && doYouWantSingleBullet == 0 && isHeroOnLadder == 0 && isHeroInElevator == 0)
		{
			activateMultiBullets(heroRow, heroCol, prevHeroDir, MultiBullets);
		}


		if ((heroDir == 'w' || heroDir == 'W' || heroDir == 's' || heroDir == 'S' || heroDir == 'a' || heroDir == 'A' || heroDir == 'd' || heroDir == 'D' || heroDir == 'j' || heroDir == 'J') && isHeroJumping == 0 && isHeroDoubleJumping == 0 && isHeroJumpingRight == 0 && isHeroJumpingLeft == 0 && (isHeroGoingDown == 0 || isHeroOnLadder == 1) && isHeroInElevator == 0)
		{
			moveHero(heroRow, heroCol, heroDir, isHeroOnLadder, isHeroInElevator, elevatorDir, elevatorRow, heroCurrFloor, isHeroJumpingLeft, strtRow, One, Two, Three, Four);

			// SCROLLING

			if (heroCol > strtCol + 60 && endCol < 360)
			{
				strtCol++;
				endCol++;
			}

			if (heroCol < strtCol + 60 && strtCol > 0)
			{
				strtCol--;
				endCol--;
			}

			if (heroRow < strtRow + 10 && strtRow > 0 && (isHeroOnLadder == 1 || isHeroInElevator == 1))
			{
				strtRow--;
				endRow--;
			}

			if (heroRow > strtRow + 10 && endRow < 90 && (isHeroOnLadder == 1 || isHeroInElevator == 1))
			{
				strtRow++;
				endRow++;
			}
		}
		else
		{
			heroDir = ' '; // TO DRAW HERO EVEN IF UNDEFINED KEY IS PRESSED
		}

		if ((heroDir == 'a' || heroDir == 'A' || heroDir == 'd' || heroDir == 'D') && doYouWantSingleBullet == 0)
		{
			prevHeroDir = heroDir;
		}
	}

	/////////////////////////////////////

	//////////////////////////////////////////////
	////  DELETING ALLOCATED MEMORY FROM HEAP
	////////////////////////////////////////////

	for (int i = 0; i < 90; i++)
	{
		delete[] world[i];
	}
	delete[] world;

	delete[] MultiBullets;
	delete[] EnemyBullets;

	delete[] Casper;

	delete[] Lasers;

	////////////////////////////////////////////

	return 0;
}
