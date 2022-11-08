#ifndef FOURIER_H
#define FOURIER_H


#include <qimage.h>
#include <cmath>


#include <complex>
#include <iostream>
#include <valarray>


namespace cg2 {

    QImage* doIFT(QImage* image);
    QImage* doFT(QImage* image);

}

#endif // FOURIER_H
