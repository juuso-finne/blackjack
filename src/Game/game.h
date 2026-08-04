#pragma once
#include "../Hand/hand.h"
#include "../Button/button.h"
#include "DrawHandler/drawHandler.h"
#include <string>
#include "../Deck/deck.h"
#include "../Timer/timer.h"

enum State{
    INIT,
    INSURANCE,
    PLAYER_TURN,
    DEALER_TURN,
    WAIT,
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
        static const float revealTime;

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
        Timer revealTimer;

        std::vector<Card> discardPile;

        void PlaceButtons();
        void Reset();

        void InitState();
        void Deal();
        void UpdateBet();

        void InsuranceState();

        void PlayerTurnState();
        void Split();
        void EndPlayerTurn();

        void DealerTurnState();
        void Evaluate();

        void WaitState();

        void EndState();
};