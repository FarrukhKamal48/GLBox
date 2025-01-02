#pragma once

#include <glm/ext/matrix_transform.hpp>

#include "GLBox/Core/Buffer.h"
#include "GLBox/Core/Shader.h"

#include "GLBox/Events/WindowEvent.h"
#include "GLBox/Renderer/Camera.h"
#include "GLBox/Renderer/UnifromBuffer.h"


class Renderer {
public:
    Renderer() = delete;
    ~Renderer() = delete;
    
    static void Clear();
    static void Clear(float r, float g, float b, float a);
    static void BasicBlend();
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int count);
    static void DrawAllInstanced(); 
    
    static void SetViewport(int x, int y, int width, int height);
    static void SetCamera(OrthoCamera& camera);
    static OrthoCamera& GetCamera() { return *s_RenderData.Camera; };

    static void OnWindowResize(WindowResizeEvent& event);
    
    struct RenderData {
        OrthoCamera* Camera;
        std::unique_ptr<UniformBuffer> CameraBuffer;
    };
    
private:
    static RenderData s_RenderData;
};
