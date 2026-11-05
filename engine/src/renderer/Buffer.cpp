#include "renderer/Buffer.h"
#include "core/Logger.h"
#include <GL/glew.h>

namespace bf {
namespace renderer {

static GLenum BufferUsageToGL(BufferUsage usage) {
    switch (usage) {
        case BufferUsage::Static:  return GL_STATIC_DRAW;
        case BufferUsage::Dynamic: return GL_DYNAMIC_DRAW;
        case BufferUsage::Stream:  return GL_STREAM_DRAW;
    }
    return GL_STATIC_DRAW;
}

// VertexBuffer Implementation
VertexBuffer::VertexBuffer()
    : m_BufferID(0)
    , m_Size(0)
    , m_Usage(BufferUsage::Static)
{
    glGenBuffers(1, &m_BufferID);
}

VertexBuffer::VertexBuffer(const void* data, uint32_t size, BufferUsage usage)
    : m_BufferID(0)
    , m_Size(size)
    , m_Usage(usage)
{
    glGenBuffers(1, &m_BufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, BufferUsageToGL(usage));
}

VertexBuffer::~VertexBuffer() {
    if (m_BufferID) {
        glDeleteBuffers(1, &m_BufferID);
    }
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, uint32_t size) {
    m_Size = size;
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ARRAY_BUFFER, size, data, BufferUsageToGL(m_Usage));
}

void VertexBuffer::SetSubData(const void* data, uint32_t size, uint32_t offset) {
    glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

// IndexBuffer Implementation
IndexBuffer::IndexBuffer()
    : m_BufferID(0)
    , m_Count(0)
    , m_Usage(BufferUsage::Static)
{
    glGenBuffers(1, &m_BufferID);
}

IndexBuffer::IndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage)
    : m_BufferID(0)
    , m_Count(count)
    , m_Usage(usage)
{
    glGenBuffers(1, &m_BufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, BufferUsageToGL(usage));
}

IndexBuffer::~IndexBuffer() {
    if (m_BufferID) {
        glDeleteBuffers(1, &m_BufferID);
    }
}

void IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void IndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::SetData(const uint32_t* indices, uint32_t count) {
    m_Count = count;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, BufferUsageToGL(m_Usage));
}

// VertexArray Implementation
VertexArray::VertexArray()
    : m_ArrayID(0)
{
    glGenVertexArrays(1, &m_ArrayID);
}

VertexArray::~VertexArray() {
    if (m_ArrayID) {
        glDeleteVertexArrays(1, &m_ArrayID);
    }
}

void VertexArray::Bind() const {
    glBindVertexArray(m_ArrayID);
}

void VertexArray::Unbind() const {
    glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const VertexBuffer& vb) {
    glBindVertexArray(m_ArrayID);
    vb.Bind();
}

void VertexArray::SetIndexBuffer(const IndexBuffer& ib) {
    glBindVertexArray(m_ArrayID);
    ib.Bind();
}

} // namespace renderer
} // namespace bf
