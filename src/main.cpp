#include <raylib.h>
#include "Card/card.h"
#include "Hand/hand.h"

int main()
{
    constexpr int screenWidth = 1600;
    constexpr int screenHeight = 900;

    InitWindow(screenWidth, screenHeight, "BlackJack");
    SetTargetFPS(60);

    Texture2D cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");

    Hand h = Hand({200,200});
    h.SetActive(true);

    Card c1 = Card(5, HEARTS);
    Card c2 = Card(12, CLUBS);
    Card c3 = Card(13, DIAMONDS);

    h.AddCard(c1);
    h.Update();
    h.AddCard(c2);
    h.Update();
    h.AddCard(c3);
    h.Update();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        h.Draw(cardSpriteSheet);
        EndDrawing();
    }

    CloseWindow();
}