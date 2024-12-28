#pragma once
#include <memory>
#include "Core/VertexArray.h"
#include "Core/IndexBuffer.h"
#include "Core/Shader.h"
#include "Core/Instancing/VertexManager.h"


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
    unsigned int m_TargetCount;
    void* m_Data;
    unsigned int m_OccupiedDataSize;
    unsigned int m_AllocatedDataSize;
    VertexManager* m_VManager;
    
public:
    InstanceRenderer(const InstanceRenderer& cp);
    InstanceRenderer(VertexManager* VManager);
    InstanceRenderer(unsigned int InstanceCount, void* data, VertexManager* VManager);
    ~InstanceRenderer();

    void SetData(unsigned int InstanceCount, void* data);
    void Init();
    void CreateShader(const std::string& vertSrcPath, const std::string& fragSrcPath);
    void Draw();
};

