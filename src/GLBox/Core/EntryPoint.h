#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLBox/Core/Application.h"

extern Application* CreateApplication();

int main (int argc, char *argv[]) {
    Application* app = CreateApplication();
    app->Run();
    delete app;
}
