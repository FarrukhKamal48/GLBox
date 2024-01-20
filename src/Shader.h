#pragma once
#include <string>

struct ShaderSrc {
    std::string vertSrc;    
    std::string fragSrc;    
};

std::string GetShaderSource(const std::string& shaderPath);
ShaderSrc GetShaderSource2(const std::string& vertPath, const std::string& fragPath);

unsigned int CreateShader(unsigned int shaderType, const std::string &shaderSrc);
unsigned int CreateShader2(const std::string &VertSrc, const std::string &fragSrc);
