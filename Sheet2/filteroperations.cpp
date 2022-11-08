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

        logFile << "Filter read:" << std::endl;
        for(int i = 0; i < filter_height; i++ ){
            for(int j = 0; j < filter_width; j++ ){
                logFile << filter[i][j];
                if(j < (filter_width-1)){
                    logFile << " | ";
                }
            }
            logFile << std::endl;
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

