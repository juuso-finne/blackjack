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

    Card c1 = Card(7, HEARTS);
    Card c2 = Card(1, CLUBS, true);
    Card c3 = Card(13, DIAMONDS);

    h.AddCard(c1);
    h.Update();
    h.AddCard(c2);
    h.Update();
    h.AddCard(c3);
    h.Update();
    h.AddCard(c3);
    h.Update();
    h.AddCard(c3);
    h.Update();
    h.AddCard(c3);
    h.Update();
    h.AddCard(c3);
    h.Update();
    h.AddCard(c3);
    h.Update();
    h.AddCard(c3);
    h.Update();
    h.AddCard(c3);
    h.Update();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        c2.Draw({200,200}, cardSpriteSheet, -90.0f);
        h.Draw(cardSpriteSheet);
        EndDrawing();
    }

    CloseWindow();
}