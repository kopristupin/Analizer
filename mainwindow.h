#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QObject>
#include"dialog.h"
#include"archive.h"
#include"chart.h"
#include"notdoneworksc.h"

#include<QTime>
#include<QTimer>
#include<archive.h>
#include<QPainter>
#include<QSql>
#include <order.h>
#include<checking.h>
#include<chart.h>
#include<QMessageBox>
#include <QPixmap>
#include<QLabel>
#include<QPushButton>
#include <QApplication>
#include<makeentry.h>

#include<QIODevice>
#include<QFile>
#include<customlabel.h>
#include<listofparts.h>
#include <QSharedPointer>
#include<labeltochangetext.h>
#include<fuelconsumption.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    labelToChangeText* lbltxt= new labelToChangeText("oil replacement");
    labelToChangeText* lblOverh= new labelToChangeText("overhaul");
    labelToChangeText* lblOverhTurb= new labelToChangeText("turbine overhaul");
    customLabel* cLbl= new customLabel;
    customLabel* pr= new customLabel;
    customLabel* tem= new customLabel;
    customLabel* newOr= new customLabel;
    customLabel* order= new customLabel;
    customLabel* makeEnt= new customLabel;
    customLabel* sched= new customLabel;
    customLabel* journalEv= new customLabel;
    customLabel* listP= new customLabel;
    customLabel* fuelConsumption= new customLabel;


     QSharedPointer<Dialog> dial_ptr= QSharedPointer<Dialog>(new Dialog);
     QSharedPointer<Archive> archives_ptr= QSharedPointer<Archive>(new Archive("Archive"));


   QSharedPointer<chart> chart_ptr= QSharedPointer<chart>(new chart("Temperatures"));
    QSharedPointer<chart> chartPr_ptr= QSharedPointer<chart>(new chart("Pressures"));

   // chart* chart_ptr= new chart("Temperatures");
  //  chart* chartPr_ptr=new chart("Pressures");

 QSharedPointer<Order> ord=QSharedPointer<Order>(new Order());





    void showLastTemps(QString tanleNameT);
    notDoneWorksC* NDWEntry= new notDoneWorksC;
    QWidget* wgt= new QWidget;
     QSharedPointer<FuelConsumption> fuel_ptr;

public slots:
    void listClicked();
    void on_pushButton_3_clicked();
    void on_archieve_clicked();
    void on_gr1_clicked();
    void UpdateTime();



signals:
   void dateChanged(QDate);


private slots:
   void on_NDWorksB_clicked();
   void fuelConsClicked();
   void changeIconNDW();
   void on_pushButton_clicked();
   void on_save_clicked();
   void on_wipe_clicked();
   void on_showOrder_clicked();
   void on_Pressures_clicked();
   void on_addOrder_clicked();
   void on_tabWidget_tabBarClicked(int index);



private:
    Ui::MainWindow *ui;
    QTimer* timer;
};
#endif // MAINWINDOW_H
