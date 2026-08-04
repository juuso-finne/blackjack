#include "../game.h"
#include <stdexcept>

void Game::InitState()
{
    Action previousAction = action;
    action = NONE;

    switch (previousAction)
    {
    case NONE:
        return;
    case INC_BET:
        currentBet += currentBet < maxBet ? betIncrement : 0;
        UpdateBet();
        return;
    case DEC_BET:
        currentBet -= currentBet > minBet ? betIncrement : 0;
        UpdateBet();
        return;
    case DEAL:
        Deal();
        return;
    default:
       throw std::logic_error("Invalid action for state INIT");
    }
}

void Game::Deal()
{
    Hand playerHand = Hand(currentBet);
    playerHand.AddCard(deck.DealOne(discardPile));
    playerHand.AddCard(deck.DealOne(discardPile));

    dealerHand.AddCard(deck.DealOne(discardPile));

    playerHands.push_back(playerHand);

    buttons.clear();

    if(dealerHand.GetScore() == 11)
    {
        message = "Insurance?";
        buttons.push_back({"Yes", INSURANCE_Y});
        buttons.push_back({"No", INSURANCE_N});
        state = INSURANCE;
    }
    else
    {
        message = "";
        buttons.push_back({"Hit", HIT});
        buttons.push_back({"Stand", STAND});
        buttons.push_back({"Double", DOUBLE});
        state = PLAYER_TURN;
    }
    PlaceButtons();
}

void Game::UpdateBet()
{
    message = "Current bet: " + std::to_string(currentBet);

    if(currentBet == maxBet)
    {
        message += " (max. bet)";
    }

    if(currentBet == minBet)
    {
        message += " (min. bet)";
    }
}