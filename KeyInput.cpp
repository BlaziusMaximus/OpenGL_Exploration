#include "KeyInput.h"

std::unordered_set<KeyInput*> KeyInput::KI_instances;

KeyInput::KeyInput(const std::unordered_set<int>& trackedKeys) {
    for (int key : trackedKeys) {
        keys[key] = {
            .pressed = false,
            .active = false,
            .holding = false
        };
    }

    KeyInput::KI_instances.insert(this);
}

KeyInput::~KeyInput() {
    KI_instances.erase(this);

    std::unordered_map<int, key_struct>().swap(keys);
}

bool KeyInput::keyIsDown(const int& key) {
    return keys[key].pressed;
}

bool KeyInput::keyIsActive(const int& key) {
    return keys[key].active;
}
void KeyInput::setKeyActive(const int& key, const bool& active) {
    keys[key].active = active;
}

bool KeyInput::keyPressed(const int& key) {
    bool press = (keys[key].pressed && !keys[key].active);
    if (press) { keys[key].active = true; }
    return press;
}
bool KeyInput::keyHolding(const int& key) {
    return keys[key].holding;
}

void KeyInput::setupKeyInput(GLFWwindow* window) {
    glfwSetKeyCallback(window, KeyInput::key_callback);
}

void KeyInput::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    for (KeyInput* keyInput : KI_instances) {
        keyInput->keys[key].pressed = (action == GLFW_PRESS);
        keyInput->keys[key].holding = (action == GLFW_REPEAT);

        if (action == GLFW_RELEASE) {
            keyInput->keys[key].active = false;
            keyInput->keys[key].holding = false;
        }
    }
}
