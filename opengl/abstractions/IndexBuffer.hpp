#pragma once

class IndexBuffer {
public:
    IndexBuffer(unsigned const* data, unsigned size);
    ~IndexBuffer();

    void bind();
    void unbind();

    unsigned getRendererId() const { return mRendererId; }
private:
    unsigned mRendererId;
    unsigned mCount;
};