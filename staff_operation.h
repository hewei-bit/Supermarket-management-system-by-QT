#ifndef STAFF_OPERATION_H
#define STAFF_OPERATION_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QStandardItemModel>
#include <QWidget>

#include "goods.h"






namespace Ui {
class staff_operation;
}

class staff_operation : public QMainWindow
{
    Q_OBJECT

public:
    explicit staff_operation(QWidget *parent = nullptr);
    ~staff_operation();
    //显示库存
    void showStock(QList<goods> &glist);
    //设置购物车标题
    void showShoppingcar(QList<goods> &glist);


private slots:



    void on_clean_Btn_clicked();

    void on_delete_Btn_clicked();

    void on_back_Btn_clicked();

    void on_return_Btn_clicked();

    void on_goods_type_comboBox_currentTextChanged(const QString &arg1);

    void on_goods_name_comboBox_currentTextChanged(const QString &arg1);



    void on_buy_Btn_clicked();

    void on_add_goods_Btn_clicked();

    void on_pay_tableView_clicked(const QModelIndex &index);

private:
    Ui::staff_operation *ui;
    QString filename = "../Supermarket_management_system/resources/goods.json";

    static int bill_serial;


};

#endif // STAFF_OPERATION_H
