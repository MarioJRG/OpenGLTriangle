#include "vertexBuffer.h"
#include <GL/glew.h>


vertexBuffer::vertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER,size,data, GL_STATIC_DRAW);

}

vertexBuffer::~vertexBuffer()
{
    glDeleteBuffers(1,&buffer);
}

void vertexBuffer::Bind()const
{
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
}

void vertexBuffer::unBind()const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
