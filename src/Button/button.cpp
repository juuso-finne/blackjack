#include "button.h"
#include "../Game/game.h"

const float Button::width = 100.0f;
const float Button::height = 50.0f;

Button::Button(const char * aLabel, Action aAction)
{
    label = aLabel;
    action = aAction;
    fontSize = Game::fontSize;

    textPosition = {0,0};
    boundaries = {0, 0, width, height};
}

void Button::SetPosition(Vector2 pos)
{

    int textWidth = MeasureText(label, fontSize);

    textPosition.x = pos.x - textWidth/2.0f;
    textPosition.y = pos.y;

    boundaries.x = textPosition.x - (width - textWidth)/2.0f;
    boundaries.y = textPosition.y - (height - fontSize)/2.0f;
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
    DrawText(label, textPosition.x, textPosition.y, fontSize, WHITE);
    DrawRectangleRoundedLines(boundaries, .5, 1, WHITE);
}
