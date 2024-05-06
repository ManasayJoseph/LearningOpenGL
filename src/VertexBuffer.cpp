#include "VertexBuffer.h"
#include "Renderer.h"
#include <GL/glew.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{                  
    //*We have not specified the size of the data nor the data
    GLCall(glGenBuffers(1, &m_Renderer_ID));              //* This returns the id of the buffer I created
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID)); //* This binds the buffer to the array buffer
    GLCall(glBufferData(GL_ARRAY_BUFFER, 4 * 2 * sizeof(float), data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_Renderer_ID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}