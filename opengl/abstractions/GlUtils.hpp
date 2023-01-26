#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace graphix
{
void GLClearErrors();

bool GLCheckError(const char* func, const char* file, int line);

#define GLCall(x) \
	::graphix::GLClearErrors(); \
	x;\
	assert(::graphix::GLCheckError(#x, __FILE__, __LINE__));

} // namespace graphix
