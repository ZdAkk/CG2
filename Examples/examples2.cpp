#include "examples2.h"
#include "imageviewer-qt5.h"

namespace cg2 {

    /**
     * @brief drawRedCrossAlgorithm Draw a big red cross in the middle of the image
     * @param scale_factor: factor how big the cross should be.
     * @return result image, will be shown in the GUI
     */
    QImage* drawRedCrossAlgorithm(int scale_factor)
    {

        // if you need a new global persistent QImage instance:
        // create new Image, allocate space with 'new'
        // workingImage: global QImage pointer
        // load new image in workingImage from a global backupImage
        // free memory space in cg2::freeMemory()
        workingImage = new QImage(*backupImage);
        int center_width = (int)(workingImage->width()/2)+0.5;
        int cross_width = (int)(workingImage->width()*((double) scale_factor/100));

        int center_height= (int)(workingImage->height()/2)+0.5;
        int cross_height = (int)(workingImage->height()*((double) scale_factor/100));

        for (int y = 0; y<workingImage->height(); y++)
        {
            for(int x = center_width-cross_width/2+0.5; x<center_width+cross_width/2;x++)
            {
                workingImage->setPixel(x,y,qRgb(255,0,0));
            }
        }

        for (int x = 0; x<workingImage->width(); x++)
        {
            for(int y = center_height-cross_height/2+0.5; y<center_height+cross_height/2;y++)
            {
                workingImage->setPixel(x,y,qRgb(255,0,0));
            }
        }

        // How to write in Logfile:
        logFile << " RedCrossAlgorithm applied: " << scale_factor << std::endl;

        return workingImage;
    }

}
