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

        void Draw();
        void WriteCentralized(const char *text, float y, float left = 0.0f, float right = (float)GetScreenWidth());
        void DrawHorizontalLine(float, Color);

    private:
        Game *game;
        Texture2D cardSpriteSheet;

        float buttonLine;
        float messageLine;
        float playerHandLine;
        float divider;
        float rulesLine;
        float insuranceLine;

        void DrawButtons();
        void WriteMessage();
        void DrawPlayerHands();
        void DrawDealerHand();
        void WriteInsurance();
        void WriteTotals();
};