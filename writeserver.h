#ifndef WRITESERVER_H
#define WRITESERVER_H
#include "mainwindow.h"
#include<QtWidgets>
#include <QDialog>
#include<QSharedPointer>
#include<QSettings>
namespace Ui {
class WriteServer;
}

class WriteServer : public QDialog
{
    Q_OBJECT

public:
    explicit WriteServer(QWidget *parent = nullptr);
    ~WriteServer();
    QString serv, db, log, pswrd;
private slots:
    void on_pushButton_clicked();

private:
    Ui::WriteServer *ui;
    QSharedPointer <MainWindow> mw_ptr;
    QSharedPointer <QSqlDatabase> sql_ptr;
     QSharedPointer <QMessageBox> bx= QSharedPointer<QMessageBox>( new QMessageBox(QMessageBox::Warning, "Warning!", "Incorrect server-database"));

};

#endif // WRITESERVER_H
