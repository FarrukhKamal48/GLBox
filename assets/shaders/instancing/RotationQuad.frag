#version 440 core

layout(location = 0) out vec4 color;
in vec4 v_Color;
in vec2 v_TexCoord;

void main() {
    color = v_Color;
};
