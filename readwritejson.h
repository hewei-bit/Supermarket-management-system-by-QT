#ifndef READWRITEJSON_H
#define READWRITEJSON_H

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

#include "login.h"
#include "goods.h"
#include "staff.h"

class readWriteJson
{
public:
    readWriteJson();
    ~readWriteJson();



    //货物操作
    void goodsJsonTolist(QString filename,QList<goods>& glist);
    void goodslistTojson(QString filename,QList<goods>& glist);

    //账户操作
    void accountJsonTolist(QString filename,QList<Staff>& slist);
    void accountlistToJson(QString filename,QList<Staff>& slist);

    //打开json和转换json
    QByteArray open_json(QString filename);
    void JsonToFile(QJsonObject object,QString filename);

private:
    QList<goods> GDLIST;
    QString acount_filename = "../Supermarket_management_system/resources/account.json";
    QString goods_filename = "../Supermarket_management_system/resources/goods.json";
};





#endif // READWRITEJSON_H
