#include "InitCopyApp.hpp"

#include <QApplication>
#include <QFileInfo>
#include <QProcess>
#include <QFile>

#include "Constants.hpp"

InitCopyApp::InitCopyApp()
{
  const auto &appInfo = QFileInfo(QCoreApplication::applicationFilePath());
  char delm = '.';
  const auto &appFileNameArr = appInfo.fileName().split(delm);

  bool isCopied = false;
  if (appFileNameArr.size() > 1)
  {
    if (appFileNameArr.at(appFileNameArr.size()-1).toStdString() == constants::appCopiedExt)
    {
      isCopied = true;
    }
  }

  if (isCopied)
  {
    return;
  }

  auto appCopiedFileNameArr = appFileNameArr;
  appCopiedFileNameArr[appCopiedFileNameArr.size() - 1] = QString(constants::appCopiedExt.c_str());
  QString appCopiedFileName = appCopiedFileNameArr.join(delm);

  // Make copy File
  QProcess process;
  qint64 pid;

  process.startDetached(
    appCopiedFileName,
    QCoreApplication::arguments(),
    appInfo.filePath(),
    &pid
    );

  //  exit(0);
}

bool InitCopyApp::init()
{

}
