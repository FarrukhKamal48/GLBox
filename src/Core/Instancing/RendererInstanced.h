#pragma once
#include <memory>
#include "Core/Buffer.h"
#include "Core/Shader.h"
#include "Core/Instancing/VertexManager.h"
#include "Core/VertexBufferLayout.h"

struct VertexData {
    unsigned int SizeOfObject;
    const std::vector<float>& MeshData;
    unsigned int SizeOfMeshData;
    const std::vector<unsigned int>& Indicies;
    unsigned int CountofIndicies;
    
    VertexData(const VertexManager* VManager)
        : MeshData(VManager->MeshData())
        , Indicies(VManager->Indicies()) {
        SizeOfObject = VManager->SizeOfObject();
        SizeOfMeshData = MeshData.size() * sizeof(MeshData[0]);
        CountofIndicies = Indicies.size() * sizeof(Indicies[0]);
    }
    ~VertexData() = default;
};

class InstanceRenderer {
public:
    std::shared_ptr<Shader> InstanceShader;
private:
    std::unique_ptr<VertexArray> m_VertexArray;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;
    std::unique_ptr<VertexBuffer> m_MeshBuffer;
    std::unique_ptr<VertexBuffer> m_InstanceBuffer;
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    
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
    // InstanceRenderer(VertexManager* VManager);
    InstanceRenderer(unsigned int InstanceCount, void* data, VertexManager* VManager);
    ~InstanceRenderer();

    void SetData(unsigned int InstanceCount, void* data);
    void Init();
    void CreateShader(const std::string& vertSrcPath, const std::string& fragSrcPath);
    void Draw();
};

