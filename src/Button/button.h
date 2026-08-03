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
    CONTINUE
};

class Game;

class Button
{
    public:
        Button(const char*, Action);

        void SetPosition(float);
        bool IsClicked();

        Action GetAction();
        static Vector2 GetDimensions();

        void Draw();

    private:
        const char* label;
        Action action;

        Vector2 textPosition;
        Rectangle boundaries;

        static const float width;
        static const float height;
};