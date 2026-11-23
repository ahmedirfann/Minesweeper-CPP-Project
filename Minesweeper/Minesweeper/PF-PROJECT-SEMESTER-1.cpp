#include <iostream>
#include<cstdlib>
#include<ctime>
#include"raylib.h"
using namespace std;
// first of all i am going to add the Grid using 2D arrays.
const int ROWS = 5;
const int COLS = 5;
int NUM_MINES = 3;
void player(int x, int y);
void gridcreation(char grid[ROWS][COLS]) {
	for (int i = 0;i < ROWS;i++) {
		for (int j = 0;j < COLS;j++) {
			grid[i][j] = '.';
		}
	}
}
void placemines(char grid[ROWS][COLS]) {
	int count = 0;
	while (count < NUM_MINES) {
		int r = rand() % ROWS;
		int c = rand() % COLS;
		if (grid[r][c] != '*') {
			grid[r][c] = '*';
			count++;
		}
	}
}
void displayboard(char grid[ROWS][COLS]) {
	cout << "\n   ";
	for (int j = 0;j < COLS;j++) {
		cout << j << " ";
	}
	cout << "\n------------\n";

	for (int i = 0;i < ROWS;i++) {
		cout << i << " ";
		cout << "|";
		for (int j = 0;j < COLS;j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}
int countadjacentMines(char mineboard[ROWS][COLS], int r, int c) {
	int minecount = 0;
	for (int i = -1;i <= 1;i++) {
		for (int j = -1;j <= 1;j++) {
			int newRow = r + i;
			int newCol = c + j;
			if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS) {
				if (mineboard[newRow][newCol] == '*') {
					minecount++;
				}
			}
		}
	}
	return minecount;
}
int main() {
	srand(time(0));
	char mineboard[ROWS][COLS];
	gridcreation(mineboard);
	placemines(mineboard);
	char playerboard[ROWS][COLS];
	gridcreation(playerboard);
	int revealedCells = 0;
	int safecellstowin = (ROWS * COLS) - NUM_MINES;
	bool gameover = false;
	while (!gameover) {
		displayboard(playerboard);
		int r, c;
		cout << "Enter Rows from 0 to 4 and Colomns from 0 to 4:";
		cin >> r >> c;
		if (r < 0 || r >= ROWS || c < 0 || c >= COLS) {
			cout << "Invalid Coordinates:" << endl;
			continue;
		}
		if (mineboard[r][c] == '*') {
			cout << "\nBoom! you hit a mine! Game Over.\n";
			displayboard(mineboard);
			gameover = true;
		}
		else {
			int adjacentmines = countadjacentMines(mineboard, r, c);
			playerboard[r][c] = (char)(adjacentmines + '0');
			revealedCells++;
			if (revealedCells == safecellstowin) {
				cout << "Congratulations! you won the game" << endl;
				displayboard(mineboard);
				gameover = true;
			}
		}
	}
	return 0;
}