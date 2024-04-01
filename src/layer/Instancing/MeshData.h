#pragma once
#include "../VertexBufferLayout.h"

enum class MeshType { 
    Triangle,
    Quad,
};

class TriangleData {
public:
    TriangleData() = delete;
    
    static constexpr float Verticies[16] = {
        -5.0f, -5.0f, 0.0f, 0.0f,
         5.0f, -5.0f, 1.0f, 0.0f,
         5.0f,  5.0f, 1.0f, 1.0f,
        -5.0f,  5.0f, 0.0f, 1.0f,
    };
    static constexpr unsigned int Indicies[6] = {
        0, 1, 2, 
        0, 2, 3
    };

public:
    static const VertexBufferLayout Layout() { 
        VertexBufferLayout MeshLayout;
        MeshLayout.Push<float>(2);
        MeshLayout.Push<float>(2);
        return MeshLayout; 
    }
    
};
class QuadData {
public:
    QuadData() = delete;
    
    static constexpr float Verticies[16] = {
        -5.0f, -5.0f, 0.0f, 0.0f,
         5.0f, -5.0f, 1.0f, 0.0f,
         5.0f,  5.0f, 1.0f, 1.0f,
        -5.0f,  5.0f, 0.0f, 1.0f,
    };
    static constexpr unsigned int Indicies[6] = {
        0, 1, 2, 
        0, 2, 3
    };

public:
    static const VertexBufferLayout Layout() { 
        VertexBufferLayout MeshLayout;
        MeshLayout.Push<float>(2);
        MeshLayout.Push<float>(2);
        return MeshLayout; 
    }
    
};

class MeshLookup {
public:
    MeshLookup() = delete;

    static const float* GetVerticies(MeshType type) { 
        switch (type) {
            case MeshType::Triangle: return TriangleData::Verticies;
            case MeshType::Quad    : return QuadData::Verticies;
            default                : return nullptr;
        }
    }
    static const unsigned int SizeofVerticies(MeshType type) {
        switch (type) {
            case MeshType::Triangle: return sizeof(TriangleData::Verticies);
            case MeshType::Quad    : return sizeof(QuadData::Verticies);
            default                : return 0;
        }
    }
    static const unsigned int* GetIndicies(MeshType type) {
        switch (type) {
            case MeshType::Triangle: return TriangleData::Indicies;
            case MeshType::Quad    : return QuadData::Indicies;
            default                : return nullptr;
        }
    }
    static const unsigned int CountofIndicies(MeshType type) {
        switch (type) {
            case MeshType::Triangle: return sizeof(TriangleData::Indicies);
            case MeshType::Quad    : return sizeof(QuadData::Indicies);
            default                : return 0;
        }
    }
    static const VertexBufferLayout Layout(MeshType type) { 
        switch (type) {
            case MeshType::Triangle: return TriangleData::Layout();
            case MeshType::Quad    : return QuadData::Layout();
            default                : { VertexBufferLayout layout; return layout; }
        }
    }
    
};
