#include "pixeloperations.h"
#include "imageviewer-qt5.h"


namespace cg2 {

/**
     * @brief calcImageCharacteristics
     *      calculation of the histogram, average value and variance of the image
     *      no return values, just set the references to the correct values
     * @param image
     *      working image
     * @param histogram_ref
     *      Reference to "inline double* histogramm = new double[256]"
     *      doubles allowed from [0-100]
     *      calculate the histogram and fill the histogramm:
     *      the histogramm[0] is corresponding to the luminance value 0 and so on
     *      NOTE!: the histogram must be scaled (linear or logarithmic) so that the
     *          highest value is 100!
     *      (reason: histogram image is 256x100 pixel)
     * @param variance_ref
     *      calculate and set the variance of the image to the variance_ref
     * @param average_ref
     *      calculate and set the average of the image to the average_ref
     * @param linear_scaling
     *      boolean, if true -> scale the histogram linear
     *               if false -> scale the histogram logarithmic
     */
void calcImageCharacteristics(QImage * image, double*& histogram_ref, int& variance_ref, int& average_ref, const bool linear_scaling){
    variance_ref = 0;
    average_ref = 0;
    int most_common_value_in_histoogram = 0;
    // init histogram list
    for (int i = 0; i < 256; ++i) {
        histogram_ref[i] = 0.0;
    }
    // calc histogram + calc average value
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            int l;
            QRgb pixel = image->pixel(i, j);
            l = round(((0.299 * qRed(pixel)) + (0.587 * qGreen(pixel)) + (0.114 * qBlue(pixel))));
            if (l < 0) l = 0;
            if (l > 255) l = 255;
            histogram_ref[l] = histogram_ref[l] + 1;
            // calc average
            average_ref += l;


        }
    }
    // average / number of pixels
    average_ref = average_ref / (image->width()*image->height());

    // variance calc
    for (int i = 0; i < 256; i++) {
        variance_ref += histogram_ref[i]*(i - average_ref)*(i - average_ref);

        // find max number of pixel for a given brightness in histogram
        if (most_common_value_in_histoogram < histogram_ref[i]) {
            most_common_value_in_histoogram = histogram_ref[i];
        }
    }
    // variance / number of pixels
    variance_ref/= (image->width()*image->height());

    logFile << "--- Max number of pixel for a given brightness: " << most_common_value_in_histoogram << "\n";

    // histrogram scale between 0 and 100
    for (int i = 0; i < 256; i++) {
        histogram_ref[i]= round(histogram_ref[i]*100.0/most_common_value_in_histoogram);
    }
    logFile << "Image characteristics calculated:" << std::endl << "--- Average: " << average_ref << " ; Variance: " << variance_ref << std::endl << "--- Histogram calculated: " << "linear scaling = " << linear_scaling << std::endl;
}

/**
     * @brief changeImageDynamic
     *      calculate an image with the desired resolution (given bit depth -> dynamic value)
     *      and return the image pointer
     * @param image
     *      input image
     * @param newDynamicValue
     *      bit depth value for resolution values from 8 to 1
     * @return new Image to show in GUI
     */
QImage* changeImageDynamic(QImage * image, int newDynamicValue) {
    cg2::freeMemory();
    image = new QImage(*backupImage);
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            QRgb pixel = image->pixel(i, j);

            // Calc YCbCr
            int gray = round(0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel));
            int cb = round(-0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel));
            int cr = round(0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel));

            int numberOfNewGrays = (pow(2, newDynamicValue)) - 1;
            int threshold = round(255/numberOfNewGrays);

            int newGray = (gray + threshold/2)/threshold * threshold;


            if (newGray > 255) {
                newGray = 255;
            }
            if (newGray < 0)  {
                newGray  = 0;
            }

            int rot   =   1.0 * newGray    + 0 * cb    + 1.402 * cr;
            int gruen   =   1.0 * newGray    - 0.344136 * cb - 0.714136 * cr;
            int blau  =   1.0 * newGray    + 1.772 * cb    + 0 * cr;

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
    logFile << "Dynamik des Bildes geändert auf: " + std::to_string(newDynamicValue) + " Bit" << std::endl;
    return image;

}

/**
     * @brief adjustBrightness
     *      Add brightness adjust on each pixel in the Image
     * @param image
     *      Input Image to work with
     * @param brightness_adjust_factor
     *      [-255,255]
     *      the brightness adjust shift, will be added on each pixel
     * @return result image, will be shown in the GUI
     */
QImage* adjustBrightness(QImage * image, int brightness_adjust_factor){
    cg2::freeMemory();
    image = new QImage(*backupImage);

    for(int i=0;i<image->width();i++)
    {
        for(int j=0;j<image->height();j++)
        {
            QRgb pixel = image->pixel(i, j);

            int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
            int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
            int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

            int newGray = gray + brightness_adjust_factor;
            if (newGray > 255) {
                newGray = 255;
            }
            if (newGray < 0) {
                newGray = 0;
            }

            int rot = newGray + 45 * cr / 32 ;
            int gruen = newGray - (11 * cb + 23 * cr) / 32 ;
            int blau = newGray + 113 * cb / 64 ;

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

    logFile << "Brightness adjust applied with factor = " <<brightness_adjust_factor << std::endl;
    return image;

}

/**
     * @brief adjustContrast
     *      calculate an contrast adjustment on each pixel in the Image
     * @param image
     *      Input Image to work with
     * @param contrast_adjust_factor
     *      [0,3]
     *      the contrast adjust factor
     * @return result image, will be shown in the GUI
     */
QImage* adjustContrast(QImage * image, double contrast_adjust_factor){
    cg2::freeMemory();
    image = new QImage(*backupImage);

    double averageGray = 0;

    // calc average value
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            int l;
            QRgb pixel = image->pixel(i, j);
            l = round(((0.299 * qRed(pixel)) + (0.587 * qGreen(pixel)) + (0.114 * qBlue(pixel))));
            if (l < 0) l = 0;
            if (l > 255) l = 255;
            // calc average
            averageGray += l;
        }
    }
    // average / number of pixels
    averageGray = averageGray / (image->width()*image->height());

    for(int i=0;i<image->width();i++)
    {
        for(int j=0;j<image->height();j++)
        {
            QRgb pixel = image->pixel(i, j);

            int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
            int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
            int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

            int movedGray = gray - averageGray;
            movedGray = movedGray *  contrast_adjust_factor;
            int newGray = movedGray+ averageGray;

            if (newGray > 255) {
                newGray = 255;
            }
            if (newGray < 0) {
                newGray = 0;
            }

            int rot = newGray + 45 * cr / 32 ;
            int gruen = newGray - (11 * cb + 23 * cr) / 32 ;
            int blau = newGray + 113 * cb / 64 ;

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
    logFile << "Contrast calculation done with contrast factor: " << contrast_adjust_factor << std::endl;
    return image;
}


/**
    * @brief doRobustAutomaticContrastAdjustment
    *      calculate the robust automatic contrast adjustment algorithm with the image as input
    * @param image
    *      Input Image to work with
    * @param plow
    *      [0%,5%]
    *      brightness saturation
    * @param phigh
    *      [0%,5%]
    *      dark saturation
    * @return result image, will be shown in the GUI
    */
QImage* doRobustAutomaticContrastAdjustment(QImage * image, double plow, double phigh){
    cg2::freeMemory();
    image = new QImage(*backupImage);

    //absolutes Histogramm erstellen
    int histogram[256];
    //initialisieren des Histogramms
    for(int i=0; i<256; i++){
        histogram[i] = 0;
    }
    //berechnen der Histogrammwerte
    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            int l;
            QRgb pixel = image->pixel(i, j);
            l = round(((0.299 * qRed(pixel)) + (0.587 * qGreen(pixel)) + (0.114 * qBlue(pixel))));
            if (l < 0) l = 0;
            if (l > 255) l = 255;
            histogram[l] = histogram[l] + 1;

        }
    }

    //kumuliertes Histogramm berechnen --> absolutes Histogramm wird in kumuliertes umgewandelt
    for(int i=1; i<256; i++){
        histogram[i] += histogram[i-1];
    }

    //eigentliche Kontrastberechnung
    int pixelAnzahl = image->width()*image->height();
    int i = 0;
    while(!(histogram[i] >= (int)(pixelAnzahl*plow))){
        i++;
    }
    int aslow = i;  //aslow ist a'low (untere Grenze der Helligkeiten, die auf 0 gemappt wird)

    i = 255;
    while(!(histogram[i] <= (int)(pixelAnzahl * ( 1 - phigh )))){
        i--;
    }
    int ashigh = i;  //ashigh ist a'high (obere Grenze der Helligkeiten, die auf 255 gemappt wird)


    double scaleFactor = 255.0/(ashigh-aslow);
    for(int i=0;i<image->width();i++){
        for(int j=0;j<image->height();j++){

            QRgb pixel = image->pixel(i, j);

            int gray = 0.299*qRed(pixel) + 0.587*qGreen(pixel) + 0.114*qBlue(pixel);
            int cb = -0.169*qRed(pixel) + -0.331*qGreen(pixel) + 0.5*qBlue(pixel);
            int cr = 0.5*qRed(pixel) + -0.419*qGreen(pixel) - 0.08*qBlue(pixel);

            int rot;
            int gruen;
            int blau;

            if(gray <= aslow){
                rot = 0 + 45 * cr / 32 ;
                gruen = 0 - (11 * cb + 23 * cr) / 32 ;
                blau = 0 + 113 * cb / 64 ;
            } else if(gray >= ashigh){
                rot = 255 + 45 * cr / 32 ;
                gruen = 255 - (11 * cb + 23 * cr) / 32 ;
                blau = 255 + 113 * cb / 64 ;
            } else {
                int newGray = (gray  - aslow) * scaleFactor + 0.0;
                rot = newGray + 45 * cr / 32 ;
                gruen = newGray - (11 * cb + 23 * cr) / 32 ;
                blau = newGray + 113 * cb / 64;
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

    logFile << "Robust automatic contrast adjustment applied with:"<< std::endl << "---plow = " << (plow*100) <<"%" << std::endl << "---phigh = " << (phigh*100)<<"%" << std::endl;

    return image;
}

}


