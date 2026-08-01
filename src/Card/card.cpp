#include "card.h"
#include <stdexcept>
#include <raymath.h>

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
    float xOffset = (isFaceUp ? (float)(rank - 1) : 13.0) * spriteWidth;
    float yOffset = (isFaceUp ? (float)suitIndex : 3.0) * spriteHeight;

    Rectangle source = {xOffset, yOffset, spriteWidth, spriteHeight};
    Rectangle dest = {position.x, position.y, width, height};

    float pivotX = width/2.0f;

    Color col = active ? WHITE : DARKGRAY;


    DrawTexturePro(spritesheet, source, dest, {pivotX, height}, rotation, col);
}

Suit Card::GetSuit()
{
    return suit;
}

int Card::GetRank()
{
    return rank;
}

int Card::GetSuitIndex()
{
    return suitIndex;
}

Vector2 Card::GetDimensions()
{
    return {width, height};
}

Rectangle Card::GetHitBox(Vector2 position)
{
    float x = position.x + width / 4.0f;
    float y = position.y + height / 4.0f;
    return {x, y, width / 2.0F, height / 2.0f};
}

/**  Whether or not other card can be placed on top of this card */
bool Card::CheckAccommodation(const Card &other)
{
    bool isOtherBlack = other.suit == Suit::CLUBS || other.suit == Suit::SPADES;
    bool isThisBlack = suit == Suit::CLUBS || suit == Suit::SPADES;

    if(isOtherBlack == isThisBlack){
        return false;
    }

    return other.rank + 1 == rank;
}
