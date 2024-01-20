#pragma once
#include <string>
#include <vector>

struct ShaderSourceElement {
    unsigned int type;
    std::string src;
};

class ShaderProgram {
private:
    unsigned int m_RendererID;
    std::vector<ShaderSourceElement> m_Sources;
public:
    ShaderProgram();
    ~ShaderProgram();

    void Bind();
    void UnBind();

    void Push(unsigned int type, const std::string& srcPath);
    void Compile();
    void Use();

    template<typename T> void SetUniform(const std::string& name, T val);
    template<typename T> void SetUniformVec2(const std::string& name, T val1, T val2);
    template<typename T> void SetUniformVec3(const std::string& name, T val1, T val2, T val3);
    template<typename T> void SetUniformVec4(const std::string& name, T val1, T val2, T val3, T val4);

    inline const unsigned int GetID() const { return m_RendererID; }
};
