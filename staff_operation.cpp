#include "staff_operation.h"
#include "ui_staff_operation.h"
#include "readwritejson.h"

#include "login.h"
#include "bill.h"

#include "goods.h"

/* 创建结算界面数据模型 */
static QStandardItemModel* settlement_model = new QStandardItemModel();
//库存界面数据模型
static QStandardItemModel* model = new QStandardItemModel();

//记录行号
int staff_operation::bill_serial = 0;
//货物链表
static QList<goods> goodslist;
//购物车链表
static QList<goods> shoppinglist;



staff_operation::staff_operation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::staff_operation)
{
    this->setWindowIcon(QIcon(":/pic/school.png"));
    this->setFixedSize(1224,758);
    ui->setupUi(this);

    //获取货品列表
    readWriteJson *RWJson = new readWriteJson();
    //从文件中读取
    RWJson->goodsJsonTolist(filename,goodslist);

    //显示库存
    showStock(goodslist);
    //购物车
    showShoppingcar(shoppinglist);

    //添加至商品类型的combox
    QStringList goodstypelist;
    QStringList goodsnamelist;
    QList<goods>::iterator iter;
    for (iter = goodslist.begin(); iter != goodslist.end(); ++iter)
    {
        for (int i = 0;i < ui->goods_name_comboBox->count();i++) {
            goodsnamelist.append(ui->goods_name_comboBox->itemText(i));
        }
        if(goodsnamelist.contains(iter->getName()) == false)
        {
           ui->goods_name_comboBox->addItem(iter->getName());
        }

        for (int i = 0;i < ui->goods_type_comboBox->count();i++) {
            goodstypelist.append(ui->goods_type_comboBox->itemText(i));
        }
        if( goodstypelist.contains(iter->getSpecies()) == false)
        {
           ui->goods_type_comboBox->addItem(iter->getSpecies());
        }
    }

    //显示结算页面
    ui->tabWidget->setCurrentIndex(0);
}

staff_operation::~staff_operation()
{
    delete ui;
}

//显示库存
void staff_operation::showStock(QList<goods> &glist)
{ 
    model->clear();
    /* 设置表格标题行(输入数据为QStringList类型) */
    model->setHorizontalHeaderLabels({"ID","种类","名称","库存","进价","售价","单位"});
    /* 自适应所有列，让它布满空间 */
    ui->goods_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    /* 加载共10行数据，并每行有6列数据 */
    for(int i = 0;i<glist.size();i++)
    {
        /* 加载第一列(ID)数据 */
        model->setItem(i, 0, new QStandardItem(QString("%1").arg(glist.at(i).getID())));
        /* 加载第二列(species)数据 */
        model->setItem(i, 1, new QStandardItem(glist.at(i).getSpecies()));
        /* 加载第三列(name)数据 */
        model->setItem(i, 2, new QStandardItem(glist.at(i).getName()));
        /* 加载第四列(quantity)数据 */
        model->setItem(i, 3, new QStandardItem(QString("%1").arg(glist.at(i).getQuantity())));
        /* 加载第五列(cost)数据 */
        model->setItem(i, 4, new QStandardItem(QString("%1").arg(glist.at(i).getCost())));
        /* 加载第六列(price)数据 */
        model->setItem(i, 5, new QStandardItem(QString("%1").arg(glist.at(i).getPrice())));
        /* 加载第七列(unit)数据 */
        model->setItem(i, 6, new QStandardItem(glist.at(i).getUnit()));
    }
    /* 设置表格视图数据 */
    ui->goods_tableView->setModel(model);
}


//设置购物车标题
void staff_operation::showShoppingcar(QList<goods> &glist)
{
    /* 设置表格标题行(输入数据为QStringList类型) */
    settlement_model->setHorizontalHeaderLabels({"ID","种类","名称","数量","售价","合计"});
    /* 自适应所有列，让它布满空间 */
    ui->pay_tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    /* 设置表格视图数据 */
    ui->pay_tableView->setModel(settlement_model);
}



//添加物品至购物车中
void staff_operation::on_add_goods_Btn_clicked()
{
    //差错检测,购买数不能大于库存数
    if(ui->goods_sell_num_spinBox->text().toInt() > ui->goods_num_textBrowser->toPlainText().toInt() )
    {
        QMessageBox::warning(this,"警告","没有那么多库存！！！！！");
    }
    else if(ui->goods_sell_num_spinBox->text().toInt() == 0)
    {
        QMessageBox::warning(this,"警告","没有放东西进购物车！！！！！");
    }
    else
    {

        bool tag = true;
        //查询是否在购物车中
        QList<goods>::iterator iter;
        QList<goods>::iterator iter_next;


        for (iter = shoppinglist.begin(); iter != shoppinglist.end(); ++iter)
        {
            //有相同ID
            if(iter->getID() == ui->goods_ID_textBrowser->toPlainText().toInt())
            {
                qDebug() << "exits";
                tag = false;

                iter->setQuantity(iter->getQuantity()+ui->goods_sell_num_spinBox->text().toInt());
                //更新购物车界面相应条款
                //找到ID所在行
                int sign;
                for (int i = 0; i < settlement_model->rowCount(); ++i)
                {
                    if(iter->getID() == settlement_model->data(settlement_model->index(i,0)))
                    {
                        sign = i;
                        qDebug() << sign;
                    }
                }

                /* 加载第四列(个数)数据 */
                //拿到原来的数再加上
                int pre_quantity = settlement_model->data(settlement_model->index(sign,3)).toInt();
                int now_quantity = ui->goods_sell_num_spinBox->text().toInt()+pre_quantity;
                settlement_model->setItem(sign, 3, new QStandardItem(QString("%1").arg(now_quantity)));

                /* 加载第六列(合计)数据 */
                //拿到原来的数再加上
                int num = ui->goods_price_textBrowser->toPlainText().toInt();
                int now_total = now_quantity*num;
                settlement_model->setItem(sign, 5, new QStandardItem(QString("%1").arg(now_total)));

                //更新库存链表
                int new_quantity;
                for (iter_next = goodslist.begin(); iter_next != goodslist.end(); ++iter_next)
                {
                    if(ui->goods_ID_textBrowser->toPlainText() == QString("%1").arg(iter_next->getID()))
                    {
                        new_quantity = iter_next->getQuantity() - ui->goods_sell_num_spinBox->text().toInt();
                        iter_next->setQuantity(new_quantity);
                    }
                }

                //更新库存界面
                showStock(goodslist);

                //更新购物界面
                ui->goods_num_textBrowser->setText(QString("%1").arg(new_quantity));

            }

        }

        //不在购物车中，加入新链表
        if(tag)
        {
            //加入购物车链表
            goods gg;
            gg.setID(ui->goods_ID_textBrowser->toPlainText().toInt());
            gg.setPrice(ui->goods_price_textBrowser->toPlainText().toInt());
            gg.setName(ui->goods_name_comboBox->currentText());
            gg.setSpecies(ui->goods_type_comboBox->currentText());
            gg.setQuantity(ui->goods_sell_num_spinBox->text().toInt());
            int num = ui->goods_sell_num_spinBox->text().toInt();
            int single = ui->goods_price_textBrowser->toPlainText().toInt();
            int single_sum = single*num;
            gg.setSingle_sum(single_sum);
            shoppinglist.append(gg);
            //不显示进价和单位
            //显示
            /* 加载第一列(ID)数据 */
            settlement_model->setItem(bill_serial, 0, new QStandardItem(ui->goods_ID_textBrowser->toPlainText()));
            /* 加载第二列(种类)数据 */
            settlement_model->setItem(bill_serial, 1, new QStandardItem(ui->goods_type_comboBox->currentText()));
            /* 加载第三列(名称)数据 */
            settlement_model->setItem(bill_serial, 2, new QStandardItem(ui->goods_name_comboBox->currentText()));
            /* 加载第四列(个数)数据 */
            settlement_model->setItem(bill_serial, 3, new QStandardItem(ui->goods_sell_num_spinBox->text()));
            /* 加载第五列(售价)数据 */
            settlement_model->setItem(bill_serial, 4, new QStandardItem(ui->goods_price_textBrowser->toPlainText()));
            /* 加载第六列(单个合计)数据 */
            settlement_model->setItem(bill_serial, 5, new QStandardItem(QString("%1").arg(single_sum)));

            bill_serial++;

            //更新库存链表
            int new_quantity;
            for (iter_next = goodslist.begin(); iter_next != goodslist.end(); ++iter_next)
            {
                if(ui->goods_ID_textBrowser->toPlainText() == QString("%1").arg(iter_next->getID()))
                {
                    new_quantity = iter_next->getQuantity() - ui->goods_sell_num_spinBox->text().toInt();
                    iter_next->setQuantity(new_quantity);
                }
            }

            //更新库存界面
            showStock(goodslist);

            //更新购物界面
            ui->goods_num_textBrowser->setText(QString("%1").arg(new_quantity));

        }

    }

}

//结算
void staff_operation::on_buy_Btn_clicked()
{
    //跳转至管理员界面
    bill *billshow = new bill(this);
    billshow->show();

    //发送账单
    connect(billshow,&bill::sendbill,billshow,&bill::showbill);
    emit billshow->sendbill(shoppinglist);

    //将链表存入文件
    readWriteJson *RWJson = new readWriteJson();
    RWJson->goodslistTojson(filename,goodslist);

    //清空购物和库存界面以及链表
    model->clear();
    settlement_model->clear();
    shoppinglist.clear();
    goodslist.clear();
    bill_serial = 0;
    //重新读取库存界面
    //从文件中读取
    RWJson->goodsJsonTolist(filename,goodslist);
    showShoppingcar(shoppinglist);
    showStock(goodslist);

    //更新商品的数量
    //将当前选项名赋值给变量str，输出当前选项名
    QString str = ui->goods_name_comboBox->currentText();

    //添加至商品类型的combox
    QList<goods>::iterator iter;
    for (iter = goodslist.begin(); iter != goodslist.end(); ++iter)
    {
        if(iter->getName() == str)
        {
            ui->goods_ID_textBrowser->setText(QString("%1").arg(iter->getID()));
            ui->goods_num_textBrowser->setText(QString("%1").arg(iter->getQuantity()));
            ui->goods_price_textBrowser->setText(QString("%1").arg(iter->getPrice()));
        }
    }
}

//清除购物车
void staff_operation::on_clean_Btn_clicked()
{
    //表标记变为零
    bill_serial = 0;
    qDebug()<< bill_serial;

    //取得货品数量加回链表之中
    int row = settlement_model->rowCount();
    qDebug() << row;
    for (int i = 0; i < row; ++i) {
        int theID = settlement_model->data(settlement_model->index(i,0)).toInt();
        qDebug() << theID;
        QList<goods>::iterator iter;
        for (iter = goodslist.begin(); iter != goodslist.end(); ++iter)
        {
            if(theID == iter->getID())
            {
                qDebug() << iter->getID();
                int thenum = settlement_model->data(settlement_model->index(i,3)).toInt();
                qDebug() << iter->getQuantity();
                iter->setQuantity(thenum + iter->getQuantity());
                qDebug() << iter->getQuantity();
            }
        }
    }


    //将链表存入文件
    readWriteJson *RWJson = new readWriteJson();
    RWJson->goodslistTojson(filename,goodslist);


    //清空购物和库存界面以及链表
    model->clear();
    settlement_model->clear();
    shoppinglist.clear();
    goodslist.clear();
    bill_serial = 0;

    //重新读取库存界面
    //从文件中读取
    RWJson->goodsJsonTolist(filename,goodslist);
    showShoppingcar(shoppinglist);
    showStock(goodslist);

    //更新商品的数量
    //将当前选项名赋值给变量str，输出当前选项名
    QString str = ui->goods_name_comboBox->currentText();

    //添加至商品类型的combox
    QList<goods>::iterator iter;
    for (iter = goodslist.begin(); iter != goodslist.end(); ++iter)
    {
        if(iter->getName() == str)
        {
            ui->goods_ID_textBrowser->setText(QString("%1").arg(iter->getID()));
            ui->goods_num_textBrowser->setText(QString("%1").arg(iter->getQuantity()));
            ui->goods_price_textBrowser->setText(QString("%1").arg(iter->getPrice()));
        }
    }
}

//删除某一项
void staff_operation::on_delete_Btn_clicked()
{

    bill_serial--;
    int row = ui->pay_tableView->currentIndex().row();

    //取得货品数量加回链表之中
    int theID = settlement_model->data(settlement_model->index(row,0)).toInt();
    QList<goods>::iterator iter;
    for (iter = goodslist.begin(); iter != goodslist.end(); ++iter){
        if(theID == iter->getID())
        {
            qDebug() << iter->getID();
            int thenum = settlement_model->data(settlement_model->index(row,3)).toInt();
            qDebug() << iter->getQuantity();
            iter->setQuantity(thenum + iter->getQuantity());
            qDebug() << iter->getQuantity();
        }
    }

    //重新显示库存
    showStock(goodslist);

    //更新商品的数量
    QString str = ui->goods_name_comboBox->currentText();
    for (iter = goodslist.begin(); iter != goodslist.end(); ++iter)
    {
        if(iter->getName() == str)
        {
            ui->goods_ID_textBrowser->setText(QString("%1").arg(iter->getID()));
            ui->goods_num_textBrowser->setText(QString("%1").arg(iter->getQuantity()));
            ui->goods_price_textBrowser->setText(QString("%1").arg(iter->getPrice()));
        }
    }

    //移除出购物车
    settlement_model->removeRow(row);
    qDebug()<< bill_serial;

}


void staff_operation::on_back_Btn_clicked()
{
    //清空链表
    goodslist.clear();
    shoppinglist.clear();

    ((login*)this->parentWidget())->show(); //QWidget*
    this->close();
}


void staff_operation::on_return_Btn_clicked()
{
    //返回结算界面
    ui->tabWidget->setCurrentIndex(0);
}

//商品种类列表
void staff_operation::on_goods_type_comboBox_currentTextChanged(const QString &arg1)
{
    //清空
    ui->goods_name_comboBox->clear();

    //将当前选项名赋值给变量str，输出当前选项名
    QString str = ui->goods_type_comboBox->currentText();

    //添加至商品类型的combox
    QStringList goodsnamelist;
    QList<goods>::iterator iter;
    for (iter = goodslist.begin(); iter != goodslist.end(); ++iter)
    {
        if(iter->getSpecies() == str)
        {
            ui->goods_name_comboBox->addItem(iter->getName());
        }
    }
}

//商品列表
void staff_operation::on_goods_name_comboBox_currentTextChanged(const QString &arg1)
{
    //将当前选项名赋值给变量str，输出当前选项名
    QString str = ui->goods_name_comboBox->currentText();

    //添加至商品类型的combox
    QList<goods>::iterator iter;
    for (iter = goodslist.begin(); iter != goodslist.end(); ++iter)
    {
        if(iter->getName() == str)
        {
            ui->goods_ID_textBrowser->setText(QString("%1").arg(iter->getID()));
            ui->goods_num_textBrowser->setText(QString("%1").arg(iter->getQuantity()));
            ui->goods_price_textBrowser->setText(QString("%1").arg(iter->getPrice()));
        }
    }
}

void staff_operation::on_pay_tableView_clicked(const QModelIndex &index)
{
    qDebug() << "item clicked";
}
