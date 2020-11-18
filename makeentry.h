
#include <QDialog>
#include<QtSql>
#include<QMessageBox>
#include<QDateTimeEdit>
#include<QHBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QSharedPointer>
#include<QLineEdit>

namespace Ui {
class makeEntry;
}

class makeEntry : public QDialog
{
    Q_OBJECT

public:
    explicit makeEntry(QWidget *parent = nullptr);
    ~makeEntry();
    QSqlDatabase addEntry;
   QDialog* entryTime= new QDialog;
   QDialog* startTime= new QDialog;
    QHBoxLayout* hbx= new QHBoxLayout;
    QLabel* lbl=new QLabel("Time of stop: ");
    QDateTimeEdit* stopTimeEdit= new QDateTimeEdit;// stop
    QDateTimeEdit* startTimeEdit= new QDateTimeEdit;//start
    QHBoxLayout* lytt= new QHBoxLayout;
    QVBoxLayout vlyt;
    QHBoxLayout hlyt;
      QHBoxLayout hlyt1;
    QLabel* lblS= new QLabel("Time of start: ");
    QLineEdit ed1;
    QLineEdit ed2;
    QLineEdit ed3;
    QLineEdit ed4;
    QLineEdit ed5;
    QLineEdit ed6;
    QLabel t1lbl;
    QLabel t2lbl;
    QLabel t3lbl;
    QLabel t4lbl;
    QLabel t5lbl;
    QLabel t6lbl;
    QLabel loaDlbl;
       QLineEdit edPower;
QMessageBox* msBx= new QMessageBox(QMessageBox::Warning, "Warning", "Not all parameters entered");

QSharedPointer<QPushButton> startOkptr;//= QSharedPointer<QPushButton>(new QPushButton("ok"));
QSharedPointer<QPushButton> stopOkptr;//= QSharedPointer<QPushButton>(new QPushButton("ok"));

    void msWrn();
    void addMeas(QString eng);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void workHoursEntry();
    void workHoursEntryStop();
    void update(int index);

private:
    Ui::makeEntry *ui;
};


