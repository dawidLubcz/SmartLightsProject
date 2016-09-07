TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    chmisignalhandler.cpp \
    ../SmartLightsFrontEnd/CSmartlightsinterface.cpp

RESOURCES += qml.qrc

LIBS += \
    -std=c++11 \

#INCLUDEPATH += ../smartLightsFronEnd/ \

#PRE_TARGETDEPS += ../smartLightsFronEnd/CSmartlightsinterface.o \

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    chmisignalhandler.h \
    ../SmartLightsFrontEnd/CSmartlightsinterface.h

