#include "fuelconsumption.h"
#include "ui_fuelconsumption.h"
#include<QDebug>


FuelConsumption::FuelConsumption() :

    ui(new Ui::FuelConsumption)
{

    ui->setupUi(this);

    ui->readingDate->setDate(QDate::currentDate());

    query.exec("SELECT SFOC, dailyCons FROM fuelConsumption WHERE date= (SELECT MAX(date) FROM fuelConsumption)");
    query.next();
    ui->SFOC1label->setText(query.value(0).toString());
    ui->dailyClbl->setText(query.value(1).toString());

    ui->SFOC1date->setDate(QDate::currentDate());
    ui->dailyC1->setDate(QDate::currentDate());





    //connect(ui->SFOC1date, SIGNAL(dateChanged(const QDate &date)), this, SLOT(SFOCdateChanged()));



    query.exec("SELECT MAX(date) FROM fuelConsumption");
    query.next();

    max->setDate(query.value(0).toDate());
    min->setDate(query.value(0).toDate().addMonths(-1));

qDebug()<< "FUEL CONS "<< query.value(0).toDateTime();
    axisX-> setFormat("dd/MM");
    axisX->setMax(query.value(0).toDateTime());
    axisX->setMin(query.value(0).toDateTime().addMonths(-1));
   // axisX->setTickCount(query.value(0).toDateTime().addMonths(-1).daysTo(query.value(0).toDateTime())+1);
    axisX->setTitleText("Date");
    diagram->addAxis(axisX, Qt::AlignBottom);


    chView->setRenderHint(QPainter::Antialiasing);
    chView->setChart(diagram);
    QVBoxLayout* vlyt= new QVBoxLayout;
    QHBoxLayout* hlyt= new QHBoxLayout;


    hlyt->addWidget(min);
    hlyt->addSpacing(650);
    hlyt->addWidget(max);
    vlyt->addWidget(chView);
    vlyt->addLayout(hlyt);
    wgt.setLayout(vlyt);
    wgt.resize(1300, 370);

    connect(ui->enterBt, SIGNAL(clicked()), this, SLOT(enterFuelReadings()));
    // connect(ui->diagramBt, SIGNAL(clicked()), this, SLOT(diagramClicked()));
    connect( min, &QDateEdit::dateChanged, this, &FuelConsumption::test);
    connect(max, &QDateEdit::dateChanged, this, &FuelConsumption::maxDateChanged);
    connect( this, &FuelConsumption::showSFOCDiagram, &FuelConsumption::showPatricDiagram);
    connect( this, &FuelConsumption::showDailyConsDiagram, &FuelConsumption::showPatricDiagram);

}

FuelConsumption::~FuelConsumption()
{
    delete ui;
}


void FuelConsumption::enterFuelReadings(){
    QSqlQuery query;
    query.exec("SELECT counter FROM fuelConsumption WHERE date= (SELECT MAX(date) FROM fuelConsumption)");
    query.next();
    int lastCounter=query.value(0).toInt();
    int dailyCons= (ui->lineEditRead->text().toInt())- lastCounter;

    query.exec("SELECT load FROM Temperatures WHERE date='"+ QDate::currentDate().toString("yyyy-MM-dd") +"' ");
    query.next();

    if(query.value(0).toInt()==0){
        QMessageBox::warning(this,"Warning", "Load was not entried! \n To calculate SFOC enter Load");
    }
    else{
        float  SFOC= dailyCons*1000/24/query.value(0).toInt();
        ui->SFOC1label->setText(QString::number(SFOC));
        ui->dailyClbl->setText(QString::number(dailyCons));
        query.exec("INSERT INTO fuelConsumption VALUES('"+ ui->readingDate->date().toString("dd-MM-yyyy") +"', "+ QString::number(ui->lineEditRead->text().toInt())+","+ QString::number(SFOC)+ ","+
                   ""+ QString::number(dailyCons)+")");
    }
}

void FuelConsumption::SFOCdateChanged(){

}

//void FuelConsumption::showDiagram(QString str)

void FuelConsumption::diagramClicked()
{
   // emit showSFOCDiagram("SFOC");
}

void FuelConsumption::showPatricDiagram(QString str){
qDebug()<<"TESSSSSSSSSSSSSSSST";
    nameOfVar.clear();
    QSqlQuery query;
    if(str=="dailyCons"){
         axisY->setRange(2500, 4000);
         axisY->setTitleText("Daily consumption");
    }

    else{
        axisY->setRange(190, 250);
    axisY->setTitleText(str);
    }
    diagram->removeSeries(SFOCseries);
    SFOCseries->clear();
    diagram->addAxis(axisY, Qt::AlignLeft);
    query.exec("SELECT date,"+ str +"  FROM fuelConsumption WHERE date>= DATEADD( month, -1,  (SELECT MAX(date) FROM fuelConsumption)) and date < (SELECT MAX(date) FROM fuelConsumption) ");
    int i=0;

    while(query.next()){
        QPoint p(query.value(0).toDateTime().toMSecsSinceEpoch(), query.value(1).toInt());
        qDebug()<<p;
        SFOCseries->append(p);
        i++;
    }
    axisX->setTickCount(i);
    diagram->addSeries(SFOCseries);
    SFOCseries->attachAxis(axisY);
    qDebug()<< SFOCseries;
    wgt.show();
    nameOfVar= str;
}

void FuelConsumption::on_SFOC1date_dateChanged(const QDate &date)
{
    QSqlQuery query;
    query.exec("SELECT SFOC FROM fuelConsumption WHERE date='"+ ui->SFOC1date->date().toString("yyyy-MM-dd") +"'");
    query.next();
    ui->SFOC1label->setText(query.value(0).toString());
}


void FuelConsumption::on_dailyC1_dateChanged(const QDate &date)
{
    QSqlQuery query;
    query.exec("SELECT dailyCons FROM fuelConsumption WHERE date='"+ ui->dailyC1->date().toString("yyyy-MM-dd") +"'");
    query.next();
    ui->dailyClbl->setText(query.value(0).toString());
}



void FuelConsumption::maxDateChanged(QDate date){
    tickCount=0;
    QDateTime d(date);
    QSqlQuery query;
    diagram->removeSeries(SFOCseries);
    bool needToChangeAxis;
    if(axisX->max().toMSecsSinceEpoch() > d.toMSecsSinceEpoch()){  //remove extra points


        SFOCseries->clear();
        query.exec("SELECT date, "+nameOfVar+" FROM fuelConsumption WHERE date>='"+  axisX->min().toString("yyyy-MM-dd")  +"' and date<='"+ date.toString("yyyy-MM-dd") +"'");
        while(query.next()){
            tickCount++;
            QPoint p(query.value(0).toDateTime().toSecsSinceEpoch(), query.value(1).toInt());
            SFOCseries->append(p);

            needToChangeAxis=1;

        }

    }

    else{   // add extra points


        SFOCseries->clear();
        query.exec("SELECT date, "+nameOfVar+" FROM fuelConsumption WHERE date>='"+  axisX->min().toString("yyyy-MM-dd")  +"' and date<='"+ date.toString("yyyy-MM-dd") +"'");
        while(query.next()){


            tickCount++;


            QPoint p(query.value(0).toDateTime().toSecsSinceEpoch(), query.value(1).toInt());
            SFOCseries->append(p);
        }
        needToChangeAxis=1;
        //  }

    }

    if(needToChangeAxis){
        axisX->setMax(axisX->min().addDays(tickCount));
        axisX->setTickCount(tickCount);
        // axisX->setTickCount(abs(date.daysTo(axisX->min().date()))+1);
    }
    diagram->addSeries(SFOCseries);
    SFOCseries->attachAxis(axisY);



}



void FuelConsumption::test(QDate date){
    tickCount=0;
    QDateTime d(date);
    QSqlQuery query;
    diagram->removeSeries(SFOCseries);
    bool needToChangeAxis;
    if(axisX->min().toMSecsSinceEpoch() < d.toMSecsSinceEpoch()){  //remove extra points


        SFOCseries->clear();
        query.exec("SELECT date, "+nameOfVar+" FROM fuelConsumption WHERE date>='"+  date.toString("yyyy-MM-dd")  +"' and date<='"+ axisX->max().date().toString("yyyy-MM-dd") +"'");
        while(query.next()){
            tickCount++;
            QPoint p(query.value(0).toDateTime().toSecsSinceEpoch(), query.value(1).toInt());
            SFOCseries->append(p);
        }
        needToChangeAxis=1;

    }

    else{   // add extra points



        SFOCseries->clear();
        query.exec("SELECT date,"+nameOfVar+" FROM fuelConsumption WHERE date>='"+  date.toString("yyyy-MM-dd")  +"' and date<='"+ axisX->max().date().toString("yyyy-MM-dd") +"'");
        int y=0;
query.next();
        while(query.next()){
            tickCount++;

            QPoint p(query.value(0).toDateTime().toSecsSinceEpoch(), query.value(1).toInt());
            SFOCseries->append(p);
            y++;
        }
        needToChangeAxis=1;
    }



    if(needToChangeAxis){
        axisX->setMin(axisX->max().addDays(-tickCount));
        axisX->setTickCount(tickCount);
    }
    diagram->addSeries(SFOCseries);
    SFOCseries->attachAxis(axisY);


}

void FuelConsumption::on_diagramBt_clicked()
{
    emit showSFOCDiagram("SFOC");
}


void FuelConsumption::on_pushButton_2_clicked(){
     emit showDailyConsDiagram("dailyCons");
}
