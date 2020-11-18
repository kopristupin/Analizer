#ifndef CHECKING_H
#define CHECKING_H

#include <QDialog>
#include<QTreeWidget>
#include<QDate>

namespace Ui {
class checking;
}

class checking : public QDialog
{
    Q_OBJECT

public:
    explicit checking(QString str, QWidget *parent = nullptr);
    ~checking();
    QString stringFrom ();
    QString stringName();
    QDate strDate();
QString AEdate();

private:
    Ui::checking *ui;
    QString nameOfSection;
};

#endif // CHECKING_H
