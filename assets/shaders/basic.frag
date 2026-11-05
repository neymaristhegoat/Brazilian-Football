#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
in mat3 TBN;

// Material properties
uniform vec3 u_Albedo;
uniform float u_Metallic;
uniform float u_Roughness;
uniform float u_AO;

// Textures
uniform sampler2D u_AlbedoMap;
uniform sampler2D u_NormalMap;
uniform sampler2D u_MetallicMap;
uniform sampler2D u_RoughnessMap;
uniform sampler2D u_AOMap;

uniform bool u_UseAlbedoMap;
uniform bool u_UseNormalMap;

// Lighting
uniform vec3 u_LightDirection;
uniform vec3 u_LightColor;
uniform vec3 u_ViewPos;

const float PI = 3.14159265359;

vec3 getNormalFromMap() {
    if (!u_UseNormalMap) {
        return normalize(Normal);
    }
    
    vec3 tangentNormal = texture(u_NormalMap, TexCoord).xyz * 2.0 - 1.0;
    return normalize(TBN * tangentNormal);
}

void main() {
    vec3 albedo = u_UseAlbedoMap ? texture(u_AlbedoMap, TexCoord).rgb : u_Albedo;
    vec3 normal = getNormalFromMap();
    
    // Simple diffuse lighting
    vec3 lightDir = normalize(-u_LightDirection);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;
    
    // Ambient
    vec3 ambient = vec3(0.1) * albedo * u_AO;
    
    // Combine
    vec3 color = ambient + diffuse * albedo;
    
    // Gamma correction
    color = pow(color, vec3(1.0/2.2));
    
    FragColor = vec4(color, 1.0);
}
