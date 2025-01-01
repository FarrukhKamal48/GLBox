#pragma once

#include <glm/ext/matrix_transform.hpp>

#include "GLBox/Core/Buffer.h"
#include "GLBox/Core/Shader.h"

#include "GLBox/Events/WindowEvent.h"
#include "GLBox/Renderer/Camera.h"


class RenderCommand {
public:
    RenderCommand() = delete;
    ~RenderCommand() = delete;
    
    static void Clear();
    static void Clear(float r, float g, float b, float a);
    static void BasicBlend();
    static void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
    static void DrawInstanced(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const int count);
    static void DrawAllInstanced(); 
    
    static void SetViewport(int x, int y, int width, int height);
    static void SetCamera(OrthoCamera& camera) { s_RenderData.Camera = &camera; };

    static void OnWindowResize(WindowResizeEvent& event);
    
    struct RenderData {
        unsigned int WindowWidth  = 1920;
        unsigned int WindowHeight = 1080;
        OrthoCamera* Camera;
    };
    
    static const RenderData& GetData() { return s_RenderData; }
private:
    static RenderData& GetRenderData() { return s_RenderData; }
    friend class InstanceRenderer;
private:
    static RenderData s_RenderData;
};
