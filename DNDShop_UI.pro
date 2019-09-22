#-------------------------------------------------
#
# Project created by QtCreator 2019-05-23T14:23:22
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DAndDShop_UI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        src/cpp/itembase.cpp \
        src/cpp/main.cpp \
        src/cpp/settingswindow.cpp \
        src/cpp/shopbase.cpp \
        src/cpp/shopwindow.cpp

HEADERS += \
        src/cpp/itembase.h \
        src/cpp/settingswindow.h \
        src/cpp/shopbase.h \
        src/cpp/shopwindow.h


FORMS += \
        src/ui/settingswindow.ui \
        src/ui/shopwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
    
QMAKE_CXXFLAGS += -static
RESOURCES +=  \
    resc/resources.qrc

