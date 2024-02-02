#pragma once
#include <memory>
#include "GL/glew.h"

#include "Scene.h"
#include "../Renderer.h"
#include "../Texture.h"
#include "../vendor/glm/ext/matrix_transform.hpp"
#include "../vendor/glm/ext/matrix_clip_space.hpp"

namespace Scene {

class Triangle : public Scene {
private:
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IBO;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<Texture> m_Texture;
    
    glm::vec3 m_Offset;
    glm::mat4 m_Proj, m_View;
    
public:
    Triangle() 
        : m_Offset(960, 540, 0),
        m_Proj(glm::ortho(0, 1920, 0, 1080, -1, 1)),
        m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    {
        
        float positions[4*4] = {
            -100.0f, -100.0f, 0.0f, 0.0f,
             100.0f, -100.0f, 1.0f, 0.0f,
             100.0f,  100.0f, 1.0f, 1.0f,
            -100.0f,  100.0f, 0.0f, 1.0f,
        };
        unsigned int indices[4*2] = {
            0, 1, 2, 
            0, 2, 3
        };
        
        Renderer renderer;
        renderer.BasicBlend();

        m_VAO = std::make_unique<VertexArray>();
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        m_IBO = std::make_unique<IndexBuffer>(indices, 6);

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Offset);
        glm::mat4 mvp = m_Proj * m_View * model;
        
        m_Shader = std::make_unique<Shader>();
        m_Shader->Push(GL_VERTEX_SHADER, "assets/shaders/Basic.vert");
        m_Shader->Push(GL_FRAGMENT_SHADER, "assets/shaders/Basic.frag");
        m_Shader->Compile();
        m_Shader->Bind();
        m_Shader->SetUniformVec4("u_color", 0.0f, 0.5f, 1.0f, 1.0f);
        m_Shader->SetUniformMat4("u_MVP", mvp);
        m_Shader->SetUniformVec2("u_Offset", 0.0f, 0.0f);

        m_Texture = std::make_unique<Texture>("assets/textures/tes_1000x1000px.png");
        m_Shader->SetUniform("u_Texture", m_Texture->GetSlot());
        
    }
    ~Triangle() {
        
    }
    
    void Update (float deltaTime) override {
        
    }
    
    template <typename T>
    T Lerp(T a, T b, T t) {
        return a + (b-a)*t;
    }
    
    void Render() override {
        Renderer renderer;
        renderer.Clear();

        m_Texture->Bind();

        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Offset);
        glm::mat4 mvp = m_Proj * m_View * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }
    
    void ImGuiRender() override {
        
    }
    
};

};
