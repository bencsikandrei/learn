#pragma once

class VertexBuffer {
public:
    VertexBuffer(void const* data, unsigned size);
    ~VertexBuffer();

    void bind();
    void unbind();

    unsigned getRendererId() const { return mRendererId; }
private:
    unsigned mRendererId;
};