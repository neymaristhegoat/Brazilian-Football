#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;
out mat3 TBN;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main() {
    FragPos = vec3(u_Model * vec4(aPosition, 1.0));
    Normal = mat3(transpose(inverse(u_Model))) * aNormal;
    TexCoord = aTexCoord;
    
    // TBN matrix for normal mapping
    vec3 T = normalize(vec3(u_Model * vec4(aTangent, 0.0)));
    vec3 B = normalize(vec3(u_Model * vec4(aBitangent, 0.0)));
    vec3 N = normalize(vec3(u_Model * vec4(aNormal, 0.0)));
    TBN = mat3(T, B, N);
    
    gl_Position = u_Projection * u_View * vec4(FragPos, 1.0);
}
