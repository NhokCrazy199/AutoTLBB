#ifndef ITEMTAB_HPP
#define ITEMTAB_HPP

#include <QFrame>

namespace Ui {
  class ItemTab;
}

class ItemTab : public QFrame
{
    Q_OBJECT

  public:
    explicit ItemTab(QWidget *parent = 0);
    ~ItemTab();

  private:
    Ui::ItemTab *ui;
};

#endif // ITEMTAB_HPP
