#include "filteroperations.h"
#include "imageviewer-qt5.h"
#include "Helper.h"


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

    int sumFilter = 0;
    for (int i=0; i<filter_width; i++) {
        for (int j=0; j<filter_height; j++) {
            sumFilter+=filter[i][j];
        }
    }

    double weight = 1.0/sumFilter;
    int L = (filter_height/2);
    int K = (filter_width/2);
    int imageHeight = image->height();
    int imageWidth = image->width();

    logFile << "Filter read:" << std::endl;

    int border_i, border_j;

    // Zentralbereich
    if (border_treatment == 0) {
        border_i = L;
        border_j = K;
    } else {
        border_i = 0;
        border_j = 0;
    }

    for(int i = border_i; i < image->width() - border_i; i++){
        for(int j = border_j; j < image->height() - border_j; j++){
            QRgb pixel;
            int sumGray = 0;
            int sumCb = 0;
            int sumCr = 0;

            for(int v = -L; v <= L; v++ ){
                for(int u = -K; u <= K; u++ ){
                    int xPos = i+v;
                    int yPos = j+u;
                    if (i+v < 0 || i+v >= imageWidth || j+u < 0 || j+u >= imageHeight) {
                        // zero padding: if index out of bounce then skip and use gray, cb, cr = 0
                        if (border_treatment == 1)
                            continue;
                        // Konstante Randbehandlung
                        else if (border_treatment == 2) {
                            if (i+v < 0)
                                xPos = 0;
                            else if (i+v >= imageWidth)
                                xPos = imageWidth - 1;

                            if (j+u < 0)
                                yPos = 0;
                            if (j+u >= imageHeight)
                                yPos = imageHeight - 1;
                        }
                        // Gespiegelte Randbehandlung
                        else if (border_treatment == 3) {
                            if (i+v < 0)
                                xPos = i - v;
                            else if (i+v >= imageWidth)
                                xPos = i - v;

                            if (j+u < 0)
                                yPos = j - u;
                            if (j+u >= imageHeight)
                                yPos = j - u;
                        }
                    }
                    pixel = copyImage->pixel(xPos, yPos);

                    int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                    int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                    int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                    clamping0_255(gray);
                    clamping_minus128_127(cb);
                    clamping_minus128_127(cr);

                    sumGray = sumGray + gray*filter[v + L][u + K];
                    sumCb = sumCb + cb*filter[v + L][u + K];
                    sumCr = sumCr + cr*filter[v + L][u + K];

                }
            }

            int newGray = (int) round((double)sumGray * weight);
            int newCb = (int) round((double)sumCb * weight);
            int newCr = (int) round((double)sumCr * weight);

            clamping0_255(newGray);
            clamping_minus128_127(newCb);
            clamping_minus128_127(newCr);

            int rot = newGray + 45 * newCr / 32 ;
            int gruen = newGray - (11 * newCb + 23 * newCr) / 32 ;
            int blau = newGray + 113 * newCb / 64 ;

            clamping0_255(rot);
            clamping0_255(gruen);
            clamping0_255(blau);

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


    // create the kernel h
    int center = (int) (3.0 * gauss_sigma);
    int h[2*center+1] = {}; // odd size

    //fill the kernel
    float gauss_sigma2 = gauss_sigma * gauss_sigma;

    int h_len = sizeof(h)/sizeof(float);
    int  h_len_half = h_len/2;


    float scaleFactor = exp(-0.5*(center*center)/gauss_sigma2);

    for (int i = 0; i < h_len; i++) {
        int r = center - i;
        h[i] = (int)(exp(-0.5*(r*r)/gauss_sigma2)/scaleFactor);
    }

    int sumGaussFilter = 0.0;
    for (int i=0; i<h_len; i++) {
        sumGaussFilter+= h[i];
    }
    //  we have to iterate through h and ddetermine the length and set it to weight
    QImage* copyImage =new QImage(*image);



    float weight = 1.0/(sumGaussFilter);

    int imageHeight = image->height();
    int imageWidth = image->width();

    int border_i, border_j;


    // Zentralbereich
    if (border_treatment == 0) {
        border_i = h_len_half;
        border_j = h_len_half;
    } else {
        border_i = 0;
        border_j = 0;
    }

    for(int i = border_i; i < image->width() - border_i; i++){
        for(int j = border_j; j < image->height() - border_j; j++){
            QRgb pixel;
            int sumGray = 0;
            int sumCb = 0;
            int sumCr = 0;

            for(int v = -h_len_half; v <= h_len_half; v++ ){
                int xPos = i + v;
                int yPos = j;
                if (i+v < 0 || i+v >= imageWidth || j < 0 || j >= imageHeight) {
                    // zero padding: if index out of bounce then skip and use gray, cb, cr = 0
                    if (border_treatment == 1)
                        continue;
                    // Konstante Randbehandlung
                    else if (border_treatment == 2) {
                        if (i+v < 0)
                            xPos = 0;
                        else if (i+v >= imageWidth)
                            xPos = imageWidth - 1;

                        if (j < 0)
                            yPos = 0;
                        if (j >= imageHeight)
                            yPos = imageHeight - 1;
                    }
                    // Gespiegelte Randbehandlung
                    else if (border_treatment == 3) {
                        if (i+v < 0)
                            xPos = i - v;
                        else if (i+v >= imageWidth)
                            xPos = i - v;

                        if (j < 0)
                            yPos = j;
                        if (j >= imageHeight)
                            yPos = j;
                    }
                }
                pixel = copyImage->pixel(xPos, yPos);

                int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                clamping0_255(gray);
                clamping_minus128_127(cb);
                clamping_minus128_127(cr);

                sumGray = sumGray + gray*h[v + h_len_half];
                sumCb = sumCb + cb*h[v + h_len_half];
                sumCr = sumCr + cr*h[v + h_len_half];
            }
            int newGray = (int) round((double)sumGray * weight);
            int newCb = (int) round((double)sumCb * weight);
            int newCr = (int) round((double)sumCr * weight);

            clamping0_255(newGray);
            clamping_minus128_127(newCb);
            clamping_minus128_127(newCr);

            int rot = newGray + 45 * (double)newCr / 32 ;
            int gruen = newGray - (double)(11 * (double)newCb + 23 * (double)newCr) / 32 ;
            int blau = (double)newGray + 113 * (double)newCb / 64 ;

            clamping0_255(rot);
            clamping0_255(gruen);
            clamping0_255(blau);

            image->setPixel(i, j, qRgb(newGray,newGray,newGray));

            sumGray = 0;
            sumCb = 0;
            sumCr = 0;

            for(int u = -h_len_half; u <= h_len_half; u++ ){
                int xPos = i;
                int yPos = j + u;
                if (i < 0 || i >= imageWidth || j+u < 0 || j+u >= imageHeight) {
                    // zero padding: if index out of bounce then skip and use gray, cb, cr = 0
                    if (border_treatment == 1)
                        continue;
                    // Konstante Randbehandlung
                    else if (border_treatment == 2) {
                        if (i < 0)
                            xPos = 0;
                        else if (i >= imageWidth)
                            xPos = imageWidth - 1;

                        if (j+u < 0)
                            yPos = 0;
                        if (j+u >= imageHeight)
                            yPos = imageHeight - 1;
                    }
                    // Gespiegelte Randbehandlung
                    else if (border_treatment == 3) {
                        if (i < 0)
                            xPos = i;
                        else if (i >= imageWidth)
                            xPos = i;

                        if (j+u < 0)
                            yPos = j - u;
                        if (j+u >= imageHeight)
                            yPos = j - u;
                    }
                }
                pixel = copyImage->pixel(xPos, yPos);

                int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                clamping0_255(gray);
                clamping_minus128_127(cb);
                clamping_minus128_127(cr);

                sumGray = sumGray + gray*h[u + h_len_half];
                sumCb = sumCb + cb*h[u + h_len_half];
                sumCr = sumCr + cr*h[u + h_len_half];
            }
            newGray = (int) round((double)sumGray * weight);
            newCb = (int) round((double)sumCb * weight);
            newCr = (int) round((double)sumCr * weight);

            clamping0_255(newGray);
            clamping_minus128_127(newCb);
            clamping_minus128_127(newCr);

            rot = newGray + 45 * (double)newCr / 32 ;
            gruen = newGray - (double)(11 * (double)newCb + 23 * (double)newCr) / 32 ;
            blau = (double)newGray + 113 * (double)newCb / 64 ;

            clamping0_255(rot);
            clamping0_255(gruen);
            clamping0_255(blau);

            image->setPixel(i, j, qRgb(rot,gruen,blau));
        }
    }

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
    return image;;
}
}

