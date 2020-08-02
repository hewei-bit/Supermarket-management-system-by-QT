#ifndef BILL_H
#define BILL_H

#include <QMainWindow>
#include "goods.h"
namespace Ui {
class bill;
}

class bill : public QMainWindow
{
    Q_OBJECT

public:
    explicit bill(QWidget *parent = nullptr);
    ~bill();
signals:
    void sendbill(QList<goods> &glist);

public slots:
    void on_return_Btn_clicked();

    void showbill(QList<goods> &glist);

private:
    Ui::bill *ui;
    QString sales_record_filename = "../Supermarket_management_system/resources/sold.txt";
};

#endif // BILL_H
