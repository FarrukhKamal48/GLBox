#pragma once
#include "../layer/Batch.h"
#include "../meshes/Quad.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

template<typename MeshType, int MeshesPerBatch>
class BatchRenderer {
public:
    std::unique_ptr<Shader> BatchShader;
private:
    Batch<MeshType, MeshesPerBatch> m_Batch;
    MeshType* m_SrcObjs;
    int m_ObjCount;

    glm::mat4 m_BatchProj;
    glm::mat4 m_BatchView;

public:
    BatchRenderer() : 
        m_BatchProj(glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f)), 
        m_BatchView(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    { }
    BatchRenderer(MeshType* srcObjs, int objCount, const glm::mat4& proj, const glm::mat4& view) : 
        m_SrcObjs(srcObjs), m_ObjCount(objCount), m_BatchProj(proj), m_BatchView(view)
    { }
    ~BatchRenderer() {}

    void ShaderInit(const std::string& vertSrcPath, const std::string& fragSrcPath) {
        BatchShader = std::make_unique<Shader>();
        BatchShader->Push(GL_VERTEX_SHADER, vertSrcPath);
        BatchShader->Push(GL_FRAGMENT_SHADER, fragSrcPath);
        BatchShader->Compile();
        BatchShader->Bind();
        BatchShader->SetUniformMat4("u_MVP", m_BatchProj * m_BatchView);
    }

    void DrawBatches() {
        unsigned int drawCalls = 0;
        for (int i=0; i<m_ObjCount; i+=MeshesPerBatch) {
            m_Batch.SetData(m_SrcObjs+i, m_ObjCount);
            m_Batch.Draw(*BatchShader);
            drawCalls++;
        }
    }
};

