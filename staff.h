#ifndef STAFF_H
#define STAFF_H


#include <iostream>
#include <QMessageBox>
#include <QtDebug>
//文件IO
#include <QFile>
#include <QTextCodec>
#include <QList>
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

class Staff
{
public:
    Staff();
    Staff(QString account,QString password);

    //链表操作
    bool isstaffInlist(Staff staffname,QList<Staff>& slist);
    void addstaff(Staff staffname,QList<Staff>& slist);
    void deletestaff(Staff staffname,QList<Staff>& slist);

    //IO直接账户操作
    int isAccountInJson(QString filename,QString account);
    bool isPasswordCorrect(QString filename,QString account,QString password);
    //未实现
    void showAcount(QString filename);

    void addAcount(QString filename,QString account,QString password);
    void deleteAcount(QString filename,QString account);


    //私有成员
    QString getAccount() const;
    void setAccount(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

private:
    QString account;
    QString password;
    QString acount_filename = "../Supermarket_management_system/resources/account.json";
};

#endif // STAFF_H
