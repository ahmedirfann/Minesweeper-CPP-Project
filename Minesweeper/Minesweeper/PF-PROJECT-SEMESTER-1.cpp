//
//#include "raylib.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//using namespace std;
//
//const int MAX_ROWS = 16;
//const int MAX_COLS = 30;
//
//int ROWS = 9;
//int COLS = 9;
//int MINES = 10;
//
//int TILE_SIZE = 50;
//
//int board[MAX_ROWS][MAX_COLS] = { 0 };
//bool revealed[MAX_ROWS][MAX_COLS] = { false };
//bool flagged[MAX_ROWS][MAX_COLS] = { false };
//
//bool gameOver = false;
//bool gameWon = false;
//
//int flagsPlaced = 0;
//
//float startTime = 0;
//float elapsedTime = 0;
//
//void revealTile(int row, int col)
//{
//    if (row < 0 || row >= ROWS ||
//        col < 0 || col >= COLS)
//    {
//        return;
//    }
//
//    if (revealed[row][col] || flagged[row][col])
//    {
//        return;
//    }
//
//    if (board[row][col] == -1)
//    {
//        return;
//    }
//
//    revealed[row][col] = true;
//
//    if (board[row][col] == 0)
//    {
//        for (int i = -1; i <= 1; i++)
//        {
//            for (int j = -1; j <= 1; j++)
//            {
//                if (i != 0 || j != 0)
//                {
//                    revealTile(row + i, col + j);
//                }
//            }
//        }
//    }
//}
//
//void resetGame()
//{
//    // Reset board and game variables
//
//    for (int row = 0; row < ROWS; row++)
//    {
//        for (int col = 0; col < COLS; col++)
//        {
//            board[row][col] = 0;
//            revealed[row][col] = false;
//            flagged[row][col] = false;
//        }
//    }
//
//    startTime = GetTime();
//    elapsedTime = 0;
//
//    gameOver = false;
//    gameWon = false;
//    flagsPlaced = 0;
//
//    // Place new mines
//
//    int minesPlaced = 0;
//
//    while (minesPlaced < MINES)
//    {
//        int row = rand() % ROWS;
//        int col = rand() % COLS;
//
//        if (board[row][col] != -1)
//        {
//            board[row][col] = -1;
//            minesPlaced++;
//        }
//    }
//
//    // Calculate neighbouring mines
//
//    for (int row = 0; row < ROWS; row++)
//    {
//        for (int col = 0; col < COLS; col++)
//        {
//            if (board[row][col] == -1)
//            {
//                continue;
//            }
//
//            int count = 0;
//
//            for (int i = -1; i <= 1; i++)
//            {
//                for (int j = -1; j <= 1; j++)
//                {
//                    int newRow = row + i;
//                    int newCol = col + j;
//
//                    if (newRow >= 0 && newRow < ROWS &&
//                        newCol >= 0 && newCol < COLS)
//                    {
//                        if (board[newRow][newCol] == -1)
//                        {
//                            count++;
//                        }
//                    }
//                }
//            }
//
//            board[row][col] = count;
//        }
//    }
//}
//
//int main()
//{
//    srand(time(0));
//
//    int minesPlaced = 0;
//
//    while (minesPlaced < MINES)
//    {
//        int row = rand() % ROWS;
//        int col = rand() % COLS;
//
//        if (board[row][col] != -1)
//        {
//            board[row][col] = -1;
//            minesPlaced++;
//        }
//    }
//
//    // Calculate neighbouring mines
//
//    for (int row = 0; row < ROWS; row++)
//    {
//        for (int col = 0; col < COLS; col++)
//        {
//            if (board[row][col] == -1)
//            {
//                continue;
//            }
//
//            int count = 0;
//
//            for (int i = -1; i <= 1; i++)
//            {
//                for (int j = -1; j <= 1; j++)
//                {
//                    int newRow = row + i;
//                    int newCol = col + j;
//
//                    if (newRow >= 0 && newRow < ROWS &&
//                        newCol >= 0 && newCol < COLS)
//                    {
//                        if (board[newRow][newCol] == -1)
//                        {
//                            count++;
//                        }
//                    }
//                }
//            }
//
//            board[row][col] = count;
//        }
//    }
//    //////////////////////////////////////////////////////////////////////////////////////////////
//
//    int windowWidth = COLS * TILE_SIZE + 150;
//    int windowHeight = ROWS * TILE_SIZE + 150;
//
//    InitWindow(windowWidth, windowHeight, "Minesweeper");
//    SetTargetFPS(60);
//
//    int startX = (windowWidth - COLS * TILE_SIZE) / 2;
//    int startY = (windowHeight - ROWS * TILE_SIZE) / 2;
//    ///////////////////////////////////////////////////////////////////////////////////
//    while (!WindowShouldClose())
//    {
//        // LEFT CLICK
//
//        if (!gameOver && !gameWon &&
//            IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//        {
//            Vector2 mousePosition = GetMousePosition();
//
//            int col = (mousePosition.x - startX) / TILE_SIZE;
//            int row = (mousePosition.y - startY) / TILE_SIZE;
//
//            if (row >= 0 && row < ROWS &&
//                col >= 0 && col < COLS)
//            {
//                if (!flagged[row][col] && !revealed[row][col])
//                {
//                    if (board[row][col] == -1)
//                    {
//                        gameOver = true;
//                        revealed[row][col] = true;
//                    }
//                    else
//                    {
//                        revealTile(row, col);
//                    }
//                }
//            }
//        }
//
//        // RIGHT CLICK
//
//        if (!gameOver && !gameWon &&
//            IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
//        {
//            Vector2 mousePosition = GetMousePosition();
//
//            int col = (mousePosition.x - startX) / TILE_SIZE;
//            int row = (mousePosition.y - startY) / TILE_SIZE;
//
//            if (row >= 0 && row < ROWS &&
//                col >= 0 && col < COLS)
//            {
//                if (!revealed[row][col])
//                {
//                    if (flagged[row][col])
//                    {
//                        flagged[row][col] = false;
//                        flagsPlaced--;
//                    }
//                    else if (flagsPlaced < MINES)
//                    {
//                        flagged[row][col] = true;
//                        flagsPlaced++;
//                    }
//                }
//            }
//        }
//
//        startTime = GetTime();
//
//        // CHECK WIN CONDITION
//
//        if (!gameOver && !gameWon)
//        {
//            int safeTiles = 0;
//
//            for (int row = 0; row < ROWS; row++)
//            {
//                for (int col = 0; col < COLS; col++)
//                {
//                    if (revealed[row][col] && board[row][col] != -1)
//                    {
//                        safeTiles++;
//                    }
//                }
//            }
//
//            if (safeTiles == ROWS * COLS - MINES)
//            {
//                gameWon = true;
//            }
//        }
//
//        // RESTART OPTION
//
//        if ((gameOver || gameWon) &&
//            IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
//        {
//            Vector2 mousePosition = GetMousePosition();
//
//            if (mousePosition.x >= 220 && mousePosition.x <= 380 &&
//                mousePosition.y >= 490 && mousePosition.y <= 535)
//            {
//                resetGame();
//            }
//        }
//
//        if (!gameOver && !gameWon)
//        {
//            elapsedTime = GetTime() - startTime;
//        }
//        ////////////////////////////////////////////////////////////////////////////////////////////////////////
//                // DRAW EVERYTHING
//
//        BeginDrawing();
//
//        ClearBackground(RAYWHITE);
//
//        for (int row = 0; row < ROWS; row++)
//        {
//            for (int col = 0; col < COLS; col++)
//            {
//                int x = startX + col * TILE_SIZE;
//                int y = startY + row * TILE_SIZE;
//
//                if (revealed[row][col])
//                {
//                    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, WHITE);
//
//                    if (board[row][col] > 0)
//                    {
//                        Color numberColor = BLUE;
//
//                        if (board[row][col] == 2)
//                            numberColor = GREEN;
//                        else if (board[row][col] == 3)
//                            numberColor = RED;
//                        else if (board[row][col] == 4)
//                            numberColor = DARKBLUE;
//                        else if (board[row][col] >= 5)
//                            numberColor = MAROON;
//
//                        DrawText(TextFormat("%d", board[row][col]),
//                            x + 18, y + 12, 25, numberColor);
//                    }
//
//                    if (board[row][col] == -1)
//                    {
//                        DrawText("*", x + 17, y + 10, 30, RED);
//                    }
//                }
//                else
//                {
//                    DrawRectangle(x, y, TILE_SIZE, TILE_SIZE, LIGHTGRAY);
//                }
//
//                if (flagged[row][col])
//                {
//                    DrawText("F", x + 17, y + 10, 30, RED);
//                }
//
//                DrawRectangleLines(x, y, TILE_SIZE, TILE_SIZE, DARKGRAY);
//            }
//        }
//
//        DrawText(TextFormat("Time: %d", (int)elapsedTime),
//            250, 20, 20, BLACK);
//
//        if (gameWon)
//        {
//            DrawText("YOU WIN!", 220, 25, 30, GREEN);
//        }
//
//        if (gameOver)
//        {
//            DrawText("GAME OVER!", 190, 25, 30, RED);
//        }
//
//        if (gameOver || gameWon)
//        {
//            DrawRectangle(220, 490, 160, 45, DARKGREEN);
//            DrawText("RESTART", 250, 502, 20, WHITE);
//        }
//
//        DrawText(TextFormat("Mines remaining: %d",
//            MINES - flagsPlaced), 180, 550, 20, BLACK);
//
//        EndDrawing();
//    }
//
//    CloseWindow();
//
//    return 0;
//}
