#include "edgefilter.h"
#include "imageviewer-qt5.h"
#include <cmath>
#include<iostream>
#include "Helper.h"


namespace cg2 {

/**
     * @brief doEdgeFilter
     *      calculate edge filter like sobel or prewitt with the help of separability.
     *      returns either the X, the Y or the entire Gradient.
     * @param image
     *      input image
     * @param derivative_filter
     *      1x3 1D filter array for derivative part
     * @param smoothing_filter
     *      1x3 1D filter array for the smoothing part
     * @param desired_image
     *      code for the desired image, that has to be shown:
     *      - desired_image = 1 -> show only X Gradient
     *      - desired_image = 2 -> show only Y Gradient
     *      - desired_image = 0 -> show Gradient: |∇I|
     * @return new Image to show in GUI
     */
QImage* doEdgeFilter(QImage * image, int*& derivative_filter, int*& smoothing_filter, int desired_image){

    QImage* temp =new QImage(*image);
    QImage* xCopy =new QImage(*image);
    QImage* yCopy =new QImage(*image);

    int sum = 0;
    // +1 because sizeof() is broken
    for (int i=0; i<(sizeof(derivative_filter)/sizeof(int))+1; i++) {
        sum+= abs(derivative_filter[i]);
    }
    float weight_derivative_filter = 1.0/(sum);

    sum = 0;
    // +1 because sizeof() is broken
    for (int j=0; j<(sizeof(smoothing_filter)/sizeof(int))+1; j++) {
        sum+= abs(smoothing_filter[j]);
    }
    float weight_smoothing_filter = 1.0/(sum);

    int border_i, border_j;

    // because  derivative and smothing filter have same length, we dont have to store another variable with smoothing filter half filter length
    int derivative_len_half  = sizeof(derivative_filter)/(sizeof(int)*2);
    // Zentralbereich
    border_i = derivative_len_half;
    border_j = derivative_len_half;

    QRgb pixel;
    int sumGray = 0;
    int sumCb = 0;
    int sumCr = 0;

    int gray = 0;
    int cb = 0;
    int cr = 0;

    int newGray = 0;
    int newCb = 0;
    int newCr = 0;

    int rot = 0;
    int gruen = 0;
    int blau = 0;

    for(int i = border_i; i < image->width() - border_i; i++){
        for(int j = border_j; j < image->height() - border_j; j++){
            // Derivative calculation in x direction
            for(int v = -derivative_len_half; v <= derivative_len_half; v++ ){
                int xPos = i + v;
                int yPos = j;

                pixel = image->pixel(xPos, yPos);

                gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                clamping0_255(gray);
                clamping_minus128_127(cb);
                clamping_minus128_127(cr);

                sumGray = sumGray + gray*derivative_filter[v + derivative_len_half];
                sumCb = sumCb + cb*derivative_filter[v + derivative_len_half];
                sumCr = sumCr + cr*derivative_filter[v + derivative_len_half];
            }

            newGray = (int) round((double)sumGray * weight_derivative_filter);
            newCb = (int) round((double)sumCb * weight_derivative_filter);
            newCr = (int) round((double)sumCr * weight_derivative_filter);

            clamping_minus128_127(newGray);
            clamping_minus128_127(newCb);
            clamping_minus128_127(newCr);

            newGray+=127;

            rot = newGray + 45 * (double)newCr / 32 ;
            gruen = newGray - (double)(11 * (double)newCb + 23 * (double)newCr) / 32 ;
            blau = newGray + 113 * (double)newCb / 64 ;

            clamping0_255(rot);
            clamping0_255(gruen);
            clamping0_255(blau);

            temp->setPixel(i, j, qRgb(rot,gruen,blau));
        }
    }
    // Smoothing in y direction
    for(int i = border_i; i < image->width() - border_i; i++){
        for(int j = border_j; j < image->height() - border_j; j++){
            sumGray = 0;
            sumCb = 0;
            sumCr = 0;

            for(int u = -derivative_len_half; u <= derivative_len_half; u++ ){
                int xPos = i;
                int yPos = j + u;

                pixel = temp->pixel(xPos, yPos);

                int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                clamping0_255(gray);
                clamping_minus128_127(cb);
                clamping_minus128_127(cr);

                sumGray = sumGray + gray*smoothing_filter[u + derivative_len_half];
                sumCb = sumCb + cb*smoothing_filter[u + derivative_len_half];
                sumCr = sumCr + cr*smoothing_filter[u + derivative_len_half];
            }
            newGray = (int) round((double)sumGray * weight_smoothing_filter);
            newCb = (int) round((double)sumCb * weight_smoothing_filter);
            newCr = (int) round((double)sumCr * weight_smoothing_filter);

            clamping0_255(newGray);
            clamping_minus128_127(newCb);
            clamping_minus128_127(newCr);

            rot = newGray + 45 * (double)newCr / 32 ;
            gruen = newGray - (double)(11 * (double)newCb + 23 * (double)newCr) / 32 ;
            blau = (double)newGray + 113 * (double)newCb / 64 ;

            clamping0_255(rot);
            clamping0_255(gruen);
            clamping0_255(blau);

            xCopy->setPixel(i, j, qRgb(rot,gruen,blau));
        }
    }
    // Smoothing in x direction
    for(int i = border_i; i < image->width() - border_i; i++){
        for(int j = border_j; j < image->height() - border_j; j++){

            sumGray = 0;
            sumCb = 0;
            sumCr = 0;

            for(int v = -derivative_len_half; v <= derivative_len_half; v++ ){
                int xPos = i + v;
                int yPos = j;

                pixel = image->pixel(xPos, yPos);

                int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                clamping0_255(gray);
                clamping_minus128_127(cb);
                clamping_minus128_127(cr);

                sumGray = sumGray + gray*smoothing_filter[v + derivative_len_half];
                sumCb = sumCb + cb*smoothing_filter[v + derivative_len_half];
                sumCr = sumCr + cr*smoothing_filter[v + derivative_len_half];
            }
            newGray = (int) round((double)sumGray * weight_smoothing_filter);
            newCb = (int) round((double)sumCb * weight_smoothing_filter);
            newCr = (int) round((double)sumCr * weight_smoothing_filter);

            clamping0_255(newGray);
            clamping_minus128_127(newCb);
            clamping_minus128_127(newCr);

            rot = newGray + 45 * (double)newCr / 32 ;
            gruen = newGray - (double)(11 * (double)newCb + 23 * (double)newCr) / 32 ;
            blau = (double)newGray + 113 * (double)newCb / 64 ;

            clamping0_255(rot);
            clamping0_255(gruen);
            clamping0_255(blau);

            temp->setPixel(i, j, qRgb(rot,gruen,blau));
        }
    }
    // Derivative calculation in y direction
    for(int i = border_i; i < image->width() - border_i; i++){
        for(int j = border_j; j < image->height() - border_j; j++){

            sumGray = 0;
            sumCb = 0;
            sumCr = 0;

            for(int u = -derivative_len_half; u <= derivative_len_half; u++ ){
                int xPos = i;
                int yPos = j + u;

                pixel = temp->pixel(xPos, yPos);

                int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
                int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
                int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

                clamping0_255(gray);
                clamping_minus128_127(cb);
                clamping_minus128_127(cr);

                sumGray = sumGray + gray*derivative_filter[u + derivative_len_half];
                sumCb = sumCb + cb*derivative_filter[u + derivative_len_half];
                sumCr = sumCr + cr*derivative_filter[u + derivative_len_half];
            }
            newGray = (int) round((double)sumGray * weight_derivative_filter);
            newCb = (int) round((double)sumCb * weight_derivative_filter);
            newCr = (int) round((double)sumCr * weight_derivative_filter);

            clamping_minus128_127(newGray);
            clamping_minus128_127(newCb);
            clamping_minus128_127(newCr);

            newGray+=127;

            rot = newGray + 45 * (double)newCr / 32 ;
            gruen = newGray - (double)(11 * (double)newCb + 23 * (double)newCr) / 32 ;
            blau = (double)newGray + 113 * (double)newCb / 64 ;

            clamping0_255(rot);
            clamping0_255(gruen);
            clamping0_255(blau);

            yCopy->setPixel(i, j, qRgb(rot,gruen,blau));
        }
    }

    //                for(int i = border_i; i < image->width() - border_i; i++){
    //                    for(int j = border_j; j < image->height() - border_j; j++){
    //                        QRgb pixel = image->pixel(i, j);
    //                        copyImageY->setPixel(i, j, pixel);
    //                    }
    //                }

    //                for(int i = border_i; i < image->width() - border_i; i++){
    //                    for(int j = border_j; j < image->height() - border_j; j++){
    //                        QRgb pixel = copyImage->pixel(i, j);
    //                        copyImageX->setPixel(i, j, pixel);
    //                    }
    //                }



    // here is the problem, how exactly do I apply the norm to the pixels in the picture?
    for(int i = border_i; i < image->width() - border_i; i++){
        for(int j = border_j; j < image->height() - border_j; j++){
            QRgb xDerivativePixel = xCopy->pixel(i, j);
            QRgb yDerivativePixel = yCopy->pixel(i, j);
            int grayX = 0.299*qRed(xDerivativePixel) + 0.587*qGreen(xDerivativePixel) + 0.114*qBlue(xDerivativePixel);
            int grayY = 0.299*qRed(yDerivativePixel) + 0.587*qGreen(yDerivativePixel) + 0.114*qBlue(yDerivativePixel);

            int norm = sqrt(pow(grayX,  2) + pow(grayY, 2));
            clamping0_255(norm);
            image->setPixel(i, j, qRgb(norm, norm, norm));
        }
    }
    delete xCopy;
    delete yCopy;
    delete temp;
    logFile << "EdgeFilter applied:" << std::endl;
    logFile << "---derivative_filter: " << derivative_filter[0] << "|"<< derivative_filter[1] << "|" << derivative_filter[2]  << std::endl;
    logFile << "---smoothing_filter: " << smoothing_filter[0] << "|"<< smoothing_filter[1] << "|" << smoothing_filter[2]  << std::endl;
    logFile << "---desired_image: " << desired_image << std::endl;
    return image;

}


/**
     * @brief doLaplaceFilter
     *      calculate the laplace edge filter
     * @param image
     *      input image
     * @param laplace_filter
     *      3x3 2D laplace filter matrix
     * @return new Image to show in GUI
     */
QImage* doLaplaceFilter(QImage * image, int**& laplace_filter){


    logFile << "Do Laplace: " << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            logFile <<  + laplace_filter[i][j] << " ";
        }
        logFile << std::endl;
    }
    return image;
}

/**
     * @brief doCanny
     *      calculate the Canny Edge Detector
     * @param img
     *      input image
     * @param sigma
     *      Canny Edge Detector parameter
     *      sigma for gauss smoothing
     * @param tHi
     *      Canny Edge Detector parameter
     *      Threshhold tHi
     * @param tLo
     *      Canny Edge Detector parameter
     *      Threshhold tLo
     * @return new Image to show in GUI
     */
QImage* doCanny(QImage * img, double sigma, int tHi, int tLo){
    logFile << "-----------\nBeginne Canny Algorithmus:\nSigma: " + std::to_string(sigma) + "\ntHi: " + std::to_string(tHi) + "\ntLo: " + std::to_string(tLo) << std::endl;

    return img;

}


/**
     * @brief doUSM
     *      calculate the Unsharp Masking
     * @param image
     *      input image
     * @param sharpening_value
     *      Unsharp Masking parameter
     *      sharpening parameter (a)
     * @param sigma
     *      Unsharp Masking parameter
     *      sigma for gauss smoothing
     * @param tc
     *      Unsharp Masking parameter
     *      |∇I| must greater then threshhold tc
     * @return new Image to show in GUI
     */
QImage* doUSM(QImage * image, double sharpening_value, double sigma, int tc){

    logFile << "Unsharp Masking ausgeführt mit Schärfungsgrad " << sharpening_value << ", Sigma " << sigma << " und tc " << tc << std::endl;
    return image;
}


}
