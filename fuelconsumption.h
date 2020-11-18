#ifndef FUELCONSUMPTION_H
#define FUELCONSUMPTION_H

#include <QWidget>
#include<QSqlQuery>
#include<QMessageBox>
#include<QtCharts>
#include<QDateEdit>

namespace Ui {
class FuelConsumption;
}

class FuelConsumption : public QWidget
{
    Q_OBJECT

public:
    explicit FuelConsumption();
    ~FuelConsumption();


    QSqlQuery query;
    int dailyC, SFOCc;
    QChartView* chView =new QChartView;
        QChart* diagram= new QChart;
    QValueAxis* axisY= new QValueAxis;
 QDateTimeAxis* axisX= new QDateTimeAxis;
    QValueAxis* axisLoad= new QValueAxis;
   QLineSeries* SFOCseries= new QLineSeries;
     QDateEdit* max=new QDateEdit;
     QDateEdit* min=new QDateEdit;
QString nameOfVar;
    QWidget wgt;

int tickCount;

signals:
void showSFOCDiagram(QString);
     void showDailyConsDiagram(QString);

public slots:
    void enterFuelReadings();
    void diagramClicked();
    void SFOCdateChanged();
    void showPatricDiagram(QString);

private slots:
    void on_SFOC1date_dateChanged(const QDate &date);

    void on_dailyC1_dateChanged(const QDate &date);

   // void on_pushButton_2_clicked();
    void test(QDate min);
    void maxDateChanged(QDate date);

    void on_diagramBt_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FuelConsumption *ui;
};

#endif // FUELCONSUMPTION_H
