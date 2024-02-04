#pragma once
#include <memory>
#include "../Renderer.h"
#include "../Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

namespace Primative {

class Circle {
public:
    std::unique_ptr<VertexArray> vertexArray;
    std::unique_ptr<IndexBuffer> indexBuffer;
    std::unique_ptr<Shader> shader;
private:
    std::unique_ptr<VertexBuffer> m_VertexBuffer;

    glm::vec2 m_Centre;
    float m_Radius;
    
    glm::mat4 m_Proj;
    glm::mat4 m_View;
    glm::mat4 m_Model;
    glm::mat4 m_MVP;
public:
    Circle(glm::mat4 proj, glm::mat4 view, glm::vec2 centre, float radius) :
        m_Centre(centre),
        m_Radius(radius),
        m_Proj(proj),
        m_View(view),
        m_Model(glm::translate(glm::mat4(1.0f), glm::vec3(centre, 0.0f))),
        m_MVP(m_Proj * m_View * m_Model)
    { 
        float positions[] = {
            -m_Radius, -m_Radius, 0.0f, 0.0f,
             m_Radius, -m_Radius, 1.0f, 0.0f,
             0.0f                 ,  m_Radius, 0.5f, 1.0f,
        };
        unsigned int indices[] = {
            0, 1, 2, 
        };
        
        Renderer renderer;
        renderer.BasicBlend();

        vertexArray = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 3 * 4 * sizeof(float));
        indexBuffer =  std::make_unique<IndexBuffer>(indices, 3);
        
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        vertexArray->AddBuffer(*m_VertexBuffer, layout);
        
        shader = std::make_unique<Shader>();
        shader->Push(GL_VERTEX_SHADER, "assets/shaders/Basic.vert");
        shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/CircleSolid.frag");
        shader->Compile();
        shader->Bind();
        shader->SetUniformVec4("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
        shader->SetUniformMat4("u_MVP", m_MVP);
    }
    ~Circle() { }

    void SetCentre(glm::vec2 position) {
        m_Centre = position;
        m_Model = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
        m_MVP = m_Proj * m_View * m_Model;
        shader->SetUniformMat4("u_MVP", m_MVP);
    }
   
};

}
