#pragma once
#include "Renderer.h"

class Texture
{
private:

	unsigned int m_RenderId;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_heigh, m_width, m_BPP;

public:

	Texture(const std::string& path);
	~Texture();

	
	void Bind(const int slot =0 )const;
	void unBind()const;

	inline int GetWidth()const { return m_width; }
	inline int GetHeigt()const { return m_heigh; }

};
