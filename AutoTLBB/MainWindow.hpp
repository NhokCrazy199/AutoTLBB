#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <Windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  public:
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public:
    bool initGamesProcess();

  private:
    Ui::MainWindow *ui;
    HWND m_gamesProcess;
};

#endif // MAINWINDOW_HPP
