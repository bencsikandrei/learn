#include "FindDialog.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace sheets
{
namespace gui
{
namespace dialog
{
FindDialog::FindDialog(QWidget *parent)
  : QDialog(parent)
  , mLabel{ new QLabel(tr("Find &what")) }
  , mLineEdit{ new QLineEdit }
  , mCsCheckBox{ new QCheckBox(tr("Match &case")) }
  , mBwCheckBox{ new QCheckBox(tr("Search &backward")) }
  , mFindButton{ new QPushButton(tr("&Find")) }
  , mCloseButton{ new QPushButton(tr("&Close")) }
{
  mLabel->setBuddy(mLineEdit);
  mFindButton->setDefault(true);
  mFindButton->setEnabled(false);

  QObject::connect(
    mLineEdit, SIGNAL(textChanged(QString const &)), this, SLOT(enableFindButton(QString const &)));
  QObject::connect(mFindButton, SIGNAL(clicked()), this, SLOT(findClicked()));
  QObject::connect(mCloseButton, SIGNAL(clicked()), this, SLOT(close()));

  QHBoxLayout *topLeftLayout = new QHBoxLayout;
  topLeftLayout->addWidget(mLabel);
  topLeftLayout->addWidget(mLineEdit);

  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(mFindButton);
  rightLayout->addWidget(mCloseButton);
  rightLayout->addStretch();

  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addLayout(topLeftLayout);
  leftLayout->addWidget(mCsCheckBox);
  leftLayout->addWidget(mBwCheckBox);

  QHBoxLayout *mainLayout = new QHBoxLayout;
  mainLayout->addLayout(leftLayout);
  mainLayout->addLayout(rightLayout);

  setLayout(mainLayout);

  setWindowTitle(tr("Find"));
  setFixedHeight(sizeHint().height());
}

FindDialog::~FindDialog() = default;

void FindDialog::findClicked()
{
  QString text = mLineEdit->text();
  Qt::CaseSensitivity cs = mCsCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

  if (mBwCheckBox->isChecked())
  {
    emit findPrevious(text, cs);
  }
  else
  {
    emit findNext(text, cs);
  }
}

void FindDialog::enableFindButton(QString const &text)
{
  mFindButton->setEnabled(!text.isEmpty());
}
} // namespace dialog
} // namespace find
} // namespace sheets