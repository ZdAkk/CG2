#include "fourierlabel.h"



FourierLabel::FourierLabel(QWidget * parent, Qt::WindowFlags f):
   QLabel(parent, f)
{}

void FourierLabel::mouseMoveEvent(QMouseEvent *event)
{
   // hier wird das event der Label-Klasse aufgerufen, damit die Implementation
   // bzw. die Funktionalität des Labels erhalten bleibt.
   QLabel::mouseMoveEvent(event);

   // in diesem Schritt löse ich das in der Klasse deklarierte Signal "posChanged"
   // mit der aktuellen Position als Parameter aus.
   emit posChanged(event);
}
