#include <Pimpl.hpp>

#include <iostream>

class Widget::WidgetImpl {
  public:
    void show(Widget *w) { std::cout << w->name << "\n"; }
};

Widget::Widget() { implementation = new WidgetImpl; }

Widget::~Widget() { delete implementation; }

void Widget::show() { implementation->show(this); }
