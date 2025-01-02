#pragma once

#include "GLBox/Core/Buffer.h"
#include "GLBox/Core/Shader.h"
#include "GLBox/Renderer/VertexManager.h"

struct VertexData {
    unsigned int SizeOfObject;
    const std::vector<float>& MeshData;
    unsigned int SizeOfMeshData;
    const std::vector<unsigned int>& Indicies;
    unsigned int CountofIndicies;
    
    VertexData(const VertexManager* VManager)
        : SizeOfObject(VManager->SizeOfObject())
        , MeshData(VManager->MeshData())
        , SizeOfMeshData(MeshData.size() * sizeof(MeshData[0]))
        , Indicies(VManager->Indicies()) 
        , CountofIndicies(Indicies.size() * sizeof(Indicies[0]))
    { }
    ~VertexData() = default;
};

class InstanceRenderer {
public:
    std::shared_ptr<Shader> InstanceShader;
private:
    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
    std::shared_ptr<VertexBuffer> m_MeshBuffer;
    std::shared_ptr<VertexBuffer> m_InstanceBuffer;
    
    unsigned int m_InstanceCount;
    unsigned int m_TargetCount;
    
    void* m_Data;
    unsigned int m_OccupiedDataSize;
    unsigned int m_AllocatedDataSize;
    
    VertexData m_VData;
    VertexBufferLayout m_MeshLayout;
    VertexBufferLayout m_VertLayout;
    
public:
    InstanceRenderer(const InstanceRenderer& cp);
    InstanceRenderer(unsigned int InstanceCount, void* data, VertexManager* VManager);
    ~InstanceRenderer();

    void SetData(unsigned int InstanceCount, void* data);
    void Init();
    void CreateShader(const std::string& vertSrcPath, const std::string& fragSrcPath);
    void Draw();
};

