#pragma once

#include <glbpch.h>

#include "GLBox/Core/Buffer.h"
#include "GLBox/Core/Shader.h"
#include "GLBox/Renderer/VertexManager.h"

struct VertexData {
    uint32_t SizeOfObject;
    const std::vector<float>& MeshData;
    uint32_t SizeOfMeshData;
    const std::vector<uint32_t>& Indicies;
    uint32_t CountofIndicies;
    
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
    
    uint32_t m_InstanceCount;
    uint32_t m_TargetCount;
    
    void* m_Data;
    uint32_t m_OccupiedDataSize;
    uint32_t m_AllocatedDataSize;
    
    VertexData m_VData;
    VertexBufferLayout m_MeshLayout;
    VertexBufferLayout m_VertLayout;
    
    static std::vector<InstanceRenderer> s_Renderers;
public:
    InstanceRenderer(const InstanceRenderer& cp);
    InstanceRenderer(uint32_t InstanceCount, void* data, VertexManager* VManager);
    ~InstanceRenderer();

    void SetData(uint32_t InstanceCount, void* data);
    void Init();
    void CreateShader(const std::string& vertSrcPath, const std::string& fragSrcPath);
    void Draw();

    template <class Object>
    static uint32_t AllocateObj(uint32_t count, std::function<void(InstanceRenderer&)> ConfigureShader, VertexManager* VManager, 
                                      std::vector<Object>& instances, int& rendererI) {
        uint32_t lastSize = instances.size();
        instances.insert(instances.end(), count, Object());
        if (rendererI == -1) {
            rendererI = s_Renderers.size();
            s_Renderers.emplace_back(instances.size(), instances.data(), VManager);
            ConfigureShader(s_Renderers[rendererI]);
        } else
            s_Renderers[rendererI].SetData(instances.size(), instances.data());
        delete VManager;
        return lastSize;
    }
private:
    friend class Renderer;
};


