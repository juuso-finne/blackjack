#include <raylib.h>
#include "Card/card.h"
#include "Game/game.h"

int main()
{
    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "BlackJack");
    SetTargetFPS(60);

    Game game = Game();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGREEN);
        game.Draw();
        game.Update();
        EndDrawing();
    }

    CloseWindow();
}