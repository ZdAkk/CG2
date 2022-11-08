QT += widgets
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer-qt5.h \
    Sheet1/pixeloperations.h \
    Sheet2/filteroperations.h \
    Sheet3/edgefilter.h \
    Sheet4/hough.h \
    Sheet5/fourier.h \
    Examples/examples1.h \
    Examples/examples2.h \
    FreeMemory/freememory.h \
    GUI/fourierlabel.h \
    GUI/tabs.h
SOURCES       = imageviewer-qt5.cpp \
                Sheet1/pixeloperations.cpp \
                Sheet2/filteroperations.cpp \
                Sheet3/edgefilter.cpp \
                Sheet4/hough.cpp \
                Sheet5/fourier.cpp \
                Examples/examples1.cpp \
                Examples/examples2.cpp \
                FreeMemory/freememory.cpp \
                GUI/fourierlabel.cpp \
                GUI/tabs.cpp \
                imageviewer-main-qt5.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target

wince*: {
   DEPLOYMENT_PLUGIN += qjpeg qgif
}
CONFIG += c++17
