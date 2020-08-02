#include "goods.h"



goods::goods(int ID,QString species,QString name,
             int quantity,int cost,int price,QString unit,int single_sum):
    ID(ID),species(species),name(name),
    quantity(quantity),cost(cost),price(price),unit(unit),single_sum(single_sum)
{}

goods::~goods()
{

}

bool goods::isgoodsInrepository(goods goodsname, QList<goods> &glist)
{
    for (int i = 0; i < glist.size(); ++i) {
        if(glist.at(i).getName() == goodsname.name)
        {
            return true;
        }
    }
    return false;
}

void goods::addgoods(goods goodsname, QList<goods> &glist)
{
    if(isgoodsInrepository(goodsname, glist))
    {
        return;
    }
    glist.append(goodsname);
}

void goods::deletegoods(goods goodsname, QList<goods> &glist)
{
    for (int i = 0; i < glist.size(); ++i)
    {
        if(glist.at(i).getName() == goodsname.name)
        {
            glist.removeAt(i);
        }
    }
}

QString goods::getName() const
{
    return name;
}

int goods::getQuantity() const
{
    return quantity;
}

int goods::getCost() const
{
    return cost;
}

int goods::getPrice() const
{
    return price;
}

int goods::getID() const
{
    return ID;
}

QString goods::getSpecies() const
{
    return species;
}

QString goods::getUnit() const
{
    return unit;
}

void goods::setID(int value)
{
    ID = value;
}

void goods::setSpecies(const QString &value)
{
    species = value;
}

void goods::setName(const QString &value)
{
    name = value;
}

void goods::setQuantity(int value)
{
    quantity = value;
}

void goods::setCost(int value)
{
    cost = value;
}

void goods::setPrice(int value)
{
    price = value;
}

void goods::setUnit(const QString &value)
{
    unit = value;
}

int goods::getSingle_sum() const
{
    return single_sum;
}

void goods::setSingle_sum(int value)
{
    single_sum = value;
}
