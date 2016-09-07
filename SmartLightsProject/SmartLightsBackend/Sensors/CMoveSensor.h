#ifndef CMOVESENSOR_H
#define CMOVESENSOR_H

#include "ISensorCommonInterface.h"

#include <chrono>

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
    class CMoveSensor: public ISensorCommonInterface
#else
    class CMoveSensor: public QThread, public ISensorCommonInterface
#endif
    {
#ifndef QT
        friend void *threadRoutineMotionSensor(void *arg);
#else
        Q_OBJECT
#endif

    public:
        enum ePinValues
        {
            E_MOVE_DEFAULT = 0xFF
        };

        class CMoveSensorData
        {
        public:
            uint8_t m_u8PinVal;
            uint64_t m_u64msec;

            CMoveSensorData(uint8_t pinVal)
            {
                m_u8PinVal = pinVal;
            }
        };

        //////////////////////////////////
        /// \brief CMoveSensor
        /// \param a_eSensorID
        /// \param a_u8EchoGPIO
        ///
        CMoveSensor(eSensorID a_eSensorID, uint8_t a_u8EchoGPIO, uint8_t a_u8LedGPIO);
        ~CMoveSensor();

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

        typedef std::chrono::high_resolution_clock high_resolution_clock;
        typedef std::chrono::milliseconds milliseconds;

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

        ///////////////////////
        /// \brief m_iCurrent
        ///
        uint8_t m_iCurrent;

        //////////////////////
        /// \brief m_eSensorID
        ///
        eSensorID m_eSensorID;

        //////////////////////
        /// \brief m_ui8EchoGPIO
        ///
        uint8_t m_ui8EchoGPIO;

        //////////////////////
        /// \brief m_fInitialized
        ///
        bool_t m_fInitialized;

        ///////////////////////
        /// \brief m_ui8LedGPIO
        ///
        uint8_t m_ui8LedGPIO;
    };

}
}

#endif // CMOVESENSOR_H
