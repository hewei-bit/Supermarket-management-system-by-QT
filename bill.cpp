#include "bill.h"
#include "ui_bill.h"
#include "QTime"
#include "QtDebug"
bill::bill(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bill)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/pic/school.png"));
    this->setFixedSize(691,587);
}

bill::~bill()
{
    delete ui;
}

void bill::on_return_Btn_clicked()
{
    this->close();
}

void bill::showbill(QList<goods> &glist)
{
    QFile file;
    QListWidgetItem *item_1 = new QListWidgetItem;
    file.setFileName(sales_record_filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Append |QIODevice::Text))
    {
        qDebug() << "File open error";
    }
    else {
        qDebug() <<"File open!";
    }
    //打印日期
    QTime tm = QTime::currentTime();
    QDateTime td = QDateTime::currentDateTime();
    QString opo = QString("日期：%1 %2").arg(td.toString("yyyy-MM-dd")).arg(tm.toString("hh:mm:ss"));
    //先写入文件
    file.write((opo+"\n").toUtf8());
    //写入文本框
    item_1->setText(opo);
    ui->listWidget->addItem(item_1);


    //标题
    QString title = QString("名称    单价    数量    合计");
    //先写入文件
    file.write((title+"\n").toUtf8());
    //写入文本框
    item_1->setText(title);
    ui->listWidget->addItem(item_1);

    //打印清单
    QList<goods>::iterator iter;
    int all_sum = 0;
    for (iter = glist.begin();iter!= glist.end();++iter) {
        //统计一项
        QString name = iter->getName();
        int num = iter->getQuantity();
        int price = iter->getPrice();
        int single_sum = iter->getSingle_sum();
        all_sum+=single_sum;
        QString allofone = QString(name+"    %1      %2      %3").arg(price).arg(num).arg(single_sum);
        //写入文件
        file.write((allofone+"\n").toUtf8());
        //写入文本框
        QListWidgetItem *item = new QListWidgetItem;
        item->setText(allofone);
        ui->listWidget->addItem(item);
    }

    //打印总和

    QString allofsum = QString("总计： %1").arg(all_sum);
    file.write((allofsum+"\n").toUtf8());
    ui->label->setText(allofsum);

    file.write("\n");
    file.close();
}
