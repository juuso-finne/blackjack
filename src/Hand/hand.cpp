#include <string>
#include "hand.h"

const float Hand::rotationAngle = 12.5f;

Hand::Hand()
{
    cards = std::vector<Card>();

    minScore = 0;
    hasAce = false;
    isActive = false;
}

void Hand::AddCard(Card c)
{
    cards.push_back(c);
}

void Hand::Update()
{
    if(cards.back().isFaceUp)
    {
        return;
    }

    cards.back().TurnFaceUp();
    int rank = cards.back().GetRank();
    minScore += rank > 10 ? 10 : rank;

    hasAce = hasAce || rank == 1;
}

void Hand::SetActive(bool a)
{
    isActive = a;
}

bool Hand::IsBlackJack()
{
    return cards.size() == 2 && GetScore() == 21;
}

bool Hand::IsBusted()
{
    return minScore > 21;
}

void Hand::Draw(Texture2D &spritesheet, Vector2 position)
{
    float startingAngle = -rotationAngle * (cards.size() - 1)/2.0f;

    for (size_t i = 0; i < cards.size(); i++)
    {
        cards[i].Draw(position, spritesheet, startingAngle + rotationAngle * i, isActive);
    }
    PrintScore(position);
}

void Hand::Discard(std::vector<Card> &discardPile)
{
    while(!cards.empty())
    {
        discardPile.push_back(cards.back());
        cards.pop_back();
    }
}

void Hand::PrintScore(Vector2 position)
{
    const int fontSize = 24;
    const float margin = Card::GetDimensions().x/2.0f;

    std::string stringTemplate = "";

    if (IsBusted())
    {
        stringTemplate = "Bust";
    }
    else if (IsBlackJack())
    {
        stringTemplate = "Blackjack!";
    }
    else
    {
        stringTemplate += std::to_string(minScore);
        stringTemplate += minScore != GetScore() ? " / " + std::to_string(GetScore()) : "";
    }

    const char* text = stringTemplate.c_str();

    Vector2 offset = {-MeasureText(text, fontSize)/2.0f, margin};
    Vector2 textPosition = Vector2Add(position, offset);

    Color col = isActive ? WHITE : DARKGRAY;

    DrawText(text, textPosition.x, textPosition.y, fontSize, col);

}

int Hand::GetScore()
{
    int output = minScore;

    if (hasAce && minScore <= 11){
        output += 10;
    }

    return output;
}
