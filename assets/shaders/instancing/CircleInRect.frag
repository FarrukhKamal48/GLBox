#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform float u_CullRadius = 0.32;
uniform float u_EdgeSmooth;

float CircleBound(float radialMask) {
    float dist = distance(v_TexCoord, vec2(0.5, 0.5));
    return 1-smoothstep(radialMask - u_EdgeSmooth, radialMask, dist);
}

void main() {
    color = u_Color;
    color.a = CircleBound(u_CullRadius);
};
