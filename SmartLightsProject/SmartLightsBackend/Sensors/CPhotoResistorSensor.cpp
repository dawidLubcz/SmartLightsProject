#include "CPhotoResistorSensor.h"

#include "../../SmartLightsCommon/CLogger.h"
#include <unistd.h>
#include <cmath>

#ifdef QT
    #include <QElapsedTimer>
#endif

#ifdef __arm__
    #include <wiringPi.h>
#endif

#undef PRINT_PREFIX
#define PRINT_PREFIX "SM:CLightIntensity: "

namespace smartLights
{
namespace smartLightsBackend
{

#ifndef QT
    void* threadRoutinephotoRSensor(void *arg)
    {
        CPhotoResistorSensor* pTmp = static_cast<CPhotoResistorSensor*>(arg);
        pTmp->workerThread();
        return arg;
    }
#endif

    CPhotoResistorSensor::CPhotoResistorSensor(smartLights::smartLightsBackend::ISensorCommonInterface::eSensorID a_eSensorID, uint8_t a_u8EchoGPIO, uint8_t a_u8Trig, uint32_t a_u32DeathZone)
        : m_pParent(nullptr)
#ifndef QT
        , m_oThreadWorker(0)
        , m_oAttr()
#endif
        , m_fRun(false)
        , m_iCurrent(0)
        , m_eSensorID(a_eSensorID)
        , m_ui8PhotoResGPIO(a_u8EchoGPIO)
        , m_ui8Trig(a_u8Trig)
        , m_fInitialized(false)
        , m_u32CurrVal(0)
        , m_u32DeathZone(a_u32DeathZone)
    {
    }

    CPhotoResistorSensor::~CPhotoResistorSensor()
    {

    }

    bool_t CPhotoResistorSensor::setParentPoiter(smartLights::smartLightsBackend::ISensorCommonInterfaceListener *a_pParent)
    {
        bool_t fRetval = false;
        if(nullptr != a_pParent)
        {
            m_pParent = a_pParent;
            fRetval = true;
        }
        return fRetval;
    }

    bool_t CPhotoResistorSensor::init()
    {
        PRINT_INF("init()");

#ifdef __arm__
        pullUpDnControl(m_ui8PhotoResGPIO, PUD_DOWN);
        pinMode(m_ui8Trig, OUTPUT);
#endif

#ifndef QT
        pthread_attr_init(&m_oAttr);
        pthread_attr_setdetachstate(&m_oAttr, PTHREAD_CREATE_JOINABLE);
#endif

        m_fInitialized = true;

        return true;
    }

    bool_t CPhotoResistorSensor::deinit()
    {
        bool_t fResult = false;
        if(false != m_fInitialized)
        {
            stopThread();
#ifndef QT
            pthread_attr_destroy(&m_oAttr);
#endif
            m_fInitialized = false;
            fResult = true;
        }
        return fResult;
    }

    ISensorCommonInterface::eReturnValue CPhotoResistorSensor::isAvailable()
    {
        return E_NOT_IMPLEMENTED;
    }

    ISensorCommonInterface::eReturnValue CPhotoResistorSensor::isActive()
    {
        return (m_fRun == false) ? E_FALSE : E_TRUE;
    }

#ifndef QT
    ISensorCommonInterface::eReturnValue CPhotoResistorSensor::start()
    {
        PRINT_INF("start()");

        eReturnValue eRetVal = E_FALSE;

        if(false != m_fInitialized)
        {
            int iRetVal = pthread_create(&m_oThreadWorker, &m_oAttr, threadRoutinephotoRSensor, (void*)this);
            if(iRetVal)
            {
                PRINT_ERR("startInThread(), pthread_create FAILED");
            }
            else
            {
                eRetVal = E_TRUE;
            }
        }
        else
        {
            PRINT_ERR("startInThread(), NOT INITIALIZED");
        }

        return eRetVal;
    }
#else
    ISensorCommonInterface::eReturnValue CPhotoResistorSensor::start()
    {
        QThread::start();
        return E_TRUE;
    }
#endif

    ISensorCommonInterface::eReturnValue CPhotoResistorSensor::stopThread()
    {
        PRINT_INF("stopThread, run: %d", m_fRun);

        if(m_fRun)
        {
            m_fRun = false;
#ifndef QT
            pthread_join(m_oThreadWorker, 0);
#endif
        }
        return E_TRUE;
    }

    ISensorCommonInterface::eReturnValue CPhotoResistorSensor::unleashSensor(uint8_t, uint32_t)
    {
        return E_NOT_IMPLEMENTED;
    }

    ISensorCommonInterface::eSensorID CPhotoResistorSensor::getSensorID()
    {
        return m_eSensorID;
    }

#ifndef QT
    void CPhotoResistorSensor::workerThread()
#else
    void CPhotoResistorSensor::run()
#endif
    {
        m_fRun = true;

        while(false != m_fRun)
        {
            countTime();

            usleep(3000000); // 3s
        }
#ifndef QT
        pthread_exit(0);
#endif
    }

    uint64_t CPhotoResistorSensor::countTime()
    {
#ifdef __arm__
#ifdef QT
        QElapsedTimer qTimer;
#endif
        uint64_t u64MilisecondsElapsed = 0;

        pinMode(m_ui8PhotoResGPIO, OUTPUT);
        digitalWrite(m_ui8PhotoResGPIO, LOW);

        usleep(1000000); // 100ms for unloading C

        pinMode(m_ui8PhotoResGPIO, INPUT);
        digitalWrite(m_ui8Trig, HIGH);
#ifdef QT
        qTimer.start();
#endif
        while(LOW == digitalRead(m_ui8PhotoResGPIO))
        {  /* just wait */  }
        digitalWrite(m_ui8Trig, LOW);
#ifdef QT
        u64MilisecondsElapsed = qTimer.nsecsElapsed(); // elapsed time in ns
#else
        PRINT_ERR("Light measure works only with QT");
#endif

        uint32_t R = ((double)u64MilisecondsElapsed)/1000 * 5.00; // t ~= 5*R*C

        if(abs(m_u32CurrVal - R) > m_u32DeathZone)
        {
            if(nullptr != m_pParent)
            {
               // sSensorCommonData sData;
               // sData.m_iSensorID = m_eSensorID;
               // sData.m_pvData = (void*)(new uint32_t(R));
                //m_pParent->handleSensorEvent(sData);
            }
            m_u32CurrVal = R;
        }
        //PRINT_INF("ns: %llu, R: %u",u64MilisecondsElapsed, R);

        return u64MilisecondsElapsed;
#else
        return 0.00;
#endif
    }

}
}
