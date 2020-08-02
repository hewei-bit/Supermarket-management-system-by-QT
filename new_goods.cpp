#include "new_goods.h"
#include "ui_new_goods.h"
#include "manager_operation.h"
#include "readwritejson.h"

static int num_1 = 0;
new_goods::new_goods(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_goods)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/pic/school.png"));
    this->setFixedSize(516,543);

}

new_goods::~new_goods()
{
    delete ui;
}

void new_goods::on_return_Btn_clicked()
{
    //返回登录界面
    ((manager_operation*)this->parentWidget())->show(); //QWidget*
    this->close();
}

void new_goods::on_add_Btn_clicked()
{

    QList<goods> goodslist_new;
    //读文件，存入本地链表中
    //获取货品和员工列表
    readWriteJson *RWJson = new readWriteJson();
    //从文件中读取
    RWJson->goodsJsonTolist(goods_filename,goodslist_new);
    for (int i = 0; i < goodslist_new.size(); ++i) {
         qDebug() << goodslist_new.at(i).getName();

    }
    //获取此次输入的商品名
    QString new_name = ui->name_lineEdit_6->text();
    //查看商品是否存在
    bool flag = false;
    for (int i = 0; i < goodslist_new.size(); ++i) {
        if(new_name == goodslist_new.at(i).getName())
        {
            flag = true;
        }
    }
    //存在则弹出警告
    if(flag)
    {
        QMessageBox::warning(this,"警告","该商品已经存在，请在库中直接修改");
    }
    //不存在则获取
    else {
//        int new_ID = ui->ID_lineEdit->text().toInt();
        int new_ID = goodslist_new.at(goodslist_new.size()-1).getID()+1;
        QString new_unit = ui->unit_lineEdit->text();
        QString new_species = ui->speiecslineEdit_7->text();
        int new_quantity = ui->num_lineEdit_5->text().toInt();
        int new_price = ui->price_lineEdit_4->text().toInt();
        int new_cost = ui->cost_lineEdit_3->text().toInt();
        //检查ID
        bool flag_2 = false;
        for (int i = 0; i < goodslist_new.size(); ++i) {
            if(new_ID == goodslist_new.at(i).getID())
            {
                flag_2 = true;
            }
        }

        //检查是否存在未输入窗口
        if(ui->unit_lineEdit->text()== ""|| ui->speiecslineEdit_7->text() == "" || ui->cost_lineEdit_3->text() == ""
                || ui->num_lineEdit_5->text() == "" || ui->price_lineEdit_4->text() == "")
        {
            QMessageBox::warning(this,"警告","信息不全无法录入");
        }
        //检查ID是否已经存在
        else if (flag_2) {
            QMessageBox::warning(this,"警告","ID已经被占用");
        }
        //检查售价是否大于进价
        else if (new_price < new_cost ) {
            QMessageBox::warning(this,"警告","你是要做赔本生意吗？？？");
        }
        //检查进货数是否为零
        else if (new_quantity <= 0) {
            QMessageBox::warning(this,"警告","请填写正确的进货数！！！");
        }
        else {
            if(num_1==0)
            {
                connect(((manager_operation*)this->parentWidget()),&manager_operation::sendAgoods,((manager_operation*)this->parentWidget()),&manager_operation::addToGoodsList);
            }
            //存入新建goods节点
            goods new_goods(new_ID,new_species,new_name,new_quantity,new_cost,new_price,new_unit);
            //发送回父界面
            emit ((manager_operation*)this->parentWidget())->sendAgoods(new_goods);
            num_1++;

        }
    }
}
