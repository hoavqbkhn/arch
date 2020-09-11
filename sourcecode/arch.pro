#-------------------------------------------------
#
# Project created by QtCreator 2019-12-01T18:04:22
#
#-------------------------------------------------

QT       -= gui
QT += serialport
QT += quick
QT += sql concurrent
TARGET = arch
TEMPLATE = lib
CONFIG += c++14 console
CONFIG -= app_bundle
DEFINES += ARCH_LIBRARY

#Check os architect: 32 bit or 64 bit, uncheck shadow build in build setting to use this feature
linux-g++:QMAKE_TARGET.arch = $$QMAKE_HOST.arch
linux-g++-32:QMAKE_TARGET.arch = x86
linux-g++-64:QMAKE_TARGET.arch = x86_64

DESTDIR = ''
contains(QMAKE_TARGET.arch, x86) {
    DESTDIR = ../archlib_32/

} else {
    DESTDIR = ../archlib_64/
}

OBJECTS_DIR = $$DESTDIR/
MOC_DIR  = $$DESTDIR/
RCC_DIR = $$DESTDIR/
UI_DIR = $$DESTDIR/



# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#spdlog
INCLUDEPATH += $$PWD/logger/spdlog
DEPENDPATH += $$PWD/logger/spdlog

SOURCES += \
    architectureabs/multiioprocessor.cpp \
    architectureabs/processorabstract.cpp \
    architectureabs/processormanager.cpp \
    architectureabs/singleioprocessor.cpp \
    codecabs/iocodec.cpp \
    connectorabs/ioconnector.cpp \
    connectorabs/natsconnector.cpp \
    connectorabs/serialconnector.cpp \
    connectorabs/tcpclientconnector.cpp \
    connectorabs/udpserverconnector.cpp \
    db/appdbaction.cpp \
    db/db_constant.cpp \
    db/dbmanager.cpp \
    db/dbresult.cpp \
    db/dbutil.cpp \
    db/dmessage.cpp \
    db/migration.cpp \
    db/querydb.cpp \
    db/queryhelper.cpp \
    messageabs/innermessage.cpp \
    messageabs/iorawmessage.cpp \
    helper/bytebuffer.cpp \
    logger/logger.cpp \
    architectureabs/workerthread.cpp \
    architectureabs/failtoleranceioprocessor.cpp \
    recorder/recorderscreen.cpp

HEADERS += \
    architectureabs/multiioprocessor.h \
    architectureabs/processorabstract.h \
    architectureabs/processormanager.h \
    architectureabs/singleioprocessor.h \
    codecabs/iocodec.h \
    connectorabs/ioconnector.h \
    connectorabs/natsconnector.h \
    connectorabs/serialconnector.h \
    connectorabs/tcpclientconnector.h \
    connectorabs/udpserverconnector.h \
    db/appdbaction.h \
    db/db_constant.h \
    db/dbmanager.h \
    db/dbresult.h \
    db/dbutil.h \
    db/dmessage.h \
    db/migration.h \
    db/querydb.h \
    db/queryhelper.h \
    messageabs/innermessage.h \
    messageabs/iorawmessage.h \
    helper/bytebuffer.h \
    logger/logger.h \
    commondef.h \
    architectureabs/workerthread.h \
    architectureabs/failtoleranceioprocessor.h \
    helper/stdendian.h \
    recorder/recorderscreen.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    logger/spdlog/contrib/README.md \
    logger/spdlog/fmt/bundled/LICENSE.rst

contains(QMAKE_TARGET.arch, x86) {
    unix:!macx: LIBS += -L$$PWD/../../cnat/lib_32/ -lnats
} else {
    unix:!macx: LIBS += -L$$PWD/../../cnat/lib_64/ -lnats
}
INCLUDEPATH += $$PWD/../../cnat/include
DEPENDPATH += $$PWD/../../cnat/include
#lib stream video
#============= opencv
#INCLUDEPATH += /usr/local/include/opencv
LIBS += `pkg-config --libs opencv`
#LIBS += lopencv

#============= gstreamer-1.0
INCLUDEPATH += /usr/include/gstreamer-1.0
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/gstreamer-1.0/include
INCLUDEPATH += /usr/include/glib-2.0
INCLUDEPATH += /usr/lib/x86_64-linux-gnu/glib-2.0/include
# Full range of gstreamer libs
LIBS += -lgstapp-1.0 -lgstbase-1.0 -lgstreamer-1.0 -lgobject-2.0 -lglib-2.0 -lgstpbutils-1.0 -lgstvideo-1.0
LIBS += -ludev

