#ifndef CLIGHTINENSITY_H
#define CLIGHTINENSITY_H

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
    class CPhotoResistorSensor: public ISensorCommonInterface
#else
    class CPhotoResistorSensor: public QThread, public ISensorCommonInterface
#endif
    {
#ifndef QT
        friend void* threadRoutineLightSensor(void *arg);
#else
        Q_OBJECT
#endif

    public:

        //////////////////////////////////
        /// \brief CMoveSensor
        /// \param a_eSensorID
        /// \param a_u8EchoGPIO
        ///
        CPhotoResistorSensor(eSensorID a_eSensorID, uint8_t a_u8EchoGPIO, uint8_t a_u8Trig, uint32_t a_u32DeathZone);
        ~CPhotoResistorSensor();

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

#ifndef QT
        ////////////////////////
        /// \brief workerThread
        ///
        ///
        void workerThread();
#else
        void run();
#endif

    private:

        uint64_t countTime();

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
        uint8_t m_ui8PhotoResGPIO;

        //////////////////////
        /// \brief m_ui8Trig
        ///
        uint8_t m_ui8Trig;

        //////////////////////
        /// \brief m_fInitialized
        ///
        bool_t m_fInitialized;

        /////////////////////
        /// \brief m_u32CurrVal
        ///
        uint32_t m_u32CurrVal;

        /////////////////////////////
        /// \brief m_u32DeathZone
        ///
        const int32_t m_u32DeathZone;
    };

}
}

#endif // CLIGHTINENSITY_H
