#include <iostream>
#include <memory>
#include <vector>

// The Rectangle class is (in maths) a super
// class of Square.
// But as seen below it's not a good way of doing
// things.
class Rectangle {
  public:
    Rectangle(int width, int height) : mWidth{width}, mHeight{height} {}

    int getHeight() const { return mHeight; }
    int getWidth() const { return mWidth; }

    virtual void setHeight(int newHeight) { mHeight = newHeight; }
    virtual void setWidth(int newWidth) { mWidth = newWidth; }

    int getArea() const { return mWidth * mHeight; }

  protected:
    int mWidth, mHeight;
};

// This breaks the Liskov substitution principle
// we have some expectations on it and they break
// when we use it in place of a rectangle
class Square : public Rectangle {
  public:
    Square(int size) : Rectangle(size, size) {}

    void setHeight(int newHeight) { this->mHeight = this->mWidth = newHeight; }

    void setWidth(int newWidth) { this->mHeight = this->mWidth = newWidth; }
};

void process(Rectangle &rect) {
    int w = rect.getWidth();
    rect.setHeight(10);

    std::cout << "expected: " << w * 10 << "\nhad: " << rect.getArea() << '\n';
}

int main() {

    Square sq{3};
    Rectangle r{3, 4};

    process(r);

    process(sq);
}
