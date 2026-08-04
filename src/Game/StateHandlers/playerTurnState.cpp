#include "../game.h"
#include <stdexcept>

void Game::PlayerTurnState()
{
    Action previousAction = action;
    action = NONE;

    if(activeHandIndex > playerHands.size() - 1)
    {
        state = DEALER_TURN;
        buttons.clear();
        return;
    }

    for (int i = 0; i < playerHands.size(); i++)
    {
        playerHands[i].SetActive(activeHandIndex == i);
    }

    Hand &activeHand = playerHands[activeHandIndex];

    if(activeHand.IsSplitAce() || activeHand.IsBusted() || activeHand.IsBlackJack())
    {
        activeHandIndex++;
        return;
    }

    if(buttons.size() > 4)
    {
        throw std::logic_error("Too many buttons");
    }

    bool splitButtonPresent = buttons.size() == 4;
    bool splitButtonNeeded = activeHand.IsSplittable() && playerHands.size() < Game::maxHands;

    if(splitButtonNeeded && !splitButtonPresent)
    {
        buttons.push_back({"Split",SPLIT});
    }

    if(!splitButtonNeeded && splitButtonPresent)
    {
        buttons.pop_back();
    }

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