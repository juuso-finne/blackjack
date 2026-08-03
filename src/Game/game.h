#pragma once
#include "../Hand/hand.h"
#include "../Button/button.h"
#include "DrawHandler/drawHandler.h"
#include <string>

class Game
{
    public:
        static const int fontSize;

        Game();

        void Update();
        void Draw();

        std::vector<Hand> playerHands;
        Hand dealerHand;

        std::vector<Button> buttons;

        std::string message;

    private:
        DrawHandler drawHandler;
        Action action;

        void PlaceButtons();
};