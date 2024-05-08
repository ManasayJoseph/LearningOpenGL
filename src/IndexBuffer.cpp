#include "IndexBuffer.h"
#include "Renderer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) 
    : m_Count(count)
{                  
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    //*We have not specified the size of the data nor the data
    GLCall(glGenBuffers(1, &m_Renderer_ID));              //* This returns the id of the buffer I created
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_ID)); //* This binds the buffer to the array buffer
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_Renderer_ID));
}

void IndexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Renderer_ID));
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}