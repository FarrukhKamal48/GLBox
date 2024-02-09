#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

float CircleBound(float radialMask) {
    float dist = distance(v_TexCoord, vec2(0.5, 0.5));
    float edgeSmooth = 0.02;
    return 1-smoothstep(radialMask-edgeSmooth, radialMask, dist);
}

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor * u_Color;
    color.a = CircleBound(0.5);
};
