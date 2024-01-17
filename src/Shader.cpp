#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>

#include "Shader.h"
#include "GLlog.h"

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
    GLCall(uint id = glCreateShader(shaderType));
    const char* src = shaderSrc.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    
    /* Error Handling */
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE) {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        
        char message[length];
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        
        std::cout << "Failed to compile " 
            << (shaderType==GL_VERTEX_SHADER ? "vertex" : "fragment") 
            << "shader!" << std::endl;
        std::cout << message << std::endl;

        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

uint CreateShader(uint shaderType, const std::string &shaderSrc) {
    GLCall(uint program = glCreateProgram());
    uint shader = CompileShader(shaderType, shaderSrc);

    GLCall(glAttachShader(program, shader));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(shader));
    
    return program;
}

uint CreateShader2(const std::string &vertSrc, const std::string &fragSrc) {
    GLCall(uint program = glCreateProgram());
    uint vs = CompileShader(GL_VERTEX_SHADER, vertSrc);
    uint fs = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    
    return program;
}
