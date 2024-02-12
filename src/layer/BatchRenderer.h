#pragma once
#include <iostream>
#include <memory>
#include <string>
#include "../layer/Batch.h"
#include "../primatives/Rect.primative.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

template<int batchSize>
class BatchRenderer {
public:
    std::unique_ptr<Shader> BatchShader;
private:
    Batch<batchSize> m_Batch;
    Primative::Rect* m_SrcObjs;
    int m_ObjCount;

    glm::mat4 m_BatchProj;
    glm::mat4 m_BatchView;

public:
    BatchRenderer() : 
        m_BatchProj(glm::ortho(0.0f, WIDTH, 0.0f, HEIGHT, -1.0f, 1.0f)), 
        m_BatchView(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
    { }
    BatchRenderer(Primative::Rect* srcObjs, int objCount, const glm::mat4& proj, const glm::mat4& view) : 
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
        Primative::Rect* batchptr = m_SrcObjs;
        Primative::Rect* endptr = m_SrcObjs + m_ObjCount-1;
        while (batchptr <= endptr) {
            m_Batch.SetData(batchptr, endptr);
            m_Batch.Draw(*BatchShader);
            batchptr += batchSize;
        }
    }
};
