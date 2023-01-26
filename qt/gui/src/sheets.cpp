#include <QApplication>

#include "gui/dialog/FindDialog.hpp"
#include "gui/dialog/GotoDialog.hpp"
#include "gui/dialog/SortDialog.hpp"

#include <memory>

int main(int argc, char **argv)
{
  QApplication app{ argc, argv };

  auto dialog{ std::make_unique<sheets::gui::dialog::SortDialog>() };

  dialog->show();

  return app.exec();
}