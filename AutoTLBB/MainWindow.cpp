#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>
#include <QDebug>

#include <tchar.h>
#include <psapi.h>

void PrintProcessNameAndID( DWORD processID )
{
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

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

    CloseHandle( hProcess );
}

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  // TODO
  m_pGameProcess = ::FindWindow(nullptr, TEXT("MINGW64"));
  qDebug() << m_pGameProcess;

  DWORD aProcesses[1024], cbNeeded, cProcesses;

  if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
  {

  }
  else
  {
    cProcesses = cbNeeded / sizeof(DWORD);
    for ( int i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 )
        {
            PrintProcessNameAndID( aProcesses[i] );
        }
    }
  }
}

MainWindow::~MainWindow()
{
  delete ui;
}
