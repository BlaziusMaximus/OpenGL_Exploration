#pragma once

#include <GLFW/glfw3.h>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

struct key_struct {
    bool pressed;
    bool active;
    bool holding;
};

class KeyInput {
protected:
    std::unordered_map<int, key_struct> keys;

public:
    KeyInput(const std::unordered_set<int>& trackedKeys);
    ~KeyInput();

    bool keyIsDown(const int& key);

    bool keyIsActive(const int& key);
    void setKeyActive(const int& key, const bool& active);

    bool keyPressed(const int& key);
    bool keyHolding(const int& key);

    static void setupKeyInput(GLFWwindow* window);

protected:
    static std::unordered_set<KeyInput*> KI_instances;
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};