#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <vector>

#include "GameWindowInfo.hpp"

#include <Windows.h>

namespace Ui {
class MainWindow;
}

typedef std::vector<GameWindowInfo*> ListGameWindowInfo;

class MainWindow : public QMainWindow
{
  public:
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private:
    bool initGamesProcess();

  private:
    Ui::MainWindow *ui;
    ListGameWindowInfo m_gamesWindowInfo;
};

#endif // MAINWINDOW_HPP
