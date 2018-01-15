#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "player_control_tabs/GeneralTab.hpp"
#include "player_control_tabs/ItemTab.hpp"
#include "player_control_tabs/SkillTab.hpp"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

#include <cstring>

#include <tchar.h>
#include <psapi.h>

#include "Constants.hpp"
#include "games_window/GameWindowInfo.hpp"
#include "games_window/Player.hpp"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  this->setMinimumSize(this->size());
//  ui->gameListTableWidget->verticalHeader()->setVisible(false);
  ui->gameListTableWidget->horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);

  {
    QFile styleSheet(":/qdarkstyle/style.qss");
    styleSheet.open(QFile::ReadOnly);
    this->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
  }
  {
//    QFile styleSheet(":/qdarkstyle/app.qss");
//    styleSheet.open(QFile::ReadOnly);
//    styleSheet.close();
  }

  this->init();
}

MainWindow::~MainWindow()
{
  delete ui;

  for (const auto& autoControlWidget : m_autoControlWidgets)
  {
    delete autoControlWidget.second;
  }

  for (const auto& gameWindowInfo : m_gamesWindowInfo)
  {
    delete gameWindowInfo;
  }
}

bool MainWindow::init()
{
  this->initAutoControlWidgets();

  if (this->initGamesProcess())
  {
    this->initGamesPlayerList();
  }

  return true;
}

bool MainWindow::initAutoControlWidgets()
{
  m_autoControlWidgets["General"] = new GeneralTab(ui->autoControlTabWidget);
  m_autoControlWidgets["Item"] = new ItemTab(ui->autoControlTabWidget);
  m_autoControlWidgets["Skill"] = new SkillTab(ui->autoControlTabWidget);

  for (auto& widget : m_autoControlWidgets)
  {
    ui->autoControlTabWidget->addTab(widget.second, widget.first);
  }
}

bool MainWindow::initGamesPlayerList()
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

  return true;
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
    bool isExistsProcess = false;
    for (std::size_t i = 0; i < gamesWindowInfo->size(); i++)
    {
      if (gamesWindowInfo->at(i)->getProcessId() == processId)
      {
        isExistsProcess = true;
        break;
      }
    }
    if (isExistsProcess)
    {
      continue;
    }

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

  for (const auto& gameWindowInfo : m_gamesWindowInfo)
  {
    gameWindowInfo->getPlayer()->sendChatMsg("ssss");
    qDebug() << "Sent";
  }

  return !m_gamesWindowInfo.empty();
}

void MainWindow::on_actionReload_Player_List_triggered()
{
  this->init();
}

void MainWindow::on_gameListTableWidget_itemClicked(QTableWidgetItem *item)
{
  for (const auto& child : ui->autoControlTabWidget->children())
  {
    for (const auto& c : child->children())
    {
      qDebug() << 1;
    }
  }
}
