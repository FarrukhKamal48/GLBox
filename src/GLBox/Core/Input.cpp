#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Core/Input.h"
#include "GLBox/Core/Application.h"

bool Input::KeyPressed(KeyCode key) {
    GLFWwindow* window = Application::Get().GetWindow().GetWindow();
    return glfwGetKey(window, key) == GLFW_PRESS;
}
bool Input::KeyReleased(KeyCode key) { 
    GLFWwindow* window = Application::Get().GetWindow().GetWindow();
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

bool Input::MousePressed(MouseCode button) { 
    GLFWwindow* window = Application::Get().GetWindow().GetWindow();
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
}
bool Input::MouseReleased(MouseCode button) { 
    GLFWwindow* window = Application::Get().GetWindow().GetWindow();
    return glfwGetMouseButton(window, button) == GLFW_RELEASE;
}

glm::vec2 Input::MousePos() { 
    double xpos;
    double ypos;
    GLFWwindow* window = Application::Get().GetWindow().GetWindow();
    glfwGetCursorPos(window, &xpos, &ypos);
    return { xpos, ypos };
}
float Input::MouseX() { 
    return MousePos().x;
}
float Input::MouseY() { 
    return MousePos().y;
}
