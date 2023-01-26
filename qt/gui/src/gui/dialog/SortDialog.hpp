#pragma once

#include <QDialog>

class QPushButton;

namespace sheets
{
namespace gui
{
namespace dialog
{
class SortDialog : public QDialog
{
  Q_OBJECT
public:
  SortDialog(QWidget *parent = nullptr);
  ~SortDialog();

private:
  void setColumnRange(QChar beg, QChar end);

private:
  QPushButton *mOkButton;
  QPushButton *mCancelButton;
  QPushButton *mMoreButton;

  class KeyConfigBox;
  KeyConfigBox *mPrimaryKeyBox;
  KeyConfigBox *mSecondaryKeyBox;
  KeyConfigBox *mTernaryKeyBox;
};
} // namespace dialog
} // namespace gui
} // namespace sheets