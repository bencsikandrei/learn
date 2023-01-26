#include "VertexBuffer.hpp"
#include "GlUtils.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer(void const *data, unsigned size) {
    GLCall(glGenBuffers(
        1, &mRendererId)); // generate 1 buffer, put identifier in buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data,
                        GL_STATIC_DRAW)); // give it to OpenGL
}

VertexBuffer::~VertexBuffer() { GLCall(glDeleteBuffers(1, &mRendererId)); }

void VertexBuffer::bind() {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererId));
}

void VertexBuffer::unbind() { GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }
