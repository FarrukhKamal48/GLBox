#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec2 translation;
layout(location = 3) in vec2 scale;
layout(location = 4) in vec4 color;
out vec2 v_TexCoord;
out vec4 v_Color;
out float v_Radius;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * (vec4(position.x * scale.x, position.y * scale.y, position.z, position.w) + vec4(translation, 0.0f, 0.0f));
    v_TexCoord = texCoord;
    v_Color = color;
    v_Radius = scale.x;
};
