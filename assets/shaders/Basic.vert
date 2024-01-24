#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform vec2 u_Offset;

void main() {
    gl_Position = u_MVP * position + vec4(u_Offset, 0.0f, 0.0f);
    v_TexCoord = texCoord;
};
