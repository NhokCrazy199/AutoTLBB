#ifndef INITCOPYAPP_HPP
#define INITCOPYAPP_HPP

class QFileInfo;
class QApplication;
class QStringList;
class QString;

class InitCopyApp
{
  public:
    InitCopyApp();

  private:
    bool isCopied();
    bool createCopyApp();

  private:
    const QString& getAppFileName() const;
    const QStringList& getAppFileNameArray() const;
    const QString& getCopyAppFileName() const;
    const QStringList& getCopyAppFileNameArray() const;

  private:
    const QFileInfo &m_pAppFileInfo;
    const char m_fileNameDelm;
    const QString &m_appCopiedFileExt;
};

#endif // INITCOPYAPP_HPP
