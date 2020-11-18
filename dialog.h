#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QTreeWidget>
#include<QDate>
#include<QtSql/QSqlDatabase>
#include<QtSql/QSqlQuery>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QString txt, txt2, dateW, AE;


QSqlQuery query2;


public slots:
    void on_pushButton_clicked();
    void getSignal(QString str);
    void flagChecked();
    void on_pushButton_2_clicked();
    void checkDate(QDate dataCh);

   signals:
        void archiveData(QString n,QString AE, QString d, QString da);
        void notDoneWork(QString w,QString AE, QString des, QString date);

private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
