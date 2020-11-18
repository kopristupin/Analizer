#ifndef ORDER_H
#define ORDER_H

#include <QWidget>
#include <QBoxLayout>
#include<QTreeWidget>
#include<QTableView>
#include<QtSql>
#include<QSqlTableModel>
#include<QPushButton>

namespace Ui {
class Order;
}

class Order : public QWidget
{
    Q_OBJECT

public:
    explicit Order(QWidget *parent = nullptr);
    ~Order();
    QVBoxLayout* vbl= new QVBoxLayout;
    QTreeWidget* twgt= new QTreeWidget;
    QSqlDatabase ordersBase;
    QTableView* view= new QTableView;
    QPushButton* del= new QPushButton("Delete order");
        QHBoxLayout* hbl= new QHBoxLayout;
    QPushButton* save= new QPushButton("Save");

public slots:
void test();
void saveOrder();



private:
    Ui::Order *ui;
};

#endif // ORDER_H
