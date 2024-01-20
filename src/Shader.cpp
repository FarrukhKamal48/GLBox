#include <GL/glew.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "Shader.h"
#include "GLlog.h"

ShaderProgram::ShaderProgram() {
}
ShaderProgram::~ShaderProgram() {
    GLCall(glDeleteProgram(m_RendererID));
}

void ShaderProgram::Bind() const {
    GLCall(glUseProgram(m_RendererID));
}
void ShaderProgram::UnBind() const {
    GLCall(glUseProgram(0));
}

// void ShaderProgram::Push(unsigned int type, const std::string& srcPath) {
//     std::ifstream stream(srcPath);
//     std::stringstream srcStream;
//     srcStream << stream.rdbuf();
//     m_Sources.push_back({ type, srcStream.str() });
// }
void ShaderProgram::Push(unsigned int type, const std::string& srcPath) {
    std::ifstream stream(srcPath);
    std::stringstream srcStream;
    srcStream << stream.rdbuf();
    switch (type) {
        case GL_VERTEX_SHADER:      m_Sources[0] = { type, srcStream.str() };
        case GL_FRAGMENT_SHADER:    m_Sources[1] = { type, srcStream.str() };
    }
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
void ShaderProgram::Compile() {
    GLCall(m_RendererID = glCreateProgram());

    for (ShaderSourceElement element : m_Sources) {
        unsigned int shaderID = CompileShader(element.type, element.src);
        GLCall(glAttachShader(m_RendererID, shaderID));
        GLCall(glDeleteShader(shaderID));
    }
    
    GLCall(glLinkProgram(m_RendererID));
    GLCall(glValidateProgram(m_RendererID));
}

int ShaderProgram::GetUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning, uniform '" << name << "' does not exist" << std::endl;
    
    m_UniformLocationCache[name] = location;
    return location;
}

template<> 
void ShaderProgram::SetUniform<float>(const std::string& name, float val) {
    GLCall(glUniform1f(GetUniformLocation(name), val));
}

template<> 
void ShaderProgram::SetUniformVec2<float>(const std::string& name, float val1, float val2) {
    GLCall(glUniform2f(GetUniformLocation(name), val1, val2));
} 

template<> 
void ShaderProgram::SetUniformVec3<float>(const std::string& name, float val1, float val2, float val3) {
    GLCall(glUniform3f(GetUniformLocation(name), val1, val2, val3));
} 

template<> 
void ShaderProgram::SetUniformVec4<float>(const std::string& name, float val1, float val2, float val3, float val4) {
    GLCall(glUniform4f(GetUniformLocation(name), val1, val2, val3, val4));
} 

