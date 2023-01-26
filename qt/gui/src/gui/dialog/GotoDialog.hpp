#pragma once

#include <QDialog>

class QLabel;
class QLineEdit;
class QDialogButtonBox;

namespace sheets
{
namespace gui
{
namespace dialog
{
class GotoDialog : public QDialog
{
  Q_OBJECT
public:
  GotoDialog(QWidget *parent = nullptr);
  ~GotoDialog();

private slots:
  void enableOkButton(QString const &text);

private:
  QLabel *mLabel;
  QLineEdit *mLineEdit;
  QDialogButtonBox *mButtonBox;
};
} // namespace dialog
} // namespace gui
} // namespace sheets