#pragma once

#include <glbpch.h>
#include <glm/glm.hpp>

struct ShaderSourceElement {
    unsigned int type;
    std::string src;
};

class Shader {
private:
    unsigned int m_RendererID;
    ShaderSourceElement m_Sources[2];
    std::unordered_map<std::string, int> m_UniformLocationCache;
public:
    Shader();
    ~Shader();

    void Bind() const;
    void UnBind() const;

    void Push(unsigned int type, const std::string& srcPath);
    void Compile();

    template<typename T> void SetUniform(const std::string& name, T val);
    template<typename T> void SetUniformVec2(const std::string& name, T val1, T val2);
    template<typename T> void SetUniformVec3(const std::string& name, T val1, T val2, T val3);
    template<typename T> void SetUniformVec4(const std::string& name, T val1, T val2, T val3, T val4);
    void SetUniformMat4(const std::string& name, const glm::mat4& mat);

    inline const unsigned int GetID() const { return m_RendererID; }
private:
    int GetUniformLocation(const std::string& name);
};
