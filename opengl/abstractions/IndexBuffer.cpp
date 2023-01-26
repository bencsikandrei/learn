#include "IndexBuffer.hpp"
#include "GlUtils.hpp"

IndexBuffer::IndexBuffer(unsigned const* data, unsigned count)
        : mCount{count}
{

    static_assert(sizeof(unsigned) == sizeof(GLuint));

	GLCall( glGenBuffers(1, &mRendererId) ); // generate 1 buffer, put identifier in buffer
	GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId) );  
	GLCall( glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * count, data, GL_STATIC_DRAW) );	// give it to OpenGL
}

IndexBuffer::~IndexBuffer() 
{
    GLCall( glDeleteBuffers(1, &mRendererId) ); 
}

void IndexBuffer::bind() {
    GLCall( glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererId) );
}

void IndexBuffer::unbind() {
    GLCall (glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
