#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>
double lastUpdaeTime = 0;
bool eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdaeTime >= interval)
    {
        lastUpdaeTime = currentTime;
        return true;
    }
    return false;
}
int main()
{

    Color darkBlue = {44, 44, 127, 255};
    InitWindow(500, 620, "Tetris"); // initialize the window;
    SetTargetFPS(60);
    Font font = LoadFontEx("Fonts/Monogram.ttf", 64, 0, 0);

    Game game = Game();
    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.handleInput();
        if (!game.isPaused)
        {
            if (eventTriggered(0.5))
            {
                game.MoveBlockDown();
            }
        }
        BeginDrawing(); // creates a blank canvas;
                        // struct Color={red,green, blue, alpha};  alpha =transpancy 255= opaque'

        ClearBackground(darkBlue);
        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
        if (game.isPaused)
        {
            DrawTextEx(font, "PAUSED", {320, 450}, 30, 2, WHITE);
        }
        if (game.isPaused)
        {
            PauseMusicStream(game.music);
        }
        else
        {
            ResumeMusicStream(game.music);
            UpdateMusicStream(game.music);
        }
        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 30, 2, WHITE);
        }
        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        char scoreText[10];
        sprintf(scoreText, "%d", game.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText, {320 + (170 - textSize.x) / 2, 65}, 38, 2, WHITE);
        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);
        game.Draw();

        EndDrawing();
    }
    CloseWindow();
}
