#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <string>
#include <vector>

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
    std::vector<HWND> m_gamesProcess;
    std::string m_gameWindowClass;
};

#endif // MAINWINDOW_HPP

