#include "fourier.h"

#include <qimage.h>
#include "imageviewer-qt5.h"
#include <cmath>

namespace cg2 {

    /**
     * @brief doFT
     *          calculate the fourier transformation with an 2D image as input and
     *          returns the visualization of the fourier coefficients as an image
     *          Note:
     *              greyscale only
     *              store the complex values, they are needed for the inverse
     *              fourier transformation
     * @param image
     *          greyscale reference on the input image
     * @return  fourier coefficients (Leistungsspektrun) as image pointer
     */
    QImage* doFT(QImage* image){

        logFile << "fourier transformation done" << std::endl;
        return image;
    }

    /**
     * @brief doIFT
     *          calculate the inverse fourier transformation with an 2D filter-image ()
     *          as input and returns the resulting 2D image
     *          Note:
     *              Use the strored complex values from doFT(...)
     * @param image
     *          reference on the Fourier coefficient filter image
     * @return  new image to show in the GUI
     */
    QImage* doIFT(QImage* image){

    logFile << "inverse fourier transformation done" << std::endl;
    return image;
    }

}
