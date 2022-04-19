#pragma once
class indexBuffer
{


private:
	unsigned int buffer;
	unsigned int indices;
public:
	indexBuffer(const unsigned int* data, unsigned int count);
	~indexBuffer();

	void Bind()const;
	void unBind()const;

	inline unsigned int getCount() const {
		return indices;
	}

};