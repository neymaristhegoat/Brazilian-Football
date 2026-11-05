#pragma once

#include <cstdint>
#include <vector>

namespace bf {
namespace renderer {

struct Vertex {
    float position[3];
    float normal[3];
    float texCoord[2];
    float tangent[3];
    float bitangent[3];
};

class Mesh {
public:
    Mesh();
    ~Mesh();

    void SetVertices(const std::vector<Vertex>& vertices);
    void SetIndices(const std::vector<uint32_t>& indices);

    void Upload();
    void Bind() const;
    void Unbind() const;
    void Draw() const;

    size_t GetVertexCount() const { return m_Vertices.size(); }
    size_t GetIndexCount() const { return m_Indices.size(); }

private:
    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;

    uint32_t m_VAO;
    uint32_t m_VBO;
    uint32_t m_EBO;
    bool m_Uploaded;
};

} // namespace renderer
} // namespace bf
