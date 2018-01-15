#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

#include <vector>
#include <map>

#include <Windows.h>

class QTableWidgetItem;
class GameWindowInfo;

namespace Ui {
class MainWindow;
}

typedef std::vector<GameWindowInfo*> ListGameWindowInfo;
typedef std::map<QString, QWidget*> ListAutoControlWidget;

class MainWindow : public QMainWindow
{
  public:
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

  private slots:
    void on_actionReload_Player_List_triggered();

    void on_gameListTableWidget_itemClicked(QTableWidgetItem *item);

  private:
    bool init();
    bool initAutoControlWidgets();
    bool initGamesProcess();
    bool initGamesPlayerList();

  private:
    Ui::MainWindow *ui;
    ListGameWindowInfo m_gamesWindowInfo;
    ListAutoControlWidget m_autoControlWidgets;
};

#endif // MAINWINDOW_HPP
