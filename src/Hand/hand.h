#pragma once

#include<vector>
#include "../Card/card.h"

class Hand
{
    public:

        Hand(Vector2);

        void SetPosition(Vector2);
        void AddCard(Card);
        void Update();

        void SetActive(bool);

        bool IsBlackJack();
        bool IsBusted();
        int GetScore();

        void Draw(Texture2D &spritesheet);

        void Discard(std::vector<Card> &discardPile);

    private:
        Vector2 position;
        const float rotationAngle = 12.5f;

        std::vector<Card> cards;
        int minScore;
        bool hasAce;
        bool isActive;

};