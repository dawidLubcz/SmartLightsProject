#include "CAppMngr.h"
#include "CLogger.h"

#include <cmath>
#include <ctime>
#include <string>

#undef PRINT_PREFIX
#define PRINT_PREFIX "SB:CAppMngr: "

namespace smartLights
{
namespace smartLightsBackend
{
    const char* g_pcCommonMsqQueueFile = "../SmartLightsCommon/smartLightsMessageQueueCommonFile";
    const char g_cProjectID = 'S' | 'L';

    CAppMngr::CAppMngr()
        : m_pMsgQueueHandler(nullptr)
        , m_oFunctionsMap()
        , m_pLightSource(nullptr)
        , m_pSensorMngr(nullptr)
        , m_sLightState{true, true, 100, E_DEFAULT_PRIO}
        , m_sBrightness{0, 0, 100, m_u8BrightnessNotSet}
        , m_sCurrentState{0, E_PERSON_DEFAULT, 100, 0}
#ifdef QT
        , m_oQTimer()
#endif
    {
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_TURN_ON_REQ,    &CAppMngr::i_call_TurnOnReq));
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_TURN_OFF_REQ,   &CAppMngr::i_call_TurnOffReq));
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_WHITE_REQ,      &CAppMngr::i_call_WhiteReq));
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_BRIGHTNESS_REQ, &CAppMngr::i_call_BrightnessReq));
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_COLOUR_REQ_E,   &CAppMngr::i_call_ColourReq));
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_COLOUR_REQ_V,   &CAppMngr::i_call_ColourReq));
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_SET_AUTO_DIMMING,    &CAppMngr::i_call_SetAutoDimming));
        m_oFunctionsMap.insert(std::make_pair(smartLightsFrontend::CSmartLightsInterface::E_SEND_SET_MINIMUM_LUX_VAL, &CAppMngr::i_call_SetMinLuxVal));

#ifdef QT
        QObject::connect(this, SIGNAL(saveInFIle(quint8, quint32)), this, SLOT(logInCSV(quint8, quint32)));
        QObject::connect(this, SIGNAL(saveInFIle()), this, SLOT(logInCSV()));
        QObject::connect(&m_oQTimer, SIGNAL(timeout()), this, SLOT(logInCSV()));
#endif
    }

    bool_t CAppMngr::create()
    {
        bool_t fRetVal = true;
        if(nullptr == m_pMsgQueueHandler)
        {
            m_pMsgQueueHandler = std::unique_ptr<CMsgQueueHandler>(  new CMsgQueueHandler( g_pcCommonMsqQueueFile
                                                    , g_cProjectID
                                                    , this ) );

            m_pLightSource = CLightsInterfacesFactory::getInterface(ILightSourceInterface::E_IF_MILIGTH);
            m_pSensorMngr  = CSensorsMngr::getInstance();
        }
        else
        {
            fRetVal = false;
        }

        PRINT_INF("create: %s",fRetVal ? "OK" : "NOK");

        return fRetVal;
    }

    bool_t CAppMngr::destroy()
    {
        // smart pointers do not require delete
        return true;
    }

    bool_t CAppMngr::init()
    {
        bool_t fRetVal = false;
        if(nullptr != m_pMsgQueueHandler &&
           nullptr != m_pSensorMngr       )
        {
            fRetVal = m_pMsgQueueHandler->init();
            fRetVal &= m_pSensorMngr->init();
            fRetVal &= m_pSensorMngr->registerListener(this);
#ifdef QT
            m_oQTimer.start(10000);
#endif
        }

        PRINT_INF("init(): %s",fRetVal ? "OK" : "NOK");

#ifndef MODULE_TESTS
    #ifdef __arm__
        PRINT_INF("init(): running from ARM DEVICE");
    #else
        PRINT_INF("init(): running from DESKTOP");
    #endif
#else
    PRINT_INF("init(): running from MODULE TESTS");
#endif

        return fRetVal;
    }

    bool_t CAppMngr::deinit()
    {
        bool_t fRetVal = false;
        if(nullptr != m_pMsgQueueHandler)
        {
            fRetVal = m_pMsgQueueHandler->stop();
            fRetVal &= m_pMsgQueueHandler->deinit();
            fRetVal &= m_pSensorMngr->deinit();
            fRetVal &= m_pSensorMngr->deregisterListener(this);
        }

        PRINT_INF("deinit(): %s",fRetVal ? "OK" : "NOK");
        return fRetVal;
    }

    void CAppMngr::run()
    {
        if(0 != m_pMsgQueueHandler)
        {
            //QTHread
            m_pMsgQueueHandler->start();
            m_pSensorMngr->start();

            PRINT_INF("run(), msgQueue running: %d", m_pMsgQueueHandler->isRunning() ? "YES" : "NO");

#ifndef QT
            do // first wait for starting thread, just in case
            {
                usleep (100000); // 100 ms
            }while(true == m_pMsgQueueHandler->isRunning());
#else
            //QTCoreApplication do it for us
#endif
        }
        else
        {
            PRINT_ERR("run() NULL m_pMsgQueueHandler");
        }
        return;
    }

    bool_t CAppMngr::stopApp()
    {
        bool_t fRetVal = false;
        if(0 != m_pMsgQueueHandler)
        {
            fRetVal = m_pMsgQueueHandler->stop();
            m_pSensorMngr->stop();
        }

        PRINT_INF("stopApp(): %s",fRetVal ? "OK" : "NOK");
        return fRetVal;
    }

    void CAppMngr::handleMessage(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        void (CAppMngr::*_pMethodPointer)(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData) = m_oFunctionsMap[static_cast<smartLightsFrontend::CSmartLightsInterface::eInterfaceMethodID>(a_sData.m_iID)];
        if(0 != _pMethodPointer)
        {
            (this->*_pMethodPointer)(a_sData);
        }
        else
        {
            PRINT_INF("handleMessage(): NULL _pMethodPointer");
        }
    }

    void CAppMngr::handleStateChanged(sCurrentState a_sCurrState)
    {
        PRINT_INF("handleStateChanged()");

        if(a_sCurrState.m_eLightState != m_sCurrentState.m_eLightState)
        {
            m_sCurrentState = a_sCurrState;

            smartLightsFrontend::CSmartLightsInterface::sData_t sData;
            sData.m_iPriority = E_SYSTEM_PRIO;
            sData.m_iGroup = 0; // ALL
            sData.m_aParams[0] = 0;

            switch (a_sCurrState.m_eLightState)
            {
                case E_PERSON_PRESENT:
                {
                    sData.m_iPriority = E_SYSTEM_PRIO;
                    sData.m_aParamsCntr = 1;

                    if(m_u8BrightnessNotSet != m_sBrightness.m_u8LastUserBr)
                    {
                        sData.m_aParams[0] = m_sBrightness.m_u8LastUserBr;
                    }
                    else
                    {
                        sData.m_aParams[0] = m_sBrightness.m_u8LastBr;
                    }

                    i_call_BrightnessReq(sData);
                }
                break;

                case E_PERSON_WENT_OUT_HIGH:
                {
                    if(m_sLightState.u8LastPriority > E_SYSTEM_PRIO)
                    {
                        sData.m_iPriority = E_USER_PRIO; // boost
                    }
                    sData.m_aParams[0] = m_sBrightness.m_u8CurrentBr/2;
                    sData.m_aParamsCntr = 1;
                    sData.m_iID = E_PERSON_WENT_OUT_HIGH;

                    i_call_BrightnessReq(sData);
                }
                break;

                case E_PERSON_WENT_OUT_LOW:
                {
                    if(m_sLightState.u8LastPriority > E_SYSTEM_PRIO)
                    {
                        sData.m_iPriority = E_USER_PRIO; // boost
                    }
                    sData.m_aParams[0] = m_sBrightness.m_u8CurrentBr/4;
                    sData.m_aParamsCntr = 1;
                    sData.m_iID = E_PERSON_WENT_OUT_LOW;

                    i_call_BrightnessReq(sData);
                }
                break;

                case E_PERSON_ABSENT:
                {
                    if(m_sLightState.u8LastPriority > E_SYSTEM_PRIO)
                    {
                        sData.m_iPriority = E_USER_PRIO; // boost
                    }

                    i_call_TurnOffReq(sData);
                    m_sLightState.u8LastPriority = E_SYSTEM_PRIO;
                }
                break;

            default:
                break;
            }
        }
        else
        {
            PRINT_INF("handleStateChanged() PEOPLE NOT CHANGED");
        }
    }

    void CAppMngr::handleLightIntesityChanged(uint32_t a_ui32LxVal)
    {
        m_sCurrentState.m_uiLightIntensityLx = a_ui32LxVal;

        if( (E_PERSON_PRESENT == m_sCurrentState.m_eLightState) &&
            (false != m_sLightState.isAutoDimmingEnabled)   )
        {
            const uint8_t u8DeathZone = 20;
            const uint8_t u8Step = 1;

            if (a_ui32LxVal > 500)
            {
                smartLightsFrontend::CSmartLightsInterface::sData_t sData;
                sData.m_iGroup = 0;
                sData.m_iPriority = E_SYSTEM_PRIO + E_BOOST_PRIO;
                i_call_TurnOffReq(sData);
            }
            else
            {
                smartLightsFrontend::CSmartLightsInterface::sData_t sData;
                sData.m_iPriority = E_SYSTEM_PRIO + E_BOOST_PRIO;
                sData.m_iGroup = 0; // ALL
                sData.m_aParamsCntr = 1;
                sData.m_aParams[0] = m_sBrightness.m_u8CurrentBr;

                if(m_sLightState.u16MinLuxVal > a_ui32LxVal)
                {
                    if((m_sBrightness.m_u8CurrentBr + u8Step) <= 100)
                    {
                        sData.m_aParams[0] = m_sBrightness.m_u8CurrentBr + u8Step;
                    }
                    else
                    {
                        sData.m_aParams[0] = 100;
                    }
                }
                else if((m_sLightState.u16MinLuxVal + u8DeathZone) < a_ui32LxVal)
                {
                    if((m_sBrightness.m_u8CurrentBr - u8Step) >= 0)
                    {
                        sData.m_aParams[0] = m_sBrightness.m_u8CurrentBr - u8Step;
                    }
                    else
                    {
                        sData.m_aParams[0] = 0;
                    }
                }

                if(sData.m_aParams[0] != m_sBrightness.m_u8CurrentBr)
                {
                    i_call_BrightnessReq(sData);

                    PRINT_WRN("handleLightIntesityChanged() set BR State: %d,currBr: %d"
                              , m_sCurrentState.m_eLightState, m_sBrightness.m_u8CurrentBr);
                }
            }
        }
    }

    void CAppMngr::i_call_TurnOnReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        PRINT_INF("i_call_TurnOnReq()");

        const int hourMin = 2, hourMax = 5;
        uint8_t localMin = 0, localHour = 0;

        CTime::getDayTimeS(localHour, localMin);

        if(nullptr != m_pLightSource && a_sData.m_iPriority >= m_sLightState.u8LastPriority)
        {
            if(hourMin <= localHour && hourMax > localHour)
            {
                softStart(a_sData, 40, 50);
            }
            else
            {
                // normal flow
                m_pLightSource->sendTurnOnReq(toEnum(a_sData.m_iGroup));
            }

            m_sLightState.isTurned = true;
            m_sLightState.u8LastPriority = a_sData.m_iPriority;

#ifdef QT
            emit saveInFIle( (m_sBrightness.m_u8LastUserBr!=m_u8BrightnessNotSet) ? m_sBrightness.m_u8LastUserBr : m_sBrightness.m_u8CurrentBr
                           , m_sCurrentState.m_uiLightIntensityLx);
#endif
        }
    }

    void CAppMngr::i_call_TurnOffReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        if(nullptr != m_pLightSource && a_sData.m_iPriority >= m_sLightState.u8LastPriority && m_sLightState.isTurned != false)
        {
            PRINT_INF("i_call_TurnOffReq(), prio: |%d|, last prio: |%d|",a_sData.m_iPriority, m_sLightState.u8LastPriority);

            m_sLightState.isTurned       = false;
            m_sLightState.u8LastPriority = a_sData.m_iPriority;
            m_sBrightness.m_u8LastBr     = m_sBrightness.m_u8CurrentBr;
            m_sBrightness.m_u8CurrentBr  = 0;

            m_pLightSource->sendTurnOffReq(toEnum(a_sData.m_iGroup));

#ifdef QT
            emit saveInFIle();
#endif
        }
        else
        {
            PRINT_INF("i_call_TurnOff(), ignore. isTurned: %d, curr: %d, pCntr: %d, currPrio:%d, lastPrio: %d"
                      , m_sLightState.isTurned, m_sBrightness.m_u8CurrentBr, a_sData.m_aParamsCntr, a_sData.m_iPriority, m_sLightState.u8LastPriority);
        }
    }

    void CAppMngr::i_call_WhiteReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        PRINT_INF("i_call_WhiteReq()");

        if(nullptr != m_pLightSource && a_sData.m_iPriority >= m_sLightState.u8LastPriority)
        {
            m_sLightState.isTurned = true;
            m_sLightState.u8LastPriority = a_sData.m_iPriority;
            m_pLightSource->sendWhiteReq(toEnum(a_sData.m_iGroup));
        }
    }

    void CAppMngr::i_call_BrightnessReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        if( nullptr != m_pLightSource                             &&
            0       <  a_sData.m_aParamsCntr                      &&
            a_sData.m_iPriority  >= m_sLightState.u8LastPriority  &&
            a_sData.m_aParams[0] != m_sBrightness.m_u8CurrentBr    )
        {
            PRINT_INF("i_call_BrightnessReq() proc: %d", a_sData.m_aParams[0]);

            if(E_PERSON_WENT_OUT_HIGH != a_sData.m_iID && E_PERSON_WENT_OUT_LOW != a_sData.m_iID)
            {
                m_sBrightness.m_u8LastBr = m_sBrightness.m_u8CurrentBr;
            }
            if(E_USER_PRIO == a_sData.m_iPriority && smartLightsFrontend::CSmartLightsInterface::E_SEND_BRIGHTNESS_REQ == a_sData.m_iID)
            {
                m_sBrightness.m_u8LastUserBr = a_sData.m_aParams[0];
            }

            m_sLightState.isTurned       = true;
            m_sLightState.u8LastPriority = a_sData.m_iPriority;
            m_sBrightness.m_u8CurrentBr  = a_sData.m_aParams[0];

            m_pLightSource->sendBrightnessReq(toEnum(a_sData.m_iGroup), a_sData.m_aParams[0]);

            if(a_sData.m_aParams[0] == 0)
                m_pLightSource->sendTurnOffReq(toEnum(a_sData.m_iGroup));

#ifdef QT
            emit saveInFIle();
#endif
        }
        else
        {
            PRINT_INF("i_call_BrightnessReq(), ignore. param: %d, curr: %d, pCntr: %d, currPrio:%d, lastPrio: %d"
                      , a_sData.m_aParams[0], m_sBrightness.m_u8CurrentBr, a_sData.m_aParamsCntr, a_sData.m_iPriority, m_sLightState.u8LastPriority);
        }
    }

    void CAppMngr::i_call_ColourReq(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        PRINT_INF("i_call_ColourReq(), colour: %d", a_sData.m_aParams[0]);

        if(nullptr != m_pLightSource && 0 < a_sData.m_aParamsCntr && a_sData.m_iPriority >= m_sLightState.u8LastPriority)
        {
            m_sLightState.isTurned = true;
            m_sLightState.u8LastPriority = a_sData.m_iPriority;
            m_pLightSource->sendColourReq(toEnum(a_sData.m_iGroup), a_sData.m_aParams[0]);
        }
    }

    void CAppMngr::i_call_SetAutoDimming(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        PRINT_INF("i_call_SetAutoDimming, param: %s", (a_sData.m_aParams[0]>0)?"ON":"OFF");

        if(nullptr != m_pLightSource && 0 < a_sData.m_aParamsCntr)
        {
            m_sLightState.isAutoDimmingEnabled = (bool_t)a_sData.m_aParams[0];
        }
    }

    void CAppMngr::i_call_SetMinLuxVal(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData)
    {
        PRINT_INF("i_call_SetMinLuxVal, param: %d", a_sData.m_aParams[0]);

        if(nullptr != m_pLightSource && 0 < a_sData.m_aParamsCntr)
        {
            m_sLightState.u16MinLuxVal = a_sData.m_aParams[0];
        }
    }

    void CAppMngr::softStart(smartLightsFrontend::CSmartLightsInterface::sData_t a_sData, uint8_t a_u8MaxBr, uint32_t a_u32TimeDuring)
    {
        const uint8_t u8SampleCntr = 20;
        const uint32_t u32Interval = a_u32TimeDuring * 1000000 / u8SampleCntr;
        const uint8_t u8Sample = (a_u8MaxBr / u8SampleCntr);

        PRINT_INF("softStart(), u8SampleCntr: |%d|, u32Interval: |%d|, u8Sample: |%d|", u8SampleCntr, u32Interval, u8Sample);

        for(uint8_t i = 0; i < u8SampleCntr; ++i)
        {
            if(nullptr != m_pLightSource)
            {
                m_pLightSource->sendBrightnessReq(toEnum(a_sData.m_iGroup), u8Sample * (i + 1));
                m_sLightState.isTurned = true;

                usleep(u32Interval);
            }
        }
    }

#ifdef QT
    void CAppMngr::logInCSV(quint8 a_u8Density, quint32 a_u32Lx)
    {
        /// int tm_sec;			/* Seconds.	[0-60] (1 leap second)
        /// int tm_min;			/* Minutes.	[0-59] */
        /// int tm_hour;			/* Hours.	[0-23] */
        /// int tm_mday;			/* Day.		[1-31] */
        /// int tm_mon;			/* Month.	[0-11] */
        /// int tm_year;			/* Year	- 1900.  */
        /// int tm_wday;			/* Day of week.	[0-6] */
        /// int tm_yday;			/* Days in year.[0-365]	*/
        /// int tm_isdst;			/* DST.		[-1/0/1]*/

        CTime oTime;
        tm localTime = oTime.getTM();

        std::string strFilename( "lifecycleStats_"
                               + std::to_string(localTime.tm_mday)
                               + "-"
                               + std::to_string(localTime.tm_mon + 1)
                               + "-"
                               + std::to_string(localTime.tm_year + 1900)
                               + ".csv"
                               );

        FILE* pFileLog = fopen(strFilename.c_str(), "a");
        fprintf( pFileLog
               , "%d:%d:%d;%d;%u\n"
               , localTime.tm_hour
               , localTime.tm_min
               , localTime.tm_sec
               , a_u8Density
               , a_u32Lx
               );

        fclose(pFileLog);
    }

    void CAppMngr::logInCSV()
    {
        logInCSV(m_sBrightness.m_u8CurrentBr, m_sCurrentState.m_uiLightIntensityLx);
    }
#endif

    ILightSourceInterface::eGroup CAppMngr::toEnum(u_int8_t a_u8Data)
    {
        return static_cast<ILightSourceInterface::eGroup>(a_u8Data);
    }
}
}

