#include "MainWindow.hpp"
#include <QApplication>

#include "InitCopyApp.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
#ifndef QT_DEBUG
  (new InitCopyApp());
#endif
  MainWindow w;
  w.show();

  return a.exec();
}
