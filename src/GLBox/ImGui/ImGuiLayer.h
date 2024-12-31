#pragma once

#include <imgui.h>
#include "GLBox/Core/Layer.h"

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;

    void Begin();
    void End();
    
    void SetDarkThemeColors();
};
