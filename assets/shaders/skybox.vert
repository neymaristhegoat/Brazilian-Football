#version 330 core

layout (location = 0) in vec3 aPosition;

out vec3 TexCoords;

uniform mat4 u_Projection;
uniform mat4 u_View;

void main() {
    TexCoords = aPosition;
    vec4 pos = u_Projection * mat4(mat3(u_View)) * vec4(aPosition, 1.0);
    gl_Position = pos.xyww; // Ensures skybox is always at max depth
}
