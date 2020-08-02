#include "manager_operation.h"
#include "ui_manager_operation.h"
#include "login.h"
#include "readwritejson.h"
#include "new_goods.h"
#include "new_staff.h"
#include "goods.h"
#include "add_num.h"



/* 创建员工界面数据模型 */
static QStandardItemModel* staff_model = new QStandardItemModel();
//库存界面数据模型
static QStandardItemModel* stock_model = new QStandardItemModel();
//货物链表
static QList<goods> goodslist_1;
//员工链表
static QList<Staff> stafflist;

manager_operation::manager_operation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::manager_operation)
{
    ui->setupUi(this);
    //获取货品和员工列表
    readWriteJson *RWJson = new readWriteJson();
    this->setWindowIcon(QIcon(":/pic/school.png"));
    this->setFixedSize(955,708);
    //从文件中读取
    RWJson->goodsJsonTolist(goods_filename,goodslist_1);
    RWJson->accountJsonTolist(account_filename,stafflist);
    //显示库存
    show_stock(goodslist_1);
    show_staff(stafflist);
    //销售记录
    QFile sales_rec;
    sales_rec.setFileName(sales_record_filename);
    sales_rec.open(QIODevice::ReadOnly);
    QByteArray  array = sales_rec.readAll();
    ui->sales_record_text->setText(array);
    //
    ui->tabWidget->setCurrentIndex(0);

}

manager_operation::~manager_operation()
{
    delete ui;
}

//设置标题
void manager_operation::show_staff(QList<Staff> &slist)
{
    staff_model->clear();
    /* 设置表格标题行(输入数据为QStringList类型) */
    staff_model->setHorizontalHeaderLabels({"账号","密码"});
    /* 自适应所有列，让它布满空间 */
    ui->staff_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /* 设置表格视图数据 */
    ui->staff_tableView->setModel(staff_model);

    /* 加载共10行数据，并每行有6列数据 */
    for(int i = 0;i<slist.size();i++)
    {
        /* 加载第一列(ID)数据 */
        staff_model->setItem(i, 0, new QStandardItem(slist.at(i).getAccount()));
        /* 加载第二列(species)数据 */
        staff_model->setItem(i, 1, new QStandardItem(slist.at(i).getPassword()));
    }
    /* 设置表格视图数据 */
    ui->staff_tableView->setModel(staff_model);
}

void manager_operation::show_stock(QList<goods> &glist)
{
    stock_model->clear();
    /* 设置表格标题行(输入数据为QStringList类型) */
    stock_model->setHorizontalHeaderLabels({"ID","种类","名称","库存","进价","售价","单位"});
    /* 自适应所有列，让它布满空间 */
    ui->goods_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /* 加载共10行数据，并每行有6列数据 */
    for(int i = 0;i<glist.size();i++)
    {
        /* 加载第一列(ID)数据 */
        stock_model->setItem(i, 0, new QStandardItem(QString("%1").arg(glist.at(i).getID())));
        /* 加载第二列(species)数据 */
        stock_model->setItem(i, 1, new QStandardItem(glist.at(i).getSpecies()));
        /* 加载第三列(name)数据 */
        stock_model->setItem(i, 2, new QStandardItem(glist.at(i).getName()));
        /* 加载第四列(quantity)数据 */
        stock_model->setItem(i, 3, new QStandardItem(QString("%1").arg(glist.at(i).getQuantity())));
        /* 加载第五列(cost)数据 */
        stock_model->setItem(i, 4, new QStandardItem(QString("%1").arg(glist.at(i).getCost())));
        /* 加载第六列(price)数据 */
        stock_model->setItem(i, 5, new QStandardItem(QString("%1").arg(glist.at(i).getPrice())));
        /* 加载第七列(unit)数据 */
        stock_model->setItem(i, 6, new QStandardItem(glist.at(i).getUnit()));
    }
    /* 设置表格视图数据 */
    ui->goods_tableView->setModel(stock_model);
}

void manager_operation::on_add_goods_Btn_clicked()
{   
    //跳转至新建货品界面
    new_goods *newgoods = new new_goods(this);
    newgoods->show();

}

void manager_operation::on_return_Btn_2_clicked()
{
    //清空链表
    goodslist_1.clear();
    stafflist.clear();

    //返回登录界面

    ((login*)this->parentWidget())->show(); //QWidget*
    this->close();
}

void manager_operation::on_add_staff_Btn_clicked()
{

    //跳转至新增员工界面
    new_staff *newstaff = new new_staff(this);
    newstaff->show();


}

void manager_operation::on_delete__staff_Btn_clicked()
{

    //获取当前行号
    int row = ui->staff_tableView->currentIndex().row();

    //查找链表中相应账户
    QList<Staff>::iterator iter;
    for ( int i = 0; i<stafflist.size(); ++i) {
        if(stafflist.at(i).getAccount() == staff_model->data(staff_model->index(row,0)))
        {
            stafflist.removeAt(i);
        }
    }

    //存入文件
    readWriteJson *RWJson = new readWriteJson();
    RWJson->accountlistToJson(account_filename,stafflist);

    //重新显示
    show_staff(stafflist);
}

void manager_operation::on_return_Btn_clicked()
{
    //清空链表
    goodslist_1.clear();
    stafflist.clear();
    //返回登录界面

    ((login*)this->parentWidget())->show(); //QWidget*
    this->close();
}

void manager_operation::addToStaffList(Staff anyone)
{
qDebug() << "cao"+anyone.getAccount();

    //加入链表
    stafflist.append(anyone);

    //存入文件
    readWriteJson *RWJson = new readWriteJson();
    RWJson->accountlistToJson(account_filename,stafflist);

    //重新显示
    show_staff(stafflist);

}

void manager_operation::addToGoodsList(goods anyone)
{
    qDebug() << anyone.getName();
    //加入链表
    goodslist_1.append(anyone);

    //存入文件
    readWriteJson *RWJson = new readWriteJson();
    RWJson->goodslistTojson(goods_filename,goodslist_1);

    //重新显示
    show_stock(goodslist_1);
}

void manager_operation::on_pushButton_clicked()
{
    //跳转至进货界面

    add_num *an = new add_num(this);
    an->show();

}

void manager_operation::addnumtostock(int num)
{
    //获取当前行号
    int row = ui->goods_tableView->currentIndex().row();
    qDebug() << row;
    //查找链表中相应账户
    QList<goods>::iterator iter;
    for (iter = goodslist_1.begin(); iter!=goodslist_1.end(); ++iter) {
        if(iter->getID() == stock_model->data(stock_model->index(row,0)))
        {
            qDebug() << iter->getQuantity();
            iter->setQuantity(iter->getQuantity()+num);
            qDebug() << iter->getQuantity();
        }
    }

    //存入文件
    readWriteJson *RWJson = new readWriteJson();
    RWJson->goodslistTojson(goods_filename,goodslist_1);

    //重新显示
    show_stock(goodslist_1);


}

void manager_operation::on_Btn_clicked()
{
    //清空链表
    goodslist_1.clear();
    stafflist.clear();

    //返回登录界面
    ((login*)this->parentWidget())->show(); //QWidget*
    this->close();
}
