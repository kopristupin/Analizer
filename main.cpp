////////////////////////////////////////////////////////////////
//          DEDVELOPED BY PRISTUPIN KONSTANTIN               //
//////////              2020              ////////////////////
///               ALL RIGHTS RESERVED            ////////////
/////////////////////////////////////////////////////////////
#include "mainwindow.h"
#include<QtWidgets>
#include <QApplication>
#include"dialog.h"
#include"archive.h"
#include<QSql>
#include<writeserver.h>
#include <QSharedPointer>
#include<QSettings>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QSettings settings("analizer","an");
    QString server, log,pswrd;
    QString dbname;
    QSharedPointer<WriteServer> wrServ_ptr;
    QSharedPointer<MainWindow> mw_ptr;
    QSqlDatabase sch;
    server= settings.value("server", " ").toString();
    dbname=settings.value("dbname", " ").toString();
    log=settings.value("login"," ").toString();
    pswrd=settings.value("password"," ").toString();
    server= "WIN-J524RTIN700";
    dbname="database";
    if(server==" " || dbname==" " || log==" " || pswrd==" "){
        wrServ_ptr=QSharedPointer<WriteServer>(new WriteServer);
        wrServ_ptr->show();
    }
    else{
        qDebug()<<server<<dbname<<log<<pswrd;
        sch = QSqlDatabase::addDatabase("QODBC");
        sch.setDatabaseName("DRIVER={SQL Server}; SERVER="+server+"; DATABASE="+dbname+";Uid="+log+";Pwd="+pswrd+";");
        //sch.setDatabaseName("DRIVER={SQL Server}; SERVER=WIN-J524RTIN700\\SQLEXPRESS; DATABASE=database; ");// home database

        if(!sch.open())
            qDebug()<<"Database not opened!";

        mw_ptr=QSharedPointer<MainWindow>(new MainWindow);
        mw_ptr->show();

    }
    return a.exec();
}
