#include "readwritejson.h"
#include "staff_operation.h"
#include "new_staff.h"
#include "manager_operation.h"


readWriteJson::readWriteJson()
{

}

readWriteJson::~readWriteJson()
{

}

void readWriteJson::goodsJsonTolist(QString filename,QList<goods>& glist)
{
    //打开文件
    QByteArray text = open_json(filename);
//    QList<goods> goodslist;

    //获取货品信息
    QJsonDocument doc = QJsonDocument::fromJson(text);
    QJsonObject object = doc.object();
    QJsonArray shop_array = object.value("shoparray").toArray();

    //遍历商品
    for (int i = 0;i < shop_array.size();i++) {

        QJsonObject anyone_object = shop_array.at(i).toObject();
        //读取信息
        int ID = anyone_object.value("ID").toInt();
        QString species = anyone_object.value("species").toString();
        QString name = anyone_object.value("name").toString();
        int quantity = anyone_object.value("quantity").toInt();
        int cost =  anyone_object.value("cost").toInt();
        int price =  anyone_object.value("price").toInt();
        QString unit = anyone_object.value("unit").toString();
        //构造商品
        goods anyone(ID,species,name,quantity,cost,price,unit);
        //将商品加入链表
        glist.append(anyone);
    }


}

void readWriteJson::goodslistTojson(QString filename,QList<goods> &glist)
{
    QFile file;
    file.setFileName(filename);
    file.remove();
    QJsonObject object;

    QJsonArray shop_array;
    for (int i = 0; i < glist.count(); ++i) {
        QJsonObject goodsObject;
        goodsObject.insert("ID",glist.at(i).getID());
        goodsObject.insert("species",glist.at(i).getSpecies());
        goodsObject.insert("name",glist.at(i).getName());
        goodsObject.insert("quantity",glist.at(i).getQuantity());
        goodsObject.insert("cost",glist.at(i).getCost());
        goodsObject.insert("price",glist.at(i).getPrice());
        goodsObject.insert("unit",glist.at(i).getUnit());
        shop_array.append(goodsObject);
    }
    object.insert("shoparray",shop_array);

    QJsonDocument doc;
    doc.setObject(object);
    JsonToFile(object,filename);

}

void readWriteJson::accountJsonTolist(QString filename, QList<Staff> &slist)
{
    //打开文件
    QByteArray text = open_json(filename);

    QJsonDocument doc = QJsonDocument::fromJson(text);
    QJsonObject object = doc.object();
    QJsonArray staffarray = object.value("staff").toArray();

    for (int i = 0; i < staffarray.size(); ++i) {
        QJsonObject anyone_object = staffarray.at(i).toObject();
        //读取信息
        QString anyone_account = anyone_object.value("account").toString();
        QString anyone_password = anyone_object.value("password").toString();
        //构造职员账户
        Staff anyone(anyone_account,anyone_password);
        //加入链表
        slist.append(anyone);
    }
}

void readWriteJson::accountlistToJson(QString filename, QList<Staff> &slist)
{
    QFile file;
    file.setFileName(filename);
    file.remove();
    QJsonObject object;

    QJsonArray staff_array;
    for (int i = 0; i < slist.count(); ++i) {
        QJsonObject staffObject;
        staffObject.insert("account",slist.at(i).getAccount());
        staffObject.insert("password",slist.at(i).getPassword());

        staff_array.append(staffObject);
    }
    object.insert("staff",staff_array);

    QJsonDocument doc;
    doc.setObject(object);
    JsonToFile(object,filename);
}


QByteArray readWriteJson::open_json(QString filename)
{
    QFile file;
    //设置文件路径
    file.setFileName(filename);
    //检查是否打开成功
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug() << "file open error";
    }
    else {
        qDebug() << "file open";
    }
    //读取文件信息
    QByteArray text = file.readAll();
    file.close();
    return text;
}

void readWriteJson::JsonToFile(QJsonObject object, QString filename)
{
    QJsonDocument doc;
    doc.setObject(object);
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    file.write(doc.toJson());
    file.close();
}
