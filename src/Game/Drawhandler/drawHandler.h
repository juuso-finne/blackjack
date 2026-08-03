#pragma once
#include <raylib.h>

class Game;

class DrawHandler
{
    public:
        DrawHandler(Game *aGame);
        DrawHandler();
        ~DrawHandler();

        void Draw();

    private:
        Game *game;
        Texture2D cardSpriteSheet;

        void DrawButtons();
};