#pragma once
#include <string>
#include <vector>

struct ShaderSrc {
    std::string vertSrc;    
    std::string fragSrc;    
};

std::string GetShaderSource(const std::string& shaderPath);
ShaderSrc GetShaderSource2(const std::string& vertPath, const std::string& fragPath);

unsigned int CreateShader(unsigned int shaderType, const std::string &shaderSrc);
unsigned int CreateShader2(const std::string &VertSrc, const std::string &fragSrc);

unsigned int CompileShader(unsigned int shaderType, const std::string& shaderSrc);

struct ShaderElement {
    unsigned int type;
    const std::string& src;
};

class Shader {
private:
    unsigned int m_RendererID;
    std::vector<ShaderElement> m_Sources;
public:
    Shader();
    ~Shader();

    void Bind();
    void UnBind();

    void AddSource(unsigned int type, std::string& srcPath);
    void Compile();
    void Use();
};
