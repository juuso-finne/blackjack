#pragma once
#include "../Hand/hand.h"
#include "../Button/button.h"
#include "DrawHandler/drawHandler.h"
#include <string>
#include "../Deck/deck.h"

enum State{
    INIT,
    INSURANCE,
    PLAYER_TURN,
    DEALER_TURN,
    END
};

class Game
{
    public:
        static const int fontSize;
        static const int minBet;
        static const int maxBet;
        static const int betIncrement;
        static const size_t maxHands;

        Game();

        void Update();
        void Draw();

        std::vector<Hand> playerHands;
        Hand dealerHand;

        std::vector<Button> buttons;

        std::string message;
        int insurance;
        int currentBet;
        int totalLosses;
        int totalWins;

    private:
        size_t activeHandIndex;

        DrawHandler drawHandler;
        Action action;
        State state;
        Deck deck;

        std::vector<Card> discardPile;

        void PlaceButtons();
        void Reset();

        void InitState();
        void Deal();
        void UpdateBet();

        void PlayerTurnState();
        void Split();

        void InsuranceState();

        void DealerTurnState();
        void Evaluate();

        void EndState();
};