QT += core gui bluetooth opengl

greaterThan(QT_MAJOR_VERSION, 4) : QT += widgets printsupport

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/lightsaber.cpp \
    src/bluetoothconnectionwindow.cpp \
    src/btclient.cpp \
    src/openglobj.cpp \
    src/layout.cpp \
    src/qcustomplot.cpp \
    src/plotter.cpp

HEADERS += \
    inc/mainwindow.h \
    inc/lightsaber.h \
    inc/bluetoothconnectionwindow.h \
    inc/btclient.h \
    inc/bluetoothdeviceitem.h \
    inc/openglobj.h \
    inc/layout.h \
    inc/qcustomplot.h \
    inc/plotter.h


FORMS +=

RESOURCES +=
