#pragma once

#include "glm/ext/vector_float2.hpp"
#include "GLBox/Core/InputCodes.h"

class Input {
public:    
    Input() = delete;
    ~Input() = delete;

    static bool KeyPressed(KeyCode key);
    static bool KeyReleased(KeyCode key);
    
    static bool MousePressed(MouseCode button);
    static bool MouseReleased(MouseCode button);
    
    static glm::vec2 MousePos();
    static glm::vec2 MouseDelta();
    static float MouseX();
    static float MouseY();
};
