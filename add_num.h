#ifndef ADD_NUM_H
#define ADD_NUM_H

#include <QMainWindow>

namespace Ui {
class add_num;
}

class add_num : public QMainWindow
{
    Q_OBJECT

public:
    explicit add_num(QWidget *parent = nullptr);
    ~add_num();

private slots:
    void on_pushButton_clicked();

private:
    Ui::add_num *ui;
};

#endif // ADD_NUM_H
