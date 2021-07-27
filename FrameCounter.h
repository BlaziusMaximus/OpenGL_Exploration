#pragma once

#include <GLFW/glfw3.h>

class FrameCounter {
public:
    unsigned int targetFPS;
    unsigned int ticks, frames;
    double startTime, prevTime, currTime, fpsTime;

    FrameCounter();
    FrameCounter(const int& FPS);

    // ticks frame counter, returns true if new frame
    bool tick();

    float getFPS();

private:
    const int MAX_FPS = 1000;
};