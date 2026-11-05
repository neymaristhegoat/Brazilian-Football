#include "renderer/Shader.h"
#include "core/Logger.h"
#include <GL/glew.h>
#include <fstream>
#include <sstream>

namespace bf {
namespace renderer {

Shader::Shader()
    : m_ProgramID(0)
{
}

Shader::~Shader() {
    if (m_ProgramID) {
        glDeleteProgram(m_ProgramID);
    }
}

bool Shader::LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath) {
    BF_LOG_INFO("Loading shader: {} + {}", vertexPath, fragmentPath);
    
    // Read vertex shader
    std::ifstream vFile(vertexPath);
    if (!vFile.is_open()) {
        BF_LOG_ERROR("Failed to open vertex shader: {}", vertexPath);
        return false;
    }
    std::stringstream vStream;
    vStream << vFile.rdbuf();
    m_VertexSource = vStream.str();
    vFile.close();

    // Read fragment shader
    std::ifstream fFile(fragmentPath);
    if (!fFile.is_open()) {
        BF_LOG_ERROR("Failed to open fragment shader: {}", fragmentPath);
        return false;
    }
    std::stringstream fStream;
    fStream << fFile.rdbuf();
    m_FragmentSource = fStream.str();
    fFile.close();

    return Compile();
}

bool Shader::LoadFromSource(const std::string& vertexSource, const std::string& fragmentSource) {
    m_VertexSource = vertexSource;
    m_FragmentSource = fragmentSource;
    return Compile();
}

bool Shader::Compile() {
    BF_LOG_DEBUG("Compiling shader program...");

    // Compile vertex shader
    uint32_t vertexShader = CompileShader(GL_VERTEX_SHADER, m_VertexSource);
    if (vertexShader == 0) {
        BF_LOG_ERROR("Failed to compile vertex shader");
        return false;
    }

    // Compile fragment shader
    uint32_t fragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_FragmentSource);
    if (fragmentShader == 0) {
        BF_LOG_ERROR("Failed to compile fragment shader");
        glDeleteShader(vertexShader);
        return false;
    }

    // Link program
    m_ProgramID = glCreateProgram();
    glAttachShader(m_ProgramID, vertexShader);
    glAttachShader(m_ProgramID, fragmentShader);
    glLinkProgram(m_ProgramID);

    // Check linking
    GLint success;
    glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_ProgramID, 512, nullptr, infoLog);
        BF_LOG_ERROR("Shader program linking failed: {}", infoLog);
        
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(m_ProgramID);
        m_ProgramID = 0;
        return false;
    }

    // Clean up shaders (no longer needed after linking)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    BF_LOG_INFO("Shader compiled successfully (ID: {})", m_ProgramID);
    return true;
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source) {
    uint32_t shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Check compilation
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        const char* typeStr = (type == GL_VERTEX_SHADER) ? "vertex" : "fragment";
        BF_LOG_ERROR("{} shader compilation failed: {}", typeStr, infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

void Shader::Bind() const {
    glUseProgram(m_ProgramID);
}

void Shader::Unbind() const {
    glUseProgram(0);
}

void Shader::SetInt(const std::string& name, int value) const {
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    if (location != -1) {
        glUniform1i(location, value);
    }
}

void Shader::SetFloat(const std::string& name, float value) const {
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    if (location != -1) {
        glUniform1f(location, value);
    }
}

void Shader::SetVec2(const std::string& name, float x, float y) const {
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    if (location != -1) {
        glUniform2f(location, x, y);
    }
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const {
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    if (location != -1) {
        glUniform3f(location, x, y, z);
    }
}

void Shader::SetVec4(const std::string& name, float x, float y, float z, float w) const {
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    if (location != -1) {
        glUniform4f(location, x, y, z, w);
    }
}

void Shader::SetMat4(const std::string& name, const float* value) const {
    GLint location = glGetUniformLocation(m_ProgramID, name.c_str());
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, value);
    }
}

void Shader::SetBool(const std::string& name, bool value) const {
    SetInt(name, value ? 1 : 0);
}

} // namespace renderer
} // namespace bf
