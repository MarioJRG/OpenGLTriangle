#pragma once

#include "vertexBuffer.h"
class vertexBufferLayout;


class vertexArray
{


private:
	unsigned int id;
public:
	vertexArray();
	~vertexArray();

	void addBuffer(const vertexBuffer& vb,const vertexBufferLayout& vbl );
	void Bind() const;
	void unBind()const;

};

