#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QDebug>

#include <tchar.h>
#include <psapi.h>

using PId = DWORD;


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // TODO
  m_gameProcesses = ::FindWindow(nullptr, TEXT("MINGW64"));
  qDebug() << m_gameProcesses;

  this->initGameProcesses();
}

MainWindow::~MainWindow()
{
  delete ui;
}

bool MainWindow::initGameProcesses()
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

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        PId cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Print the process name and identifier.

    qDebug() << szProcessName << processID;

    // Release the handle to the process.

    CloseHandle(hProcess);
  }

  return true;
}
