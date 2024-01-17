#pragma once
#include <string>
#include <sys/types.h>

struct ShaderSrc {
    std::string vertSrc;    
    std::string fragSrc;    
};

std::string ParseShader(const std::string& shaderPath);
uint CreateShader(uint shaderType, const std::string &shaderSrc);
uint CreateShader2(const std::string &VertSrc, const std::string &fragSrc);
