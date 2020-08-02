#ifndef LOGIN_H
#define LOGIN_H


#include <iostream>
#include <list>

#include <QMainWindow>
#include <QMessageBox>
#include <QtDebug>
#include <QJsonParseError>
//文件IO
#include <QFile>
#include <QTextCodec>

//JSON数据解析
#include<QJsonArray>  //[]
#include <QJsonDocument> //JSON文档 --- 将服务器数据转换成一个QJsonDocument
#include <QJsonObject> //{}
#include <QJsonArray>

#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>

#include <QDateTime>
#include <QDir>



namespace Ui {
class login;
}

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_mannager_Btn_clicked();

    void on_staff_Btn_clicked();

    void on_exit_btn_clicked();


private:
    Ui::login *ui;
    QString account;
    QString password;
    QString accountfilename = "../Supermarket_management_system/resources/account.json";
    QString goodsfilename = "../Supermarket_management_system/resources/goods.json";
    QString managerfilename = "../Supermarket_management_system/resources/manager_account.json";

};

#endif // LOGIN_H
