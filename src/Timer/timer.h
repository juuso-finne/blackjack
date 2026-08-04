#pragma once

class Timer{
    public:
        Timer();
        Timer(float seconds);
        void Reset();
        void Tick();
        float current_seconds_;

    private:
        float initial_seconds_;
};