#include "filteroperations.h"
#include "imageviewer-qt5.h"


namespace cg2 {

/**
     * @brief filterImage
     *      calculate the 2D filter over the image
     *      handle border treatment as desired
     * @param image
     *      input image
     * @param filter
     *      filter matrix with filter coefficients
     *      can reach up to 15x15
     * @param filter_width
     *      filter matrix width in range [0,15]
     * @param filter_height
     *      filter matrix height in range [0,15]
     * @param border_treatment
     *      0: Zentralbereich
     *      1: Zero Padding
     *      2: Konstante Randbedingung
     *      3: Gespiegelte Randbedingung
     * @return new Image to show in GUI
     */
QImage* filterImage(QImage * image, int**& filter, int filter_width, int filter_height, int border_treatment) {

    QImage* copyImage =new QImage(*image);

    double weight = 1.0/((filter_width)*(filter_height));
    int L = (filter_height/2);
    int K = (filter_width/2);
    int imageHeight = image->height();
    int imageWidth = image->width();

    logFile << "Filter read:" << std::endl;
    for(int i=L;i<image->width()-L;i++){
        for(int j=K;j<image->height()-K;j++){
            QRgb pixel;
            double sumGray = 0;
            double sumCb = 0;
            double sumCr = 0;

            for(int v = -L; v <= L; v++ ){
                for(int u = -K; u <= K; u++ ){

                if ((i + v < 0) || (i + v > imageWidth)  || (j + u < 0) || (j + u > imageHeight)) {
                    sumCb = sumCb + (-128)*filter[v + L][u + K];
                    sumCr = sumCr + (-128)*filter[v + L][u + K];
                    continue;
                }
                     pixel = copyImage->pixel(i+v, j+u);

                    int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                    int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                    int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                    if (gray > 255) {
                        gray = 255;
                    }
                    if (gray < 0) {
                        gray = 0;
                    }

                    if (cb  < -128) {
                        cb = -128;
                    }

                    if (cb > 127) {
                        cb = 127;
                    }

                    if (cr  < -128) {
                        cr = -128;
                    }

                    if (cr > 127) {
                        cr = 127;
                    }

                    sumGray = sumGray + gray*filter[v + L][u + K];
                    sumCb = sumCb + cb*filter[v + L][u + K];
                    sumCr = sumCr + cr*filter[v + L][u + K];

                }
            }

            int newGray = (int) round((double)sumGray * weight);
            int newCb = (int) round((double)sumCb * weight);
            int newCr = (int) round((double)sumCr * weight);

            if (newGray < 0) {
                newGray = 0;
            }

            if (newGray > 255) {
                newGray = 255;
            }

            if (newCb  < -128) {
                newCb = -128;
            }

            if (newCb > 127) {
                newCb = 127;
            }

            if (newCr  < -128) {
                newCr = -128;
            }

            if (newCr > 127) {
                newCr = 127;
            }

            int rot = newGray + 45 * newCr / 32 ;
            int gruen = newGray - (11 * newCb + 23 * newCr) / 32 ;
            int blau = newGray + 113 * newCb / 64 ;

            if (rot > 255) {
                rot = 255;
            }
            if (rot < 0)  {
                rot  = 0;
            }
            if (gruen > 255) {
                gruen = 255;
            }
            if (gruen < 0)  {
                gruen  = 0;
            }
            if (blau > 255) {
                blau = 255;
            }
            if (blau < 0)  {
                blau  = 0;
            }
            if (rot > 255) {
                rot = 255;
            }
            if (rot < 0)  {
                rot  = 0;
            }
            if (gruen > 255) {
                gruen = 255;
            }
            if (gruen < 0)  {
                gruen  = 0;
            }
            if (blau > 255) {
                blau = 255;
            }
            if (blau < 0)  {
                blau  = 0;
            }

            image->setPixel(i, j, qRgb(rot,gruen,blau));
        }
    }



    logFile << "filter applied:" << std::endl << "---border treatment: ";
    switch (border_treatment) {
    case 0:
        logFile << "Zentralbereich" << std::endl;
        break;
    case 1:
        logFile << "Zero Padding" << std::endl;
        break;
    case 2:
        logFile << "Konstante Randbedingung" << std::endl;
        break;
    case 3:
        logFile << "Gespiegelte Randbedingung" << std::endl;
        break;
    }
    logFile << "---filter width: " << filter_width << std::endl;
    logFile << "---filter height: " << filter_height << std::endl;
    return image;
}

/**
     * @brief filterGauss2D
     *      calculate the 2D Gauss filter algorithm via two separate 1D operations,
     *      handle border treatment as desired
     * @param image
     *      input image
     * @param gauss_sigma
     *      sigma for gauss kernel
     * @param border_treatment
     *      0: Zentralbereich
     *      1: Zero Padding
     *      2: Konstante Randbedingung
     *      3: Gespiegelte Randbedingung
     * @return new Image to show in GUI
     */
QImage* filterGauss2D(QImage * image, double gauss_sigma, int border_treatment){


    logFile << "2D Gauss-Filter angewendet mit σ: " << gauss_sigma;
    logFile <<  " ---border treatment: ";
    switch (border_treatment) {
    case 0:
        logFile << "Zentralbereich" << std::endl;
        break;
    case 1:
        logFile << "Zero Padding" << std::endl;
        break;
    case 2:
        logFile << "Konstante Randbedingung" << std::endl;
        break;
    case 3:
        logFile << "Gespiegelte Randbedingung" << std::endl;
        break;
    }
    return image;
}
}

