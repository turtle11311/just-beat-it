#-------------------------------------------------
#
# Project created by QtCreator 2018-04-06T16:30:44
#
#-------------------------------------------------

copydata.commands = $(COPY_DIR) $$PWD/sources/ $$OUT_PWD/sources/
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = just-beat-it
TEMPLATE = app

LIBS += -Lsources/libs/

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    mainwindow.cpp \
    menu.cpp \
    member.cpp \
    mysql.cpp \
    about.cpp \
    room.cpp

HEADERS += \
    mainwindow.h \
    menu.h \
    member.h \
    mysql.h \
    about.h \
    room.h \
    properties.h

FORMS += \
    mainwindow.ui \
    menu.ui \
    member.ui \
    about.ui \
    room.ui

RESOURCES += \
    resource.qrc

DISTFILES += \
    sources/libs/libmysqlclient.so.18 \
    sources/images/about1.png \
    sources/images/about2.png \
    sources/images/about3.png \
    sources/images/about4.png \
    sources/images/logo.png \
    sources/tools/youtube-dl
