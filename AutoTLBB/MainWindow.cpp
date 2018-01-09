#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

#include <cstring>

#include <tchar.h>
#include <psapi.h>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->setMinimumSize(this->size());
  ui->gameListTableWidget->horizontalHeader()->resizeSections(QHeaderView::Stretch);

  QFile styleSheet(":/qdarkstyle/style.qss");
  styleSheet.open(QFile::ReadOnly);
  this->setStyleSheet(styleSheet.readAll());
  styleSheet.close();

  m_gameWindowClass = "TianLongBaBu WndClass";

  // TODO
  if (this->initGamesProcess())
  {
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}

static BOOL CALLBACK EnumWindowsProcCallback(HWND hwnd, LPARAM lParam)
{
  char className[MAX_PATH];
  ::GetClassNameA(hwnd, className, sizeof(className));

  auto gamesProcess = reinterpret_cast<std::vector<HWND>*>(lParam);

  std::vector<std::string> classNames{
    "TianLongBaBu WndClass"
  };

  for (const auto& name : classNames)
  {
    if (std::strcmp(className, name.c_str()) == 0)
    {
      gamesProcess->push_back(hwnd);
    }
  }

  qDebug() << gamesProcess->size() << className;

  return TRUE;
}

bool MainWindow::initGamesProcess()
{
  ::EnumWindows(&EnumWindowsProcCallback, reinterpret_cast<LPARAM>(&m_gamesProcess));

  qDebug() << m_gamesProcess.size();

  return true;
}
