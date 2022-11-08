#include "hough.h"

#include <qimage.h>
#include "imageviewer-qt5.h"
#include <cmath>
#include <iostream>

namespace cg2 {

    /**
     * @brief showAccumulatorArray
     *          apply Hough-Transformation and return the accumulator array in four 4 ways:
     *          1. without any changes
     *          2. with threshhold reduction
     *          3. with non maxima suppression
     *          4. with non maxima suppression and threshhold reduction
     * @param image
     *          input image
     * @param angular_steps
     *          angular steps for the first demension of accumulator array
     * @param radial_steps
     *          radial steps for the second demension of accumulator array
     * @param do_bias_compensation
     *          Boolean: if true apply bias compensation
     * @param threshhold_a_min
     *          Hough transformation threshhold parameter in percent
     * @param do_threshhold_reduction
     *          Boolean: if true apply threshold reduction
     * @param do_non_maxima_suppression
     *          Boolean: if true apply non maxima suppression
     * @param canny_sigma
     *          Canny edge detector parameter
     *          sigma for gauss smoothing
     * @param canny_tHi
     *          Canny edge detector parameter
     *          Threshhold tHi
     * @param canny_tLo
     *          Canny edge detector parameter
     *          Threshhold tLo
     * @return
     *          Accumulator array as QImage pointer in dimension [angular_steps * radial_steps]
     */
    QImage* showAccumulatorArray(QImage* image, int angular_steps, int radial_steps, bool do_bias_compensation, double threshhold_a_min,
                                 bool do_threshhold_reduction, bool do_non_maxima_suppression,
                                 double canny_sigma, int canny_tHi, int canny_tLo){
        logFile << "Start Hough-Transformation" << std::endl;
        logFile << "--- Canny parameter:\n---Sigma: " + std::to_string(canny_sigma) + "\n---tHi: " + std::to_string(canny_tHi) + "\n---tLo: " + std::to_string(canny_tLo) << std::endl;

        logFile << "Hough Transformation done | angular steps = " <<  angular_steps << "  |  radial steps  = " << radial_steps << std::endl;
        if(do_threshhold_reduction && do_non_maxima_suppression){
            logFile << "Show accumulator Array with combined evaluation, threshhold: " << threshhold_a_min << std::endl;
        } else if(do_threshhold_reduction) {
            logFile << "Show accumulator Array with threshold evaluation: " << threshhold_a_min << std::endl;
        } else if(do_non_maxima_suppression) {
            logFile << "Show accumulator Array with non-maxima suppression evaluation" << std::endl;
        } else {
            logFile << "Show accumulator Array" << std::endl;
        }
        logFile << "Bias Kompensation " << do_bias_compensation << std::endl;



        return image;
    }

    /**
     * @brief drawHoughLinesInImage
     *            apply Hough-Transformation, draw the line in the input image
     *            and return the this image
     *            with non maxima suppression and threshhold reduction
     * @param image
     *          input image
     * @param angular_steps
     *          angular steps for the first demension of accumulator array
     * @param radial_steps
     *          radial steps for the second demension of accumulator array
     * @param do_bias_compensation
     *          Boolean: if true apply bias compensation
     * @param threshhold_a_min
     *          Hough transformation threshhold parameter in percent
     * @param canny_sigma
     *          Canny edge detector parameter
     *          sigma for gauss smoothing
     * @param canny_tHi
     *          Canny edge detector parameter
     *          Threshhold tHi
     * @param canny_tLo
     *          Canny edge detector parameter
     *          Threshhold tLo
     * @return
     *          input image as QImage pointer with found lines
     */
    QImage* drawHoughLinesInImage(QImage* image, int angular_steps, int radial_steps, bool do_bias_compensation, double threshhold_a_min,
                                  double canny_sigma, int canny_tHi, int canny_tLo){
        logFile << "Start Hough-Transformation" << std::endl;
        logFile << "--- Canny parameter:\n---Sigma: " + std::to_string(canny_sigma) + "\n---tHi: " + std::to_string(canny_tHi) + "\n---tLo: " + std::to_string(canny_tLo) << std::endl;
        logFile << "Hough Transformation done | angular steps = " <<  angular_steps << "  |  radial steps  = " << radial_steps << std::endl;
        logFile << "Bias Kompensation " << do_bias_compensation << std::endl;
        logFile << "Accumulator Array with combined evaluation, threshhold: " << threshhold_a_min << std::endl;

        return image;
    }
}
