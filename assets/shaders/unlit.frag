#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform bool u_UseTexture;

void main() {
    if (u_UseTexture) {
        FragColor = texture(u_Texture, TexCoord) * u_Color;
    } else {
        FragColor = u_Color;
    }
}
