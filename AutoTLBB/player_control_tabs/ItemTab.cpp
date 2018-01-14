#include "ItemTab.hpp"
#include "ui_ItemTab.h"

ItemTab::ItemTab(QWidget *parent) :
  QFrame(parent),
  ui(new Ui::ItemTab)
{
  ui->setupUi(this);
}

ItemTab::~ItemTab()
{
  delete ui;
}
