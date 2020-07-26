#-------------------------------------------------
#
# Project created by QtCreator 2020-07-24T21:21:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SettingPanel
TEMPLATE = app


SOURCES += main.cpp\
        settingpanel.cpp \
    epushbutton.cpp \
    egroupbox.cpp \
    elineedit.cpp

HEADERS  += settingpanel.h \
    epushbutton.h \
    egroupbox.h \
    elineedit.h

RESOURCES += \
    settingpanel.qrc

DISTFILES += \
    background.png \
    close.png \
    close_hover.png \
    close_pressed.png \
    defend.png \
    min.png \
    min_hover.png \
    min_pressed.png \
    point.png \
    popwindow.png \
    repair.png \
    setting.png \
    start.png
