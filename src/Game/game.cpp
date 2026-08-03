#include "game.h"

const int Game::fontSize = 24;
const int Game::maxBet = 100;
const int Game::minBet = 10;

Game::Game(): drawHandler(this)
{
    dealerHand = Hand();
    playerHands = std::vector<Hand>();
    buttons = std::vector<Button>();
    message = "This is a message";

    insurance = 25;
    totalLosses = 5000;
    totalWins = 100;

    buttons.push_back(Button("Hit", HIT));
    buttons.push_back(Button("Stand", STAND));
    buttons.push_back(Button("Split", SPLIT));
    buttons.push_back(Button("Double", DOUBLE));

    PlaceButtons();

    Card c1 = Card(9, SPADES);
    Card c2 = Card(1, CLUBS);
    Card c3 = Card(3, HEARTS);

    Hand h1 = Hand(10);

    h1.AddCard(c1);
    h1.Update();
    h1.AddCard(c2);
    h1.Update();
    h1.Resolve(0);


    dealerHand.AddCard(c1);
    dealerHand.Update();
    dealerHand.AddCard(c2);
    dealerHand.Update();

    playerHands.push_back(h1);
    playerHands.push_back(h1);
    playerHands.push_back(h1);
    playerHands.push_back(h1);
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
}
