#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

#include <cstring>

#include <tchar.h>
#include <psapi.h>

#include "Constants.hpp"
#include "Player.hpp"

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
  if (this->initGamesProcess())
  {
    ui->gameListTableWidget->setRowCount(m_gamesWindowInfo.size());
    for (std::size_t i = 0; i < m_gamesWindowInfo.size(); i++)
    {
      auto gameWindowInfo = m_gamesWindowInfo.at(i);
      ::SetWindowText(gameWindowInfo->getHwnd(), TEXT("Test TLBB Change Win Title"));

      auto player = gameWindowInfo->getPlayer();

      qDebug() << *player;

      auto no = new QTableWidgetItem(QString::number(i + 1));
      ui->gameListTableWidget->setItem(i, 0, no);

      auto username = new QTableWidgetItem(player->getName());
      ui->gameListTableWidget->setItem(i, 1, username);

      auto hp = new QTableWidgetItem(QString::number(player->getHpPercent()));
      ui->gameListTableWidget->setItem(i, 2, hp);

      auto mp = new QTableWidgetItem(QString::number(player->getMpPercent()));
      ui->gameListTableWidget->setItem(i, 3, mp);

      auto pet_hp = new QTableWidgetItem("1");
      ui->gameListTableWidget->setItem(i, 4, pet_hp);

      auto mode = new QTableWidgetItem("1");
      ui->gameListTableWidget->setItem(i, 5, mode);

      ui->gameListTableWidget->setSizeAdjustPolicy(QTableWidget::QAbstractItemView::AdjustToContents);

      qDebug() << "Added";
    }
  }
}

MainWindow::~MainWindow()
{
  delete ui;

  for (const auto& gameWindowInfo : m_gamesWindowInfo)
  {
    delete gameWindowInfo;
  }
}

static BOOL CALLBACK EnumWindowsProcCallback(HWND hwnd, LPARAM lParam)
{
  TCHAR className[MAX_PATH];
  ::GetClassName(hwnd, className, sizeof(className));

  auto gamesWindowInfo = reinterpret_cast<ListGameWindowInfo*>(lParam);

  DWORD processId;
  HANDLE handle = nullptr;
  for (const auto& name : constants::gameClassNames)
  {
    if (::_tcscmp(className, name) != 0)
    {
      continue;
    }

    ::GetWindowThreadProcessId(hwnd, &processId);
    handle = ::OpenProcess(READ_CONTROL | PROCESS_ALL_ACCESS | PROCESS_VM_READ, FALSE, processId);
    if (handle == nullptr)
    {
      qDebug() << "Can not open game";
    }

    auto gameWindowInfo = new GameWindowInfo();
    gameWindowInfo->setHwnd(hwnd);
    gameWindowInfo->setProcessId(processId);
    gameWindowInfo->setHandle(handle);

    qDebug() << *gameWindowInfo;

    gamesWindowInfo->push_back(gameWindowInfo);
  }

  return TRUE;
}

bool MainWindow::initGamesProcess()
{
  ::EnumWindows(&EnumWindowsProcCallback, reinterpret_cast<LPARAM>(&m_gamesWindowInfo));

  return !m_gamesWindowInfo.empty();
}
