#pragma once
#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"
#include "../Renderer.h"

class InstanceRenderer;

class VertexManager {
public:
    virtual ~VertexManager() {}
    virtual VertexBufferLayout VertLayout(unsigned int divisor) const = 0;
    virtual unsigned int SizeOfObject() const = 0;
    virtual const float* MeshData() const = 0;
    virtual const unsigned int SizeOfMeshData() const = 0; 
    virtual const unsigned int* Indicies() const = 0; 
    virtual const unsigned int CountofIndicies() const = 0; 
    virtual const VertexBufferLayout MeshLayout() const = 0; 
    virtual const void* GetInstances() const = 0;
    virtual const void* GetRenderer() const = 0;
    virtual const unsigned int AllocateObject(unsigned int count, void (*ConfigureShader)(InstanceRenderer&)) const = 0;
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
    VertexBufferLayout VertLayout(unsigned int divisor) const override;
    const VertexBufferLayout MeshLayout()               const override;
    unsigned int SizeOfObject()                         const override;
    const float* MeshData()                             const override;
    const unsigned int* Indicies()                      const override;
    const unsigned int SizeOfMeshData()                 const override;
    const unsigned int CountofIndicies()                const override;
    const void* GetInstances()                          const override;
    const void* GetRenderer()                           const override;
    const unsigned int AllocateObject(unsigned int count, void (*ConfigureShader)(InstanceRenderer&)) const override;
    
    Pos_Scale_Col_Quad* Instantiate(unsigned int count, void (*ConfigureShader)(InstanceRenderer&));
private:
    static constexpr float m_Mesh[16] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    static constexpr unsigned int m_Indicies[6] = {
        0, 1, 2, 
        0, 2, 3
    };
public:
    inline static std::vector<Pos_Scale_Col_Quad> m_Instances;
    inline static InstanceRenderer* m_Renderer = nullptr;
};

