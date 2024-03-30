#pragma once
#include "../Renderer.h"

class QuadData {
private:
    static constexpr const float positions[16] = {
        -5.0f, -5.0f, 0.0f, 0.0f,
         5.0f, -5.0f, 1.0f, 0.0f,
         5.0f,  5.0f, 1.0f, 1.0f,
        -5.0f,  5.0f, 0.0f, 1.0f,
    };
    static constexpr const unsigned int indices[6] = {
        0, 1, 2, 
        0, 2, 3
    };

public:
    QuadData() { }
    ~QuadData() { }
    
    static const float* GetVerticies() { return positions; }
    static const unsigned int SizeofVerticies() { return sizeof(positions); }
    static const unsigned int* GetIndicies() { return indices; }
    static const unsigned int SizeofIndicies() { return sizeof(positions); }

    static const VertexBufferLayout Layout() { 
        VertexBufferLayout MeshLayout;
        MeshLayout.Push<float>(2);
        MeshLayout.Push<float>(2);
        return MeshLayout; 
    }
    
};
