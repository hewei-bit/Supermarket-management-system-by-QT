#include "add_num.h"
#include "ui_add_num.h"
#include "manager_operation.h"


add_num::add_num(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::add_num)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/pic/school.png"));
    connect(((manager_operation*)this->parentWidget()),&manager_operation::addnum,
            ((manager_operation*)this->parentWidget()),&manager_operation::addnumtostock);
}

add_num::~add_num()
{
    delete ui;
}

void add_num::on_pushButton_clicked()
{
    int num = ui->lineEdit->text().toInt();
    qDebug() <<num;
    emit ((manager_operation*)this->parentWidget())->addnum(num);
    ((manager_operation*)this->parentWidget())->show(); //QWidget*
    this->close();
}
