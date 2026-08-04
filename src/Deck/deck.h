#pragma once
#include <raylib.h>
#include <vector>
#include "../Card/card.h"

class Deck{
    public:
        Deck(int);
        Deck();
        void Shuffle();
        bool IsEmpty();
        void Reset();
        Card DealOne(std::vector<Card> &);
        void Append(const std::vector<Card> &);

    private:
        std::vector<Card> cards;
        void Generate();
        int decks;
};