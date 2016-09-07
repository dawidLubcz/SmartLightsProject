#ifndef CLIGHTINTENSITYSENSOR_H
#define CLIGHTINTENSITYSENSOR_H

#include "ISensorCommonInterface.h"
#include <time.h>

#ifndef QT
    #include <pthread.h>
#else
    #include <QThread>
#endif

namespace smartLights
{
namespace smartLightsBackend
{

    ////////////////////////////////////////////////
    /// \brief The CMoveSensor class
    ///
#ifndef QT
    class CLightIntensitySensor: public ISensorCommonInterface
#else
    class CLightIntensitySensor: public QThread, public ISensorCommonInterface
#endif
    {
#ifndef QT
        friend void* threadRoutineLightSensor(void *arg);
#else
        Q_OBJECT
#endif

    public:
        static const uint8_t POWER_DOWN = 0;
        static const uint8_t POWER_UP = 0x1;

        // Start measurement at 4lx resolution. Time typically 16ms.
        static const uint8_t CONTINUOUS_LOW_RES_MODE = 0x13;
        // Start measurement at 1lx resolution. Time typically 120ms
        static const uint8_t CONTINUOUS_HIGH_RES_MODE_1 = 0x10;
        // Start measurement at 0.5lx resolution. Time typically 120ms
        static const uint8_t CONTINUOUS_HIGH_RES_MODE_2 = 0x11;
        // Start measurement at 1lx resolution. Time typically 120ms
        // Device is automatically set to Power Down after measurement.
        static const uint8_t ONE_TIME_HIGH_RES_MODE_1 = 0x20;
        // Start measurement at 0.5lx resolution. Time typically 120ms
        // Device is automatically set to Power Down after measurement.
        static const uint8_t ONE_TIME_HIGH_RES_MODE_2 = 0x21;
        // Start measurement at 1lx resolution. Time typically 120ms
        // Device is automatically set to Power Down after measurement.
        static const uint8_t ONE_TIME_LOW_RES_MODE = 0x23;

        //////////////////////////////////
        /// \brief CMoveSensor
        /// \param a_eSensorID
        /// \param a_u8EchoGPIO
        ///
        CLightIntensitySensor(eSensorID a_eSensorID, uint8_t m_ui8I2CDeviceAddress, uint8_t a_u8DeathZOne);
        ~CLightIntensitySensor();

        /////////////////////////////////
        /// \brief setParentPoiter
        /// \param a_pParent
        /// \return
        ///
        bool_t setParentPoiter(ISensorCommonInterfaceListener *a_pParent);

        ////////////////////////////////
        /// \brief init
        /// \return
        ///
        bool_t init();

        ///////////////////////////////
        /// \brief deinit
        /// \return
        ///
        bool_t deinit();

        //////////////////////////////
        /// \brief isAvailable
        /// \return
        ///
        eReturnValue isAvailable();

        /////////////////////////////
        /// \brief isActive
        /// \return
        ///
        eReturnValue isActive();

        ////////////////////////////
        /// \brief startInThread
        /// \return
        ///
        eReturnValue start();

        ///////////////////////////
        /// \brief stopThread
        /// \return
        ///
        eReturnValue stopThread();

        //////////////////////////
        /// \brief unleashSensor
        /// \param a_u8Repeat
        /// \param a_u32TimePeriod
        /// \return
        ///
        eReturnValue unleashSensor(uint8_t, uint32_t);

        /////////////////////////
        /// \brief getSensorID
        /// \return
        ///
        eSensorID getSensorID();

    private:

#ifndef QT
        ////////////////////////
        /// \brief workerThread
        ///
        void workerThread();
#else
        void run();
#endif
        ///////////////////////
        /// \brief m_pParent
        ///
        ISensorCommonInterfaceListener * m_pParent;

#ifndef QT
        ///////////////////////
        /// \brief m_oThreadWorker
        ///
        pthread_t m_oThreadWorker;

        //////////////////////
        /// \brief m_oAttr
        ///
        pthread_attr_t m_oAttr;
#endif

        ////////////////////////
        /// \brief m_fRun
        ///
        bool_t m_fRun;

        //////////////////////
        /// \brief m_eSensorID
        ///
        eSensorID m_eSensorID;

        //////////////////////
        /// \brief m_ui8EchoGPIO
        ///
        uint8_t m_ui8I2CDeviceAddress;

        ////////////////////////////////
        /// \brief m_i32I2CDeviceDescriptor
        ///
        int32_t m_i32I2CDeviceDescriptor;

        //////////////////////
        /// \brief m_fInitialized
        ///
        bool_t m_fInitialized;

        ///////////////////////
        /// \brief m_ui32CurrentVal
        ///
        uint32_t m_ui32CurrentVal;

        ////////////////////////////
        /// \brief m_u8DeathZone
        ///
        const uint8_t m_u8DeathZone;
    };

}
}

#endif // CLIGHTINTENSITYSENSOR_H
