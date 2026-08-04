#pragma once

#include<vector>
#include "../Card/card.h"

class Game;

class Hand
{
    public:

        Hand(int aBet = 0);

        void AddCard(Card);
        void Update();

        void SetActive(bool);
        void Double();
        Hand Split();

        bool IsSplittable();
        bool IsSplitAce();
        bool IsBlackJack();
        bool IsBusted();

        int GetBet();
        int GetScore();

        void Resolve(int);

        void Draw(Texture2D &, Vector2);

        void Discard(std::vector<Card> &);

    protected:
        bool isSplit;

    private:
        static const float rotationAngle;

        std::vector<Card> cards;
        int minScore;
        bool hasAce;
        bool isActive;

        int bet;
        int winnings;

        bool isDoubled;
        bool isResolved;

        void PrintScore(Vector2);
        void PrintBet(Vector2);
};

class SplitHand: public Hand
{   public:
        SplitHand(int);
};