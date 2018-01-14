#include "SkillTab.hpp"
#include "ui_SkillTab.h"

SkillTab::SkillTab(QWidget *parent) :
  QFrame(parent),
  ui(new Ui::SkillTab)
{
  ui->setupUi(this);
}

SkillTab::~SkillTab()
{
  delete ui;
}
