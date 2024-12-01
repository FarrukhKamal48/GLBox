#pragma once
#include <memory>

#include "../../vendor/glm/ext/matrix_transform.hpp"
#include "../../vendor/glm/ext/matrix_clip_space.hpp"
#include "../Renderer.h"

class VertexLookup {
public:
    virtual ~VertexLookup() {}
    virtual VertexBufferLayout VertLayout(unsigned int divisor) const = 0;
    virtual unsigned int SizeOfVertex() const = 0;
    virtual const float* MeshData() const = 0;
    virtual const unsigned int SizeOfMeshData() const = 0; 
    virtual const unsigned int* Indicies() const = 0; 
    virtual const unsigned int CountofIndicies() const = 0; 
    virtual const VertexBufferLayout MeshLayout() const = 0; 
};

class InstanceRenderer {
public:
    std::unique_ptr<Shader> InstanceShader;
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_MeshBuffer;
    std::unique_ptr<VertexBuffer> m_InstanceBuffer;
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    
    unsigned int m_InstanceCount;
    void* m_Data;
    unsigned int m_DataSize;
    VertexLookup* m_Lookup;
    
public:
    InstanceRenderer(const InstanceRenderer& cp);
    InstanceRenderer(VertexLookup* Lookup);
    InstanceRenderer(unsigned int InstanceCount, void* data, VertexLookup* Lookup);
    ~InstanceRenderer();

    void SetData(unsigned int InstanceCount, void* data);
    void Init();
    void ShaderInit(const std::string& vertSrcPath, const std::string& fragSrcPath);
    void Draw();
};

static std::vector<InstanceRenderer> Renderers;

class Pos_Quad {
public:
    inline static std::vector<Pos_Quad> instances;
    inline static InstanceRenderer* renderer;
    glm::vec2 position;
    static constexpr float Verticies[16] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    static constexpr unsigned int Indicies[6] = {
        0, 1, 2, 
        0, 2, 3
    };

    Pos_Quad();
    ~Pos_Quad();

    static Pos_Quad* Instantiate(unsigned int count);
    static const VertexBufferLayout VertLayout(unsigned int divisor);
    static const VertexBufferLayout MeshLayout();
};

class Pos_Quad_Lookup : public VertexLookup {
public:
    Pos_Quad_Lookup() {}
    ~Pos_Quad_Lookup() {}
    VertexBufferLayout VertLayout(unsigned int divisor) const override { return Pos_Quad::VertLayout(divisor); }
    unsigned int SizeOfVertex()                         const override { return sizeof(Pos_Quad); }
    const float* MeshData()                             const override { return Pos_Quad::Verticies; }
    const unsigned int* Indicies()                      const override { return Pos_Quad::Indicies; }
    const unsigned int SizeOfMeshData()                 const override { return sizeof(Pos_Quad::Verticies); }
    const unsigned int CountofIndicies()                const override { return sizeof(Pos_Quad::Indicies); }
    const VertexBufferLayout MeshLayout()               const override { return Pos_Quad::MeshLayout(); }
};

class Pos_Col_Quad {
public:
    inline static std::vector<Pos_Col_Quad> instances;
    inline static InstanceRenderer* renderer = nullptr;
    glm::vec2 position;
    glm::vec4 color;
    static constexpr float Verticies[16] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    static constexpr unsigned int Indicies[6] = {
        0, 1, 2, 
        0, 2, 3
    };

    Pos_Col_Quad();
    ~Pos_Col_Quad();

    static Pos_Col_Quad* Instantiate(unsigned int count);
    static const VertexBufferLayout VertLayout(unsigned int divisor);
    static const VertexBufferLayout MeshLayout();
};

class Pos_Col_Quad_Lookup : public VertexLookup {
public:
    Pos_Col_Quad_Lookup() {}
    ~Pos_Col_Quad_Lookup() {}
    VertexBufferLayout VertLayout(unsigned int divisor) const override { return Pos_Col_Quad::VertLayout(divisor); }
    unsigned int SizeOfVertex()                         const override { return sizeof(Pos_Col_Quad); }
    const float* MeshData()                             const override { return Pos_Col_Quad::Verticies; }
    const unsigned int* Indicies()                      const override { return Pos_Col_Quad::Indicies; }
    const unsigned int SizeOfMeshData()                 const override { return sizeof(Pos_Col_Quad::Verticies); }
    const unsigned int CountofIndicies()                const override { return sizeof(Pos_Col_Quad::Indicies); }
    const VertexBufferLayout MeshLayout()               const override { return Pos_Col_Quad::MeshLayout(); }
};

class Pos_Scale_Col_Quad {
public:
    inline static std::vector<Pos_Scale_Col_Quad> instances;
    inline static InstanceRenderer* renderer = nullptr;
    glm::vec2 position;
    glm::vec2 scale;
    glm::vec4 color;
    static constexpr float Verticies[16] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
    };
    static constexpr unsigned int Indicies[6] = {
        0, 1, 2, 
        0, 2, 3
    };

    Pos_Scale_Col_Quad();
    ~Pos_Scale_Col_Quad();

    static Pos_Scale_Col_Quad* Instantiate(unsigned int count);
    static const VertexBufferLayout VertLayout(unsigned int divisor);
    static const VertexBufferLayout MeshLayout();
};

class Pos_Scale_Col_Quad_Lookup : public VertexLookup {
public:
    Pos_Scale_Col_Quad_Lookup() {}
    ~Pos_Scale_Col_Quad_Lookup() {}
    VertexBufferLayout VertLayout(unsigned int divisor) const override { return Pos_Scale_Col_Quad::VertLayout(divisor); }
    unsigned int SizeOfVertex()                         const override { return sizeof(Pos_Scale_Col_Quad); }
    const float* MeshData()                             const override { return Pos_Scale_Col_Quad::Verticies; }
    const unsigned int* Indicies()                      const override { return Pos_Scale_Col_Quad::Indicies; }
    const unsigned int SizeOfMeshData()                 const override { return sizeof(Pos_Scale_Col_Quad::Verticies); }
    const unsigned int CountofIndicies()                const override { return sizeof(Pos_Scale_Col_Quad::Indicies); }
    const VertexBufferLayout MeshLayout()               const override { return Pos_Scale_Col_Quad::MeshLayout(); }
};


namespace Render {
    void InitAllInstanced();
    void InitAllInstanced(void (*shaderInit)(InstanceRenderer&));
    void DrawAllInstanced(); 
}
