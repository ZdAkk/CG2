#include "examples1.h"
#include <imageviewer-qt5.h>


namespace cg2 {

    /**
     * @brief new_clippedRGB_value: Adds brightness adjust to pixel value. clipping the result to [0,255].
     * @param pixel_value
     * @param brightness_adjust_factor
     * @return result int [0,255]
     */
    constexpr int new_clippedRGB_value(int pixel_value, int brightness_adjust_factor){
        int color = pixel_value + brightness_adjust_factor;
        if(color > 255){
            color = 255;
        }
        else if(color < 0){
            color = 0;
        }
        return color;
    }


    /**
     * @brief exampleAlgorithm Adds brightness adjust on each pixel in the Image
     * @param image: Input Image to work with
     * @param brightness_adjust_factor: the brightness adjust factor, will be added on each pixel
     * @return result image, will be shown in the GUI
     */
    QImage*  exampleAlgorithm(QImage * image, int brightness_adjust_factor)
    {
        // Width and height of the image
        int image_width = image->width();
        int image_height = image->height();

        for(int column = 0 ; column < image_width; column++){
            for(int row = 0  ; row < image_height; row++){
                // Pixel object and pixel getter from image
                QRgb pixel = image->pixel(column, row);
                int rot = new_clippedRGB_value(qRed(pixel), brightness_adjust_factor);
                int gruen = new_clippedRGB_value(qGreen(pixel), brightness_adjust_factor);
                int blau = new_clippedRGB_value(qBlue(pixel), brightness_adjust_factor);

                // pixel setter in image with qRgb
                // note that qRgb values must be in [0,255]
                image->setPixel(column, row, qRgb(rot,gruen,blau));
            }
        }
        logFile << "Example algorithm 1 applied" << std::endl;
        return image;
    }
}
