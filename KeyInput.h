#pragma once

#include <GLFW/glfw3.h>
#include <unordered_set>
#include <unordered_map>

class KeyInput {
protected:
    std::unordered_map<int, bool> keys;
    std::unordered_map<int, bool> keysActive;

public:
    KeyInput(std::unordered_set<int> trackedKeys);
    ~KeyInput();

    bool keyIsDown(int key);

    bool keyIsActive(int key);
    void setKeyActive(int key, bool active);

    bool keyPress(int key);

    static void setupKeyInput(GLFWwindow* window);

protected:
    static std::unordered_set<KeyInput*> KI_instances;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};