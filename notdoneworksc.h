#ifndef NOTDONEWORKSC_H
#define NOTDONEWORKSC_H

#include <QDialog>

namespace Ui {
class notDoneWorksC;
}

class notDoneWorksC : public QDialog
{
    Q_OBJECT

public:
    explicit notDoneWorksC(QWidget *parent = nullptr);
    ~notDoneWorksC();

public slots:
      void notDoneWorkAdd(QString w,QString ae, QString des, QString dat);
      void transfer();

private:
    Ui::notDoneWorksC *ui;
};

#endif // NOTDONEWORKSC_H
