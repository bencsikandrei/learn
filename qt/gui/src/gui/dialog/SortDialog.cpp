#include "SortDialog.hpp"

#include <QCheckBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>

#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QSpacerItem>

#include <array>

namespace sheets
{
namespace gui
{
namespace dialog
{
class SortDialog::KeyConfigBox : public QGroupBox
{
public:
  KeyConfigBox(QString const &title, QWidget *parent)
    : QGroupBox(title, parent)
    , mColumnLabel{ new QLabel(tr("Column:")) }
    , mColumnComboBox{ new QComboBox }
    , mOrderLabel{ new QLabel(tr("Order:")) }
    , mOrderComboBox{ new QComboBox }
    , mSpacerItem{ new QSpacerItem(0, 10) }
  {
    mColumnLabel->setBuddy(mColumnComboBox);
    mOrderLabel->setBuddy(mOrderComboBox);

    mColumnComboBox->addItem(tr("None"));
    mOrderComboBox->addItem(tr("Ascending"));
    mOrderComboBox->addItem(tr("Descending"));

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(mColumnLabel, 0, 0);
    mainLayout->addWidget(mColumnComboBox, 0, 1);
    mainLayout->addItem(mSpacerItem, 0, 2, 1);
    mainLayout->addWidget(mOrderLabel, 1, 0);
    mainLayout->addWidget(mOrderComboBox, 1, 1, 1, 2);

    setLayout(mainLayout);
  }

public:
  QLabel *mColumnLabel;
  QComboBox *mColumnComboBox;
  QLabel *mOrderLabel;
  QComboBox *mOrderComboBox;
  QSpacerItem *mSpacerItem;
};

SortDialog::SortDialog(QWidget *parent)
  : QDialog(parent)
  , mOkButton{ new QPushButton(tr("&OK")) }
  , mCancelButton{ new QPushButton(tr("&Cancel")) }
  , mMoreButton{ new QPushButton(tr("&More")) }
  , mPrimaryKeyBox{ new KeyConfigBox(tr("Primary Key"), this) }
  , mSecondaryKeyBox{ new KeyConfigBox(tr("Secondary Key"), this) }
  , mTernaryKeyBox{ new KeyConfigBox(tr("Ternary Key"), this) }
{
  mOkButton->setDefault(true);
  mMoreButton->setCheckable(true);

  mSecondaryKeyBox->hide();
  mTernaryKeyBox->hide();

  QObject::connect(mOkButton, SIGNAL(clicked()), this, SLOT(accept()));
  QObject::connect(mCancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  QObject::connect(mMoreButton, SIGNAL(toggled(bool)), mSecondaryKeyBox, SLOT(setVisible(bool)));
  QObject::connect(mMoreButton, SIGNAL(toggled(bool)), mTernaryKeyBox, SLOT(setVisible(bool)));

  setColumnRange('A', 'Z');

  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(mPrimaryKeyBox);
  leftLayout->addSpacing(1);
  leftLayout->addWidget(mSecondaryKeyBox);
  leftLayout->addWidget(mTernaryKeyBox);

  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(mOkButton);
  rightLayout->addWidget(mCancelButton);
  rightLayout->addSpacing(1);
  rightLayout->addWidget(mMoreButton);

  QGridLayout *mainLayout = new QGridLayout;
  mainLayout->addLayout(leftLayout, 0, 0, 4, 1);
  mainLayout->addLayout(rightLayout, 0, 1, 2, 1);

  mainLayout->setSizeConstraint(QLayout::SetFixedSize);

  setLayout(mainLayout);

  setWindowTitle(tr("Sort"));
}

SortDialog::~SortDialog() = default;

void SortDialog::setColumnRange(QChar beg, QChar end)
{
  std::array<KeyConfigBox *, 3> keyConfigs{ mPrimaryKeyBox, mSecondaryKeyBox, mTernaryKeyBox };
  QChar b = beg;
  for (auto box : keyConfigs)
  {
    for (QChar b = beg; b != end; b = b.unicode() + 1)
    {
      box->mColumnComboBox->addItem(QString(b));
    }
  }
}

} // namespace dialog
} // namespace gui
} // namespace sheets