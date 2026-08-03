#include "drawHandler.h"
#include "../game.h"

const float DrawHandler::margin = 20.0f;

DrawHandler::DrawHandler()
{
}

DrawHandler::DrawHandler(Game *aGame)
{
    game = aGame;
    cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");

    buttonLine = GetScreenHeight() - Button::GetDimensions().y - margin;
    messageLine = buttonLine - margin - Game::fontSize;
    playerHandLine = messageLine - 3.0f * (float)Game::fontSize;
}

DrawHandler::~DrawHandler()
{
    UnloadTexture(cardSpriteSheet);
}

void DrawHandler::Draw()
{
    DrawButtons();
    WriteMessage();
    DrawDealerHand();
    DrawPlayerHands();
}

void DrawHandler::WriteCentralized(const char *text, float y, float left, float right)
{
    int textWidth = MeasureText(text, Game::fontSize);
    DrawText(text, (right - left)/2.0f - (float)textWidth/2.0f, y, Game::fontSize, WHITE);
}

void DrawHandler::DrawButtons()
{
    for (Button b: game->buttons)
    {
        b.Draw();
    }
}

void DrawHandler::WriteMessage()
{
    WriteCentralized(game->message.c_str(), messageLine);
}

void DrawHandler::DrawPlayerHands()
{
    float segment = (float)GetScreenWidth()/((float)game->playerHands.size() + 1.0f);

    for (size_t i = 0; i < game->playerHands.size(); i++)
    {
        float x = segment * ((float)i + 1.0f);
        game->playerHands[i].Draw(cardSpriteSheet, {x, playerHandLine});
    }
}

void DrawHandler::DrawDealerHand()
{
    game->dealerHand.Draw(cardSpriteSheet, {(float)GetScreenWidth()/2.0f, (float)Card::GetDimensions().y + margin});
}
