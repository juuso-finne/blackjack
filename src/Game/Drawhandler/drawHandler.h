#pragma once
#include <raylib.h>

class Game;

class DrawHandler
{
    public:

        static const float margin;

        DrawHandler(Game *aGame);
        DrawHandler();
        ~DrawHandler();

        const void Draw();

    private:
        Game *game;
        Texture2D cardSpriteSheet;

        float buttonLine;
        float messageLine;
        float playerHandLine;
        float divider;
        float rulesLine;
        float insuranceLine;

        const void DrawHorizontalLine(float, Color);
        void WriteCentralized(const char *text, float y, float left = 0.0f, float right = (float)GetScreenWidth());

        const void DrawButtons();
        const void WriteMessage();
        const void DrawPlayerHands();
        const void DrawDealerHand();
        const void WriteInsurance();
        const void WriteTotals();
};