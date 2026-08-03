#pragma once
#include "../Hand/hand.h"
#include "../Button/button.h"
#include "DrawHandler/drawHandler.h"

class Game
{
    public:
        Game();

        void Update();
        void Draw();

        std::vector<Hand> playerHands;
        Hand dealerHand;

        std::vector<Button> buttons;

    private:
        DrawHandler drawHandler;
        Action action;

        void PlaceButtons();
};