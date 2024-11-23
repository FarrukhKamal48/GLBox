#pragma once
#include "../../vendor/glm/ext/vector_float2.hpp"
#include "../../vendor/glm/ext/vector_float4.hpp"
#include "../VertexBufferLayout.h"
#include <algorithm>
#include <vector>

template<typename VertexT> 
class VertexLookup {
public:
    VertexLookup() = delete;
    static VertexBufferLayout VertLayout(unsigned int divisor);
    static unsigned int SizeOfVertex();
    static const float* MeshData();
    static const unsigned int SizeofMeshData(); 
    static const unsigned int* Indicies(); 
    static const unsigned int CountofIndicies(); 
    static const VertexBufferLayout MeshLayout(); 
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

template<>
class VertexLookup<Pos_Quad> {
public:
    VertexLookup() = delete;
    static VertexBufferLayout Layout(unsigned int divisor)  { return Pos_Quad::VertLayout(divisor); }
    static unsigned int SizeOfVertex()                      { return sizeof(Pos_Quad); }
    static const float* MeshData()                          { return Pos_Quad::Verticies; }
    static const unsigned int* Indicies()                   { return Pos_Quad::Indicies; }
    static const unsigned int SizeofVerticies()             { return sizeof(Pos_Quad::Verticies); }
    static const unsigned int CountofIndicies()             { return sizeof(Pos_Quad::Indicies); }
    static const VertexBufferLayout MeshLayout()            { return Pos_Quad::MeshLayout(); }
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

template<>
class VertexLookup<Pos_Col_Quad> {
public:
    VertexLookup() = delete;
    static VertexBufferLayout Layout(unsigned int divisor)  { return Pos_Col_Quad::VertLayout(divisor); }
    static unsigned int SizeOfVertex()                      { return sizeof(Pos_Col_Quad); }
    static const float* MeshData()                          { return Pos_Col_Quad::Verticies; }
    static const unsigned int* Indicies()                   { return Pos_Col_Quad::Indicies; }
    static const unsigned int SizeofVerticies()             { return sizeof(Pos_Col_Quad::Verticies); }
    static const unsigned int CountofIndicies()             { return sizeof(Pos_Col_Quad::Indicies); }
    static const VertexBufferLayout MeshLayout()            { return Pos_Col_Quad::MeshLayout(); }
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

template<>
class VertexLookup<Pos_Scale_Col_Quad> {
public:
    VertexLookup() = delete;
    static VertexBufferLayout VertLayout(unsigned int divisor)  { return Pos_Scale_Col_Quad::VertLayout(divisor); }
    static unsigned int SizeOfVertex()                          { return sizeof(Pos_Scale_Col_Quad); }
    static const float* MeshData()                              { return Pos_Scale_Col_Quad::Verticies; }
    static const unsigned int* Indicies()                       { return Pos_Scale_Col_Quad::Indicies; }
    static const unsigned int SizeofVerticies()                 { return sizeof(Pos_Scale_Col_Quad::Verticies); }
    static const unsigned int CountofIndicies()                 { return sizeof(Pos_Scale_Col_Quad::Indicies); }
    static const VertexBufferLayout MeshLayout()                { return Pos_Scale_Col_Quad::MeshLayout(); }
};

