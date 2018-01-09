#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>

#include <tchar.h>
#include <psapi.h>

using PId = DWORD;


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

bool MainWindow::initGamesProcess()
{
  PId aProcesses[1024], cbNeeded, cProcesses;

  if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
  {
    return false;
  }

  cProcesses = cbNeeded / sizeof(PId);
  for (unsigned int i = 0; i < cProcesses; i++)
  {
    if(aProcesses[i] == 0)
    {
      continue;
    }

    PId &processID = aProcesses[i];

    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = ::OpenProcess( PROCESS_QUERY_INFORMATION |
                                    PROCESS_VM_READ,
                                    FALSE, processID );

    // Get the process name.

    if (nullptr != hProcess )
    {
      HMODULE hMod;
      PId cbNeeded;

      if ( ::EnumProcessModules( hProcess, &hMod, sizeof(hMod),
                                &cbNeeded) )
      {
        ::GetModuleBaseName( hProcess, hMod, szProcessName,
                            sizeof(szProcessName)/sizeof(TCHAR) );
        ::GetWind
      }
    }

    // Print the process name and identifier.

    qDebug() << szProcessName << processID;

    // Release the handle to the process.

    ::CloseHandle(hProcess);
  }

  return true;
}

