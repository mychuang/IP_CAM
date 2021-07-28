#-------------------------------------------------
#
# Project created by QtCreator 2021-07-09T10:21:34
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = devSearch
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

win32 {
INCLUDEPATH += ../include \
               "C:\Program Files\OpenSSL\include"
LIBS += -L"C:\Program Files\OpenSSL\lib" libcrypto.lib
}

CONFIG += c++11

SOURCES += \
        dialogdevice.cpp \
        dialoglogin.cpp \
        dialoguser.cpp \
        dialoguseredit.cpp \
        main.cpp \
        mainwindow.cpp \
        secureudp.cpp \
        crypto.cpp

HEADERS += \
        dialogdevice.h \
        dialoglogin.h \
        dialoguser.h \
        dialoguseredit.h \
        mainwindow.h \
        secureudp.h \
        crypto.h \
        device.h

FORMS += \
        dialogdevice.ui \
        dialoglogin.ui \
        dialoguser.ui \
        dialoguseredit.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
