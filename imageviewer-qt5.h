/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QMainWindow>
#ifndef QT_NO_PRINTER
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QPrinter>
#include <QSlider>
#include <qtablewidget.h>

#include <GUI/fourierlabel.h>

#endif

#include "fstream"
#include "Examples/examples1.h"
#include "Examples/examples2.h"
#include "FreeMemory/freememory.h"
#include "Sheet1/pixeloperations.h"
#include "Sheet2/filteroperations.h"
#include "Sheet3/edgefilter.h"
#include "Sheet4/hough.h"
#include "Sheet5/fourier.h"



class QAction;
class QLabel;
class QMenu;
class QScrollArea;
class QScrollBar;
class QTextEdit;
class QVBoxLayout;
class QTabWidget;
class QPushButton;
class QSpinBox;


inline QImage* backupImage;
inline std::fstream logFile;


class ImageViewer : public QMainWindow
{
    Q_OBJECT
 private:

    // Example Tab
     QWidget*	m_option_panel1;
     QVBoxLayout*    m_option_layout1;
     QWidget*	m_option_panel2;
     QVBoxLayout*    m_option_layout2;
     QPushButton* button1;
     QSlider* red_cross_thickness_slider;


     QWidget*	m_option_panel6;
     QVBoxLayout* m_option_layout6;

     QLabel* average_brithness_label;
     QLabel* variance_label;
     QComboBox* accu_auswahl_comboBox;
     QComboBox* bit_tiefe_comboBox;
     QImage *histogrammChart;
     QLabel *histogrammLabel;
     QSlider *brightness_slider;
     QSlider *contrast_slider;
     QSlider *plow_slider;
     QSlider *phigh_slider;
     bool isDrawn = false;

     // Filter tab
     QSlider *x_filter_slider;
     QSlider *y_filter_slider;
     QLabel *x_filter_label;
     QLabel *y_filter_label;
     QTableWidget *tab1;
     QComboBox* border_treatment_comboBox;
     QDoubleSpinBox *gauss_sigma_input;
     int** filter;
     int filter_width = 0;
     int filter_height = 0;

     // edge filter tab
     QTableWidget *table_abl_filter_x_aufg5;
     QTableWidget *table_abl_filter_y_aufg5;
     QTableWidget *table_laplace_filter_aufg5;
     int** laplace_filter = nullptr;




     // Canny and USM
     QDoubleSpinBox *spinbox_canny_sigma_aufg6;
     QSpinBox *spinbox_canny_tHi_aufg6;
     QSpinBox *spinbox_canny_tLo_aufg6;
     QDoubleSpinBox *spinbox_usm_schaerfungsgrad_aufg6;
     QDoubleSpinBox *spinbox_usm_sigma_aufg6;
     QSpinBox *spinbox_usm_tc_aufg6;

     // Hough
     QLineEdit *angularSteps;
     QLineEdit *radialSteps;
     QLineEdit *accumulatorCount;
     QLabel *label_u54;
     bool biasCompensation = false;

     // Fourier Transformation
     FourierLabel *fourierLabel;
     QImage *fourierChart;
     QSlider * eraser_slider;



 private slots:
     // Trigger slots
     void applyExampleAlgorithm();
     void applyRedCrossAlgorithm();



     // Actions
     void open();
     void print();
     void zoomIn();
     void zoomOut();
     void normalSize();
     void fitToWindow();
     void about();
     void reset();
     void applyCalcImageCharacteristics();
     void applyBitdepth();
     void applyBrightnessAdjust();
     void applyContrastAdjust();
     void applyRobustAutomaticContrastAdjustment();
     void setXLabel(int x);
     void setYLabel(int y);
     void makeTableWidget();
     void applyLinearFilter();
     void applyGauss2DFilter();
     void aufg5_setPerwittFilter();
     void aufg5_setSobelFilter();
     void applyYDerivative();
     void applyXDerivative();
     void applyKantenfilter();
     void applyLaplaceFilter();
     void applyCannyAlgorithm();
     void applyUSMSharpening();
     //void applyKantenFilter(int desired_image);
     void switchBiasKompensation();
     void applyShowingAccuArray();
     void applyShowingAccuArrayCombined();
     void applyShowingAccuArrayNonMaximaSupp();
     void applyShowingAccuArrayTreshold();
     void applyDrawingHoughLines();
     void applyFT();
     void applyIFT();
     void applyClickOnFT(QMouseEvent *ev);
public:
     ImageViewer();
     ~ImageViewer();
     void freeMemory();
     bool loadFile(const QString &);
     void updateImageDisplay();
     void renewLogging();


protected:
    void resizeEvent(QResizeEvent * event);

 private:
    // in diesen Beiden Methoden sind Änderungen nötig bzw. sie dienen als
    // Vorlage für eigene Methoden.
    void generateControlPanels();


    // Ab hier technische Details die nicht für das Verständnis notwendig sind.
    void startLogging();
    void generateMainGui(); 
    
    void createActions();
    void createMenus();
    void updateActions();
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QTabWidget* tabWidget;
    QTextEdit* logBrowser;
    QWidget* centralwidget;
    QLabel* imageLabel;
    QScrollArea* scrollArea;
    double scaleFactor;
    QImage* image;



#ifndef QT_NO_PRINTER
    QPrinter printer;
#endif

    QAction *openAct;
    QAction *printAct;
    QAction *exitAct;
    QAction *zoomInAct;
    QAction *zoomOutAct;
    QAction *normalSizeAct;
    QAction *fitToWindowAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QAction *resetAct;

    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *helpMenu;
    QWidget *exampleTab();
    QWidget *infoTab();
    QWidget *pointOperations();
    void newImageLoaded();
    void setImagePropertieLabels();
    void clearHistogramm();
    void zeichneHistogramm();
    void imageChanged();
    QWidget *filterOperations();
    void findFilterMatrix();
    void deleteFilterMemory();
    QWidget *edgeFilter();
    QWidget *cannyAndUsm();
    void triggerKantenFilter(int desired_image);
    void findLaplaceFilter();
    QWidget *houghTab();
    void triggerShowingAccuArray(int type_of_Array);
    QWidget *fourierTab();
    void drawFTFilterInImage(int x, int y, int width);
};

#endif
