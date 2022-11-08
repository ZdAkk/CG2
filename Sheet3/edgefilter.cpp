#include "edgefilter.h"
#include "imageviewer-qt5.h"
#include <cmath>
#include<iostream>



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
