#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QMainWindow>


#include<QtWidgets>
#include <QApplication>
#include<QLabel>


    class customLabel : public QLabel
    {
        Q_OBJECT
    public:
        explicit customLabel(QWidget *parent = nullptr);

protected:
    void mouseMoveEvent(QMouseEvent *ev) override;
   void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* ev) override;
    void mousePressEvent(QMouseEvent *ev) override;

QLabel lbl;
int anchorY=0;

    signals:
    void labelClicked();
};

#endif // CUSTOMLABEL_H
