#-------------------------------------------------
#
# Project created by QtCreator 2013-03-09T06:25:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditor
TEMPLATE = app


SOURCES += main.cpp\
        texteditormainwindow.cpp \
    finddialog/finddialog.cpp \
    settingsDialog/dialog.cpp

HEADERS  += texteditormainwindow.h \
    finddialog/finddialog.h \
    finddialog/ui_finddialog.h \
    settingsDialog/dialog.h

FORMS    += texteditormainwindow.ui \
    settingsDialog/dialog.ui

RESOURCES += \
    icons.qrc
