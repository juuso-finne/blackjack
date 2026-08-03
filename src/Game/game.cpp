#include "game.h"

const int Game::fontSize = 24;
const int Game::maxBet = 100;
const int Game::minBet = 10;
const int Game::betIncrement = 10;

Game::Game(): drawHandler(this)
{
    dealerHand = Hand();
    playerHands = std::vector<Hand>();
    buttons = std::vector<Button>();
    discardPile = std::vector<Card>();

    currentBet = minBet;
    deck = Deck(5);

    Reset();
}

void Game::Update()
{
    for (Button b : buttons)
    {
        if(b.IsClicked() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            action = b.GetAction();
        }
    }

    switch (state)
    {
    case INIT:
        InitState();
        break;
    default:
        break;
    }

}

void Game::Draw()
{
    drawHandler.Draw();
}

void Game::PlaceButtons()
{
    float segment = (float)GetScreenWidth()/((float)buttons.size() + 1.0f);

    for (size_t i = 0; i < buttons.size(); i++)
    {
        float x = segment * ((float)i + 1.0f);
        buttons[i].SetPosition(x);
    }
}

void Game::Reset()
{
    action = NONE;
    state = INIT;
    insurance = 0;
    totalLosses = 0;
    totalWins = 0;
    activeHandIndex = 0;

    buttons.clear();
    buttons.push_back({"Bet -", DEC_BET});
    buttons.push_back({"Deal", DEAL});
    buttons.push_back({"Bet +", INC_BET});

    PlaceButtons();

    for(Hand h: playerHands)
    {
        h.Discard(discardPile);
    }
    playerHands.clear();
    dealerHand.Discard(discardPile);
}
