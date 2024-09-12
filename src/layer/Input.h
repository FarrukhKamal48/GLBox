#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

namespace Input {

void Init(GLFWwindow* window);
glm::vec2 GetMousePos();

}
