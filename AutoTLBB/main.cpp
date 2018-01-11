#include "MainWindow.hpp"
#include <QApplication>

#include "InitCopyApp.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  (new InitCopyApp());
  MainWindow w;
  w.show();

  return a.exec();
}
