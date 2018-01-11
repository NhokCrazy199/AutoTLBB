#include "InitCopyApp.hpp"

#include <QApplication>
#include <QFileInfo>
#include <QProcess>
#include <QString>
#include <QFile>

#include "Constants.hpp"

InitCopyApp::InitCopyApp() :
  m_pAppFileInfo(QFileInfo(QCoreApplication::applicationFilePath())),
  m_fileNameDelm('.'),
  m_appCopiedFileExt("bin")
{
  if (!this->isCopied())
  {
    // Make copy File
    QProcess process;
    qint64 pid;

    process.startDetached(
          this->getCopyAppFileName(),
          QCoreApplication::arguments(),
          m_pAppFileInfo.filePath(),
          &pid
          );

//    exit(0);
  }

  delete this;
}

bool InitCopyApp::isCopied()
{
  bool isCopied = false;
  if (this->getAppFileNameArray().size() > 1)
  {
    if (*(this->getAppFileNameArray().cend() - 1) == m_appCopiedFileExt)
    {
      isCopied = true;
    }
  }

  return isCopied;
}

bool InitCopyApp::createCopyApp()
{

  return true;
}

const QString& InitCopyApp::getAppFileName() const
{
  static const auto &appFileName = m_pAppFileInfo.fileName();

  return appFileName;
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
