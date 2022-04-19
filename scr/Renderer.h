#pragma once
#include <GL/glew.h>

#include <iostream>




#define ASSERT(x) if(!(x)) __debugbreak();
#define GLcall(x) glClearError();\
x;\
ASSERT(GlLogCall(#x,__FILE__,__LINE__))

void glClearError();
bool GlLogCall(const char* funtion, const char* file, int line);