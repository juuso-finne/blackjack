#include "../game.h"
#include <stdexcept>

void Game::EndState()
{
    Action previousAction = action;
    action = NONE;

    switch (previousAction)
    {
    case NONE:
        return;
    case RESET:
        Reset();
        return;
    default:
        throw std::logic_error("Invalid action for state END");
    }
}