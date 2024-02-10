#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec4 v_VertColor;

uniform vec4 u_Color;

void main() {
    color = u_Color * v_VertColor;
};
