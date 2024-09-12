#include "Input.h"

static GLFWwindow* window;
static double MousePosX;
static double MousePosY;

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    // if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &MousePosX, &MousePosY);
    // }
}

namespace Input {


void Init(GLFWwindow* _window) {
    window = _window;
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
    // glfwSetMouseButtonCallback(_window, mouse_button_callback);
}

glm::vec2 GetMousePos() {
    glfwGetCursorPos(window, &MousePosX, &MousePosY);
    return glm::vec2(MousePosX, MousePosY);
}

}
