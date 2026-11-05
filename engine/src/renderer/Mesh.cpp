#include "renderer/Mesh.h"
#include "core/Logger.h"

namespace bf {
namespace renderer {

Mesh::Mesh()
    : m_VAO(0)
    , m_VBO(0)
    , m_EBO(0)
    , m_Uploaded(false)
{
}

Mesh::~Mesh() {
    // TODO: Delete GPU buffers
}

void Mesh::SetVertices(const std::vector<Vertex>& vertices) {
    m_Vertices = vertices;
    m_Uploaded = false;
}

void Mesh::SetIndices(const std::vector<uint32_t>& indices) {
    m_Indices = indices;
    m_Uploaded = false;
}

void Mesh::Upload() {
    if (m_Uploaded) return;

    BF_LOG_DEBUG("Uploading mesh to GPU ({} vertices, {} indices)", 
                 m_Vertices.size(), m_Indices.size());

    // TODO: Upload to GPU buffers
    
    m_Uploaded = true;
}

void Mesh::Bind() const {
    // TODO: Bind VAO
}

void Mesh::Unbind() const {
    // TODO: Unbind VAO
}

void Mesh::Draw() const {
    if (!m_Uploaded) {
        BF_LOG_WARN("Attempting to draw non-uploaded mesh");
        return;
    }

    // TODO: Draw mesh
}

} // namespace renderer
} // namespace bf
