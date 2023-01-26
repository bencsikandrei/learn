#include <string>

class Widget {
  public:
    Widget();
    ~Widget();

    void show();

  private:
    class WidgetImpl;
    WidgetImpl *implementation;

    std::string name;
};
