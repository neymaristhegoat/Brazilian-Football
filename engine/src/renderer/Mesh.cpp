#include "renderer/Mesh.h"
#include "core/Logger.h"
#include <GL/glew.h>

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
    if (m_Uploaded) {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }
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
    if (m_Uploaded) {
        // Delete old buffers
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }

    BF_LOG_DEBUG("Uploading mesh to GPU ({} vertices, {} indices)", 
                 m_Vertices.size(), m_Indices.size());

    // Create VAO
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    // Create VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), 
                 m_Vertices.data(), GL_STATIC_DRAW);

    // Create EBO
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(uint32_t), 
                 m_Indices.data(), GL_STATIC_DRAW);

    // Vertex attributes
    // Position (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (void*)offsetof(Vertex, position));

    // Normal (location 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (void*)offsetof(Vertex, normal));

    // TexCoord (location 2)
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (void*)offsetof(Vertex, texCoord));

    // Tangent (location 3)
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (void*)offsetof(Vertex, tangent));

    // Bitangent (location 4)
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 
                         (void*)offsetof(Vertex, bitangent));

    glBindVertexArray(0);

    m_Uploaded = true;
    BF_LOG_DEBUG("Mesh uploaded successfully (VAO: {})", m_VAO);
}

void Mesh::Bind() const {
    glBindVertexArray(m_VAO);
}

void Mesh::Unbind() const {
    glBindVertexArray(0);
}

void Mesh::Draw() const {
    if (!m_Uploaded) {
        BF_LOG_WARN("Attempting to draw non-uploaded mesh");
        return;
    }

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

// Helper function to create a cube mesh
std::shared_ptr<Mesh> Mesh::CreateCube(float size) {
    auto mesh = std::make_shared<Mesh>();
    float s = size * 0.5f;

    std::vector<Vertex> vertices = {
        // Front face
        {{-s, -s,  s}, {0, 0, 1}, {0, 0}, {1, 0, 0}, {0, 1, 0}},
        {{ s, -s,  s}, {0, 0, 1}, {1, 0}, {1, 0, 0}, {0, 1, 0}},
        {{ s,  s,  s}, {0, 0, 1}, {1, 1}, {1, 0, 0}, {0, 1, 0}},
        {{-s,  s,  s}, {0, 0, 1}, {0, 1}, {1, 0, 0}, {0, 1, 0}},

        // Back face
        {{ s, -s, -s}, {0, 0, -1}, {0, 0}, {-1, 0, 0}, {0, 1, 0}},
        {{-s, -s, -s}, {0, 0, -1}, {1, 0}, {-1, 0, 0}, {0, 1, 0}},
        {{-s,  s, -s}, {0, 0, -1}, {1, 1}, {-1, 0, 0}, {0, 1, 0}},
        {{ s,  s, -s}, {0, 0, -1}, {0, 1}, {-1, 0, 0}, {0, 1, 0}},

        // Top face
        {{-s,  s,  s}, {0, 1, 0}, {0, 0}, {1, 0, 0}, {0, 0, -1}},
        {{ s,  s,  s}, {0, 1, 0}, {1, 0}, {1, 0, 0}, {0, 0, -1}},
        {{ s,  s, -s}, {0, 1, 0}, {1, 1}, {1, 0, 0}, {0, 0, -1}},
        {{-s,  s, -s}, {0, 1, 0}, {0, 1}, {1, 0, 0}, {0, 0, -1}},

        // Bottom face
        {{-s, -s, -s}, {0, -1, 0}, {0, 0}, {1, 0, 0}, {0, 0, 1}},
        {{ s, -s, -s}, {0, -1, 0}, {1, 0}, {1, 0, 0}, {0, 0, 1}},
        {{ s, -s,  s}, {0, -1, 0}, {1, 1}, {1, 0, 0}, {0, 0, 1}},
        {{-s, -s,  s}, {0, -1, 0}, {0, 1}, {1, 0, 0}, {0, 0, 1}},

        // Right face
        {{ s, -s,  s}, {1, 0, 0}, {0, 0}, {0, 0, -1}, {0, 1, 0}},
        {{ s, -s, -s}, {1, 0, 0}, {1, 0}, {0, 0, -1}, {0, 1, 0}},
        {{ s,  s, -s}, {1, 0, 0}, {1, 1}, {0, 0, -1}, {0, 1, 0}},
        {{ s,  s,  s}, {1, 0, 0}, {0, 1}, {0, 0, -1}, {0, 1, 0}},

        // Left face
        {{-s, -s, -s}, {-1, 0, 0}, {0, 0}, {0, 0, 1}, {0, 1, 0}},
        {{-s, -s,  s}, {-1, 0, 0}, {1, 0}, {0, 0, 1}, {0, 1, 0}},
        {{-s,  s,  s}, {-1, 0, 0}, {1, 1}, {0, 0, 1}, {0, 1, 0}},
        {{-s,  s, -s}, {-1, 0, 0}, {0, 1}, {0, 0, 1}, {0, 1, 0}},
    };

    std::vector<uint32_t> indices;
    for (uint32_t i = 0; i < 6; i++) {
        uint32_t base = i * 4;
        indices.push_back(base + 0);
        indices.push_back(base + 1);
        indices.push_back(base + 2);
        indices.push_back(base + 0);
        indices.push_back(base + 2);
        indices.push_back(base + 3);
    }

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->Upload();

    return mesh;
}

// Helper function to create a plane mesh
std::shared_ptr<Mesh> Mesh::CreatePlane(float width, float height) {
    auto mesh = std::make_shared<Mesh>();
    float w = width * 0.5f;
    float h = height * 0.5f;

    std::vector<Vertex> vertices = {
        {{-w, 0, -h}, {0, 1, 0}, {0, 0}, {1, 0, 0}, {0, 0, 1}},
        {{ w, 0, -h}, {0, 1, 0}, {1, 0}, {1, 0, 0}, {0, 0, 1}},
        {{ w, 0,  h}, {0, 1, 0}, {1, 1}, {1, 0, 0}, {0, 0, 1}},
        {{-w, 0,  h}, {0, 1, 0}, {0, 1}, {1, 0, 0}, {0, 0, 1}},
    };

    std::vector<uint32_t> indices = {
        0, 1, 2,
        0, 2, 3
    };

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->Upload();

    return mesh;
}

// Helper function to create a sphere mesh
std::shared_ptr<Mesh> Mesh::CreateSphere(float radius, uint32_t segments, uint32_t rings) {
    auto mesh = std::make_shared<Mesh>();
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    const float PI = 3.14159265359f;

    for (uint32_t ring = 0; ring <= rings; ring++) {
        float theta = ring * PI / rings;
        float sinTheta = sin(theta);
        float cosTheta = cos(theta);

        for (uint32_t seg = 0; seg <= segments; seg++) {
            float phi = seg * 2.0f * PI / segments;
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);

            Vertex vertex;
            vertex.position[0] = radius * sinTheta * cosPhi;
            vertex.position[1] = radius * cosTheta;
            vertex.position[2] = radius * sinTheta * sinPhi;

            vertex.normal[0] = sinTheta * cosPhi;
            vertex.normal[1] = cosTheta;
            vertex.normal[2] = sinTheta * sinPhi;

            vertex.texCoord[0] = (float)seg / segments;
            vertex.texCoord[1] = (float)ring / rings;

            // Tangent and bitangent calculation
            vertex.tangent[0] = -sinPhi;
            vertex.tangent[1] = 0;
            vertex.tangent[2] = cosPhi;

            vertex.bitangent[0] = cosTheta * cosPhi;
            vertex.bitangent[1] = -sinTheta;
            vertex.bitangent[2] = cosTheta * sinPhi;

            vertices.push_back(vertex);
        }
    }

    for (uint32_t ring = 0; ring < rings; ring++) {
        for (uint32_t seg = 0; seg < segments; seg++) {
            uint32_t first = ring * (segments + 1) + seg;
            uint32_t second = first + segments + 1;

            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);

            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }

    mesh->SetVertices(vertices);
    mesh->SetIndices(indices);
    mesh->Upload();

    return mesh;
}

} // namespace renderer
} // namespace bf
