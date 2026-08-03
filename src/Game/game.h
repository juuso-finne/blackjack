#pragma once
#include "../Hand/hand.h"
#include "../Button/button.h"
#include "DrawHandler/drawHandler.h"
#include <string>

class Game
{
    public:
        static const int fontSize;
        static const int minBet;
        static const int maxBet;

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
        DrawHandler drawHandler;
        Action action;

        void PlaceButtons();
        void Reset();
};