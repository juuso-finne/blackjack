#include "drawHandler.h"

DrawHandler::DrawHandler(Game *aGame)
{
    game = aGame;
    cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");
}

DrawHandler::~DrawHandler()
{
    UnloadTexture(cardSpriteSheet);
}