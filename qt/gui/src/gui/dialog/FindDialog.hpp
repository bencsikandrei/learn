#pragma once

#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

namespace sheets
{
namespace gui
{
namespace dialog
{
class FindDialog : public QDialog
{
  Q_OBJECT
public:
  FindDialog(QWidget *parent = nullptr);
  ~FindDialog();

signals:
  void findNext(QString const &strToFind, Qt::CaseSensitivity cs);
  void findPrevious(QString const &strToFind, Qt::CaseSensitivity cs);

private slots:
  void findClicked();
  void enableFindButton(QString const &text);

private:
  QLabel *mLabel;
  QLineEdit *mLineEdit;
  QCheckBox *mCsCheckBox;
  QCheckBox *mBwCheckBox;
  QPushButton *mFindButton;
  QPushButton *mCloseButton;
};
} // namespace dialog
} // namespace gui
} // namespace sheets
