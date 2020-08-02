#include "login.h"
#include "ui_login.h"
#include "staff_operation.h"
#include "new_staff.h"
#include "manager_operation.h"

#include "readwritejson.h"
#include "goods.h"
#include "staff.h"


login::login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/pic/school.png"));
       this->setFixedSize(662,442);
    QImage Image;
        Image.load(":/pic/school.png");
        QPixmap pixmap = QPixmap::fromImage(Image);
        int with = ui->label_4->width();
        int height = ui->label_4->height();
        QPixmap fitpixmap = pixmap.scaled(with, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // 饱满填充
        //QPixmap fitpixmap = pixmap.scaled(with, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);  // 按比例缩放
        ui->label_4->setPixmap(fitpixmap);


}

login::~login()
{
    delete ui;


}

void login::on_mannager_Btn_clicked()
{
    static int count_1 = 0;
    readWriteJson *RWJson = new readWriteJson();

    //获取键入账号密码
    QString account = ui->account_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    //打开json文件
    QByteArray text = RWJson->open_json(managerfilename);

    //获取json中管理员账号密码
    QJsonDocument doc = QJsonDocument::fromJson(text);
    QJsonObject object = doc.object();
    QJsonArray staffarray = object.value("manager").toArray();
    QJsonObject anyoneObject = staffarray.at(0).toObject();

    //校验密码
    if(anyoneObject.value("account").toString()==account)
    {
        if(anyoneObject.value("password").toString()==password)
        {
            count_1 = 0;
            QMessageBox QM;
            //设置文本框的大小
            QM.setStyleSheet("QLabel{"
                             "min-width:130px;"
                             "min-height:100px; "
                                  "font-size:16px;"
                                  "}");
            QM.setText(QString::fromStdString("登陆成功"));
            QM.setWindowTitle(QString::fromStdString("恭喜"));
            QM.setIcon(QMessageBox::Icon::Information );
            QM.setButtonText(QMessageBox::Ok , QString::fromStdString("确定"));
            QM.exec();

//            QM.information(this,"管理员登录成果","success！！！");
            //跳转至管理员界面
            manager_operation *mop = new manager_operation(this);
            mop->show();

            this->hide();
        }
        else
        {
            QMessageBox QM;
            //设置文本框的大小
            QM.setStyleSheet("QLabel{"
                             "min-width:130px;"
                             "min-height:100px; "
                                  "font-size:16px;"
                                  "}");
            QM.warning(this,"登录失败","password wrong");
            count_1+=1;
        }
    }
    else
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");

        QM.warning(this,"登录失败","account wrong");
        count_1+=1;
    }
    if(count_1 == 3)
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");
        QM.warning(this,"fail","you have try 3 times");
        this->close();
    }


}

void login::on_staff_Btn_clicked()
{

    Staff *st = new Staff();
    //获取员工账号密码
    QString account = ui->account_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    static int count = 0;
    //校验账号密码
    if(st->isAccountInJson(accountfilename,account)!= -1)
    {
        if(st->isPasswordCorrect(accountfilename,account,password) == true)
        {
            count = 0;
            QMessageBox QM;
            //设置文本框的大小
            QM.setStyleSheet("QLabel{"
                             "min-width:130px;"
                             "min-height:100px; "
                                  "font-size:16px;"
                                  "}");
            QM.information(this,"员工成功","success");
            staff_operation *sop = new staff_operation(this);
            sop->show();
            this->hide();
        }
        else
        {
            QMessageBox QM;
            //设置文本框的大小
            QM.setStyleSheet("QLabel{"
                             "min-width:130px;"
                             "min-height:100px; "
                                  "font-size:16px;"
                                  "}");
            QM.warning(this,"fail","password wrong");
            count+=1;
        }
    }
    else
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");
        QM.warning(this,"fail","account wrong");
        count+=1;
    }
    if(count == 3)
    {
        QMessageBox QM;
        //设置文本框的大小
        QM.setStyleSheet("QLabel{"
                         "min-width:130px;"
                         "min-height:100px; "
                              "font-size:16px;"
                              "}");
        QM.warning(this,"fail","you have try 3 times");
        this->close();
    }

}


//退出
void login::on_exit_btn_clicked()
{
    this->close();
}
