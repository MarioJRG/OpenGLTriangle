#pragma once
class vertexBuffer
{


private:
	unsigned int buffer;
public:
	vertexBuffer(const void* data, unsigned int size);
	~vertexBuffer();

	void Bind()const;
	void unBind()const;

};