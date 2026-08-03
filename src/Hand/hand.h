#pragma once

#include<vector>
#include "../Card/card.h"

class Hand
{
    public:

        Hand();

        void AddCard(Card);
        void Update();

        void SetActive(bool);

        bool IsBlackJack();
        bool IsBusted();
        int GetScore();

        void Draw(Texture2D &, Vector2);

        void Discard(std::vector<Card> &);

    private:
        static const float rotationAngle;

        std::vector<Card> cards;
        int minScore;
        bool hasAce;
        bool isActive;

        void PrintScore(Vector2);
};