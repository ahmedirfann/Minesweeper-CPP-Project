#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_ROWS = 16;
const int MAX_COLS = 30;

int ROWS = 9;
int COLS = 9;
int MINES = 10;

int TILE_SIZE = 50;

int board[MAX_ROWS][MAX_COLS] = { 0 };
bool revealed[MAX_ROWS][MAX_COLS] = { false };
bool flagged[MAX_ROWS][MAX_COLS] = { false };

bool gameOver = false;
bool gameWon = false;

int flagsPlaced = 0;

float startTime = 0;
float elapsedTime = 0;

void revealTile(int row, int col)
{
    if (row < 0 || row >= ROWS ||
        col < 0 || col >= COLS)
    {
        return;
    }

    if (revealed[row][col] || flagged[row][col])
    {
        return;
    }

    if (board[row][col] == -1)
    {
        return;
    }

    revealed[row][col] = true;

    if (board[row][col] == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                if (i != 0 || j != 0)
                {
                    revealTile(row + i, col + j);
                }
            }
        }
    }
}
void resetGame()

{
    // Reset board and game variables

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            board[row][col] = 0;
            revealed[row][col] = false;
            flagged[row][col] = false;
        }
    }
    startTime = GetTime();
    elapsedTime = 0;

    gameOver = false;
    gameWon = false;
    flagsPlaced = 0;

    // Place new mines

    int minesPlaced = 0;

    while (minesPlaced < MINES)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;

        if (board[row][col] != -1)
        {
            board[row][col] = -1;
            minesPlaced++;
        }
    }
    // Calculate neighbouring mines

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (board[row][col] == -1)
            {
                continue;
            }

            int count = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < ROWS &&
                        newCol >= 0 && newCol < COLS)
                    {
                        if (board[newRow][newCol] == -1)
                        {
                            count++;
                        }
                    }
                }
            }

            board[row][col] = count;
        }
    }
}
int main()
{
    srand(time(0));

    int minesPlaced = 0;

    while (minesPlaced < MINES)
    {
        int row = rand() % ROWS;
        int col = rand() % COLS;

        if (board[row][col] != -1)
        {
            board[row][col] = -1;
            minesPlaced++;
        }
    }

    // Calculate neighbouring mines

    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (board[row][col] == -1)
            {
                continue;
            }

            int count = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    int newRow = row + i;
                    int newCol = col + j;

                    if (newRow >= 0 && newRow < ROWS &&
                        newCol >= 0 && newCol < COLS)
                    {
                        if (board[newRow][newCol] == -1)
                        {
                            count++;
                        }
                    }
                }
            }

            board[row][col] = count;
        }
    }







