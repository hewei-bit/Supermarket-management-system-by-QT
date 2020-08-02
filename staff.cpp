#include "staff.h"
#include "readwritejson.h"

Staff::Staff()
{

}

//遍历员工账号，未找到返回0，已找到返回1
int Staff::isAccountInJson(QString filename, QString account)
{
    readWriteJson *RWJson = new readWriteJson();
    QByteArray text = RWJson->open_json(filename);

    QJsonDocument doc = QJsonDocument::fromJson(text);
    QJsonObject object = doc.object();
    QJsonArray staffarray = object.value("staff").toArray();

    for (int i = 0; i < staffarray.count(); i++) {
        QJsonObject anyoneObject = staffarray.at(i).toObject();
        QString anyone_account = anyoneObject.value("account").toString();
        qDebug()<<anyone_account;
        if(anyone_account != account)
            continue;
        else {
            return i;
        }
    }

    return -1;
}
//检查员工密码是否正确，正确返回true，错误返回false
bool Staff::isPasswordCorrect(QString filename, QString account, QString password)
{
    readWriteJson *RWJson = new readWriteJson();
    int i = isAccountInJson(filename,account);
    if(i != -1)
    {
        QByteArray text = RWJson->open_json(filename);
        QJsonParseError errora;
        QJsonDocument doc(QJsonDocument::fromJson(text,&errora));
        QJsonObject object = doc.object();
        QJsonArray staffarray = object.value("staff").toArray();
        QJsonObject anyoneObject = staffarray.at(i).toObject();
        QString anyone_password = anyoneObject.value("password").toString();
        if(anyone_password != password)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else {
        return false;
    }
}

void Staff::showAcount(QString filename)
{
    readWriteJson *RWJson = new readWriteJson();
    RWJson->open_json(filename);



}

//添加员工账户，不存在才执行
void Staff::addAcount(QString filename, QString account, QString password)
{
    readWriteJson *RWJson = new readWriteJson();
    if(isAccountInJson(filename,account) == 0)
    {
        QByteArray text = RWJson->open_json(filename);
        // 使用QJsonObject对象插入键值对s
        QJsonDocument doc(QJsonDocument::fromJson(text));
        QJsonObject object = doc.object();
        QJsonArray staffarray = object.value("staff").toArray();
        QJsonObject accountObject;
        accountObject.insert("account",account);
        accountObject.insert("password",password);
        staffarray.append(accountObject);
        object.insert("staff",staffarray);

        RWJson->JsonToFile(object,filename);
    }
    else
    {
        qDebug() << "exits";
    }
}

//删除员工账户
void Staff::deleteAcount(QString filename, QString account)
{
    readWriteJson *RWJson = new readWriteJson();
    int i = isAccountInJson(filename,account);
    if(i != -1)
    {
        QFile file;
        file.setFileName(filename);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug() << "file open error";
        }
        else {
            qDebug() << "file open";
        }
        QByteArray text = file.readAll();
        file.close();
        file.remove();
        // 使用QJsonObject对象插入键值对。
        QJsonDocument doc(QJsonDocument::fromJson(text));
        QJsonObject object = doc.object();
        QJsonArray staffarray = object.value("staff").toArray();
        QJsonObject anyoneObject = staffarray.at(i).toObject();
        staffarray.removeAt(i);
        object.insert("staff",staffarray);

        RWJson->JsonToFile(object,filename);
    }
    else
    {
        qDebug() << "don't exist";
    }
}


Staff::Staff(QString account, QString password):
    account(account),password(password){}

bool Staff::isstaffInlist(Staff staffname, QList<Staff> &slist)
{
    for (int i = 0;i < slist.size();++i) {
        if(slist.at(i).getAccount() == staffname.account)
        {
            return true;
        }
    }
    return false;
}

void Staff::addstaff(Staff staffname, QList<Staff> &slist)
{
    if(isstaffInlist(staffname,slist))
    {
        return;
    }
    slist.append(staffname);
}

void Staff::deletestaff(Staff staffname, QList<Staff> &slist)
{
    for (int i = 0;i < slist.size();++i) {
        if(slist.at(i).getAccount() == staffname.account)
        {
            slist.removeAt(i);
        }
    }
}

QString Staff::getAccount() const
{
    return account;
}

void Staff::setAccount(const QString &value)
{
    account = value;
}

QString Staff::getPassword() const
{
    return password;
}

void Staff::setPassword(const QString &value)
{
    password = value;
}
