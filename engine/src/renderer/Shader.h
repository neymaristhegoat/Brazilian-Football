#pragma once

#include <cstdint>
#include <string>
#include <memory>

namespace bf {
namespace renderer {

class Shader {
public:
    Shader();
    ~Shader();

    bool LoadFromFile(const std::string& vertexPath, const std::string& fragmentPath);
    bool LoadFromSource(const std::string& vertexSource, const std::string& fragmentSource);
    
    void Bind() const;
    void Unbind() const;

    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVec2(const std::string& name, float x, float y) const;
    void SetVec3(const std::string& name, float x, float y, float z) const;
    void SetVec4(const std::string& name, float x, float y, float z, float w) const;
    void SetMat4(const std::string& name, const float* value) const;
    void SetBool(const std::string& name, bool value) const;

    uint32_t GetID() const { return m_ProgramID; }

private:
    bool Compile();
    uint32_t CompileShader(uint32_t type, const std::string& source);

private:
    uint32_t m_ProgramID;
    std::string m_VertexSource;
    std::string m_FragmentSource;
};

} // namespace renderer
} // namespace bf
