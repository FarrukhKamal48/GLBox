#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform vec4 u_Color;

float CircleBound(float radialMask) {
    float dist = distance(v_TexCoord, vec2(0.5, radialMask-0.01));
    float edgeSmooth = 0.02;
    return 1-smoothstep(radialMask-edgeSmooth, radialMask, dist);
}

void main() {
    color = u_Color;
    color.a = 1-CircleBound(0.32);
};
