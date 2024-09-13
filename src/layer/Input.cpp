#include "Input.h"
#include <GLFW/glfw3.h>

static GLFWwindow* window;
static double MousePosX;
static double MousePosY;

struct Button {
    int key;
    int scancode;
    int action;
    int mods;
};
static Button Mouse;
static Button Keyboard;

static void mouse_callback(GLFWwindow* window, int key, int action, int mods)
{
    Mouse.key = key;
    Mouse.scancode = 0;
    Mouse.action = action;
    Mouse.mods = mods;
}
static void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Keyboard.key = key;
    Keyboard.scancode = scancode;
    Keyboard.action = action;
    Keyboard.mods = mods;
}

namespace Input {


void Init(GLFWwindow* _window) {
    window = _window;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
    glfwSetMouseButtonCallback(window, mouse_callback);
    glfwSetKeyCallback(window, keyboard_callback);
}

bool Button(int button, int action) {
    if (button >= GLFW_MOUSE_BUTTON_1 && button <= GLFW_MOUSE_BUTTON_8)
        return Mouse.key == button && Mouse.action == action;
    return Keyboard.key == button && Keyboard.action == action;
}

bool ButtonHold(int button) {
    return Button(button, GLFW_PRESS) && !Button(button, GLFW_RELEASE);
}

glm::vec2 GetMousePos() {
    glfwGetCursorPos(window, &MousePosX, &MousePosY);
    return glm::vec2(MousePosX, MousePosY);
}

}
