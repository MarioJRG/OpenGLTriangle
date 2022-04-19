#include "indexBuffer.h"
#include <GL/glew.h>
#include "Renderer.h"


indexBuffer::indexBuffer(const unsigned int* data, unsigned int count):indices(count)
{
    ASSERT(sizeof(unsigned int) == sizeof(GLint));
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,count *sizeof(unsigned int),data, GL_STATIC_DRAW);

}

indexBuffer::~indexBuffer()
{
    glDeleteBuffers(1, &buffer);
}

void indexBuffer::Bind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
}

void indexBuffer::unBind()const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
