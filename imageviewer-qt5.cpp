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

#include <QtWidgets>
#ifndef QT_NO_PRINTER
#include <QPrintDialog>
#endif
#include<iostream>


#include "imageviewer-qt5.h"

ImageViewer::ImageViewer()
{

	image=NULL;
	resize(1600, 600);
	
	startLogging();

	generateMainGui();
	renewLogging();

	generateControlPanels();
    	createActions();
    	createMenus();

    	resize(QGuiApplication::primaryScreen()->availableSize() * 0.85 );

}

/****************************************************************************************
*
*  Trigger Slots
*       triggered out of Gui
*       delegate to logic functions
*
*****************************************************************************************/

/****************************************************************************************
*                       TAB "Example tab" Trigger
*****************************************************************************************/
void ImageViewer::applyExampleAlgorithm()
{
	if(image!=NULL)
	{
        this->image = cg2::exampleAlgorithm(image,20);
        imageChanged();
    }
}

void ImageViewer::applyRedCrossAlgorithm()
{
    if(image!=NULL)
    {
        //delete image;
        this->image = cg2::drawRedCrossAlgorithm(red_cross_thickness_slider->value());
        imageChanged();

    }
}

/***************************************************^*************************************
*                       TAB "Punktoperationen" Trigger
*****************************************************************************************/

void ImageViewer::applyCalcImageCharacteristics(){
    if(image!=NULL){
        bool linear_scaling;
        if(accu_auswahl_comboBox->currentIndex() == 0){
            linear_scaling= true;
        } else {
            linear_scaling = false;
        }
        cg2::calcImageCharacteristics(image, cg2::histogramm, cg2::variance, cg2::average, linear_scaling);
        setImagePropertieLabels();
        zeichneHistogramm();
        renewLogging();
    }
}

void ImageViewer::setImagePropertieLabels(){
    variance_label->setNum(cg2::variance);
    average_brithness_label->setNum(cg2::average);
}

void ImageViewer::zeichneHistogramm(){
    clearHistogramm();
    QRgb color = qRgb(255,0,0);
    if(accu_auswahl_comboBox->currentIndex() == 1){
        color = qRgb(255,255,0);
    }
    for(int i = 0; i<256; i++)
    {
        for(int j =99; j>(100-cg2::histogramm[i]); j--)
        {
            histogrammChart->setPixel(i,j,color);
        }
    }
    isDrawn = true;
    histogrammLabel->setPixmap(QPixmap::fromImage(*histogrammChart));
}

void ImageViewer::clearHistogramm(){
    if(isDrawn){
        QRgb color = qRgb(0,0,0);
        for(int i = 0; i<256; i++)
        {
            for(int j = 0; j<100; j++)
            {
                histogrammChart->setPixel(i,j,color);
            }
        }
        isDrawn =false;
    }
}

void ImageViewer::applyBitdepth(){
    if(image!=NULL){
        int index = bit_tiefe_comboBox->currentIndex();
        index = 8- index;
        this->image = cg2::changeImageDynamic(image, index);
        imageChanged();
    }
}

void ImageViewer::applyBrightnessAdjust(){
    if(image!=NULL){
        int brightness_adjust_factor = brightness_slider->value();
        this->image = cg2::adjustBrightness(image, brightness_adjust_factor);
        imageChanged();
    }
}

void ImageViewer::applyContrastAdjust(){
    if(image!=NULL){
        double contrast_adjust_factor = contrast_slider->value();

        // rescale from 0-50 to 0-1
        // and 50-100 to 1-3
        if(contrast_adjust_factor>50){
            contrast_adjust_factor = (contrast_adjust_factor -50.) ;
            contrast_adjust_factor = contrast_adjust_factor / 50 * 2;
            contrast_adjust_factor = 1 + contrast_adjust_factor;
        } else {
            contrast_adjust_factor = contrast_adjust_factor * 2;
            contrast_adjust_factor = contrast_adjust_factor / 100 ;
        }
        this->image = cg2::adjustContrast(image, contrast_adjust_factor);
        imageChanged();
    }
}

void ImageViewer::applyRobustAutomaticContrastAdjustment(){
    if(image!=NULL){
        double plow = plow_slider->value()/1000.;
        double phigh = phigh_slider->value()/1000.;
        this->image = cg2::doRobustAutomaticContrastAdjustment(image,plow,phigh);
        imageChanged();
    }
}

/***************************************************^*************************************
*                       TAB "Filteroperationen" Trigger
*****************************************************************************************/


void ImageViewer::setXLabel(int x ) {
    x_filter_label->setNum(x*2-1);
}

void ImageViewer::setYLabel(int y ) {
    y_filter_label->setNum(y*2-1);
}

void ImageViewer::makeTableWidget(){
    int x = x_filter_slider->value()*2-1;
    int y = y_filter_slider->value()*2-1;
    tab1->setRowCount(y);
    tab1->setColumnCount(x);
    QString *strings = new QString();
    strings->setNum(1);
    for(int i = 0; i < y; i++ ){
        for(int j = 0; j < x; j++ ){
            QTableWidgetItem *	 item = tab1->item(i,j);
            if(item == 0){
                QTableWidgetItem * item_setter = new QTableWidgetItem(*new QString('1'));
                tab1->setItem(i,j,item_setter);

            }

        }
    }

}

void ImageViewer::deleteFilterMemory(){
    if(filter_width == 0) {
        return;
    }
    for(int i = 0; i < filter_width; ++i){
        delete [] filter[i];
    }
      delete [] filter;
}

void ImageViewer::findFilterMatrix(){
    if(filter_width == 0){
        // dynamic allocation
        filter = new int*[15];
        for(int i = 0; i < 15; ++i)
            filter[i] = new int[15];
    }

    filter_width = x_filter_slider->value()*2-1;
    filter_height = y_filter_slider->value()*2-1;

    for(int i = 0; i < filter_height; i++ ){
        for(int j = 0; j < filter_width; j++ ){
            QTableWidgetItem *	 item = tab1->item(i,j);
            double num;
            if(item == 0){
                num = 0;
            } else {
                QString s = item->text();
                num = s.toInt();
            }

            filter[i][j] = num;
        }
    }
}

void ImageViewer::applyLinearFilter(){
    if(image!=NULL){
        findFilterMatrix();
        this->image = cg2::filterImage(image, filter, filter_width, filter_height, border_treatment_comboBox->currentIndex());
        imageChanged();
    }
}

void ImageViewer::applyGauss2DFilter(){
    if(image!=NULL){
        double sigma = gauss_sigma_input->value();
        this->image = cg2::filterGauss2D(image, sigma, border_treatment_comboBox->currentIndex());
        imageChanged();
    }
}

/***************************************************^*************************************
*                       TAB "Kantenfilter" Trigger
*****************************************************************************************/


void ImageViewer::aufg5_setPerwittFilter() {
    QTableWidgetItem *xwi100 = new QTableWidgetItem("-1");
    QTableWidgetItem *xwi010 = new QTableWidgetItem("0");
    QTableWidgetItem *xwi001 = new QTableWidgetItem("1");
    table_abl_filter_x_aufg5->setItem(0, 0, xwi100);
    table_abl_filter_x_aufg5->setItem(0, 1, xwi010);
    table_abl_filter_x_aufg5->setItem(0, 2, xwi001);




    QTableWidgetItem *ywi100 = new QTableWidgetItem("1");
    QTableWidgetItem *ywi010 = new QTableWidgetItem("1");
    QTableWidgetItem *ywi001 = new QTableWidgetItem("1");
    table_abl_filter_y_aufg5->setItem(0, 0, ywi100);
    table_abl_filter_y_aufg5->setItem(0, 1, ywi010);
    table_abl_filter_y_aufg5->setItem(0, 2, ywi001);

}

void ImageViewer::aufg5_setSobelFilter() {
    QTableWidgetItem *xwi100 = new QTableWidgetItem("-1");
    QTableWidgetItem *xwi010 = new QTableWidgetItem("0");
    QTableWidgetItem *xwi001 = new QTableWidgetItem("1");
    table_abl_filter_x_aufg5->setItem(0, 0, xwi100);
    table_abl_filter_x_aufg5->setItem(0, 1, xwi010);
    table_abl_filter_x_aufg5->setItem(0, 2, xwi001);




    QTableWidgetItem *ywi100 = new QTableWidgetItem("1");
    QTableWidgetItem *ywi010 = new QTableWidgetItem("2");
    QTableWidgetItem *ywi001 = new QTableWidgetItem("1");
    table_abl_filter_y_aufg5->setItem(0, 0, ywi100);
    table_abl_filter_y_aufg5->setItem(0, 1, ywi010);
    table_abl_filter_y_aufg5->setItem(0, 2, ywi001);

}

void ImageViewer::applyYDerivative(){
    if(image!=NULL){
        triggerKantenFilter(2);
    }
}

void ImageViewer::applyXDerivative(){
    if(image!=NULL){
        triggerKantenFilter(1);
    }
}

void ImageViewer::applyKantenfilter(){
    if(image!=NULL){
        triggerKantenFilter(0);
    }
}

void ImageViewer::triggerKantenFilter(int desired_image){
    int* derivative_filter = new int[3];
    int* smoothing_filter = new int[3];

    for(int i=0;i<3;i++){

        QTableWidgetItem *	 item = table_abl_filter_x_aufg5->item(0,i);
        QString s = item->text();
        int num = s.toInt();
        derivative_filter[i] = num;

        QTableWidgetItem *	 item2 = table_abl_filter_y_aufg5->item(0,i);
        QString s2 = item2->text();
        int num2 = s2.toInt();
        smoothing_filter[i] = num2;

    }

    this->image = cg2::doEdgeFilter(image,derivative_filter,smoothing_filter,desired_image);
    imageChanged();
    delete[] derivative_filter;
    delete[] smoothing_filter;
}

void ImageViewer::findLaplaceFilter(){
    if(laplace_filter == nullptr){
            // dynamic allocation
            laplace_filter = new int*[3];
            for(int i = 0; i < 3; ++i)
                laplace_filter[i] = new int[3];

    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            laplace_filter[i][j] = table_laplace_filter_aufg5->item(i,j)->text().toInt();
        }
    }
}

void ImageViewer::applyLaplaceFilter(){
    if(image!=NULL){
        findLaplaceFilter();
        this->image = cg2::doLaplaceFilter(image, laplace_filter);
        imageChanged();
    }
}


/***************************************************^*************************************
*                       TAB "Canny und USM" Trigger
*****************************************************************************************/

void ImageViewer::applyCannyAlgorithm(){
    if(image!=NULL){
        double sigma = spinbox_canny_sigma_aufg6->value();
        int tHi = spinbox_canny_tHi_aufg6->value();
        int tLo = spinbox_canny_tLo_aufg6->value();

        this->image = cg2::doCanny(image, sigma, tHi, tLo);

        imageChanged();
    }
}


void ImageViewer::applyUSMSharpening(){
    if(image!=NULL){
        double sharpening_value = spinbox_usm_schaerfungsgrad_aufg6->value();
        double sigma = spinbox_usm_sigma_aufg6->value();
        int tc = spinbox_usm_tc_aufg6->value();
        this->image = cg2::doUSM(image, sharpening_value, sigma, tc);
        imageChanged();
    }
}

/***************************************************^*************************************
*                       TAB "Hough" Trigger
*****************************************************************************************/

void ImageViewer::switchBiasKompensation(){
    if(biasCompensation == false) {
         biasCompensation = true;
         label_u54->setText("ON");
    } else {
        biasCompensation = false;
        label_u54->setText("OFF");
    }
}

void ImageViewer::applyShowingAccuArray(){
    if(image!=NULL) {
        triggerShowingAccuArray(0);
    }
}


void ImageViewer::applyShowingAccuArrayTreshold(){
    if(image!=NULL) {
        triggerShowingAccuArray(1);
    }
}


void ImageViewer::applyShowingAccuArrayNonMaximaSupp(){
    if(image!=NULL) {
        triggerShowingAccuArray(2);
    }
}


void ImageViewer::applyShowingAccuArrayCombined(){
    if(image!=NULL) {
        triggerShowingAccuArray(3);
    }
}

void ImageViewer::triggerShowingAccuArray(int type_of_Array){
    int angular_steps = angularSteps->text().toDouble();
    int radial_steps = radialSteps->text().toDouble();
    double threshhold_a_min = accumulatorCount->text().toDouble() / 100.;
    bool do_threshhold_reduction = false;
    bool do_non_maxima_suppression = false;
    bool bias_compensation = biasCompensation;
    double sigma = spinbox_canny_sigma_aufg6->value();
    int tHi = spinbox_canny_tHi_aufg6->value();
    int tLo = spinbox_canny_tLo_aufg6->value();

    if (type_of_Array == 1)
    {
        do_threshhold_reduction = true;
    } else if(type_of_Array == 2)
    {
        do_non_maxima_suppression = true;
    } else if(type_of_Array == 3)
    {
        do_non_maxima_suppression = true;
        do_threshhold_reduction = true;
    }
    this->image = cg2::showAccumulatorArray(image, angular_steps, radial_steps, bias_compensation, threshhold_a_min,
                                            do_threshhold_reduction, do_non_maxima_suppression,
                                            sigma, tHi, tLo);
    imageChanged();
}

void ImageViewer::applyDrawingHoughLines(){
    if(image != NULL){
        int angular_steps = angularSteps->text().toDouble();
        int radial_steps = radialSteps->text().toDouble();
        double threshhold_a_min = accumulatorCount->text().toDouble() / 100.;
        bool bias_compensation = biasCompensation;
        double sigma = spinbox_canny_sigma_aufg6->value();
        int tHi = spinbox_canny_tHi_aufg6->value();
        int tLo = spinbox_canny_tLo_aufg6->value();
        this->image = cg2::drawHoughLinesInImage(image, angular_steps, radial_steps, bias_compensation, threshhold_a_min,
                                                sigma, tHi, tLo);
        imageChanged();
    }
}

/***************************************************^*************************************
*                       TAB Fourier Trigger
*****************************************************************************************/



void ImageViewer::applyFT(){
    if(image != NULL){
        fourierChart = new QImage(image->convertToFormat(QImage::Format_Grayscale8));
        fourierChart = cg2::doFT(fourierChart);
        fourierLabel->setPixmap(QPixmap::fromImage(*fourierChart));
        renewLogging();
        updateImageDisplay();
    }
}

void ImageViewer::applyIFT(){
    if(image != NULL){
        this->image = cg2::doIFT(fourierChart);
        imageChanged();
    }
}

void ImageViewer::applyClickOnFT(QMouseEvent* ev){
    if(image != NULL) {
        int Xpos=ev->x();
        int Ypos=ev->y();
        int eraser_width = eraser_slider->value();
        drawFTFilterInImage(Xpos, Ypos, eraser_width);
    }
}

void ImageViewer::drawFTFilterInImage(int x, int y, int eraser_width){
    logFile << "Radiere FFT-Koeffizienten bei pos x:" << x << " und y:" << y << " mit Radierer breite: " << eraser_width << std::endl;
    int filter_center = eraser_width / 2;
    int min_value = 0;
    int max_x_value = fourierChart->width() -1;
    int max_y_value = fourierChart->height() -1;


    for (int j = -filter_center; j <= filter_center; j++) {
        for (int i = -filter_center; i <= filter_center; i++) {
            int pixel_x = x + i;
            pixel_x = std::max(min_value,pixel_x);
            pixel_x = std::min(max_x_value,pixel_x);

            int pixel_y = y + j;
            pixel_y = std::max(min_value,pixel_y);
            pixel_y = std::min(max_y_value,pixel_y);
            fourierChart->setPixel(pixel_x, pixel_y, QColor(0, 0, 0).rgb());


        }
    }
    fourierLabel->setPixmap(QPixmap::fromImage(*fourierChart));
    renewLogging();
}


/****************************************************************************************
*   
*  GUI
*
*****************************************************************************************/

void ImageViewer::generateControlPanels()
{
    tabWidget->addTab(infoTab(),"Info");
    tabWidget->addTab(exampleTab(),"Bsp.");
    tabWidget->addTab(pointOperations(),"Punktop.");
    tabWidget->addTab(filterOperations(),"Filterop.");
    tabWidget->addTab(edgeFilter(),"Kantenerkennung");
    tabWidget->addTab(cannyAndUsm(),"Canny/USM");
    tabWidget->addTab(houghTab(),"Hough");
    tabWidget->addTab(fourierTab(),"Fourier");
    aufg5_setSobelFilter();
}

/**************************************************************************************** 
*
*   UTILS ->
*       Image pixel operations
*       Label setting
*       Destructor
*       LogFile
*       Image loading
*       GUI creating
*       Actions
*
*****************************************************************************************/
void ImageViewer::imageChanged(){
    applyCalcImageCharacteristics();
    renewLogging();
    updateImageDisplay();
    logFile << std::endl;
}

void ImageViewer::newImageLoaded()
{
    backupImage = new QImage(*image);
    cg2::imageGotChangedFlag = true;
    imageChanged();
}

ImageViewer::~ImageViewer()
{
    cg2::freeMemory();
    deleteFilterMemory();
    delete image;
    delete[] cg2::histogramm;
    delete backupImage;
}

void ImageViewer::startLogging()
{
	//LogFile
    logFile.open("log.txt", std::ios::out);
    logFile << "Logging: \n" << std::endl;
}

void ImageViewer::renewLogging()
{
	QFile file("log.txt"); // Create a file handle for the file named
	QString line;
	file.open(QIODevice::ReadOnly); // Open the file

	QTextStream stream( &file ); // Set the stream to read from myFile
	logBrowser->clear();
	while(!stream.atEnd()){

		line = stream.readLine(); // this reads a line (QString) from the file
		logBrowser->append(line);
	}
}


void ImageViewer::resizeEvent(QResizeEvent * event)
{
	QMainWindow::resizeEvent(event);
	centralwidget->setMinimumWidth(width());	
    	centralwidget->setMinimumHeight(height());
	centralwidget->setMaximumWidth(width());	
    	centralwidget->setMaximumHeight(height());
 	logBrowser->setMinimumWidth(width()-40);
    	logBrowser->setMaximumWidth(width()-40);
}

void ImageViewer::updateImageDisplay()
{
	imageLabel->setPixmap(QPixmap::fromImage(*image));
}


void ImageViewer::generateMainGui()
{
	/* Tab widget */
        tabWidget = new QTabWidget(this);
	tabWidget->setObjectName(QStringLiteral("tabWidget"));
	


	/* Center widget */
	centralwidget = new QWidget(this);
	centralwidget->setObjectName(QStringLiteral("centralwidget"));
	//centralwidget->setFixedSize(200,200);
	//setCentralWidget(centralwidget);

    	imageLabel = new QLabel;
 	imageLabel->setBackgroundRole(QPalette::Base);
    	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    	imageLabel->setScaledContents(true);
	

	/* Center widget */
	scrollArea = new QScrollArea;
   	scrollArea->setBackgroundRole(QPalette::Dark);
    	scrollArea->setWidget(imageLabel);
	
	
    	setCentralWidget(scrollArea);

	/* HBox layout */
	QGridLayout* gLayout = new QGridLayout(centralwidget);
	gLayout->setObjectName(QStringLiteral("hboxLayout"));
	gLayout->addWidget(new QLabel(),1,1);
	gLayout->setVerticalSpacing(50);
	gLayout->addWidget(tabWidget,2,1);
	gLayout->addWidget(scrollArea,2,2);
	
	logBrowser= new QTextEdit(this);
	logBrowser->setMinimumHeight(100);
	logBrowser->setMaximumHeight(200);
	logBrowser->setMinimumWidth(width());
	logBrowser->setMaximumWidth(width());
	gLayout->addWidget(logBrowser,3,1,1,2);
	gLayout->setVerticalSpacing(50);
}


bool ImageViewer::loadFile(const QString &fileName)
{
    if(image!=NULL)
    {
	delete image;
	image=NULL;
    }

    image = new QImage(fileName);	

    if (image->isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        imageLabel->setPixmap(QPixmap());
        imageLabel->adjustSize();
        return false;
    }
    
    scaleFactor = 1.0;

   
    updateImageDisplay();

    printAct->setEnabled(true);
    fitToWindowAct->setEnabled(true);
    updateActions();

    if (!fitToWindowAct->isChecked())
        imageLabel->adjustSize();

    setWindowFilePath(fileName);
    logFile << "geladen: " << fileName.toStdString().c_str()  << std::endl;
    newImageLoaded();
    return true;
}




void ImageViewer::open()
{
    QStringList mimeTypeFilters;
    foreach (const QByteArray &mimeTypeName, QImageReader::supportedMimeTypes())
        mimeTypeFilters.append(mimeTypeName);
    mimeTypeFilters.sort();
    const QStringList picturesLocations = QStandardPaths::standardLocations(QStandardPaths::PicturesLocation);
    QFileDialog dialog(this, tr("Open File"),
                       picturesLocations.isEmpty() ? QDir::currentPath() : picturesLocations.first());
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.selectMimeTypeFilter("image/jpeg");

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}

void ImageViewer::print()
{
    Q_ASSERT(imageLabel->pixmap());
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrintDialog dialog(&printer, this);
    if (dialog.exec()) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = imageLabel->pixmap()->size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(imageLabel->pixmap()->rect());
        painter.drawPixmap(0, 0, *imageLabel->pixmap());
    }
#endif
}

void ImageViewer::zoomIn()
{
    scaleImage(1.25);
}

void ImageViewer::zoomOut()
{
    scaleImage(0.8);
}

void ImageViewer::normalSize()
{
    imageLabel->adjustSize();
    scaleFactor = 1.0;
}

void ImageViewer::reset()
{
    //freeMemory();
    delete image;
    image = new QImage(*backupImage);
    logFile << "Reset Image" << std::endl;
    imageChanged();
}
void ImageViewer::fitToWindow()
{
    bool fitToWindow = fitToWindowAct->isChecked();
    scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
}

void ImageViewer::about()
{
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The <b>Image Viewer</b> example shows how to combine QLabel "
               "and QScrollArea to display an image. QLabel is typically used "
               "for displaying a text, but it can also display an image. "
               "QScrollArea provides a scrolling view around another widget. "
               "If the child widget exceeds the size of the frame, QScrollArea "
               "automatically provides scroll bars. </p><p>The example "
               "demonstrates how QLabel's ability to scale its contents "
               "(QLabel::scaledContents), and QScrollArea's ability to "
               "automatically resize its contents "
               "(QScrollArea::widgetResizable), can be used to implement "
               "zooming and scaling features. </p><p>In addition the example "
               "shows how to use QPainter to print an image.</p>"));
}

void ImageViewer::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(tr("Ctrl+O"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    printAct = new QAction(tr("&Print..."), this);
    printAct->setShortcut(tr("Ctrl+P"));
    printAct->setEnabled(false);
    connect(printAct, SIGNAL(triggered()), this, SLOT(print()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    zoomInAct = new QAction(tr("Zoom &In (25%)"), this);
    zoomInAct->setShortcut(tr("Ctrl++"));
    zoomInAct->setEnabled(false);
    connect(zoomInAct, SIGNAL(triggered()), this, SLOT(zoomIn()));

    zoomOutAct = new QAction(tr("Zoom &Out (25%)"), this);
    zoomOutAct->setShortcut(tr("Ctrl+-"));
    zoomOutAct->setEnabled(false);
    connect(zoomOutAct, SIGNAL(triggered()), this, SLOT(zoomOut()));

    resetAct = new QAction(tr("&Reset"), this);
    resetAct->setDisabled(true);
    resetAct->setShortcut(tr("Ctrl+R"));
    connect(resetAct, SIGNAL(triggered()), this, SLOT(reset()));

    normalSizeAct = new QAction(tr("&Normal Size"), this);
    normalSizeAct->setShortcut(tr("Ctrl+S"));
    normalSizeAct->setEnabled(false);
    connect(normalSizeAct, SIGNAL(triggered()), this, SLOT(normalSize()));

    fitToWindowAct = new QAction(tr("&Fit to Window"), this);
    fitToWindowAct->setEnabled(false);
    fitToWindowAct->setCheckable(true);
    fitToWindowAct->setShortcut(tr("Ctrl+F"));
    connect(fitToWindowAct, SIGNAL(triggered()), this, SLOT(fitToWindow()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void ImageViewer::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    viewMenu = new QMenu(tr("&View"), this);
    viewMenu->addAction(zoomInAct);
    viewMenu->addAction(zoomOutAct);
    viewMenu->addAction(normalSizeAct);
    viewMenu->addSeparator();
    viewMenu->addAction(fitToWindowAct);
    viewMenu->addAction(resetAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(viewMenu);
    menuBar()->addMenu(helpMenu);
}

void ImageViewer::updateActions()
{
    zoomInAct->setEnabled(!fitToWindowAct->isChecked());
    zoomOutAct->setEnabled(!fitToWindowAct->isChecked());
    normalSizeAct->setEnabled(!fitToWindowAct->isChecked());
    resetAct->setEnabled(!fitToWindowAct->isChecked());
}

void ImageViewer::scaleImage(double factor)
{
    Q_ASSERT(imageLabel->pixmap());
    scaleFactor *= factor;
    imageLabel->resize(scaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(scrollArea->verticalScrollBar(), factor);

    zoomInAct->setEnabled(scaleFactor < 10.0);
    zoomOutAct->setEnabled(scaleFactor > 0.05);
}

void ImageViewer::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}
