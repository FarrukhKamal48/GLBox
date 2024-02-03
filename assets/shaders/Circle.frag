#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform vec4 u_color;
uniform sampler2D u_Texture;

float CircleBound() {
    float dist = distance(v_TexCoord, vec2(0.5, 0.5));
    float val = 1-step(0.5, dist);
    return val;
}

void main() {
    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor * u_color;
    color.a = CircleBound();
};
