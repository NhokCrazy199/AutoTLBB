#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

#include <cstring>

#include <tchar.h>
#include <psapi.h>

#include "Constants.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->setMinimumSize(this->size());
  ui->gameListTableWidget->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

  QFile styleSheet(":/qdarkstyle/style.qss");
  styleSheet.open(QFile::ReadOnly);
  this->setStyleSheet(styleSheet.readAll());
  styleSheet.close();

  // TODO
  m_gamesProcess.push_back(nullptr);
  if (this->initGamesProcess())
  {
    ui->gameListTableWidget->setRowCount(m_gamesProcess.size());
    for (std::size_t i = 0; i < m_gamesProcess.size(); i++)
    {
      auto no = new QTableWidgetItem("111111");
      ui->gameListTableWidget->setItem(i, 1, no);

      auto username = new QTableWidgetItem("111111");
      ui->gameListTableWidget->setItem(i, 2, username);

      auto hp = new QTableWidgetItem("111111111");
      ui->gameListTableWidget->setItem(i, 3, hp);

      auto mp = new QTableWidgetItem("1");
      ui->gameListTableWidget->setItem(i, 4, mp);

      auto pet_hp = new QTableWidgetItem("1");
      ui->gameListTableWidget->setItem(i, 5, pet_hp);

      auto mode = new QTableWidgetItem("1");
      ui->gameListTableWidget->setItem(i, 6, mode);

      auto status = new QTableWidgetItem("1");
      ui->gameListTableWidget->setItem(i, 7, status);

      ui->gameListTableWidget->setSizeAdjustPolicy(QTableWidget::QAbstractItemView::AdjustToContents);

      qDebug() << "Added";
    }
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

  for (const auto& name : constants::gameClassNames)
  {
    if (std::strcmp(className, name.c_str()) == 0)
    {
      gamesProcess->push_back(hwnd);
    }
  }

  return TRUE;
}

bool MainWindow::initGamesProcess()
{
  ::EnumWindows(&EnumWindowsProcCallback, reinterpret_cast<LPARAM>(&m_gamesProcess));

  return !m_gamesProcess.empty();
}
