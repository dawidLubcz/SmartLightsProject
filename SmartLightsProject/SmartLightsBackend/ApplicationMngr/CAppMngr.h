#ifndef CAPPMNGR_H
#define CAPPMNGR_H

#include <map>
#include <memory>
#include <unistd.h>
#include <stdio.h>

#include "common.h"
#include "CMsgQueueHandler.h"
#include "CLightsInterfacesFactory.h"
#include "IApplicationStateInterface.h"
#include "CSensorsMngr.h"
#include "CTime.h"

#include "SmartLightsFrontEnd/CSmartlightsinterface.h"

#ifdef QT
#include<QTimer>
#endif

namespace smartLights
{

namespace smartLightsTests
{
    class CTestMoveSensor;
}

namespace smartLightsBackend
{
    class CMsgQueueHandler;

#ifdef QT
    class CAppMngr : public QObject, public IApplicationStateInterfaceListener
#else
    class CAppMngr : public IApplicationStateInterfaceListener
#endif
    {
#ifdef QT
        Q_OBJECT
#endif

        friend class smartLights::smartLightsTests::CTestMoveSensor;

    public:
        ////////////////////
        /// \brief CAppMngr
        ///
        CAppMngr();
    
        ////////////////////
        /// \brief create
        /// \return
        ///
        bool_t create();

        ////////////////////
        /// \brief destroy
        /// \return
        ///
        bool_t destroy();

        ////////////////////
        /// \brief init
        /// \return
        ///
        bool_t init();

        ///////////////////
        /// \brief deinit
        /// \return
        ///
        bool_t deinit();

        ///////////////////
        /// \brief run
        ///
        void run();

        ///////////////////
        /// \brief stopApp
        /// \return
        ///
        bool_t stopApp();

        ///////////////////
        /// \brief handleMessage
        /// \param a_sData
        ///
        void handleMessage(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);

        ///////////////////
        /// \brief handleStateChanged
        /// \param a_sCurrState
        ///
        void handleStateChanged(sCurrentState a_sCurrState);

        ////////////////////
        /// \brief handleLightIntesityChanged
        /// \param a_ui32LxVal
        ///
        void handleLightIntesityChanged(uint32_t a_ui32LxVal);

        ////////////////////
        /// \brief m_u8BrightnessDefault
        ///
        static const uint8_t m_u8BrightnessNotSet = 0xFF;

    private:

        /////////////////////////////////
        /// \brief The sLightState struct
        ///
        struct sLightState
        {
            bool_t isTurned;
            bool_t isAutoDimmingEnabled;
            uint32_t u16MinLuxVal;
            uint8_t u8LastPriority;
        };

        ////////////////////////////////////////
        /// \brief The sCurrentBrightness struct
        ///
        struct sCurrentBrightness
        {
            uint8_t m_u8CumulatedBr;
            uint8_t m_u8CurrentBr;
            uint8_t m_u8LastBr;
            uint8_t m_u8LastUserBr;
        };

        ///////////////////////////
        /// \brief i_call_TurnOnReq
        /// \param a_sData
        ///
        void i_call_TurnOnReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);
        void i_call_TurnOffReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);
        void i_call_WhiteReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);
        void i_call_BrightnessReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);
        void i_call_ColourReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);
        void i_call_SetAutoDimming(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);
        void i_call_SetMinLuxVal(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData);

        /////////////////////////
        /// \brief softStart
        /// \param a_sData
        /// \param a_u8MaxBr
        /// \param a_u32TimeDuring
        ///
        void softStart(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData, uint8_t a_u8MaxBr, uint32_t a_u32TimeDuring = 10);


#ifdef QT
public slots:
        ////////////////////
        /// \brief logInCSV
        /// \param a_u8Density
        /// \param a_u32Lx
        ///
        void logInCSV(quint8 a_u8Density, quint32 a_u32Lx);
        void logInCSV();
signals:
        //////////////////////
        /// \brief saveInFIle
        /// \param a_u8Density
        /// \param a_u32Lx
        ///
        void saveInFIle(quint8 a_u8Density, quint32 a_u32Lx);
        void saveInFIle();
#endif

private:

        typedef void (CAppMngr::*pToHandler)(smartLightsFrontend::CSmartLightsInterface::sData_t);

        /////////////////////////////
        /// \brief m_pMsgQueueHandler
        ///
        std::unique_ptr<CMsgQueueHandler> m_pMsgQueueHandler;
        /////////////////////////////
        /// \brief m_oFunctionsMap
        ///
        std::map < smartLightsFrontend::CSmartLightsInterface::eInterfaceMethodID, pToHandler> m_oFunctionsMap;
        /////////////////////////////
        /// \brief m_pLightSource
        ///
        std::unique_ptr<ILightSourceInterface> m_pLightSource;
        /////////////////////////////
        /// \brief m_pSensorMngr
        ///
        std::shared_ptr<IApplicationStateInterface> m_pSensorMngr;
        ////////////////////////////
        /// \brief m_sLightState
        ///
        sLightState m_sLightState;
        ////////////////////////////
        /// \brief m_sBrightness
        ///
        sCurrentBrightness m_sBrightness;
        ////////////////////////////
        /// \brief m_sCurrentState
        ///
        sCurrentState m_sCurrentState;

#ifdef QT
        ///////////////////////////
        /// \brief m_oQTimer
        ///
        QTimer m_oQTimer;
#endif

        ////////////////////////////
        /// \brief toEnum
        /// \param a_u8Data
        /// \return
        ///
        inline ILightSourceInterface::eGroup toEnum(u_int8_t a_u8Data);
    };

} //smartLightsBackend
} //smartLights

#endif // CAPPMNGR_H
