#pragma once
#include "../VertexArray.h"

enum class MeshType { Quad };

class QuadData {
private:
    static constexpr float positions[16] = {
        -5.0f, -5.0f, 0.0f, 0.0f,
         5.0f, -5.0f, 1.0f, 0.0f,
         5.0f,  5.0f, 1.0f, 1.0f,
        -5.0f,  5.0f, 0.0f, 1.0f,
    };
    static constexpr unsigned int indices[6] = {
        0, 1, 2, 
        0, 2, 3
    };

public:
    QuadData() = delete;
    
    static const float* GetVerticies() { return positions; }
    static const unsigned int SizeofVerticies() { return sizeof(positions); }
    static const unsigned int* GetIndicies() { return indices; }
    static const unsigned int CountofIndicies() { return 6; }

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
            case MeshType::Quad: return QuadData::GetVerticies();
            default: return nullptr;
        }
    }
    static const unsigned int SizeofVerticies(MeshType type) {
        switch (type) {
            case MeshType::Quad: return QuadData::SizeofVerticies();
            default: return 0;
        }
    }
    static const unsigned int* GetIndicies(MeshType type) {
        switch (type) {
            case MeshType::Quad: return QuadData::GetIndicies();
            default: return nullptr;
        }
    }
    static const unsigned int CountofIndicies(MeshType type) {
        switch (type) {
            case MeshType::Quad: return QuadData::CountofIndicies();
            default: return 0;
        }
    }
    static const VertexBufferLayout Layout(MeshType type) { 
        switch (type) {
            case MeshType::Quad: return QuadData::Layout();
            default: {
                VertexBufferLayout layout; 
                return layout;
            }
        }
    }
    
};
