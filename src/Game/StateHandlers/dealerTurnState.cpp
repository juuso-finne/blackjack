#include "../game.h"

void Game::DealerTurnState()
{
    bool uncontestedBlackJack = true;

    for (Hand h: playerHands)
    {
        uncontestedBlackJack = uncontestedBlackJack && h.IsBlackJack() && !dealerHand.IsBlackJack();
        if(!uncontestedBlackJack)
        {
            break;
        }
    }

    if(dealerHand.IsBlackJack() || dealerHand.GetMinScore() >= 17 || uncontestedBlackJack)
    {
        Evaluate();
        return;
    }

    dealerHand.AddCard(deck.DealOne(discardPile), false);
    state = WAIT;
}

void Game::Evaluate()
{
    if(dealerHand.IsBlackJack() && insurance > 0)
    {
        message = "Insurance pays " + std::to_string(2 * insurance);
        totalWins += 2 * insurance;
    }
    else
    {
        totalLosses += insurance;
    }

    for (Hand &playerHand: playerHands)
    {
        playerHand.SetActive(true);
        int result = playerHand.Resolve(dealerHand);

        if (result > 0)
        {
            totalWins += result;
        }
        else
        {
            totalLosses -= result;
        }
    }

    state = END;
    buttons.push_back({"New round", RESET});
    PlaceButtons();
}