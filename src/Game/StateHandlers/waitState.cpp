#include "../game.h"

void Game::WaitState()
{
    if (revealTimer.current_seconds_ > 0)
    {
        revealTimer.Tick();
        return;
    }

    revealTimer.Reset();
    dealerHand.Update();
    state = DEALER_TURN;
}