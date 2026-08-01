#include <raylib.h>
#include "Card/card.h"

int main()
{
    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "BlackJack");
    SetTargetFPS(60);

    Texture2D cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");

    Card c = Card(7,Suit::HEARTS, true);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        c.Draw({168,200}, cardSpriteSheet, -90.0f, false);
        c.Draw({168,200}, cardSpriteSheet, 90.0f, false);
        c.Draw({504,200}, cardSpriteSheet, -90.0f);
        c.Draw({504,200}, cardSpriteSheet, 90.0f);
        c.Draw({840,200}, cardSpriteSheet, 90.0f, false);
        c.Draw({840,200}, cardSpriteSheet, -90.0f, false);
        c.Draw({1176,200}, cardSpriteSheet, 90.0f, false);
        c.Draw({1176,200}, cardSpriteSheet, -90.0f, false);
        EndDrawing();
    }

    CloseWindow();
}