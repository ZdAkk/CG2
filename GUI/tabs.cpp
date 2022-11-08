#include "fourierlabel.h"
#include "tabs.h"

#include <QLabel>
#include <QTableWidget>
#include <imageviewer-qt5.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qwidget.h>


QWidget* ImageViewer::infoTab(){


    m_option_panel6 = new QWidget();
    m_option_layout6 = new QVBoxLayout();
    m_option_panel6->setLayout(m_option_layout6);

    QWidget* m_info_panel = new QWidget();
    QHBoxLayout* m_info_layout = new QHBoxLayout();
    m_info_panel->setLayout(m_info_layout);
    m_option_layout6->addWidget(m_info_panel);

    QWidget* m_info_panel2 = new QWidget();
    QHBoxLayout* m_info_layout2 = new QHBoxLayout();
    m_info_panel2->setLayout(m_info_layout2);
    m_option_layout6->addWidget(m_info_panel2);

    QWidget* m_info_panel3 = new QWidget();
    QHBoxLayout* m_info_layout3 = new QHBoxLayout();
    m_info_panel3->setLayout(m_info_layout3);
    m_option_layout6->addWidget(m_info_panel3);

    QWidget* m_info_panel4 = new QWidget();
    QHBoxLayout* m_info_layout4 = new QHBoxLayout();
    m_info_panel4->setLayout(m_info_layout4);
    m_option_layout6->addWidget(m_info_panel4);

    QWidget* m_info_panel5 = new QWidget();
    QHBoxLayout* m_info_layout5 = new QHBoxLayout();
    m_info_panel5->setLayout(m_info_layout5);
    m_option_layout6->addWidget(m_info_panel5);

    QWidget* m_info_panel6 = new QWidget();
    QHBoxLayout* m_info_layout6 = new QHBoxLayout();
    m_info_panel6->setLayout(m_info_layout6);
    m_option_layout6->addWidget(m_info_panel6);

    QWidget* m_info_panelLast = new QWidget();
    QHBoxLayout* m_info_layoutLast = new QHBoxLayout();
    m_info_panelLast->setLayout(m_info_layoutLast);
    m_option_layout6->addWidget(m_info_panelLast);

    QLabel* z1 = new QLabel("Aktion:");
    QLabel* z2 = new QLabel("Taste:");
    QFont font = z1->font();
    font.setPointSize(22);
    font.setBold(true);
    z1->setFont(font);
    z2->setFont(font);

    QLabel* a1 = new QLabel("Neues Bild Laden:");
    QLabel* a2 = new QLabel("STRG + O");
    QLabel* b1 = new QLabel("Bild reset:");
    QLabel* b2 = new QLabel("STRG + R");


    QLabel* c1 = new QLabel("Bild verkleinern:");
    QLabel* c2 = new QLabel("STRG + -");

    QLabel* d1 = new QLabel("Bild vergrößern:");
    QLabel* d2 = new QLabel("STRG + +");

    QLabel* e1 = new QLabel("Bild maximieren:");
    QLabel* e2 = new QLabel("STRG + F");

    QLabel* last1 = new QLabel("Programm schließen:");
    QLabel* last2 = new QLabel("STRG + Q");

    m_info_layout->addWidget(z1);
    m_info_layout->addWidget(z2);
    m_info_layout2->addWidget(a1);
    m_info_layout2->addWidget(a2);
    m_info_layout3->addWidget(b1);
    m_info_layout3->addWidget(b2);
    m_info_layout4->addWidget(c1);
    m_info_layout4->addWidget(c2);
    m_info_layout5->addWidget(d1);
    m_info_layout5->addWidget(d2);
    m_info_layout6->addWidget(e1);
    m_info_layout6->addWidget(e2);
    m_info_layoutLast->addWidget(last1);
    m_info_layoutLast->addWidget(last2);

    return m_option_panel6;

}

QWidget* ImageViewer::exampleTab(){
    m_option_panel1 = new QWidget();
    m_option_layout1 = new QVBoxLayout();
    m_option_panel1->setLayout(m_option_layout1);


    button1 = new QPushButton();
    button1->setText("Apply example algorithm 1");


    red_cross_thickness_slider = new QSlider(Qt::Horizontal);
    red_cross_thickness_slider->setMaximum(0);
    red_cross_thickness_slider->setMaximum(100);
    QObject::connect(red_cross_thickness_slider, SIGNAL(valueChanged(int)), this, SLOT(applyRedCrossAlgorithm()));

    QLabel* label1 = new QLabel("Apply example algorithm 2 via Slider:");

    QObject::connect(button1, SIGNAL (clicked()), this, SLOT (applyExampleAlgorithm()));

    m_option_layout1->addWidget(button1);
    m_option_layout1->addWidget(label1);
    m_option_layout1->addWidget(red_cross_thickness_slider);

    m_option_panel1->setLayout(m_option_layout1);
    return m_option_panel1;

}

QWidget* ImageViewer::pointOperations(){
    QWidget *m_option_panel_u2 = new QWidget();
    QGridLayout* m_option_layout_u2 = new QGridLayout(m_option_panel_u2);
    m_option_layout_u2->setRowStretch(0|1|2|3|4|5|6|7|8,50);
    m_option_layout_u2->setColumnStretch(0|1|2,300);
    m_option_layout_u2->setMargin(20);

    accu_auswahl_comboBox = new QComboBox();
    accu_auswahl_comboBox->addItem("Histogramm linear");
    accu_auswahl_comboBox->addItem("Histogramm logarithmisch");
    QObject::connect(accu_auswahl_comboBox, SIGNAL (currentIndexChanged(int)), this, SLOT(applyCalcImageCharacteristics()));


    QLabel* label2_1 = new QLabel(tr("    Mittlere Helligkeit: "));
    average_brithness_label = new QLabel( " ");


    QLabel* label2_3 = new QLabel(tr("    Varianz: "));
    variance_label = new QLabel( " ");

    bit_tiefe_comboBox = new QComboBox();
    bit_tiefe_comboBox->addItem("Bittiefe: 8");
    bit_tiefe_comboBox->addItem("Bittiefe: 7");
    bit_tiefe_comboBox->addItem("Bittiefe: 6");
    bit_tiefe_comboBox->addItem("Bittiefe: 5");
    bit_tiefe_comboBox->addItem("Bittiefe: 4");
    bit_tiefe_comboBox->addItem("Bittiefe: 3");
    bit_tiefe_comboBox->addItem("Bittiefe: 2");
    bit_tiefe_comboBox->addItem("Bittiefe: 1");
    QObject::connect(bit_tiefe_comboBox, SIGNAL (currentIndexChanged(int)), this, SLOT(applyBitdepth()));


    // Histogramm
    histogrammLabel = new QLabel();
    histogrammChart = new QImage(256,100, QImage::Format_RGB32);
    histogrammLabel->setScaledContents(true);
    histogrammLabel->setPixmap(QPixmap::fromImage(*histogrammChart));

    QLabel* label2_8 = new QLabel(tr("Kontrastskalierung: "));

    contrast_slider = new QSlider(Qt::Horizontal);
    contrast_slider->setRange(0,100);
    contrast_slider->setTickInterval(1);
    contrast_slider->setValue(50);

    contrast_slider->setTickPosition(QSlider::TicksBelow);
    QObject::connect(contrast_slider, SIGNAL(sliderMoved(int)) , this , SLOT(applyContrastAdjust()));



    QLabel* label2_9 = new QLabel(tr("Helligkeitsskalierung: "));

    brightness_slider = new QSlider(Qt::Horizontal);
    brightness_slider->setRange(-256,256);
    brightness_slider->setTickInterval(1);
    brightness_slider->setValue(0);
    brightness_slider->setTickPosition(QSlider::TicksBelow);
    QObject::connect(brightness_slider, SIGNAL(sliderMoved(int)), this , SLOT(applyBrightnessAdjust()));


    QLabel* plow = new QLabel(tr("Automatische Kontrastanpassung sLow (0%-5%): "));
    QLabel* phigh = new QLabel(tr("Automatische Kontrastanpassung sHigh (0%-5%): "));


    plow_slider = new QSlider(Qt::Horizontal);
    plow_slider->setRange(1,50);
    plow_slider->setTickInterval(1);
    plow_slider->setValue(10);

    phigh_slider = new QSlider(Qt::Horizontal);
    phigh_slider->setRange(1,50);
    phigh_slider->setTickInterval(1);
    phigh_slider->setValue(10);


    QPushButton *button_AK = new QPushButton();
    button_AK->setText("Automatische robuste Kontrastanpasung");


    QObject::connect(button_AK, SIGNAL (clicked()), this, SLOT (applyRobustAutomaticContrastAdjustment()));


    m_option_layout_u2->addWidget(label2_1,3,1);
    m_option_layout_u2->addWidget(average_brithness_label,3,2);

    m_option_layout_u2->addWidget(label2_3,4,1);
    m_option_layout_u2->addWidget(variance_label,4,2);

    m_option_layout_u2->addWidget(histogrammLabel,2,1,1,3);
    m_option_layout_u2->addWidget(accu_auswahl_comboBox,1,1,1,3);

    m_option_layout_u2->addWidget(bit_tiefe_comboBox,5,1,1,3);


    m_option_layout_u2->addWidget(label2_8,6,1);
    m_option_layout_u2->addWidget(contrast_slider,7,1,1,3);

    m_option_layout_u2->addWidget(label2_9,8,1);
    m_option_layout_u2->addWidget(brightness_slider,9,1,1,3);

    m_option_layout_u2->addWidget(plow,12,1);
    m_option_layout_u2->addWidget(plow_slider,12,2,2,3);
    m_option_layout_u2->addWidget(phigh,13,1);
    m_option_layout_u2->addWidget(phigh_slider,13,2,2,3);
    m_option_layout_u2->addWidget(button_AK,15,1,1,3);


    return m_option_panel_u2;

}

QWidget* ImageViewer::filterOperations(){
    QWidget *m_option_panel_u3 = new QWidget();
    QGridLayout* m_option_layout_u3 = new QGridLayout(m_option_panel_u3);
    m_option_layout_u3->setRowStretch(0|1|2|3|4|5|6|7|8,50);
    m_option_layout_u3->setColumnStretch(2,300);
    m_option_layout_u3->setMargin(20);

    QLabel* label3_1 = new QLabel(tr("X - Filter Größe: "));

    x_filter_slider = new QSlider(Qt::Horizontal);
    x_filter_slider->setRange(1,8);
    x_filter_slider->setTickInterval(1);
    //x_filter_slider->setTickPosition(QSlider::TicksBelow);
    x_filter_slider->setValue(2);

    x_filter_label = new QLabel(tr("?"));
    x_filter_label->setNum(3);
    QObject::connect(x_filter_slider, SIGNAL(sliderMoved(int)) , SLOT(setXLabel(int)));
    QObject::connect(x_filter_slider, SIGNAL(valueChanged(int)),this, SLOT(makeTableWidget()));


    QLabel *label3_2 = new QLabel( "Filter Koeffizienten auswählen:  ");
    tab1 = new QTableWidget(this);



    QLabel* label3_3 = new QLabel(tr("Y - Filter Größe: "));

    y_filter_slider = new QSlider(Qt::Horizontal);
    y_filter_slider->setRange(1,8);
    y_filter_slider->setTickInterval(1);
    y_filter_slider->setValue(2);

    y_filter_label = new QLabel(tr("?"));
    y_filter_label->setNum(3);
    QObject::connect(y_filter_slider, SIGNAL(sliderMoved(int)), SLOT(setYLabel(int)));
    QObject::connect(y_filter_slider, SIGNAL(valueChanged(int)),this, SLOT(makeTableWidget()));



    border_treatment_comboBox = new QComboBox();
    border_treatment_comboBox->addItem("Zentralbereich");
    border_treatment_comboBox->addItem("Zero Padding");
    border_treatment_comboBox->addItem("Konstante Randbedingung");
    border_treatment_comboBox->addItem("Gespiegelte Randbedingung");
    QObject::connect(border_treatment_comboBox, SIGNAL (currentIndexChanged(int)), this, SLOT(applyLinearFilter()));

    QPushButton* apply_filters = new QPushButton();
    apply_filters->setText("Linearer Filter anwenden");
    QObject::connect(apply_filters, SIGNAL (clicked()), SLOT (applyLinearFilter()));


    gauss_sigma_input = new QDoubleSpinBox();
    gauss_sigma_input->setMinimum(0);
    gauss_sigma_input->setMaximum(15);
    gauss_sigma_input->setValue(0.85);
    QLabel* label_u4B5 = new QLabel(tr("Wähle σ für 2D Gauss-Filter: "));

    QPushButton* apply_gauss = new QPushButton();
    apply_gauss->setText("2D Gauss mit σ anwenden");
    QObject::connect(apply_gauss, SIGNAL (clicked()), SLOT (applyGauss2DFilter()));


    m_option_layout_u3->addWidget(label3_1,1,1);
    m_option_layout_u3->addWidget(x_filter_label,1,2);
    m_option_layout_u3->addWidget(x_filter_slider,2,1,1,2);

    m_option_layout_u3->addWidget(label3_3,3,1);
    m_option_layout_u3->addWidget(y_filter_label,3,2);
    m_option_layout_u3->addWidget(y_filter_slider,4,1,1,2);

    m_option_layout_u3->addWidget(label3_2,5,1);
    m_option_layout_u3->addWidget(tab1,6,1,1,2);

    m_option_layout_u3->addWidget(border_treatment_comboBox,7,1,1,2);
    m_option_layout_u3->addWidget(apply_filters,8,1,1,2);
    m_option_layout_u3->addWidget(label_u4B5,10,1);
    m_option_layout_u3->addWidget(gauss_sigma_input,10,2);
    m_option_layout_u3->addWidget(apply_gauss,11,1,1,2);

    makeTableWidget();
    return m_option_panel_u3;
}

QWidget* ImageViewer::edgeFilter(){
    QWidget *m_option_panel_aufg5 = new QWidget();
    QVBoxLayout *m_option_layout_aufg5 = new QVBoxLayout();
    m_option_panel_aufg5->setLayout(m_option_layout_aufg5);

    // Horizontal Box Layout Button
    QWidget *panel_button_tabelle_aufg5a = new QWidget();
    QHBoxLayout *layout_button_panel_tabelle_aufg5a = new QHBoxLayout();
    panel_button_tabelle_aufg5a->setLayout(layout_button_panel_tabelle_aufg5a);
    m_option_layout_aufg5->addWidget(panel_button_tabelle_aufg5a);

    // Button Fill with Perwitt
    QPushButton *button_perwitt_fill_aufg5a = new QPushButton("Prewitt-Werte füllen");
    QObject::connect(button_perwitt_fill_aufg5a, SIGNAL(released()), this, SLOT(aufg5_setPerwittFilter()));
    layout_button_panel_tabelle_aufg5a->addWidget(button_perwitt_fill_aufg5a);

    // Button Fill with Sobel
    QPushButton *button_sobel_fill_aufg5a = new QPushButton("Sobel-Werte füllen");
    QObject::connect(button_sobel_fill_aufg5a, SIGNAL(released()), this, SLOT(aufg5_setSobelFilter()));
    layout_button_panel_tabelle_aufg5a->addWidget(button_sobel_fill_aufg5a);


    // Horizontal Box Layout Label
    QWidget *panel_label_filter_aufg5 = new QWidget();
    QHBoxLayout *layout_filter_panel_label_aufg5 = new QHBoxLayout();
    panel_label_filter_aufg5->setLayout(layout_filter_panel_label_aufg5);
    m_option_layout_aufg5->addWidget(panel_label_filter_aufg5);


    // Label Filter X
    QLabel *label_filter_x_aufg5 = new QLabel("1D Ableitungsfilter");
    layout_filter_panel_label_aufg5->addWidget(label_filter_x_aufg5);

    // Label Filter Y
    QLabel *label_filter_y_aufg5 = new QLabel("1D Glättungsfilter");
    layout_filter_panel_label_aufg5->addWidget(label_filter_y_aufg5);

    // Horizontal Box Layout Table
    QWidget *panel_table_filter_aufg5 = new QWidget();
    QHBoxLayout *layout_filter_panel_table_aufg5 = new QHBoxLayout();
    //panel_table_filter_aufg5->setMaximumSize(126,20);
    panel_table_filter_aufg5->setLayout(layout_filter_panel_table_aufg5);
    m_option_layout_aufg5->addWidget(panel_table_filter_aufg5);

    // Tabelle Filter X
    table_abl_filter_x_aufg5 = new QTableWidget(1, 3);
    //QObject::connect(table_abl_filter_x_aufg5, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(aufg4_validateTableWidgetCell(QTableWidgetItem*))); // Ganzzahlige Integer
    layout_filter_panel_table_aufg5->addWidget(table_abl_filter_x_aufg5);

    // Tabelle Filter Y
    table_abl_filter_y_aufg5 = new QTableWidget(1, 3);
    //QObject::connect(table_abl_filter_y_aufg5, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(aufg4_validateTableWidgetCell(QTableWidgetItem*))); // Ganzzahlige Integer
    layout_filter_panel_table_aufg5->addWidget(table_abl_filter_y_aufg5);

    // Horizontal Box Layout Button
    QWidget *panel_button_tabelle_aufg5b = new QWidget();
    QHBoxLayout *layout_button_panel_tabelle_aufg5b = new QHBoxLayout();
    panel_button_tabelle_aufg5b->setLayout(layout_button_panel_tabelle_aufg5b);
    m_option_layout_aufg5->addWidget(panel_button_tabelle_aufg5b);

    // Button do Y derivative
    QPushButton *button_do_Y_derivative = new QPushButton("Ableitung nur in Y-Richtung");
    QObject::connect(button_do_Y_derivative, SIGNAL(released()), this, SLOT(applyYDerivative()));
    layout_button_panel_tabelle_aufg5b->addWidget(button_do_Y_derivative);

    // Button do X derivative
    QPushButton *button_do_X_derivative = new QPushButton("Ableitung nur in X-Richtung");
    QObject::connect(button_do_X_derivative, SIGNAL(released()), this, SLOT(applyXDerivative()));
    layout_button_panel_tabelle_aufg5b->addWidget(button_do_X_derivative);

    // Button Ableitungsfilter
    QPushButton *button_abl_filter_aufg5 = new QPushButton("Kantenfilter ausführen");
    QObject::connect(button_abl_filter_aufg5, SIGNAL(released()), this, SLOT(applyKantenfilter()));
    m_option_layout_aufg5->addWidget(button_abl_filter_aufg5);

    // Label Laplace Filter
    QLabel *label_laplace_filter_aufg5 = new QLabel("Laplace-Filter:");
    m_option_layout_aufg5->addWidget(label_laplace_filter_aufg5);

    // Table Laplace Filter
    table_laplace_filter_aufg5 = new QTableWidget(3, 3);
    //QObject::connect(table_laplace_filter_aufg5, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(aufg4_validateTableWidgetCell(QTableWidgetItem*))); // Ganzzahlige Integer
    m_option_layout_aufg5->addWidget(table_laplace_filter_aufg5);

    QTableWidgetItem * item_setter = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(0,0,item_setter);
    QTableWidgetItem * item_setter2 = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(0,1,item_setter2);
    QTableWidgetItem * item_setter3 = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(0,2,item_setter3);
    QTableWidgetItem * item_setter4 = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(1,0,item_setter4);
    QString temp8 = *new QString();
    temp8.append('-');
    temp8.append('8');
    QTableWidgetItem * item_setter5 = new QTableWidgetItem(*new QString(temp8));
    table_laplace_filter_aufg5->setItem(1,1,item_setter5);
    QTableWidgetItem * item_setter6 = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(1,2,item_setter6);
    QTableWidgetItem * item_setter7 = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(2,0,item_setter7);
    QTableWidgetItem * item_setter8 = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(2,1,item_setter8);
    QTableWidgetItem * item_setter9 = new QTableWidgetItem(*new QString('1'));
    table_laplace_filter_aufg5->setItem(2,2,item_setter9);

    // Button Laplace Filter
    QPushButton *button_laplace_filter_aufg5 = new QPushButton("Laplace Filter");
    QObject::connect(button_laplace_filter_aufg5, SIGNAL(released()), this, SLOT(applyLaplaceFilter()));
    m_option_layout_aufg5->addWidget(button_laplace_filter_aufg5);

    return m_option_panel_aufg5;
}

QWidget* ImageViewer::cannyAndUsm(){
    QWidget *m_option_panel_aufg6 = new QWidget();
    QVBoxLayout *m_option_layout_aufg6 = new QVBoxLayout();
    m_option_panel_aufg6->setLayout(m_option_layout_aufg6);

    QLabel *label_canny_aufg6 = new QLabel("Canny Algorithmus:");
    m_option_layout_aufg6->addWidget(label_canny_aufg6);
    QFont font = label_canny_aufg6->font();
    font.setPointSize(15);
    font.setBold(true);
    label_canny_aufg6->setFont(font);



    // Horizontal Box Layout Canny Sigma
    QWidget *panel_canny_sigma_aufg6 = new QWidget();
    QHBoxLayout *layout_canny_sigma_aufg6 = new QHBoxLayout();
    panel_canny_sigma_aufg6->setLayout(layout_canny_sigma_aufg6);
    m_option_layout_aufg6->addWidget(panel_canny_sigma_aufg6);

    // Label Canny Sigma
    QLabel *label_canny_sigma_aufg6 = new QLabel("σ Canny");
    label_canny_sigma_aufg6->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout_canny_sigma_aufg6->addWidget(label_canny_sigma_aufg6);

    // DoubleSpinBox Canny Sigma
    spinbox_canny_sigma_aufg6 = new QDoubleSpinBox();
    spinbox_canny_sigma_aufg6->setMinimum(0);
    spinbox_canny_sigma_aufg6->setMaximum(15);
    spinbox_canny_sigma_aufg6->setValue(1.50);
    layout_canny_sigma_aufg6->addWidget(spinbox_canny_sigma_aufg6);

    // Horizontal Box Layout Canny tHi
    QWidget *panel_canny_tHi_aufg6 = new QWidget();
    QHBoxLayout *layout_canny_tHi_aufg6 = new QHBoxLayout();
    panel_canny_tHi_aufg6->setLayout(layout_canny_tHi_aufg6);
    m_option_layout_aufg6->addWidget(panel_canny_tHi_aufg6);

    // Label Canny tHi
    QLabel *label_canny_tHi_aufg6 = new QLabel("tHi Canny");
    label_canny_tHi_aufg6->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout_canny_tHi_aufg6->addWidget(label_canny_tHi_aufg6);

    // DoubleSpinBox Canny tHi
    spinbox_canny_tHi_aufg6 = new QSpinBox();
    spinbox_canny_tHi_aufg6->setMinimum(2);
    spinbox_canny_tHi_aufg6->setMaximum(255);
    spinbox_canny_tHi_aufg6->setValue(20);
    layout_canny_tHi_aufg6->addWidget(spinbox_canny_tHi_aufg6);

    // Horizontal Box Layout Canny tLo
    QWidget *panel_canny_tLo_aufg6 = new QWidget();
    QHBoxLayout *layout_canny_tLo_aufg6 = new QHBoxLayout();
    panel_canny_tLo_aufg6->setLayout(layout_canny_tLo_aufg6);
    m_option_layout_aufg6->addWidget(panel_canny_tLo_aufg6);

    // Label Canny tLo
    QLabel *label_canny_tLo_aufg6 = new QLabel("tLo Canny");
    label_canny_tLo_aufg6->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout_canny_tLo_aufg6->addWidget(label_canny_tLo_aufg6);

    // DoubleSpinBox Canny tLo
    spinbox_canny_tLo_aufg6 = new QSpinBox();
    spinbox_canny_tLo_aufg6->setMinimum(1);
    spinbox_canny_tLo_aufg6->setMaximum(255);
    spinbox_canny_tLo_aufg6->setValue(10);
    layout_canny_tLo_aufg6->addWidget(spinbox_canny_tLo_aufg6);

    // Button Canny Algorithm
    QPushButton *button_apply_canny_aufg6 = new QPushButton("Canny Algorithmus");
    QObject::connect(button_apply_canny_aufg6, SIGNAL(released()), this, SLOT(applyCannyAlgorithm()));
    m_option_layout_aufg6->addWidget(button_apply_canny_aufg6);

    QLabel *label_usm_aufg6 = new QLabel("Unsharp Masking:");
    m_option_layout_aufg6->addWidget(label_usm_aufg6);
    label_usm_aufg6->setFont(font);


    // Horizontal Box Layout USM Schärfungsgrad
    QWidget *panel_usm_schaerfungsgrad_aufg6 = new QWidget();
    QHBoxLayout *layout_usm_schaerfungsgrad_aufg6 = new QHBoxLayout();
    panel_usm_schaerfungsgrad_aufg6->setLayout(layout_usm_schaerfungsgrad_aufg6);
    m_option_layout_aufg6->addWidget(panel_usm_schaerfungsgrad_aufg6);

    // Label USM Schärfungsgrad
    QLabel *label_usm_schaerfungsgrad_aufg6 = new QLabel("Schärfungsgrad:");
    label_usm_schaerfungsgrad_aufg6->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout_usm_schaerfungsgrad_aufg6->addWidget(label_usm_schaerfungsgrad_aufg6);

    // DoubleSpinBox USM Schärfungsgrad
    spinbox_usm_schaerfungsgrad_aufg6 = new QDoubleSpinBox();
    spinbox_usm_schaerfungsgrad_aufg6->setMinimum(0.2);
    spinbox_usm_schaerfungsgrad_aufg6->setMaximum(4.0);
    spinbox_usm_schaerfungsgrad_aufg6->setValue(0.7);
    layout_usm_schaerfungsgrad_aufg6->addWidget(spinbox_usm_schaerfungsgrad_aufg6);

    // Horizontal Box Layout USM Sigma
    QWidget *panel_usm_sigma_aufg6 = new QWidget();
    QHBoxLayout *layout_usm_sigma_aufg6 = new QHBoxLayout();
    panel_usm_sigma_aufg6->setLayout(layout_usm_sigma_aufg6);
    m_option_layout_aufg6->addWidget(panel_usm_sigma_aufg6);

    // Label USM Sigma
    QLabel *label_usm_sigma_aufg6 = new QLabel("σ USM:");
    label_usm_sigma_aufg6->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout_usm_sigma_aufg6->addWidget(label_usm_sigma_aufg6);

    // DoubleSpinBox USM Sigma
    spinbox_usm_sigma_aufg6 = new QDoubleSpinBox();
    spinbox_usm_sigma_aufg6->setMinimum(0);
    spinbox_usm_sigma_aufg6->setMaximum(15);
    spinbox_usm_sigma_aufg6->setValue(1.2);
    layout_usm_sigma_aufg6->addWidget(spinbox_usm_sigma_aufg6);

    // Horizontal Box Layout USM tc
    QWidget *panel_usm_tc_aufg6 = new QWidget();
    QHBoxLayout *layout_usm_tc_aufg6 = new QHBoxLayout();
    panel_usm_tc_aufg6->setLayout(layout_usm_tc_aufg6);
    m_option_layout_aufg6->addWidget(panel_usm_tc_aufg6);

    // Label USM tc
    QLabel *label_usm_tc_aufg6 = new QLabel("tc USM:");
    label_usm_tc_aufg6->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    layout_usm_tc_aufg6->addWidget(label_usm_tc_aufg6);

    // SpinBox USM tc
    spinbox_usm_tc_aufg6 = new QSpinBox();
    spinbox_usm_tc_aufg6->setMinimum(0);
    spinbox_usm_tc_aufg6->setMaximum(255);
    spinbox_usm_tc_aufg6->setValue(15);
    layout_usm_tc_aufg6->addWidget(spinbox_usm_tc_aufg6);

    // Button USM
    QPushButton *button_apply_usm_aufg6 = new QPushButton("Unsharp Masking");
    QObject::connect(button_apply_usm_aufg6, SIGNAL(released()), this, SLOT(applyUSMSharpening()));
    m_option_layout_aufg6->addWidget(button_apply_usm_aufg6);


    return m_option_panel_aufg6;
}

QWidget* ImageViewer::houghTab(){
    QWidget *m_option_panel_u5 = new QWidget();
    QGridLayout* m_option_layout_u5 = new QGridLayout(m_option_panel_u5);
    m_option_layout_u5->setRowStretch(0|1|2|3|4|5|6|7|8,50);
    m_option_layout_u5->setColumnStretch(0|1,300);
    m_option_layout_u5->setMargin(20);

    QLabel *ueberschrift = new QLabel(tr("Hough Transformation:"));

    QFont font = ueberschrift->font();
    font.setPointSize(19);
    font.setBold(true);
    ueberschrift->setFont(font);
    font.setPointSize(16);

    angularSteps = new QLineEdit("200");
    QLabel* label_u51 = new QLabel(tr("Angular Steps: "));

    radialSteps = new QLineEdit("200");
    QLabel* label_u52 = new QLabel(tr("Radial Steps: "));

    accumulatorCount = new QLineEdit("50");
    QLabel* label_u53 = new QLabel(tr("Accumulator Count in % vom max: "));

    QLabel *label_show = new QLabel(tr("Zeige Akkumulator Array:"));
    label_show->setFont(font);


    QPushButton* button_u51 = new QPushButton();
    button_u51->setText("Unverändertes Akkumulator Array");
    QObject::connect(button_u51, SIGNAL (clicked()), SLOT (applyShowingAccuArray()));


    QPushButton* button_u52 = new QPushButton();
    button_u52->setText("Akkumulator Array mit Schwellwertoperation");
    QObject::connect(button_u52, SIGNAL (clicked()), SLOT (applyShowingAccuArrayTreshold()));

    QPushButton* button_u53 = new QPushButton();
    button_u53->setText("Akkumulator Array mit Non-Maxima Suppression");
    QObject::connect(button_u53, SIGNAL (clicked()), SLOT (applyShowingAccuArrayNonMaximaSupp()));


    QPushButton* button_u54 = new QPushButton();
    button_u54->setText("Schwellwertoperation + Non-Maxima Suppression");
    QObject::connect(button_u54, SIGNAL (clicked()), SLOT (applyShowingAccuArrayCombined()));


    QLabel *label_graden_zeichen = new QLabel(tr("Zeichne Geraden ins Bild:"));
    label_graden_zeichen->setFont(font);

    QPushButton* button_u55 = new QPushButton();
    button_u55->setText("Gefunde Geraden in das Originalbild zeichnen");
    QObject::connect(button_u55, SIGNAL (clicked()), SLOT (applyDrawingHoughLines()));

    QPushButton* button_u58 = new QPushButton();
    button_u58->setText(" Bias - Kompensation An/Aus :");
    QObject::connect(button_u58, SIGNAL (clicked()), SLOT (switchBiasKompensation()));

    label_u54 = new QLabel(tr("OFF"));

    m_option_layout_u5->addWidget(ueberschrift,1,1);
    m_option_layout_u5->addWidget(angularSteps,2,2);
    m_option_layout_u5->addWidget(label_u51,2,1);
    m_option_layout_u5->addWidget(radialSteps,3,2);
    m_option_layout_u5->addWidget(label_u52,3,1);
    m_option_layout_u5->addWidget(accumulatorCount,4,2);
    m_option_layout_u5->addWidget(label_u53,4,1);

    m_option_layout_u5->addWidget(label_show,7,1);
    m_option_layout_u5->addWidget(button_u51,8,1);
    m_option_layout_u5->addWidget(button_u52,8,2);
    m_option_layout_u5->addWidget(button_u53,9,1);
    m_option_layout_u5->addWidget(button_u54,9,2);

    m_option_layout_u5->addWidget(label_graden_zeichen,11,1);
    m_option_layout_u5->addWidget(button_u55,12,1);
    m_option_layout_u5->addWidget(button_u58,5,1);
    m_option_layout_u5->addWidget(label_u54,5,2);


    return m_option_panel_u5;
}

QWidget* ImageViewer::fourierTab(){
    QWidget *m_option_panel_fourier = new QWidget();
    QGridLayout* m_option_layout_u5 = new QGridLayout(m_option_panel_fourier);
    m_option_layout_u5->setRowStretch(0|1|2|3|4|5|6|7|8,50);
    m_option_layout_u5->setColumnStretch(0|1,300);
    m_option_layout_u5->setMargin(20);

    QLabel *ueberschrift = new QLabel(tr("Fourier Transformation:"));

    QFont font = ueberschrift->font();
    font.setPointSize(15);
    font.setBold(true);
    ueberschrift->setFont(font);
    font.setPointSize(15);

    QPushButton* do_fourier_transformation = new QPushButton();
    do_fourier_transformation->setText("Fourier Transformation:");
    QObject::connect(do_fourier_transformation, SIGNAL (clicked()), SLOT (applyFT()));

    QPushButton* do_backwarts_fourier_transformation = new QPushButton();
    do_backwarts_fourier_transformation->setText("Inverse Fourier Transformation:");
    QObject::connect(do_backwarts_fourier_transformation, SIGNAL (clicked()), SLOT (applyIFT()));

    fourierLabel = new FourierLabel();
    fourierChart = new QImage(512,512, QImage::Format_Grayscale8);
    //fourierLabel->setScaledContents(true);
    fourierLabel->setPixmap(QPixmap::fromImage(*fourierChart));


    QHBoxLayout *layout_fourier = new QHBoxLayout();

    layout_fourier->addWidget(fourierLabel);

    QLabel* eraser_label = new QLabel(tr("Radierer größe:"));
    QObject::connect(fourierLabel, SIGNAL (posChanged(QMouseEvent*)), SLOT (applyClickOnFT(QMouseEvent*)));

    eraser_slider = new QSlider(Qt::Horizontal);
    eraser_slider->setRange(1,20);
    eraser_slider->setTickInterval(1);
    eraser_slider->setValue(5);


    m_option_layout_u5->addWidget(ueberschrift,1,1);
    m_option_layout_u5->addWidget(do_fourier_transformation,2,1);
    m_option_layout_u5->addWidget(do_backwarts_fourier_transformation,2,2);
    m_option_layout_u5->addWidget(fourierLabel,4,1,1,2);

    m_option_layout_u5->addWidget(eraser_label,3,1);
    m_option_layout_u5->addWidget(eraser_slider,3,2);



    return m_option_panel_fourier;
}
