#ifndef INITCOPYAPP_HPP
#define INITCOPYAPP_HPP

#include <QString>

class QFileInfo;
class QApplication;
class QStringList;

class InitCopyApp
{
  public:
    InitCopyApp();

  private:
    bool isCopyApp();
    bool createCopyApp();

  private:
    const QString& getAppFileName() const;
    const QStringList& getAppFileNameArray() const;
    const QString& getCopyAppFileName() const;
    const QStringList& getCopyAppFileNameArray() const;
    QString getCopyAppFilePath() const;

  private:
    const QFileInfo &m_pAppFileInfo;
    const char m_fileNameDelm;
    const QString &m_appCopiedFileExt;
};

#endif // INITCOPYAPP_HPP
