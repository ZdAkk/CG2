#ifndef FOURIERLABEL_H
#define FOURIERLABEL_H

#include <qlabel.h>



class FourierLabel: public QLabel
{
   Q_OBJECT

signals:
   void posChanged(QMouseEvent *event);

public:
   FourierLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);

protected:
   virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif // FOURIERLABEL_H


