#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>


std::string GetShaderSource(const std::string& shaderPath) {
    std::ifstream stream(shaderPath);
    std::stringstream ss;

    ss << stream.rdbuf();
    
    return ss.str();
}

ShaderSrc GetShaderSource2(const std::string& vertPath, const std::string& fragPath) {
    return { GetShaderSource(vertPath), GetShaderSource(fragPath), };
}

uint CompileShader(uint shaderType, const std::string& shaderSrc) {
    uint id = glCreateShader(shaderType);
    const char* src = shaderSrc.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    
    /* Error Handling */
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        
        char message[length];
        glGetShaderInfoLog(id, length, &length, message);
        
        std::cout << "Failed to compile " 
            << (shaderType==GL_VERTEX_SHADER ? "vertex" : "fragment") 
            << "shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

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
