#include "../game.h"
#include <stdexcept>

void Game::InsuranceState()
{
    Action previousAction = action;
    action = NONE;

    switch (previousAction)
    {
    case NONE:
        return;

    case INSURANCE_Y:
        insurance = currentBet / 2;
        break;

    case INSURANCE_N:
        break;

    default:
        throw std::logic_error("Invalid action for state INSURANCE");
    }

    buttons.clear();
    message = "";
    buttons.push_back({"Hit", HIT});
    buttons.push_back({"Stand", STAND});
    buttons.push_back({"Double", DOUBLE});

    PlaceButtons();
    state = PLAYER_TURN;
}