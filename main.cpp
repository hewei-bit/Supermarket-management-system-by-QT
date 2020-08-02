#include "login.h"
#include "manager_operation.h"
#include "staff_operation.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //定制皮肤在程序运行之前设置
    QFile file(":/qss/mystyle.qss");
    file.open(QIODevice::ReadOnly);
    QByteArray array =  file.readAll();
    // #define qApp (static_cast<QApplication *>(QCoreApplication::instance()))
    qApp->setStyleSheet(array);


    login w;
    w.show();

//    staff_operation so;
//    so.show();

//    manager_operation mo;
//    mo.show();

    return a.exec();
}
