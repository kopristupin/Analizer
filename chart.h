#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include<QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include<QtSql>
#include<QLineSeries>
#include<QPushButton>
#include<QPrinter>


namespace Ui {
class chart;
}

class chart : public QWidget
{
    Q_OBJECT

public:
    explicit chart(QString str);
 //   chart(QString);
    ~chart();

    QString tableName;
    int numberSeries;

    QVector<QString> columnNames;
    QChart* ch= new QChart;
    QChartView *chartView = new QChartView(ch);
    QValueAxis* axisY= new QValueAxis;
    QDateTimeAxis* axisX= new QDateTimeAxis;
    QValueAxis* axisLoad= new QValueAxis;
    QLineSeries *s= new QLineSeries();

    QVector<QLineSeries*> seriesToDraw;
    QVector<QMap<int, int>*> toCalculateDynamicLines;
    QVector<QLineSeries*> dynamicLines;
    QSqlDatabase temp, tem;
    QCheckBox* chBox[8]= {new QCheckBox};
    QList<QPointF> linearRe(QMap<int, int>*, QDate, QDate);

private slots:
    void checkChBox();
    void on_setDateB_clicked();
    void changeDateRange(QDate newMin, QDate newMax);
    void on_pushButton_clicked();



signals:
    void changeRange(QDate m,QDate maxi);

private:
    Ui::chart *ui;
};

#endif // CHART_H
