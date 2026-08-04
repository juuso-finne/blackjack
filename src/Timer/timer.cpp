#include "timer.h"
#include <raylib.h>

Timer::Timer(){
    current_seconds_ = 0;
    initial_seconds_ = 0;
}

Timer::Timer(float seconds)
{
    current_seconds_ = seconds;
    initial_seconds_ = seconds;
}

void Timer::Reset(){
    current_seconds_ = initial_seconds_;
}

void Timer::Tick(){
    current_seconds_ -= GetFrameTime();
}
