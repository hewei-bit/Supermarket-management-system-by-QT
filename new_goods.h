#ifndef NEW_GOODS_H
#define NEW_GOODS_H

#include <QMainWindow>
#include <QMessageBox>
#include "goods.h"

namespace Ui {
class new_goods;
}

class new_goods : public QMainWindow
{
    Q_OBJECT

public:
    explicit new_goods(QWidget *parent = nullptr);
    ~new_goods();



private slots:
    void on_return_Btn_clicked();

    void on_add_Btn_clicked();

private:
    Ui::new_goods *ui;
    QString account_filename = "../Supermarket_management_system/resources/account.json";
    QString goods_filename = "../Supermarket_management_system/resources/goods.json";
};

#endif // NEW_GOODS_H
