#-------------------------------------------------
#
# Project created by QtCreator 2020-07-18T19:16:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cell.cpp \
    finddialog.cpp \
    gotocelldialog.cpp \
    sortdialog.cpp \
    spreadsheet.cpp

HEADERS  += mainwindow.h \
    cell.h \
    finddialog.h \
    gotocelldialog.h \
    sortdialog.h \
    spreadsheet.h \
    ui_gotocelldialog.h \
    ui_gotocelldialog.h.autosave \
    ui_sortdialog.h \
    QtGUI.h

RESOURCES += \
    spreadsheet.qrc

FORMS += \
    gotocelldialog.ui \
    sortdialog.ui

DISTFILES += \
    3.pro.user
