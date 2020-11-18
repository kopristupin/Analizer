#ifndef LISTOFPARTS_H
#define LISTOFPARTS_H

#include <QWidget>
#include<QTreeWidget>
#include<QSpinBox>
#include<QtSql>
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
namespace Ui {
class listOfParts;
}

class listOfParts : public QWidget
{
    Q_OBJECT

public:
    explicit listOfParts(QWidget *parent = nullptr);
    ~listOfParts();
    QTreeWidget* widgetList= new QTreeWidget;
    QTreeWidget* twgt= new QTreeWidget;
    QList<QTreeWidgetItem*> listOfAllParts;
    QList<QTreeWidgetItem*> listOfOrderedParts;
      QVBoxLayout* lyt= new QVBoxLayout;
    QHBoxLayout* searchLay= new QHBoxLayout;
    QLabel* searchL= new QLabel("Search: ");
    QLineEdit* textSearch=new QLineEdit;
    QVector<QSpinBox*> qsbVector;
    QWidget wgt;
    QPushButton* add= new QPushButton("Add to order");
    QPushButton* saveTaken= new QPushButton("Save changes");

 public slots:
    void showResult(QString query);
    void showChanged();
    void saveOrder();


private:
    Ui::listOfParts *ui;
};

#endif // LISTOFPARTS_H
