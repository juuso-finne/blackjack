#pragma once
#include <raylib.h>
#include <vector>
#include "../Card/card.h"

class Deck{
    public:
        Deck(int);
        void Shuffle();
        bool IsEmpty();
        void Reset();
        Card DealOne();
        std::vector<Card> DealN(int n);
        void Append(const std::vector<Card> &newCards);

    private:
        std::vector<Card> cards;
        void Generate();
        int decks;
};