#pragma once
#include <vector>

#include "Renderer.h"

struct vertexArrayElement
{
	

	unsigned int type;
	unsigned int count;
	bool normalize;

	static unsigned  int  getSizeofType(int type) {
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
		ASSERT(false);
	}


};

class vertexBufferLayout
{
private:
	std::vector<vertexArrayElement> Elemens;
	unsigned int m_stride;
public:
	vertexBufferLayout() :m_stride(0) {};
	
	template<typename T>

	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		//unsigned int c = count;
		Elemens.push_back({ GL_FLOAT, count, false });
		m_stride += count * vertexArrayElement::getSizeofType(GL_FLOAT);
	}
	template<>
	void Push<unsigned int>(unsigned int count) {
		//unsigned int  c = count;
		Elemens.push_back({ GL_UNSIGNED_INT,count,false });
		m_stride +=count * vertexArrayElement::getSizeofType(GL_UNSIGNED_INT);
	}
	template<>
	void Push<unsigned char>(unsigned int count) {
		//unsigned int c = count;
		Elemens.push_back({ GL_UNSIGNED_BYTE,count,true });
		m_stride += count * vertexArrayElement::getSizeofType(GL_UNSIGNED_BYTE);
	}
	inline const std::vector<vertexArrayElement> GetElements() const {
		return Elemens;
	}
	inline unsigned int GetStride() const {
		return m_stride;
	}
};


