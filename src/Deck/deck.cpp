#include <algorithm>
#include <random>
#include <stdexcept>
#include "deck.h"
#include <raymath.h>

Deck::Deck(int aDecks)
{
    cards = std::vector<Card>{};
    decks = aDecks;
    Reset();
}

Deck::Deck()
{
}

void Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

const bool Deck::IsEmpty()
{
    return cards.empty();
}

void Deck::Reset(){
    cards.clear();

    for(int i = 0; i < decks; i++)
    {
        Generate();
    }

    Shuffle();
}

void Deck::Generate()
{
    std::vector<Suit> suits = {Suit::CLUBS, Suit::DIAMONDS, Suit::HEARTS, Suit::SPADES};

    for (Suit suit : suits){
        for(int rank = 1; rank < 14; rank++){
            cards.push_back(Card(rank, suit));
        }
    }
}

Card Deck::DealOne(std::vector<Card> &discardPile)
{
    if (cards.empty()){
        Append(discardPile);
        discardPile.clear();
        Shuffle();
    }

    Card output = cards.back();
    cards.pop_back();
    return output;
}

void Deck::Append(const std::vector<Card> &newCards)
{
    for (Card c: newCards)
    {
        c.TurnFaceDown();
        cards.insert(cards.begin(), c);
    }
}


