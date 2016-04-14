/*
ECE 114 L - 01
Dr. Chandra
Fall 2013
12/6/13
Project #2: Knight's Tour
- Byron Phung
- Gregory Lynch
- Jenwinn Baltazar
*/

#include "stdafx.h"
#include <iostream>
#include <iomanip>
using namespace std;

const int boardSize = 8;
const int maxMoves = boardSize * boardSize;
int board[boardSize][boardSize] = { 0 };
int move1[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
int move2[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };
int numPossibilities = 0;
int tempI, tempJ, nextI[8], nextJ[8];
int exits[8];
int checkI, checkJ, minValExits;
int i, j, k;

void setStart();
void checkPossibleMoves();
void checkExits();
void findMinExits(int);
void checkMinExits(int, int);
void moveKnight(int);
void print();

void main() {
	setStart();

	for (int m = 2; m <= maxMoves; m++, numPossibilities = 0) {
		checkPossibleMoves();

		switch (numPossibilities) {
		case 0: // The tour came to a premature end.
			cout << endl; // Space out the message.
			cout << "The knight's tour at this location ended prematurely.";
			cout << endl; // Space out the message.
			m = maxMoves; // Exit by skipping to the last move.
			break;
		case 1:
			minValExits = 0; // There is only one possibility for the next move.
			break;
		default: // Find the next squares with the minimum number of exits.
			findMinExits(numPossibilities);
			checkMinExits(m, numPossibilities);
		}

		moveKnight(m);
	}

	print();
}

/*
This function reads the user-defined starting row & column and
sets the knight in that location for the program to follow.
*/
void setStart() {
	int check = 0;
	while (check == 0) { // Ensure values are between 1 & the board size.
		cout << "Please specify i & j (row column): ";
		cin >> i >> j;
		if (1 <= i && i <= boardSize && 1 <= j && j <= boardSize) {
			board[i - 1][j - 1] = 1; // Set the initial position as 1.
			check = 1; // Exit the check loop.
		}

		else {
			cout << endl << " ~ Please input values between 1 & "
				<< boardSize << "." << endl << endl;
		}
	}
}

/*
This function forms a set of possible next squares and checks it
to determine which moves are valid to be stored within an array
of only the next possible moves.
*/
void checkPossibleMoves() {
	for (k = 0; k < boardSize; k++) { // Check all 8 possible moves.
		tempI = i + move1[k]; // Check next move without storing it
		tempJ = j + move2[k]; // until it satisfies the proper conditions.
		if (tempI >= 1 && tempI <= boardSize
			&& tempJ >= 1 && tempJ <= boardSize
			&& board[tempI - 1][tempJ - 1] == 0) {
			nextI[numPossibilities] = tempI;
			nextJ[numPossibilities] = tempJ;
			numPossibilities++;
		}
	}
}

/*
By Warnsdorff's Rule, the most efficient algorithm for a knight's tour
of this small degree is to find the minimum number of exits for the next
move of the stored possible next moves.
*/
void findMinExits(int numPossibilities) {
	for (int n = 1, numExits = 0; n <= numPossibilities; n++, numExits = 0) {
		for (int y = 0; y < boardSize; y++) {
			// Check exits of the move after the next move.
			checkI = nextI[n - 1] + move1[y];
			checkJ = nextJ[n - 1] + move2[y];
			if (checkI >= 1 && checkI <= boardSize
				&& checkJ >= 1 && checkJ <= boardSize
				&& board[checkI - 1][checkJ - 1] == 0) {
				numExits++; // Increment if unused and on the board.
			}
		}
		exits[n - 1] = numExits; // Assign exit values to an array.
	}
}

/*
This function employs the number of exits stored from the above function
to determine which is the smallest to ultimately decide the knight's
next move.
*/
void checkMinExits(int m, int numPossibilities) {
	int z, ans, smallestPosition;

	for (z = 0, ans = exits[0], smallestPosition = 0; z < numPossibilities; z++) {
		if (ans > exits[z]) { // Check for the minimum exit ocurrence.
			ans = exits[z];
			smallestPosition = z;
		}
	}
	minValExits = smallestPosition;
}

void moveKnight(int moveNumber) {
	i = nextI[minValExits];
	j = nextJ[minValExits];
	board[i - 1][j - 1] = moveNumber;
}

void print() {
	// Determine the number of digits of the maximum number of moves
	// so that the setw can print 1 space between each printout.
	for (k = 0; maxMoves - pow(10.0, k) >= 0; k++);

	cout << endl; // Spacing out the grid.

	for (i = 0; i < boardSize; i++) {
		for (j = 0; j < boardSize; j++) {
			cout << setw(k + 1) << board[i][j];
		}
		cout << endl;
	}

	cout << endl; // Spacing out the grid.
}