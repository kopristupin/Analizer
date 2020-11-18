#ifndef LABELTOCHANGETEXT_H
#define LABELTOCHANGETEXT_H

#include <QWidget>
#include <QLabel>
#include<QDateEdit>
#include<QPushButton>
#include<QHBoxLayout>
#include<QSqlQuery>

class labelToChangeText : public QLabel
{


public:
   labelToChangeText(QString str);
   void  mouseDoubleClickEvent( QMouseEvent * e );
    QString nameStr;
   QWidget wgt;
   QDateEdit edit;
   QPushButton bt;
   QHBoxLayout lyt;

private slots:
   void setT();
};

#endif // LABELTOCHANGETEXT_H
