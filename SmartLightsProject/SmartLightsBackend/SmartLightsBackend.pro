TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt
#/home/dawid/Qt5.5.1/5.5/gcc_64/mkspecs/devices/linux-rasp-SM

LIBS += -pthread \
        --std=c++11 \
       # -lwiringPi

QMAKE_CXXFLAGS += \
    -lpthread \
    --std=c++11 \

QMAKE_CXXFLAGS_CXX11 -= \
    -std=c++0x \
    -std=gnu++0x \

INCLUDEPATH += $$PWD/ \

SOURCES += \
    ApplicationMngr/CAppMngr.cpp \
    LightBulbsInterfaces/CMapperToLedCommand.cpp \
    LightBulbsInterfaces/CMessageCreator.cpp \
    LightBulbsInterfaces/CUDPSender.cpp \
    CMsgQueueHandler.cpp \
    main.cpp \
    LightBulbsInterfaces/ClightsInterfacesFactory.cpp \
    LightBulbsInterfaces/CMilightSource.cpp \
    Sensors/CSensorsMngr.cpp \
    Sensors/CMoveSensor.cpp \
    Sensors/CDistanceSensor.cpp \
    CTime.cpp \
    Sensors/CPhotoResistorSensor.cpp \
    Sensors/CLightIntensitySensor.cpp

HEADERS += \
    ApplicationMngr/CAppMngr.h \
    LightBulbsInterfaces/CMapperToLedCommand.h \
    LightBulbsInterfaces/CMessageCreator.h \
    LightBulbsInterfaces/CommonTypes.h \
    LightBulbsInterfaces/CUDPSender.h \
    CMsgQueueHandler.h \
    LightBulbsInterfaces/CLightsInterfacesFactory.h \
    LightBulbsInterfaces/ILightSourceInterface.h \
    LightBulbsInterfaces/CMilightSource.h \
    Sensors/CSensorsMngr.h \
    Sensors/CMoveSensor.h \
    Sensors/IApplicationStateInterface.h \
    Sensors/ISensorCommonInterface.h \
    Sensors/CDistanceSensor.h \
    CTime.h \
    Sensors/CPhotoResistorSensor.h \
    Sensors/CLightIntensitySensor.h

message($$PWD/../SmartLightsCommon)

INCLUDEPATH += \
    $$PWD/../SmartLightsCommon \
    $$PWD/ApplicationMngr \
    $$PWD/LightBulbsInterfaces \
    $$PWD/Sensors \
    $$PWD/.. \

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
