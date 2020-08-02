#ifndef GOODS_H
#define GOODS_H

#include <iostream>

//文件IO
#include <QFile>
#include <QTextCodec>

using namespace std;

class goods
{
public:

    goods(int ID=1000,QString species="",QString name="",
          int quantity=0,int cost=0,int price=0,QString unit="",int single_sum=0);
    ~goods();

    bool isgoodsInrepository(goods goodsname,QList<goods>& glist);
    void addgoods(goods goodsname,QList<goods>& glist);
    void deletegoods(goods goodsname,QList<goods>& glist);


    QString getName() const;

    int getQuantity() const;

    int getCost() const;

    int getPrice() const;

    int getID() const;

    QString getSpecies() const;

    QString getUnit() const;

    void setID(int value);

    void setSpecies(const QString &value);

    void setName(const QString &value);

    void setQuantity(int value);

    void setCost(int value);

    void setPrice(int value);

    void setUnit(const QString &value);

    int getSingle_sum() const;
    void setSingle_sum(int value);

private:
    int ID;
    QString species;
    QString name;
    int quantity;
    int cost;
    int price;
    int single_sum;
    QString unit;

};

#endif // GOODS_H
