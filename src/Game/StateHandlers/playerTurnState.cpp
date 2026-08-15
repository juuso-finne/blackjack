#include "../game.h"
#include <stdexcept>
#include "../game.h"

void Game::PlayerTurnState()
{
    Action previousAction = action;
    action = NONE;

    if(activeHandIndex > playerHands.size() - 1)
    {
        EndPlayerTurn();
        return;
    }

    for (size_t i = 0; i < playerHands.size(); i++)
    {
        playerHands[i].SetActive(activeHandIndex == i);
    }

    Hand &activeHand = playerHands[activeHandIndex];


    if(activeHand.IsSplitAce() || activeHand.IsBusted() || activeHand.IsBlackJack())
    {
        activeHandIndex++;
        return;
    }

    while (buttons.size() > 2)
    {
        buttons.pop_back();
    }

    if (activeHand.GetSize() == 2)
    {
        buttons.push_back({"Double", DOUBLE});
    }

    if(activeHand.IsSplittable() && playerHands.size() < Game::maxHands)
    {
        buttons.push_back({"Split",SPLIT});
    }

    PlaceButtons();

    switch (previousAction)
    {
    case NONE:
        return;

    case SPLIT:
        Split();
        return;

    case STAND:
        activeHandIndex++;
        return;

    case HIT:
        activeHand.AddCard(deck.DealOne(discardPile));
        return;

    case DOUBLE:
        activeHand.Double();
        activeHand.AddCard(deck.DealOne(discardPile));
        activeHandIndex++;
        return;

    default:
        throw std::logic_error("Invalid action for state PLAYER_TURN");
    }
}

void Game::Split()
{
    Hand newHand = playerHands[activeHandIndex].Split();

    playerHands[activeHandIndex].AddCard(deck.DealOne(discardPile));
    newHand.AddCard(deck.DealOne(discardPile));

    playerHands.insert(std::next(playerHands.begin(), activeHandIndex + 1), newHand);
}
void Game::EndPlayerTurn()
{
    bool skipDealerTurn = insurance == 0;
    buttons.clear();

    for (Hand &h: playerHands)
    {
        skipDealerTurn = skipDealerTurn && ((h.IsBlackJack() && dealerHand.GetScore() < 10) || h.IsBusted());
        h.SetActive(true);
    }

    if(skipDealerTurn)
    {
        Evaluate();
        return;
    }

    dealerHand.AddCard(deck.DealOne(discardPile), false);
    state = WAIT;
}