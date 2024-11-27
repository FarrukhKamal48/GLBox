#pragma once
#include "GL/glew.h"
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

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
    const VertexLookup& m_Lookup;
    
public:
    InstanceRenderer(const VertexLookup& Lookup) : m_Lookup(Lookup) { }
    InstanceRenderer(unsigned int InstanceCount, void* data, const VertexLookup& Lookup) 
        : m_InstanceCount(InstanceCount), m_Data(data), m_DataSize(InstanceCount * Lookup.SizeOfVertex())
        , m_Lookup(Lookup) {
        Init();
    }
    ~InstanceRenderer() { }

    void SetData(unsigned int InstanceCount, void* data) {
        m_InstanceCount = InstanceCount;
        m_Data = data;
        m_DataSize = InstanceCount * m_Lookup.SizeOfVertex();
    }

    void Init() {
        Render::BasicBlend();

        m_VertexArray =  std::make_unique<VertexArray>();
        m_MeshBuffer = std::make_unique<VertexBuffer>(m_Lookup.MeshData(), m_Lookup.SizeOfMeshData());
        m_IndexBuffer =  std::make_unique<IndexBuffer>(m_Lookup.Indicies(), m_Lookup.CountofIndicies());
        m_InstanceBuffer = std::make_unique<VertexBuffer>(nullptr, m_DataSize, GL_DYNAMIC_DRAW);
        
        m_VertexArray->AddBuffer(*m_MeshBuffer, m_Lookup.MeshLayout());
        m_VertexArray->AddBuffer(*m_InstanceBuffer, m_Lookup.VertLayout(1));

        m_Proj = glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f);
        m_View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    }
    
    void ShaderInit(const std::string& vertSrcPath, const std::string& fragSrcPath) {
        InstanceShader = std::make_unique<Shader>();
        InstanceShader->Push(GL_VERTEX_SHADER, vertSrcPath);
        InstanceShader->Push(GL_FRAGMENT_SHADER, fragSrcPath);
        InstanceShader->Compile();
        InstanceShader->Bind();
        InstanceShader->SetUniformMat4("u_MVP", m_Proj * m_View);
    }

    void Draw() {
        m_InstanceBuffer->SetData(m_Data, m_DataSize);
        Render::DrawInstanced(*m_VertexArray, *m_IndexBuffer, *InstanceShader, m_InstanceCount);
    }
};

static std::vector<InstanceRenderer> Renderers;

class Pos_Quad {
public:
    inline static std::vector<Pos_Quad*> instances;
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

    Pos_Quad() : position(0) { instances.push_back(this); }
    ~Pos_Quad() { 
        auto it = std::find(instances.begin(), instances.end(), this);
        if (it != instances.end())
            instances.erase(it);
    }

    static VertexBufferLayout VertLayout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        return layout;
    }
    static const VertexBufferLayout MeshLayout() { 
        VertexBufferLayout MeshLayout;
        MeshLayout.Push<float>(2);
        MeshLayout.Push<float>(2);
        return MeshLayout; 
    }
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
    inline static std::vector<Pos_Col_Quad*> instances;
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

    Pos_Col_Quad() : position(0), color(0) { instances.push_back(this); }
    ~Pos_Col_Quad() {
        auto it = std::find(instances.begin(), instances.end(), this);
        if (it != instances.end())
            instances.erase(it);
    }

    static VertexBufferLayout VertLayout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        layout.Push<float>(4, divisor);
        return layout;
    }
    static const VertexBufferLayout MeshLayout() { 
        VertexBufferLayout MeshLayout;
        MeshLayout.Push<float>(2);
        MeshLayout.Push<float>(2);
        return MeshLayout; 
    }
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

    Pos_Scale_Col_Quad() : position(0), scale(0), color(0) { }
    ~Pos_Scale_Col_Quad() { }

    static Pos_Scale_Col_Quad* Instantiate(unsigned int count) {
        instances.insert(instances.end(), count, Pos_Scale_Col_Quad());
        // if (!renderer) {
        //     Renderers.push_back(InstanceRenderer(Pos_Col_Quad_Lookup()));
        //     renderer = &Renderers.back();
        // }
        // renderer->SetData(instances.size(), instances.data());
        return instances.data();
    }

    static VertexBufferLayout VertLayout(unsigned int divisor) {
        VertexBufferLayout layout;
        layout.Push<float>(2, divisor);
        layout.Push<float>(2, divisor);
        layout.Push<float>(4, divisor);
        return layout;
    }
    static const VertexBufferLayout MeshLayout() { 
        VertexBufferLayout MeshLayout;
        MeshLayout.Push<float>(2);
        MeshLayout.Push<float>(2);
        return MeshLayout; 
    }
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
