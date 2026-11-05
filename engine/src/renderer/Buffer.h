#pragma once

#include <cstdint>
#include <vector>

namespace bf {
namespace renderer {

enum class BufferUsage {
    Static,
    Dynamic,
    Stream
};

class VertexBuffer {
public:
    VertexBuffer();
    VertexBuffer(const void* data, uint32_t size, BufferUsage usage = BufferUsage::Static);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
    
    void SetData(const void* data, uint32_t size);
    void SetSubData(const void* data, uint32_t size, uint32_t offset);
    
    uint32_t GetID() const { return m_BufferID; }
    uint32_t GetSize() const { return m_Size; }

private:
    uint32_t m_BufferID;
    uint32_t m_Size;
    BufferUsage m_Usage;
};

class IndexBuffer {
public:
    IndexBuffer();
    IndexBuffer(const uint32_t* indices, uint32_t count, BufferUsage usage = BufferUsage::Static);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    
    void SetData(const uint32_t* indices, uint32_t count);
    
    uint32_t GetID() const { return m_BufferID; }
    uint32_t GetCount() const { return m_Count; }

private:
    uint32_t m_BufferID;
    uint32_t m_Count;
    BufferUsage m_Usage;
};

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    
    void AddVertexBuffer(const VertexBuffer& vb);
    void SetIndexBuffer(const IndexBuffer& ib);
    
    uint32_t GetID() const { return m_ArrayID; }

private:
    uint32_t m_ArrayID;
};

} // namespace renderer
} // namespace bf
