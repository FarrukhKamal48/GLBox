#pragma once
#include "../VertexBufferLayout.h"


class TriangleData {
public:
    TriangleData() = delete;
    
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
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f,
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

// ###################################################################################################
// ################################  MeshLookup  #####################################################
// ###################################################################################################

template<typename MeshT> class MeshLookup {};

template<>
class MeshLookup<QuadData> {
public:
    MeshLookup() = delete;

    static const float* GetVerticies()          { return QuadData::Verticies; }
    static const unsigned int SizeofVerticies() { return sizeof(QuadData::Verticies); }
    static const unsigned int* GetIndicies()    { return QuadData::Indicies; }
    static const unsigned int CountofIndicies() { return sizeof(QuadData::Indicies); }
    static const VertexBufferLayout Layout()    { return QuadData::Layout(); }
    
};

template<>
class MeshLookup<TriangleData> {
public:
    MeshLookup() = delete;

    static const float* GetVerticies()          { return TriangleData::Verticies; }
    static const unsigned int SizeofVerticies() { return sizeof(TriangleData::Verticies); }
    static const unsigned int* GetIndicies()    { return TriangleData::Indicies; }
    static const unsigned int CountofIndicies() { return sizeof(TriangleData::Indicies); }
    static const VertexBufferLayout Layout()    { return TriangleData::Layout(); }
    
};
