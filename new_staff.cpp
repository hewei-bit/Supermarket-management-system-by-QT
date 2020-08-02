#include "new_staff.h"
#include "ui_new_staff.h"
#include "manager_operation.h"
#include "readwritejson.h"

static int num = 0;
new_staff::new_staff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_staff)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/pic/school.png"));
    this->setFixedSize(463,407);

}

new_staff::~new_staff()
{
    delete ui;
}

void new_staff::on_register_Btn_clicked()
{
    QList<Staff> stafflist_new;
    //读文件，存入本地链表中
    //获取货品和员工列表
    readWriteJson *RWJson = new readWriteJson();
    //从文件中读取
    RWJson->accountJsonTolist(account_filename,stafflist_new);

    //获取此次输入的账户名
    QString new_account = ui->account_lineEdit->text();
    qDebug() << "new"+new_account;
    //查看账户是否存在
    bool flag = false;
    for (int i = 0; i < stafflist_new.size(); ++i) {
        if(new_account == stafflist_new.at(i).getAccount())
        {
            flag = true;
        }
    }

    //存在则弹出警告
    if(flag)
    {
        QMessageBox::warning(this,"警告","该用户名已经存在");
        return;
    }
    //不存在则获取
    else {
        //检测两次密码输入是否一致
        QString new_password_1 = ui->password_lineEdit->text();
        QString new_password_2 = ui->password_lineEdit_2->text();
        if(new_password_1 == new_password_2)
        {
            //存入新建Staff节点
            Staff new_staff(new_account,new_password_1);
            if(num == 0)
            {
                connect(((manager_operation*)this->parentWidget()),&manager_operation::sendAstaff,((manager_operation*)this->parentWidget()),&manager_operation::addToStaffList);
            }
            //发送回父界面
            qDebug() << "emit";
            emit ((manager_operation*)this->parentWidget())->sendAstaff(new_staff);

            num++;
        }
        else {
            QMessageBox::warning(this,"警告","两次密码不一致");
            return;
        }
    }

    this->close();

}

void new_staff::on_exit_btn_clicked()
{
    //返回登录界面
    ((manager_operation*)this->parentWidget())->show(); //QWidget*
    this->close();
}
