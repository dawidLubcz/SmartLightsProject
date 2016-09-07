#ifndef CSENSORSMNGR_H
#define CSENSORSMNGR_H

#include "common.h"
#include "CAppMngr.h"
#include "IApplicationStateInterface.h"
#include "ISensorCommonInterface.h"
#include "CMoveSensor.h"
#include "CDistanceSensor.h"
#include "CPhotoResistorSensor.h"
#include "CLightIntensitySensor.h"

#include <vector>
#include <memory>

#include <chrono>

#ifdef QT
    #include <QObject>
    #include <QTimer>
#endif

namespace smartLights
{

namespace smartLightsTests
{
    class CTestMoveSensor;
}

namespace smartLightsBackend
{

    ///////////////////////////////////////////////////////////////////
    /// \brief The CSensorsMngr class
    ///
#ifndef QT
    class CSensorsMngr : public IApplicationStateInterface, public ISensorCommonInterfaceListener
#else
    class CSensorsMngr : public QObject, public IApplicationStateInterface, public ISensorCommonInterfaceListener
#endif
    {
#ifdef QT
        Q_OBJECT
#endif

        friend class smartLights::smartLightsTests::CTestMoveSensor;

    public:
        ~CSensorsMngr();

        /////////////////////////
        /// \brief init
        /// \return
        ///
        bool_t init();

        ///////////////////////
        /// \brief deinit
        /// \return
        ///
        bool_t deinit();

        //////////////////////
        /// \brief start
        ///
        void start();

        //////////////////////
        /// \brief start
        ///
        void stop();

        ///////////////////////////
        /// \brief registerListener
        /// \param a_pListener
        /// \return
        ///
        bool_t registerListener(IApplicationStateInterfaceListener *a_pListener);

        ///////////////////////////
        /// \brief deregisterListener
        /// \param a_pListener
        /// \return
        ///
        bool_t deregisterListener(IApplicationStateInterfaceListener *a_pListener);

        //////////////////////////
        /// \brief getState
        /// \return
        ///
        sCurrentState getState();

        /////////////////////////
        /// \brief getInstance
        /// \return
        ///
        static std::shared_ptr<IApplicationStateInterface> getInstance();

        ////////////////////////
        /// \brief handleSensorEvent
        /// \param a_sData
        ///
        void handleSensorEvent(ISensorCommonInterface::sSensorCommonData a_sData);

#ifdef QT
public slots:
        void timerSlot();
signals:
        void openTimeWindow();
#endif

    private:

        enum eSensorsMngr
        {
            E_SENSORS_CNTR = 2,
        };

        struct sDistanceSensorStatus
        {
            enum eDirect
            {
                E_DIRECT_NOT_SET,
                E_DIRECT_INCOMING = 1,
                E_DIRECT_OUTCOMING = 2
            };

            bool_t m_fBusy;
            eDirect m_eDirect;
        };

        typedef std::chrono::high_resolution_clock high_resolution_clock;
        typedef std::chrono::milliseconds milliseconds;

        ///////////////////////
        /// \brief CSensorsMngr
        ///
        CSensorsMngr();

        ///////////////////////
        /// \brief notifyListeners
        /// \param a_sCurrState
        ///
        void notifyListeners(sCurrentState a_sCurrState);

        ///////////////////////
        /// \brief stopTimer
        ///
        void stopTimer();

        ////////////////////////
        /// \brief handleDistanceSensor
        /// \param a_sData
        ///
        void handleDistanceSensor(ISensorCommonInterface::sSensorCommonData a_sData);
        void handleMoveSensorGate(ISensorCommonInterface::sSensorCommonData a_sData);
        void handleMoveSensorRoom(ISensorCommonInterface::sSensorCommonData a_sData);
        void handlePhotoResistor(ISensorCommonInterface::sSensorCommonData a_sData);
        void handleI2CLightSensor(ISensorCommonInterface::sSensorCommonData a_sData);

        ////////////////////////////
        /// \brief addPerson
        ///
        void notifyPersonChange(ePersonState a_eState);

        //////////////////////////
        /// \brief notifyLightIntensityChanged
        /// \param a_ui32LuxVal
        ///
        void notifyLightIntensityChanged(uint32_t a_ui32LuxVal);

        ////////////////////////////
        /// \brief m_pInstance
        ///
        static std::shared_ptr<IApplicationStateInterface> m_pInstance;

        ///////////////////////////
        /// \brief m_vpListeners
        ///
        std::vector<IApplicationStateInterfaceListener*> m_vpListeners;

        ////////////////////////////
        /// \brief m_sCurrentState
        ///
        sCurrentState m_sCurrentState;

        ///////////////////////////
        /// \brief m_vSensorsArray
        ///
        std::vector<ISensorCommonInterface*> m_vSensorsArray;

        //////////////////////////
        ///
        ///
        typedef void (CSensorsMngr::*pToHandler)(ISensorCommonInterface::sSensorCommonData);

        ////////////////////////////
        /// \brief m_oHandlersMap
        ///
        std::map <ISensorCommonInterface::eSensorID, pToHandler> m_oHandlersMap;

        ///////////////////////////
        /// \brief m_fIsRunning
        ///
        uint8_t m_u8RunningSensorsNumber;

        ///////////////////////////
        /// \brief m_u8MoveSensorsBitmask
        ///
        uint8_t m_u8MoveSensorsBitmask;

        //////////////////////////////////////
        /// \brief m_sDistanceSensorStatus
        ///
        sDistanceSensorStatus m_sDistanceSensorStatus;

        ///////////////////////////
        /// \brief m_u8MoveSensor1
        ///
        const uint8_t m_u8MoveSensorGate;
        const uint8_t m_u8MoveSensorRoom;

        bool_t m_fTimerStarted;
        bool_t m_fTimerStartedAbort;
    };
}
}
#endif // CSENSORSMNGR_H
