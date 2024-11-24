#pragma once
#include "../../vendor/glm/ext/vector_float2.hpp"
#include "../../vendor/glm/ext/vector_float4.hpp"
#include "../VertexBufferLayout.h"
#include <algorithm>
#include <vector>

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
    inline static std::vector<Pos_Scale_Col_Quad*> instances;
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

    Pos_Scale_Col_Quad() : position(0), scale(0), color(0) { instances.push_back(this); }
    ~Pos_Scale_Col_Quad() { 
        auto it = std::find(instances.begin(), instances.end(), this);
        if (it != instances.end())
            instances.erase(it);
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

