#pragma once

#include <imgui.h>
#include "GLBox/Core/Layer.h"

class ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnEvent(Event& event) override;

    void OnAttach() override;
    void OnDetach() override;

    void Begin();
    void End();
    
    void SetDarkThemeColors();

    void SetBlockEvents(bool block) { m_BlockEvents = block; }
private:
    bool m_BlockEvents;
};
