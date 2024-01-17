#pragma once
#include <string>
#include <sys/types.h>

struct ShaderSrc {
    std::string vertSrc;    
    std::string fragSrc;    
};

std::string GetShaderSource(const std::string& shaderPath);
ShaderSrc GetShaderSource2(const std::string& vertPath, const std::string& fragPath);

uint CreateShader(uint shaderType, const std::string &shaderSrc);
uint CreateShader2(const std::string &VertSrc, const std::string &fragSrc);
