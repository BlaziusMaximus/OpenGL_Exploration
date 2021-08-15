#include "FrameCounter.h"

#include <iostream>

FrameCounter::FrameCounter() :
    targetFPS(MAX_FPS), ticks(0), counter(0) {
    currTime = prevTime = startTime = glfwGetTime();
}

FrameCounter::FrameCounter(const int& FPS) :
    targetFPS(FPS), ticks(0), counter(0) {
    currTime = prevTime = startTime = glfwGetTime();
}

frame_struct FrameCounter::tick() {
    ticks++;
    counter++;
    currTime = glfwGetTime();
    float timeDiff = currTime - prevTime;

    frame_struct fpsStruct{
        .ticked = (timeDiff >= (1. / (float)targetFPS)),
        .FPS = 1.0f / timeDiff,
        .MS = 1000 * timeDiff
    };
    if (fpsStruct.ticked) {
        prevTime = currTime;
        counter = 0;
    }

    return fpsStruct;
}
