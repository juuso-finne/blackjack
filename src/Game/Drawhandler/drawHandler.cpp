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
}

DrawHandler::~DrawHandler()
{
    UnloadTexture(cardSpriteSheet);
}

void DrawHandler::Draw()
{
    DrawButtons();
}

void DrawHandler::DrawButtons()
{
    for (Button b: game->buttons)
    {
        b.Draw();
    }
}
