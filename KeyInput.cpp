#include "KeyInput.h"

std::unordered_set<KeyInput*> KeyInput::KI_instances;

KeyInput::KeyInput(std::unordered_set<int> trackedKeys) {
    for (int key : trackedKeys) {
        keys[key] = false;
        keysActive[key] = false;
    }

    KeyInput::KI_instances.insert(this);
}

KeyInput::~KeyInput() {
    KI_instances.erase(this);
}

bool KeyInput::keyIsDown(int key) {
    return keys[key];
}

bool KeyInput::keyIsActive(int key) {
    return keysActive[key];
}
void KeyInput::setKeyActive(int key, bool active) {
    keysActive[key] = active;
}

bool KeyInput::keyPress(int key) {
    bool press = (keys[key] && !keysActive[key]);
    if (press) { keysActive[key] = true; }
    return press;
}

void KeyInput::setupKeyInput(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyInput::key_callback);
}

void KeyInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (KeyInput* keyInput : KI_instances) {
        keyInput->keys[key] = (action == GLFW_PRESS);
        if (action == GLFW_RELEASE) {
            keyInput->keysActive[key] = false;
        }
    }
}
