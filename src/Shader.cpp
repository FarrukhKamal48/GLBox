#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Shader.h"
#include "GLlog.h"

Shader::Shader() {
}
Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() {
}
void Shader::UnBind() {
    GLCall(glUseProgram(0));
}

void Shader::AddSource(unsigned int type, std::string& srcPath) {
    std::ifstream stream(srcPath);
    std::stringstream srcStream;
    srcStream << stream.rdbuf();
    m_Sources.push_back({ type, srcStream.str() });
}

unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSrc) {
    GLCall(unsigned int id = glCreateShader(shaderType));
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
void Shader::Compile() {
    GLCall(m_RendererID = glCreateProgram());
    unsigned int shaderID;

    for (ShaderElement element : m_Sources) {
        shaderID = CompileShader(element.type, element.src);
        GLCall(glAttachShader(m_RendererID, shaderID));
        GLCall(glDeleteShader(shaderID));
    }
    
    GLCall(glLinkProgram(m_RendererID));
    GLCall(glValidateProgram(m_RendererID));
}

void Shader::Use() {
    GLCall(glUseProgram(m_RendererID));
}




std::string GetShaderSource(const std::string& shaderPath) {
    std::ifstream stream(shaderPath);
    std::stringstream ss;

    ss << stream.rdbuf();
    
    return ss.str();
}

ShaderSrc GetShaderSource2(const std::string& vertPath, const std::string& fragPath) {
    return { GetShaderSource(vertPath), GetShaderSource(fragPath), };
}


unsigned int CreateShader(unsigned int shaderType, const std::string &shaderSrc) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int shader = CompileShader(shaderType, shaderSrc);

    GLCall(glAttachShader(program, shader));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(shader));
    
    return program;
}

unsigned int CreateShader2(const std::string &vertSrc, const std::string &fragSrc) {
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertSrc);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragSrc);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    
    return program;
}
