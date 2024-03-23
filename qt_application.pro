#-------------------------------------------------
#
# Project created by QtCreator 2023-08-07T17:00:53
#
#-------------------------------------------------

QT       += core gui serialport network widgets

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = qt_application
TEMPLATE = app

requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

SOURCES += main.cpp\
    maindlg.cpp \
    can_drv.cpp \
    canreceivethread.cpp \
    cansendthread.cpp \
    page1.cpp \
    mthread.cpp \
    colortest.cpp \
    flatui.cpp \
    rtc.cpp \
    autoimage.cpp \
    touch.cpp \
    systimer_drv.cpp

HEADERS  += maindlg.h \
    can_drv.h \
    canreceivethread.h \
    cansendthread.h \
    systimer_drv.h \
    page1.h \
    mthread.h \
    colortest.h \
    flatui.h \
    rtc.h \
    backlight.h \
    autoimage.h \
    touch.h

FORMS    += \
    page1.ui \
    colortest.ui \
    rtc.ui \
    maindlg.ui \
    autoimage.ui \
    touch.ui

#target.path = /opt
#INSTALLS += target

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \


