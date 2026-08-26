#pragma once

#include<vector>
#include <map>
#include "../Card/card.h"

class Game;

enum Outcome
{
    WIN_REGULAR,
    WIN_BLACKJACK,
    LOSS,
    PUSH
};

class Hand
{
    public:

        Hand(int aBet = 0);

        void AddCard(Card, bool instantReveal = true);
        void Update();

        void SetActive(bool);
        void Double();
        Hand Split();

        const bool IsSplittable();
        const bool IsSplitAce();
        const bool IsBlackJack();
        const bool IsBusted();

        const int GetBet();
        const int GetMinScore();
        const int GetScore();
        const int GetSize();

        int Resolve(Hand);

        const void Draw(Texture2D &, Vector2);

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

        void Reset();

        const void PrintScore(Vector2);
        const void PrintBet(Vector2);

        std::map<int, float> coefficients;
};

class SplitHand: public Hand
{   public:
        SplitHand(int);
};