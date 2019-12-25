#-------------------------------------------------
#
# Project created by QtCreator 2019-12-16T18:38:00
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyMediaPlayer
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
        main.cpp \
        mainwidget.cpp \
    songlist.cpp \
    scoredialog.cpp \
    searchdialog.cpp \
    adddialog.cpp \
    minimizewidget.cpp \
    modifydialog.cpp \
    thankdialog.cpp

HEADERS += \
        mainwidget.h \
    songlist.h \
    scoredialog.h \
    searchdialog.h \
    adddialog.h \
    minimizewidget.h \
    modifydialog.h \
    thankdialog.h

FORMS += \
        mainwidget.ui \
    scoredialog.ui \
    searchdialog.ui \
    adddialog.ui \
    minimizewidget.ui \
    modifydialog.ui \
    thankdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    imageresource.qrc
