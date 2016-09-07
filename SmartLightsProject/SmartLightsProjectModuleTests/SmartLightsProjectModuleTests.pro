QT += core
QT -= gui

TARGET = SmartLightsProjectModuleTests
CONFIG += console
CONFIG -= app_bundle


QMAKE_CXXFLAGS += \
    -lpthread \
    --std=c++11

LIBS += --std=c++11

TEMPLATE = app

SOURCES += main.cpp \
    ctestmovesensor.cpp \
    ../SmartLightsBackend/ApplicationMngr/CAppMngr.cpp \
    ../SmartLightsBackend/LightBulbsInterfaces/ClightsInterfacesFactory.cpp \
    ../SmartLightsBackend/LightBulbsInterfaces/CMapperToLedCommand.cpp \
    ../SmartLightsBackend/LightBulbsInterfaces/CMessageCreator.cpp \
    ../SmartLightsBackend/LightBulbsInterfaces/CMilightSource.cpp \
    ../SmartLightsBackend/LightBulbsInterfaces/CUDPSender.cpp \
    ../SmartLightsBackend/Sensors/CDistanceSensor.cpp \
    ../SmartLightsBackend/Sensors/CLightIntensitySensor.cpp \
    ../SmartLightsBackend/Sensors/CMoveSensor.cpp \
    ../SmartLightsBackend/Sensors/CPhotoResistorSensor.cpp \
    ../SmartLightsBackend/Sensors/CSensorsMngr.cpp \
    ../SmartLightsBackend/CMsgQueueHandler.cpp \
    ../SmartLightsBackend/CTime.cpp

HEADERS += \
    ctestmovesensor.h \
    ../SmartLightsBackend/ApplicationMngr/CAppMngr.h \
    ../SmartLightsBackend/LightBulbsInterfaces/CLightsInterfacesFactory.h \
    ../SmartLightsBackend/LightBulbsInterfaces/CMapperToLedCommand.h \
    ../SmartLightsBackend/LightBulbsInterfaces/CMessageCreator.h \
    ../SmartLightsBackend/LightBulbsInterfaces/CMilightSource.h \
    ../SmartLightsBackend/LightBulbsInterfaces/CommonTypes.h \
    ../SmartLightsBackend/LightBulbsInterfaces/CUDPSender.h \
    ../SmartLightsBackend/LightBulbsInterfaces/ILightSourceInterface.h \
    ../SmartLightsBackend/Sensors/CDistanceSensor.h \
    ../SmartLightsBackend/Sensors/CLightIntensitySensor.h \
    ../SmartLightsBackend/Sensors/CMoveSensor.h \
    ../SmartLightsBackend/Sensors/CPhotoResistorSensor.h \
    ../SmartLightsBackend/Sensors/CSensorsMngr.h \
    ../SmartLightsBackend/Sensors/IApplicationStateInterface.h \
    ../SmartLightsBackend/Sensors/ISensorCommonInterface.h \
    ../SmartLightsBackend/CMsgQueueHandler.h \
    ../SmartLightsBackend/CTime.h

INCLUDEPATH += \
    $$PWD/../SmartLightsCommon \
    $$PWD/.. \
    $$PWD/../SmartLightsBackend \
    $$PWD/../SmartLightsBackend/ApplicationMngr \
    $$PWD/../SmartLightsBackend/LightBulbsInterfaces \
    $$PWD/../SmartLightsBackend/Sensors \
    $$PWD/../SmartLightsCommon \

DEFINES += MODULE_TESTS
