#pragma once
#include <raylib.h>
#include <raymath.h>

enum Suit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

class Card
{
    public:
        Card(int aRank, Suit aSuit, bool aIsVisible = false);

        void TurnFaceUp();
        void TurnFaceDown();

        void Draw(Vector2 position, const Texture2D &spritesheet, float rotation, bool active = true);

        int GetRank();

        static Vector2 GetDimensions();
        bool isFaceUp;

    protected:
        int rank;
        int suitIndex;

        Suit suit;

        static float spriteWidth;
        static float spriteHeight;

        static float width;
        static float height;
};