#pragma once
#include <GL/glew.h>

#include <iostream>
#include "vertexArray.h"
#include "indexBuffer.h"
#include "Shader.h"



#define ASSERT(x) if(!(x)) __debugbreak();
#define GLcall(x) glClearError();\
x;\
ASSERT(GlLogCall(#x,__FILE__,__LINE__))

void glClearError();
bool GlLogCall(const char* funtion, const char* file, int line);


class Renderer
{
public:
	void Draw(const vertexArray& va,const indexBuffer& ib, const Shader& shader ) const;
	void Clean()const;
};

