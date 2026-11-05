#include "renderer/Shader.h"
#include "core/Logger.h"
#include <fstream>
#include <sstream>

namespace bf {
namespace renderer {

Shader::Shader()
    : m_ProgramID(0)
{
}

Shader::~Shader() {
    // TODO: Delete shader program
}

bool Shader::LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
    std::ifstream vFile(vertexPath);
    std::ifstream fFile(fragmentPath);

    if (!vFile.is_open() || !fFile.is_open()) {
        BF_LOG_ERROR("Failed to open shader files: {} {}", vertexPath, fragmentPath);
        return false;
    }

    std::stringstream vStream, fStream;
    vStream << vFile.rdbuf();
    fStream << fFile.rdbuf();

    m_VertexSource = vStream.str();
    m_FragmentSource = fStream.str();

    return Compile();
}

bool Shader::LoadFromSource(const std::string& vertexSource, const std::string& fragmentSource) {
    m_VertexSource = vertexSource;
    m_FragmentSource = fragmentSource;
    return Compile();
}

void Shader::Bind() const {
    // TODO: Bind shader program
}

void Shader::Unbind() const {
    // TODO: Unbind shader program
}

void Shader::SetInt(const std::string& name, int value) {
    // TODO: Set uniform int
}

void Shader::SetFloat(const std::string& name, float value) {
    // TODO: Set uniform float
}

void Shader::SetVec2(const std::string& name, float x, float y) {
    // TODO: Set uniform vec2
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) {
    // TODO: Set uniform vec3
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) {
    // TODO: Set uniform vec4
}

void Shader::SetMat4(const std::string& name, const float* value) {
    // TODO: Set uniform mat4
}

bool Shader::Compile() {
    BF_LOG_INFO("Compiling shader...");
    // TODO: Compile shader stages and link program
    return true;
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
    // TODO: Compile individual shader stage
    return 0;
}

} // namespace renderer
} // namespace bf
