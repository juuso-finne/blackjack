#include "../game.h"

void Game::DealerTurnState()
{
    bool skipDealerTurn = insurance == 0;

    for (Hand h: playerHands)
    {
        skipDealerTurn = skipDealerTurn && (h.IsBlackJack() || h.IsBusted());
        if (!skipDealerTurn)
        {
            break;
        }
    }

    if(skipDealerTurn)
    {
        Evaluate();
        return;
    }

    dealerHand.AddCard(deck.DealOne(discardPile));

    if(dealerHand.IsBlackJack() || dealerHand.GetMinScore() >= 17)
    {
        Evaluate();
    }
}

void Game::Evaluate()
{
    if(dealerHand.IsBlackJack())
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
        int result = playerHand.Resolve(dealerHand);

        if (result > 0)
        {
            totalWins += result;
        }
        else
        {
            totalLosses -= result;
        }
        /*
        if(dealerHand.IsBlackJack())
        {
            if (!playerHand.IsBlackJack())
            {
                totalLosses += playerHand.GetBet();
                playerHand.Resolve(-playerHand.GetBet());
            }
            else
            {
                playerHand.Resolve(0);
            }
            continue;
        }

        if(playerHand.IsBlackJack())
        {
            totalWins += playerHand.GetBet() + playerHand.GetBet() / 2;
            playerHand.Resolve(playerHand.GetBet() + playerHand.GetBet() / 2);
            continue;
        }

        if(dealerHand.IsBusted() && !playerHand.IsBusted())
        {
            totalWins += playerHand.GetBet();
            playerHand.Resolve(-playerHand.GetBet());
            continue;
        }

        if (playerHand.IsBusted() || playerHand.GetScore() < dealerHand.GetScore())
        {
            totalLosses += playerHand.GetBet();
            playerHand.Resolve(-playerHand.GetBet());
            continue;
        }

        if(playerHand.GetScore() > dealerHand.GetScore())
        {
            totalWins += playerHand.GetBet();
            playerHand.Resolve(playerHand.GetBet());
        }
        else
        {
            playerHand.Resolve(0);
        }

        */
    }

    state = END;
}