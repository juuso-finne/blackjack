#include "game.h"

const int Game::fontSize = 24;

Game::Game()
{
    drawHandler = DrawHandler(this);
    dealerHand = Hand();
    playerHands = std::vector<Hand>();
    buttons = std::vector<Button>();
    buttons.push_back(Button("Hit", HIT));
    buttons.push_back(Button("Stand", STAND));
    buttons.push_back(Button("Deal", DEAL));
    buttons.push_back(Button("Double", DOUBLE));

    PlaceButtons();
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
