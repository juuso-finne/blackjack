#pragma once
#include <raylib.h>

enum Action{
    NONE,
    DEAL,
    INC_BET,
    DEC_BET,
    HIT,
    STAY,
    DOUBLE,
    SPLIT,
    INSURANCE_Y,
    INSURANCE_N
};

class Button
{
    public:
        Button(const char*, Action);

        void SetPosition(Vector2);
        bool IsClicked();

        Action GetAction();
        Rectangle GetBoundaries();

        void Draw();

    private:
        const char* label;
        Action action;

        Vector2 textPosition;
        Rectangle boundaries;

        static const float width;
        static const float height;

        static const int fontSize;
};