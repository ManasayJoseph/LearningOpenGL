#ifndef VERTEX_BUFFER_LAYOUT_H
#define VERTEX_BUFFER_LAYOUT_H

#include <vector>
#include <GL/glew.h>
#include "Renderer.h"

#ifndef VERTEX_BUFFER_ELEMENT
#define VERTEX_BUFFER_ELEMENT
struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeofType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT:
            return 4;
        case GL_UNSIGNED_INT:
            return 4;
        case GL_UNSIGNED_BYTE:
            return 1;
        }
        ASSERT(false)
        return 0;
    }
};
#endif



class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout()
        : m_Stride(0)
    {
    }

void PushFloat(unsigned int count)
    {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeofType(GL_FLOAT);
    }

    template <typename T>
    void Push(unsigned int count)
    {
        ASSERT(false);
    }

    // Regular function overload for unsigned int
    void PushUInt(unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_INT) ;
    }

    // Regular function overload for unsigned char
    void PushUChar(unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count * VertexBufferElement::GetSizeofType(GL_UNSIGNED_BYTE);
    }

    inline const std::vector<VertexBufferElement> &GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
};



#endif
