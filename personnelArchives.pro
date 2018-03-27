#-------------------------------------------------
#
# Project created by QtCreator 2017-09-27T22:27:15
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = personnelArchives
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    accessdb.cpp \
    maintableview.cpp \
    searchdlg.cpp \
    archivesdlg.cpp \
    archivestablemodel.cpp \
    readonlydelegate.cpp \
    mysqldb.cpp

HEADERS  += mainwindow.h \
    accessdb.h \
    maintableview.h \
    searchdlg.h \
    archivesdlg.h \
    archivestablemodel.h \
    readonlydelegate.h \
    mysqldb.h \
    mysqldb.h

FORMS    += mainwindow.ui \
    searchdlg.ui \
    archivesdlg.ui

RESOURCES += \
    myimages.qrc
