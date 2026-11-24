#include "raylib.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

const int MAX_ROWS = 16;
const int MAX_COLS = 30;

int ROWS = 9;
int COLS = 9;
int MINES = 10;
int TILE_SIZE = 50;
int difficulty = 1;

int board[MAX_ROWS][MAX_COLS] = { 0 };
bool revealed[MAX_ROWS][MAX_COLS] = { false };
bool flagged[MAX_ROWS][MAX_COLS] = { false };

bool gameOver = false;
bool gameWon = false;

int flagsPlaced = 0;
float startTime = 0;
float elapsedTime = 0;

Texture2D bombTexture;
Texture2D flagTexture;
Texture2D explosionTexture;

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
    startTime = (float)GetTime();
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

                    if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLS)
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

void setDifficulty()
{
    if (difficulty == 1)
    {
        ROWS = 9;
        COLS = 9;
        MINES = 10;
        TILE_SIZE = 50;
    }
    else if (difficulty == 2)
    {
        ROWS = 16;
        COLS = 16;
        MINES = 40;
        TILE_SIZE = 40;
    }
    else if (difficulty == 3)
    {
        ROWS = 16;
        COLS = 30;
        MINES = 99;
        TILE_SIZE = 32;
    }
}

int main()
{
    srand(time(0));

    int windowWidth = 1100;
    int windowHeight = 750;

    InitWindow(windowWidth, windowHeight, "Minesweeper");
    bombTexture = LoadTexture("bomb.png");
    flagTexture = LoadTexture("flag.png");
    explosionTexture = LoadTexture("explosion_spritesheet.png");
    startTime = (float)GetTime();
    elapsedTime = 0;

    SetTargetFPS(60);

    int startX = 0;
    int startY = 0;
    bool showStartMenu = true;

    while (!WindowShouldClose())
    {
        if (showStartMenu)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                Vector2 mouse = GetMousePosition();
                
                Rectangle beginnerButton = { 400, 250, 300, 70 };
                Rectangle intermediateButton = { 400, 350, 300, 70 };
                Rectangle expertButton = { 400, 450, 300, 70 };

                if (CheckCollisionPointRec(mouse, beginnerButton))
                {
                    difficulty = 1;
                }
                else if (CheckCollisionPointRec(mouse, intermediateButton))
                {
                    difficulty = 2;
                }
                else if (CheckCollisionPointRec(mouse, expertButton))
                {
                    difficulty = 3;
                }
                else
                {
                    difficulty = 0;
                }

                if (difficulty != 0)
                {
                    setDifficulty();
                    resetGame();

                    startX = (windowWidth - COLS * TILE_SIZE) / 2;
                    startY = 90;

                    showStartMenu = false;
                }
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            
            DrawText("MINESWEEPER", 350, 100, 50, DARKBLUE);
            DrawText("CHOOSE DIFFICULTY", 410, 190, 25, DARKGRAY);
            
            DrawRectangle(400, 250, 300, 70, DARKGREEN);
            DrawText("BEGINNER", 480, 272, 25, WHITE);

            DrawRectangle(400, 350, 300, 70, BLUE);
            DrawText("INTERMEDIATE", 435, 372, 25, WHITE);

            DrawRectangle(400, 450, 300, 70, MAROON);
            DrawText("EXPERT", 490, 472, 25, WHITE);

            EndDrawing();
            continue;
        }
        // LEFT CLICK
        if (!gameOver && !gameWon && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();

            int col = (mousePosition.x - startX) / TILE_SIZE;
            int row = (mousePosition.y - startY) / TILE_SIZE;

            if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
            {
                if (!flagged[row][col] && !revealed[row][col])
                {
                    if (board[row][col] == -1)
                    {
                        gameOver = true;
                        revealed[row][col] = true;
                    }
                    else
                    {
                        revealTile(row, col);
                    }
                }
            }
        }
        // RIGHT CLICK
        if (!gameOver && !gameWon && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Vector2 mousePosition = GetMousePosition();

            int col = (mousePosition.x - startX) / TILE_SIZE;
            int row = (mousePosition.y - startY) / TILE_SIZE;

            if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
            {
                if (!revealed[row][col])
                {
                    if (flagged[row][col])
                    {
                        flagged[row][col] = false;
                        flagsPlaced--;
                    }
                    else if (flagsPlaced < MINES)
                    {
                        flagged[row][col] = true;
                        flagsPlaced++;
                    }
                }
            }
        }
        
        // CHECK WIN CONDITION
        if (!gameOver && !gameWon)
        {
            int safeTiles = 0;

            for (int row = 0; row < ROWS; row++)
            {
                for (int col = 0; col < COLS; col++)
                {
                    if (revealed[row][col] && board[row][col] != -1)
                    {
                        safeTiles++;
                    }
                }
            }

            if (safeTiles == ROWS * COLS - MINES)
            {
                gameWon = true;
            }
        }
        
        // RESTART OPTION
        if ((gameOver || gameWon) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int buttonX = (windowWidth - 160) / 2;
            int buttonY = windowHeight - 65;
            Rectangle restartButton = {
            (float)buttonX,
            (float)buttonY,
            160,
            45
        };
            if (CheckCollisionPointRec(mousePosition, restartButton))
            {
                resetGame();
            }
        }
        if (!gameOver && !gameWon)
        {
            elapsedTime = GetTime() - startTime;
        }
       
        // DRAW EVERYTHING
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                int x = startX + col * TILE_SIZE;
                int y = startY + row * TILE_SIZE;

                if (revealed[row][col])
                {
                    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, WHITE);
                                        if (board[row][col] == -1)
                    {
                        DrawTexturePro(
                            bombTexture,
                            { 0, 0, (float)bombTexture.width, (float)bombTexture.height },
                            { (float)x + 3, (float)y + 3, (float)TILE_SIZE - 6, (float)TILE_SIZE - 6 },
                            { 0, 0 },
                            0,
                            WHITE
                        );
                    }
                    else if (board[row][col] > 0)
                    {
                        Color numberColor = BLUE;
                        if (board[row][col] == 2)
                            numberColor = GREEN;
                        else if (board[row][col] == 3)
                            numberColor = RED;
                        else if (board[row][col] == 4)
                            numberColor = DARKBLUE;
                        else if (board[row][col] >= 5)
                            numberColor = MAROON;

                        int fontSize = (TILE_SIZE * 3)/ 5;
                        const char* number = TextFormat("%d", board[row][col]);
                        int textWidth = MeasureText(number, fontSize);

                        DrawText(number,
                            x + (TILE_SIZE - textWidth) / 2,
                            y + (TILE_SIZE - fontSize) / 2,
                            fontSize, numberColor);
                    }
                }
                else
                {
                    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, LIGHTGRAY);

                    if (flagged[row][col])
                    {
                        DrawTexturePro(
                            flagTexture,
                            { 0, 0, (float)flagTexture.width, (float)flagTexture.height },
                            { (float)x + 3, (float)y + 3, (float)TILE_SIZE - 6, (float)TILE_SIZE - 6 },
                            { 0, 0 },
                            0,
                            WHITE
                        );
                    }
                }

                DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
            }
        }
        
        DrawText(TextFormat("Time: %d", (int)elapsedTime), 20, 15, 20, BLACK);

        if (gameWon)
        {
            DrawText("YOU WIN!", windowWidth / 2 - 70, 15, 30, GREEN);
        }

        if (gameOver)
        {
            DrawText("GAME OVER!", windowWidth / 2 - 95, 15, 30, RED);
        }

        // COUNT CORRECTLY PLACED FLAGS
        int correctFlags = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (flagged[row][col] && board[row][col] == -1)
                {
                    correctFlags++;
                }
            }
        }

        // FLAGS REMAINING
        const char* flagsText = TextFormat("Flags remaining: %d", MINES - flagsPlaced);
        DrawText(flagsText, windowWidth - MeasureText(flagsText, 20) - 20, 12, 20, BLACK);

        // MINES REMAINING
        const char* minesText = TextFormat("Mines remaining: %d", MINES - correctFlags);
        DrawText(minesText, windowWidth - MeasureText(minesText, 20) - 20, 38, 20, BLACK);

        if (gameOver || gameWon)
        {
            int buttonX = (windowWidth - 160) / 2;
            int buttonY = windowHeight - 65;

            DrawRectangle(buttonX, buttonY, 160, 45, DARKGREEN);
            DrawText("RESTART", buttonX + 30, buttonY + 12, 20, WHITE);
        }
            
        EndDrawing();
    }
    UnloadTexture(bombTexture);
    UnloadTexture(flagTexture);
    UnloadTexture(explosionTexture);
    
    CloseWindow();

    return 0;
}
