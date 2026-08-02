#include "hand.h"

Hand::Hand(Vector2 aPosition)
{
    cards = std::vector<Card>();
    SetPosition(aPosition);

    minScore = 0;
    hasAce = false;
    isActive = false;
}

void Hand::SetPosition(Vector2 aPosition)
{
    position = aPosition;
}

void Hand::AddCard(Card c)
{
    cards.push_back(c);
}

void Hand::Update()
{
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

void Hand::Draw(Texture2D &spritesheet)
{
    float startingAngle = -rotationAngle * (cards.size() - 1)/2.0f;

    for (size_t i = 0; i < cards.size(); i++)
    {
        cards[i].Draw(position, spritesheet, startingAngle + rotationAngle * i, isActive);
    }
}

void Hand::Discard(std::vector<Card> &discardPile)
{
    while(!cards.empty())
    {
        discardPile.push_back(cards.back());
        cards.pop_back();
    }
}

int Hand::GetScore()
{
    int output = minScore;

    if (hasAce && minScore <= 11){
        output += 10;
    }

    return output;
}
