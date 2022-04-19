#include "vertexArray.h"
#include "Renderer.h"

vertexArray::vertexArray()
{
	glGenVertexArrays(1, &id);
}

vertexArray::~vertexArray()
{
	glDeleteVertexArrays(1, &id);
}

void vertexArray::addBuffer(const vertexBuffer& vb, const vertexBufferLayout& vbl)
{
	Bind();
	vb.Bind();
	const auto& elements = vbl.GetElements();
	unsigned int offset=0;
	for (unsigned int i = 0; i < elements.size();i++) {
		const auto& elemen = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elemen.count,elemen.type,elemen.normalize,vbl.GetStride(),(void*)offset);
		offset = +elemen.count * vertexArrayElement::getSizeofType(elemen.type);
	}
	
}

void vertexArray::Bind() const
{
	glBindVertexArray(id);
}

void vertexArray::unBind() const
{
	glBindVertexArray(0);
}
