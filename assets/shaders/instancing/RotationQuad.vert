#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec2 translation;
layout(location = 3) in vec2 scale;
layout(location = 4) in float angle;
layout(location = 5) in vec4 color;
out vec2 v_TexCoord;
out vec4 v_Color;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * (vec4((position.x * scale.x)*cos(angle) - (position.y * scale.y)*sin(angle), (position.x * scale.x)*sin(angle) + (position.y * scale.y)*cos(angle), position.z, position.w) + vec4(translation, 0.0f, 0.0f));
    v_TexCoord = texCoord;
    v_Color = color;
};
