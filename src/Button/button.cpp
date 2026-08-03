#include "button.h"
#include "../Game/game.h"

const float Button::width = 100.0f;
const float Button::height = 50.0f;

Button::Button(const char * aLabel, Action aAction)
{
    label = aLabel;
    action = aAction;

    textPosition = {0,0};
    boundaries = {0, 0, width, height};
}

void Button::SetPosition(float xPos)
{
    boundaries.y = GetScreenHeight() - DrawHandler::margin - height;
    textPosition.y = boundaries.y + height/2.0f - (float)Game::fontSize/2.0f;

    int textWidth = MeasureText(label, Game::fontSize);

    textPosition.x = xPos - textWidth/2.0f;

    boundaries.x = textPosition.x - (width - textWidth)/2.0f;
}

bool Button::IsClicked()
{
    return CheckCollisionPointRec(GetMousePosition(), boundaries);
}

Action Button::GetAction()
{
    return action;
}

Vector2 Button::GetDimensions()
{
    return {width, height};
}

void Button::Draw()
{
    DrawText(label, textPosition.x, textPosition.y, Game::fontSize, WHITE);
    DrawRectangleRoundedLines(boundaries, .5, 1, WHITE);
}
