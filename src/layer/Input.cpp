#include "Input.h"

static double MousePosX;
static double MousePosY;

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        glfwGetCursorPos(window, &MousePosX, &MousePosY);
    }
}

namespace Input {


void Init(GLFWwindow* window) {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
}

glm::vec2 GetMousePos() {
    return glm::vec2(MousePosX, MousePosY);
}

}
