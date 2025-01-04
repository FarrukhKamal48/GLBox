#pragma once

#include <glbpch.h>
#include <glm/ext/matrix_transform.hpp>

#include "GLBox/Core/VertexBufferLayout.h"

class InstanceRenderer;

class VertexManager {
public:
    virtual ~VertexManager() {}
    virtual uint32_t SizeOfObject() const = 0;
    virtual const VertexBufferLayout MeshLayout() const = 0; 
    virtual VertexBufferLayout VertLayout(uint32_t divisor) const = 0;
    virtual const std::vector<float>& MeshData() const = 0;
    virtual const std::vector<uint32_t>& Indicies() const = 0; 
    virtual const uint32_t AllocateObject
        (uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader) const = 0;
};


class Pos_Scale_Col_Quad {
public:
    Pos_Scale_Col_Quad();
    ~Pos_Scale_Col_Quad();
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec4 color;
};

class Pos_Scale_Col_Quad_Manager : public VertexManager {
public:
    Pos_Scale_Col_Quad_Manager() {}
    ~Pos_Scale_Col_Quad_Manager() {}
    uint32_t SizeOfObject()                             const override;
    const VertexBufferLayout MeshLayout()                   const override;
    VertexBufferLayout VertLayout(uint32_t divisor)     const override;
    const std::vector<float>& MeshData()                    const override;
    const std::vector<uint32_t>& Indicies()             const override;
    const uint32_t AllocateObject(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader) const override;
    
    Pos_Scale_Col_Quad& operator[](uint32_t i);
private:
    inline static const std::vector<float> m_Mesh = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    inline static const std::vector<uint32_t> m_Indicies = {
        0, 1, 2, 
        0, 2, 3
    };
    inline static std::vector<Pos_Scale_Col_Quad> m_Instances = {};
    inline static int m_RendererI = -1;
};

class QuadTransform {
public:
    QuadTransform();
    ~QuadTransform();
    glm::vec3 position;
    glm::vec2 scale;
    float rotation;
    glm::vec4 color;
};

class QuadTransform_Manager : public VertexManager {
public:
    QuadTransform_Manager() {}
    ~QuadTransform_Manager() {}
    uint32_t SizeOfObject()                             const override;
    const VertexBufferLayout MeshLayout()               const override;
    VertexBufferLayout VertLayout(uint32_t divisor)     const override;
    const std::vector<float>& MeshData()                const override;
    const std::vector<uint32_t>& Indicies()             const override;
    const uint32_t AllocateObject(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader) const override;
    
    QuadTransform& operator[](uint32_t i);
private:
    inline static const std::vector<float> m_Mesh = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    inline static const std::vector<uint32_t> m_Indicies = {
        0, 1, 2, 
        0, 2, 3
    };
    inline static std::vector<QuadTransform> m_Instances = {};
    inline static int m_RendererI = -1;
};


