#ifndef EDGEFILTER_H
#define EDGEFILTER_H

#include <qimage.h>




namespace cg2 {
    QImage* doEdgeFilter(QImage * image, int*& derivative_filter, int*& smoothing_filter, int desired_image);
    QImage* doLaplaceFilter(QImage * image, int**& laplace_filter);
    QImage* doCanny(QImage * img, double sigma, int tHi, int tLo);
    inline bool imageGotChangedFlag = true;
    QImage* doUSM(QImage * image, double sharpening_value, double sigma, int tc);

}

#endif // EDGEFILTER_H
