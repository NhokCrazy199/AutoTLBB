#include "InitCopyApp.hpp"

#include <QApplication>
#include <QFileInfo>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QDir>

#include <QDebug>

#include "Constants.hpp"

InitCopyApp::InitCopyApp() :
  m_pAppFileInfo(QFileInfo(QCoreApplication::applicationFilePath())),
  m_fileNameDelm('.'),
  m_appCopiedFileExt("bin")
{
  qDebug() << m_pAppFileInfo.absoluteDir();
  qDebug() << m_pAppFileInfo.absoluteFilePath();
  qDebug() << QCoreApplication::applicationDirPath();

  if (this->isCopyApp())
  {
    return;
  }

  if (this->createCopyApp())
  {
    // Make copy File
    QProcess process;
    qint64 pid;

    process.startDetached(
          this->getCopyAppFileName(),
          QCoreApplication::arguments(),
          QDir::currentPath(),
          &pid
          );

    exit(0);
  }

  delete this;
}

bool InitCopyApp::isCopyApp()
{
  bool isCopyApp = false;

  if (this->getAppFileNameArray().size() > 1)
  {
    if (*(this->getAppFileNameArray().cend() - 1) == m_appCopiedFileExt)
    {
      isCopyApp = true;
    }
  }

  return isCopyApp;
}

bool InitCopyApp::createCopyApp()
{
  QFile appFile(QCoreApplication::applicationFilePath());
  appFile.copy(this->getCopyAppFilePath());

  return true;
}

const QString& InitCopyApp::getAppFileName() const
{
  static const auto &appFileName = m_pAppFileInfo.fileName();

  return appFileName;
}

QString InitCopyApp::getCopyAppFilePath() const
{
  static auto copyAppFileInfo = m_pAppFileInfo;
  copyAppFileInfo.setFile(copyAppFileInfo.path(), this->getCopyAppFileName());

  qDebug() << copyAppFileInfo.filePath();

  return copyAppFileInfo.filePath();
}

const QStringList& InitCopyApp::getAppFileNameArray() const
{
  static const auto &appFileNameArr = this->getAppFileName().split(m_fileNameDelm);

  return appFileNameArr;
}

const QString& InitCopyApp::getCopyAppFileName() const
{
  static const auto &copyAppFileName = this->getCopyAppFileNameArray().join(m_fileNameDelm);

  return copyAppFileName;
}

const QStringList& InitCopyApp::getCopyAppFileNameArray() const
{
  static auto appCopiedFileNameArr = this->getAppFileNameArray();
  *(appCopiedFileNameArr.end() - 1) = m_appCopiedFileExt;

  return appCopiedFileNameArr;
}
