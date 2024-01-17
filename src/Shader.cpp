#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>


std::string ParseShader(const std::string& shaderPath) {
    std::ifstream stream(shaderPath);
    std::stringstream ss;

    ss << stream.rdbuf();
    
    return ss.str();
}

uint CompileShader(uint shaderType, const std::string& shaderSrc) {
    uint id = glCreateShader(shaderType);
    const char* src = shaderSrc.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    return id;
}

uint CreateShader(uint shaderType, const std::string &shaderSrc) {
    uint program = glCreateProgram();
    uint shader = CompileShader(shaderType, shaderSrc);

    glAttachShader(program, shader);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(shader);
    
    return program;
}

uint CreateShader2(const std::string &vertSrc, const std::string &fragSrc) {
    uint program = glCreateProgram();
    uint vs = CompileShader(GL_VERTEX_SHADER, vertSrc);
    uint fs = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    
    return program;
}
