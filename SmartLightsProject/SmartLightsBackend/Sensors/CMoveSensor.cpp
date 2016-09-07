#include "CMoveSensor.h"
#include <stdio.h>
#include <unistd.h>

#include "CLogger.h"

#ifdef __arm__
    #include <wiringPi.h>
#endif

#undef PRINT_PREFIX
#define PRINT_PREFIX "SB:CMoveSensor: "

namespace smartLights
{
namespace smartLightsBackend
{

#ifndef QT
    void* threadRoutineMotionSensor(void *arg)
    {
        CMoveSensor* pTmp = static_cast<CMoveSensor*>(arg);
        pTmp->workerThread();
        return arg;
    }
#endif

    CMoveSensor::CMoveSensor(ISensorCommonInterface::eSensorID a_eSensorID, uint8_t a_u8EchoGPIO, uint8_t a_u8LedGPIO)
        : m_pParent(nullptr)
#ifndef QT
        , m_oThreadWorker(0)
        , m_oAttr()
#endif
        , m_fRun(false)
        , m_iCurrent(0)
        , m_eSensorID(a_eSensorID)
        , m_ui8EchoGPIO(a_u8EchoGPIO)
        , m_fInitialized(false)
        , m_ui8LedGPIO(a_u8LedGPIO)
    {

    }

    CMoveSensor::~CMoveSensor()
    {

    }

    bool_t CMoveSensor::setParentPoiter(smartLights::smartLightsBackend::ISensorCommonInterfaceListener *a_pParent)
    {
        bool_t fRetval = false;
        if(nullptr != a_pParent)
        {
            m_pParent = a_pParent;
            fRetval = true;
        }
        return fRetval;
    }

    bool_t CMoveSensor::init()
    {
        PRINT_INF("init()");

#ifdef __arm__
        pinMode(m_ui8EchoGPIO, INPUT); //17
        //pinMode(m_ui8LedGPIO, OUTPUT); //27
#endif

#ifndef QT
        pthread_attr_init(&m_oAttr);
        pthread_attr_setdetachstate(&m_oAttr, PTHREAD_CREATE_JOINABLE);
#endif

        m_fInitialized = true;

        return true;
    }

    bool_t CMoveSensor::deinit()
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

    ISensorCommonInterface::eReturnValue CMoveSensor::isAvailable()
    {
        return E_NOT_IMPLEMENTED;
    }

    ISensorCommonInterface::eReturnValue CMoveSensor::isActive()
    {
        return (m_fRun == false) ? E_FALSE : E_TRUE;
    }

#ifndef QT
    ISensorCommonInterface::eReturnValue CMoveSensor::start()
    {
        PRINT_INF("CMoveSensor::start");

        eReturnValue eRetVal = E_FALSE;

        if(false != m_fInitialized)
        {
            int iRetVal = pthread_create(&m_oThreadWorker, &m_oAttr, threadRoutineMotionSensor, (void*)this);
            if(iRetVal)
            {
                PRINT_ERR("CMoveSensor::start, pthread_create FAILED");
            }
            else
            {
                eRetVal = E_TRUE;
            }
        }
        else
        {
            PRINT_ERR("CMoveSensor::startInThread, NOT INITIALIZED");
        }

        return eRetVal;
    }
#else
    ISensorCommonInterface::eReturnValue CMoveSensor::start()
    {
        QThread::start();
        return E_TRUE;
    }
#endif

    ISensorCommonInterface::eReturnValue CMoveSensor::stopThread()
    {
        PRINT_INF("stop(), frun: %d", m_fRun);

        if(m_fRun)
        {
            m_fRun = false;
#ifndef QT
            pthread_join(m_oThreadWorker, 0);
#endif
        }
        return E_TRUE;
    }

    ISensorCommonInterface::eReturnValue CMoveSensor::unleashSensor(uint8_t , uint32_t )
    {
        return E_NOT_SUPPORTED;
    }

    ISensorCommonInterface::eSensorID CMoveSensor::getSensorID()
    {
        return m_eSensorID;
    }

#ifndef QT
    void CMoveSensor::workerThread()
#else
    void CMoveSensor::run()
#endif
    {
        m_fRun = true;
        while(false != m_fRun)
        {
#ifdef __arm__
            static long long int cntr = 0;
            static bool x = false;
            uint8_t pinVal = digitalRead(m_ui8EchoGPIO);

            if(cntr%100 == 0)
            {
                //printf("CMoveSensor:workerThread, pin 11 val: |%d|, currentVal: |%d|\n",pinVal,m_iCurrent);
                x = !x;
                //digitalWrite(m_ui8LedGPIO, (int)x);
            }
            ++cntr;
#else
            uint8_t pinVal = 0;
#endif

            if(m_iCurrent != pinVal)
            {
                if(nullptr != m_pParent)
                {
                    sSensorCommonData sData;
                    sData.m_iSensorID = m_eSensorID;
                    sData.m_pvData = (void*)(new CMoveSensorData(pinVal));

                    m_pParent->handleSensorEvent(sData);
                }
                m_iCurrent = pinVal;
            }

            usleep (10000); // 10 ms
        }

#ifndef QT
        pthread_exit(0);
#endif
    }

}
}
