#pragma once
#include <raylib.h>

enum Action{
    NONE,
    DEAL,
    INC_BET,
    DEC_BET,
    HIT,
    STAND,
    DOUBLE,
    SPLIT,
    INSURANCE_Y,
    INSURANCE_N,
    RESET
};

class Game;

class Button
{
    public:
        Button(const char*, Action);

        void SetPosition(const float);
        const bool IsClicked();

        const Action GetAction();
        static const Vector2 GetDimensions();

        const void Draw();

    private:
        const char* label;
        Action action;

        Vector2 textPosition;
        Rectangle boundaries;

        static const float width;
        static const float height;
};