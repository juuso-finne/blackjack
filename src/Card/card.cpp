#include "card.h"
#include <stdexcept>

float Card::spriteWidth = 75.0f;
float Card::spriteHeight = 112.0f;

const float scaling = 1.5f;

float Card::width = spriteWidth * scaling;
float Card::height = spriteHeight * scaling;

Card::Card(int aRank, Suit aSuit, bool isVisible)
{
    if(aRank < 1 || aRank > 13)
    {
        throw std::invalid_argument("Card.cpp: Card rank must be between 1 and 13 (incl.)");
    }

    rank = aRank;
    suit = aSuit;
    suitIndex = static_cast<int>(aSuit);

    isFaceUp = isVisible;
}

void Card::TurnFaceUp()
{
    isFaceUp = true;
}

void Card::TurnFaceDown()
{
    isFaceUp = false;
}

void Card::Draw(Vector2 position, const Texture2D &spritesheet, float rotation, bool active)
{
    float xOffset = (isFaceUp ? (float)(rank - 1) : 13.0f) * spriteWidth;
    float yOffset = (isFaceUp ? (float)suitIndex : 3.0f) * spriteHeight;

    Rectangle source = {xOffset, yOffset, spriteWidth, spriteHeight};
    Rectangle dest = {position.x, position.y, width, height};

    float pivotX = width/2.0f;
    Color col = active ? WHITE : DARKGRAY;

    DrawTexturePro(spritesheet, source, dest, {pivotX, height}, rotation, col);
}

int Card::GetRank()
{
    return rank;
}

Vector2 Card::GetDimensions()
{
    return {width, height};
}