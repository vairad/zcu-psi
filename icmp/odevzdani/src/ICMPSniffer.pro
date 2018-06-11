#-------------------------------------------------
#
# Project created by QtCreator 2018-05-29T13:46:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ICMPSniffer
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

LIBS += -pthread

SOURCES += \
        main.cpp \
        gui/mainwindow.cpp \
    icmp/icmputils.cpp \
    icmp/icmpmessage.cpp \
    icmp/sender.cpp \
    gui/packettablemodel.cpp \
    gui/guimessage.cpp \
    gui/guiinterface.cpp \
    icmp/messagequeue.cpp \
    icmp/messenger.cpp \
    icmp/messagefactory.cpp \
    icmp/reciever.cpp \
    icmp/exceptions.cpp \
    gui/packetdialog.cpp \
    icmp/utils.cpp

HEADERS += \
        gui/mainwindow.h \
    icmp/icmpdefinitions.h \
    icmp/icmputils.h \
    icmp/icmpmessage.h \
    icmp/sender.h \
    errorcodes.h \
    gui/packettablemodel.h \
    gui/guimessage.h \
    gui/packetcolumnorder.h \
    gui/guiinterface.h \
    icmp/messagequeue.h \
    icmp/messenger.h \
    icmp/messagefactory.h \
    icmp/reciever.h \
    icmp/exceptions.h \
    gui/packetdialog.h \
    icmp/utils.h

FORMS += \
        gui/mainwindow.ui \
    gui/packetdialog.ui
