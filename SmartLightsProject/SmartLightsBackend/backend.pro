TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

INCLUDEPATH += $$PWD/../../SmartLigthsCommon/ \

LIBS += -pthread \
        --std=c++11 \
        -lwiringPi

linux-arm-g++{
LIBS += -lwiringPi \
}

QMAKE_CXXFLAGS += \
    -lpthread \
    --std=c++11 \

QMAKE_CXXFLAGS_CXX11 -= \
    -std=c++0x \
    -std=gnu++0x \

INCLUDEPATH += $$PWD/ \

SOURCES += \
    applicationManager/CAppMngr.cpp \
    commandsSender/CMapperToLedCommand.cpp \
    commandsSender/CMessageCreator.cpp \
    commandsSender/CUDPSender.cpp \
    CMsgQueueHandler.cpp \
    main.cpp \
    commandsSender/main2.cpp \
    commandsSender/ClightsInterfacesFactory.cpp \
    commandsSender/CMilightSource.cpp \
    sensors/CSensorsMngr.cpp \
    sensors/CMoveSensor.cpp \
    sensors/CDistanceSensor.cpp \
    sensors/CLightInensity.cpp \
    #CTimer.cpp

HEADERS += \
    applicationManager/CAppMngr.h \
    commandsSender/CMapperToLedCommand.h \
    commandsSender/CMessageCreator.h \
    commandsSender/CommonTypes.h \
    commandsSender/CUDPSender.h \
    CMsgQueueHandler.h \
    commandsSender/CLightsInterfacesFactory.h \
    commandsSender/ILightSourceInterface.h \
    commandsSender/CMilightSource.h \
    sensors/CSensorsMngr.h \
    sensors/CMoveSensor.h \
    sensors/IApplicationStateInterface.h \
    sensors/ISensorCommonInterface.h \
    sensors/CDistanceSensor.h \
    sensors/CLightInensity.h \
    #CTimer.h

unix:!android {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
            target.path = /opt/$${TARGET}/bin
        }
        export(target.path)
    }
    INSTALLS += target
}

export(INSTALLS)

