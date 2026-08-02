#pragma once
#include <raylib.h>

class Game;

class DrawHandler
{
    public:
        DrawHandler(Game *aGame);
        ~DrawHandler();
        Game *game;
        Texture2D cardSpriteSheet;
};