#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <Windows.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  public:
    bool initGameProcesses();

  private:
    Ui::MainWindow *ui;
    HWND m_gameProcesses;
};

#endif // MAINWINDOW_HPP
