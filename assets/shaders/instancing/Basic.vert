#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 3) in vec2 translation;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main() {
    gl_Position = u_MVP * (position + vec4(translation, 0.0f, 0.0f));
    v_TexCoord = texCoord;
};
