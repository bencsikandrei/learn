#include "GotoDialog.hpp"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <QPushButton>
#include <QDialogButtonBox>

namespace sheets
{
namespace gui
{
namespace dialog
{
GotoDialog::GotoDialog(QWidget *parent)
  : QDialog(parent)
  , mLabel{ new QLabel(tr("&Cell location")) }
  , mLineEdit{ new QLineEdit }
  , mButtonBox{ new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel) }
{
  mLabel->setBuddy(mLineEdit);

  QRegExp regExp{ "[A-Za-z][1-9][0-9]{0,2}" };
  mLineEdit->setValidator(new QRegExpValidator(regExp, this));
  mButtonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

  QObject::connect(mButtonBox, SIGNAL(accepted()), this, SLOT(accept()));
  QObject::connect(mButtonBox, SIGNAL(rejected()), this, SLOT(reject()));
  QObject::connect(
    mLineEdit, SIGNAL(textChanged(QString const &)), this, SLOT(enableOkButton(QString const &)));

  QHBoxLayout *topLayout = new QHBoxLayout;
  topLayout->addWidget(mLabel);
  topLayout->addWidget(mLineEdit);

  QHBoxLayout *bottomLayout = new QHBoxLayout;
  bottomLayout->addStretch();
  bottomLayout->addWidget(mButtonBox);

  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addLayout(topLayout);
  mainLayout->addLayout(bottomLayout);

  setLayout(mainLayout);

  setWindowTitle(tr("Go to cell"));
  setFixedHeight(sizeHint().height());
}

GotoDialog::~GotoDialog() = default;

void GotoDialog::enableOkButton(QString const &text)
{
  mButtonBox->button(QDialogButtonBox::Ok)->setEnabled(mLineEdit->hasAcceptableInput());
}

} // namespace dialog
} // namespace gui
} // namespace sheets