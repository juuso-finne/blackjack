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

        const void Draw(Vector2 position, const Texture2D &spritesheet, float rotation, bool active = true);

        const int GetRank();

        static const Vector2 GetDimensions();
        bool isFaceUp;

    protected:
        int rank;
        int suitIndex;

        Suit suit;

        static const float spriteWidth;
        static const float spriteHeight;

        static const float width;
        static const float height;
};