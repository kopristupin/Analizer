#include "dialog.h"
#include "ui_dialog.h"
#include<mainwindow.h>
#include<checking.h>
#include<QTreeWidget>
#include<QDebug>
#include <QFile>
#include<QFlags>
#include<QObject>
#include<QDialog>
#include<QDate>
#include<QtSql/QSqlRecord>
#include<QtSql/QSqlRelationalTableModel>
//#include<QHeaderView>



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);



    ui->treeWidget->setColumnWidth(1,60);
ui->treeWidget-> setColumnWidth(0, 170);
ui->treeWidget->setColumnWidth(2, 240);

    QSqlQuery query;



    QVector<QString>resultNames;
    QVector<QString> resultAE;
    QVector<QString> resultDescrs;
    QVector<QVariant> resultDates;
    if(!query.exec("SELECT * FROM dataV;")){
        qDebug()<<"ERROR";
    }

     while(query.next()){
         resultNames.push_back(query.value(0).toString());
         resultAE.push_back(query.value(3).toString());
         resultDescrs.push_back(query.value(1).toString());
         resultDates.push_back(query.value(2));


     }

   QVector<QString>::iterator itName= resultNames.begin();
   QVector<QString>::iterator itAE= resultAE.begin();
   QVector<QString>::iterator itDescr= resultDescrs.begin();
   QVector<QVariant>::iterator itDate= resultDates.begin();

    for(; itName<resultNames.end(); itName++,itAE++, itDescr++, itDate++){
        QTreeWidgetItem* item= new QTreeWidgetItem;
        item->setText(0, *itName);
        item->setText(1, *itAE);
        item->setTextAlignment(1, Qt::AlignCenter);
        item->setText(2, *itDescr);
        item->setText(3, itDate->toDate().toString("yyyy-MM-dd"));
        ui->treeWidget->addTopLevelItem(item);
    }

    ui->treeWidget->setSelectionMode(QAbstractItemView::MultiSelection);
}

Dialog::~Dialog( )
{

    delete ui;
}


void Dialog::on_pushButton_clicked()
{
    checking* ob= new checking("Name of work");
    if(ob->exec()==QDialog::Accepted){
        txt= ob->stringFrom();
        AE= ob->AEdate();
        txt2= ob->stringName();
        dateW=ob->strDate().toString("yyyy-MM-dd");
        QTreeWidgetItem* item= new QTreeWidgetItem();
        item->setText(0, txt2);
        item->setText(1, AE);
        item->setText(2, txt);
        item->setText(3, dateW);
        ui->treeWidget->addTopLevelItem(item);

        QString q={"INSERT INTO dataV VALUES('%1','%2', '%3','%4')"};
        QString addQ= q.arg(txt2)
                .arg(AE)
                .arg(txt)
                .arg(dateW);
        QSqlQuery query;
        query.exec(addQ);
    }
}

void Dialog::getSignal(QString str){
    txt=str;

}

void Dialog::flagChecked(){

}



void Dialog::on_pushButton_2_clicked()
{
    QList<QTreeWidgetItem*>items =ui->treeWidget->selectedItems();
    for(int i=0; i<items.size(); i++){
        QString works,AE, descr, date;
        works= items[i]->text(0);
        AE= items[i]->text(1);
        descr= items[i]->text(2);
        date= items[i]->text(3);
        emit archiveData(works,AE, descr, date);

        QSqlQuery query;
        QString qsrt="DELETE FROM dataV WHERE NAME= '"+ items[i]->text(0)  +"';";
        query.exec(qsrt);

        QString qAstr="INSERT INTO Archive(NAME, DESCR, DATE, AE)"
                      "VALUES ('%1', '%2', '%3');";
        QString strAr= qAstr.arg(items[i]->text(0))
                            .arg(items[i]->text(2))
                            .arg(items[i]->text(3))
                            .arg(items[i]->text(1));
        query.exec(strAr);

        delete items[i];
    }
}

void Dialog::checkDate(QDate dataCh){
    QTreeWidgetItemIterator it(ui->treeWidget);
    while (*it) {
        QString dateToCheck=(*it)->text(3);
        dateToCheck.remove('\r');
        dateToCheck.remove('\n');
        QDate dateD= QDate::fromString(dateToCheck, "yyyy-MM-dd");
        if(dateD < dataCh){
            QString works, AEd, descr, date;
            works= (*it)->text(0);
            AEd= (*it)->text(1);
            descr= (*it)->text(2);
            date= (*it)->text(3);
            emit notDoneWork(works, AEd, descr, date);
            delete *it;
        }
        ++it;
    }
}


