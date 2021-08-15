#pragma once

#include <GLFW/glfw3.h>

struct frame_struct {
    bool ticked;
    double FPS;
    double MS;
};

class FrameCounter {
public:
    unsigned int targetFPS;
    unsigned int ticks, counter;
    double startTime, prevTime, currTime;

    FrameCounter();
    FrameCounter(const int& FPS);

    // ticks frame counter, returns true if new frame
    frame_struct tick();

private:
    const int MAX_FPS = 10000;
};