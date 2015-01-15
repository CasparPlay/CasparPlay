#-------------------------------------------------
#
# Project created by QtCreator 2012-04-12T13:07:49
#
#-------------------------------------------------
QT -= gui
QT += network

TARGET = caspar
TEMPLATE = lib

DEFINES += CASPAR_LIBRARY

HEADERS += \
    CasparDevice.h \
    Shared.h \
    Models/CasparThumbnail.h \
    Models/CasparTemplate.h \
    Models/CasparMedia.h \
    Models/CasparData.h \
    AmcpDevice.h
	
SOURCES += \
    CasparDevice.cpp \
    Models/CasparThumbnail.cpp \
    Models/CasparTemplate.cpp \
    Models/CasparMedia.cpp \
    Models/CasparData.cpp \
    AmcpDevice.cpp

DEPENDPATH += $$OUT_PWD/../Common $$PWD/../Common
INCLUDEPATH += $$OUT_PWD/../Common $$PWD/../Common
win32:CONFIG(release, debug|release):LIBS += -L$$OUT_PWD/../Common/release/ -lcommon
else:win32:CONFIG(debug, debug|release):LIBS += -L$$OUT_PWD/../Common/debug/ -lcommon
else:macx:LIBS += -L$$OUT_PWD/../Common/ -lcommon
else:unix:LIBS += -L$$OUT_PWD/../Common/ -lcommon
