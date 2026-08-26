#include "drawHandler.h"
#include "../game.h"
#include <math.h>

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
    playerHandLine = messageLine - 5.0f * (float)Game::fontSize;
    divider = playerHandLine - margin - Card::GetDimensions().y;
    rulesLine = divider - margin - Game::fontSize;
    insuranceLine = rulesLine - (2 * margin) - Game::fontSize;
}

DrawHandler::~DrawHandler()
{
    UnloadTexture(cardSpriteSheet);
}

const void DrawHandler::Draw()
{
    DrawButtons();
    WriteMessage();
    DrawDealerHand();
    DrawPlayerHands();
    DrawHorizontalLine(divider, GREEN);
    WriteCentralized("BLACKJACK PAYS 3:2, INSURANCE PAYS 2:1, DEALER MUST STAND ON HARD 17", rulesLine);
    DrawHorizontalLine(rulesLine - margin, GREEN);
    WriteInsurance();
    WriteTotals();
}

void DrawHandler::WriteCentralized(const char *text, float y, float left, float right)
{
    int textWidth = MeasureText(text, Game::fontSize);
    DrawText(text, (right - left)/2.0f - (float)textWidth/2.0f, y, Game::fontSize, WHITE);
}

const void DrawHandler::DrawHorizontalLine(float y, Color col)
{
    DrawLine(0, y, GetScreenWidth(), y, col);
}

const void DrawHandler::DrawButtons()
{
    for (Button b: game->buttons)
    {
        b.Draw();
    }
}

const void DrawHandler::WriteMessage()
{
    WriteCentralized(game->message.c_str(), messageLine);
}

const void DrawHandler::DrawPlayerHands()
{
    float segment = (float)GetScreenWidth()/((float)game->playerHands.size() + 1.0f);

    for (size_t i = 0; i < game->playerHands.size(); i++)
    {
        float x = segment * ((float)i + 1.0f);
        game->playerHands[i].Draw(cardSpriteSheet, {x, playerHandLine});
    }
}

const void DrawHandler::DrawDealerHand()
{
    game->dealerHand.Draw(cardSpriteSheet, {(float)GetScreenWidth()/2.0f, (float)Card::GetDimensions().y + margin});
}

const void DrawHandler::WriteInsurance()
{
    if(game->insurance > 0)
    {
        const char *text = (std::string("Insurance: ") + std::to_string(game->insurance)).c_str();
        WriteCentralized(text, insuranceLine);
    }
}

const void DrawHandler::WriteTotals()
{

    const char *totalWins = std::to_string(game->totalWins).c_str();
    const char *totalLosses = std::to_string(game->totalLosses).c_str();
    const char *netWins = std::to_string(game->totalWins - game->totalLosses).c_str();
    //const char *netWinsAbs = std::to_string(std::abs(game->totalWins - game->totalLosses)).c_str();

    float textCol = GetScreenWidth() - 2 * margin - MeasureText("-0000", Game::fontSize) - MeasureText("Total winnings:", Game::fontSize);

    float row = margin;
    float numberCol = GetScreenWidth() - MeasureText(totalWins, Game::fontSize) - margin;

    DrawText(totalWins, numberCol, row, Game::fontSize, WHITE);
    DrawText("Total winnings:", textCol, row, Game::fontSize, WHITE);

    row += margin + Game::fontSize;
    numberCol = GetScreenWidth() - MeasureText(totalLosses, Game::fontSize) - margin;

    DrawText(totalLosses, numberCol, row, Game::fontSize, WHITE);
    DrawText("Total losses:", textCol, row, Game::fontSize, WHITE);

    DrawLine(textCol, row + Game::fontSize, GetScreenWidth() - margin, row + Game::fontSize, WHITE);

    row += margin + Game::fontSize;
    numberCol = GetScreenWidth() - MeasureText(netWins, Game::fontSize) - margin;

    DrawText(netWins, numberCol, row, Game::fontSize, WHITE);
    DrawText("Net winnings:", textCol, row, Game::fontSize, WHITE);
}
