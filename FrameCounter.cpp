#include "FrameCounter.h"

#include <iostream>

FrameCounter::FrameCounter() :
    targetFPS(MAX_FPS), ticks(0), frames(0) {
    fpsTime = currTime = prevTime = startTime = glfwGetTime();
}

FrameCounter::FrameCounter(const int& FPS) :
    targetFPS(FPS), ticks(0), frames(0) {
    fpsTime = currTime = prevTime = startTime = glfwGetTime();
}

bool FrameCounter::tick() {
    ticks++;
    currTime = glfwGetTime();

    if (currTime - fpsTime >= 1.) {
        frames = 0;
        fpsTime = currTime;
    }

    bool newFrame = (currTime - prevTime >= (1. / (float)targetFPS));
    if (newFrame) {
        frames++;
        prevTime = currTime;
    }
    return newFrame;
}

float FrameCounter::getFPS() {
    return (float)frames / (currTime - fpsTime);
}