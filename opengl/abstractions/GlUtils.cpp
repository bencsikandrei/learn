#include <iostream>
#include <cassert>

#include <GL/glew.h>

namespace graphix
{
void GLClearErrors() {
	while(glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* func, const char* file, int line) {
	while(GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << " in: " << func << " file: " 
			<< file << " line: " << line << ")\n";
		return false;
	}
	return true;
}

} // namespace graphix
