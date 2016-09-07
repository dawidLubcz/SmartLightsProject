#include "CLightIntensitySensor.h"

#include "../../SmartLightsCommon/CLogger.h"
#include <unistd.h>
#include <cmath>

#ifdef __arm__
    #include <wiringPiI2C.h>
#endif

#undef PRINT_PREFIX
#define PRINT_PREFIX "SM:CLightIntensity: "

namespace smartLights
{
namespace smartLightsBackend
{

#ifndef QT
    void* threadRoutineLightSensor(void *arg)
    {
        CLightIntensitySensor* pTmp = static_cast<CLightIntensitySensor*>(arg);
        pTmp->workerThread();
        return arg;
    }
#endif

    CLightIntensitySensor::CLightIntensitySensor(ISensorCommonInterface::eSensorID a_eSensorID, uint8_t m_ui8I2CDeviceAddress, uint8_t a_u8DeathZOne)
        : m_pParent(nullptr)
#ifndef QT
        , m_oThreadWorker(0)
        , m_oAttr()
#endif
        , m_fRun(false)
        , m_eSensorID(a_eSensorID)
        , m_ui8I2CDeviceAddress(m_ui8I2CDeviceAddress)
        , m_i32I2CDeviceDescriptor(-1)
        , m_fInitialized(false)
        , m_ui32CurrentVal(0)
        , m_u8DeathZone(a_u8DeathZOne)
    {
    }

    CLightIntensitySensor::~CLightIntensitySensor()
    {

    }

    bool_t CLightIntensitySensor::setParentPoiter(smartLights::smartLightsBackend::ISensorCommonInterfaceListener *a_pParent)
    {
        bool_t fRetval = false;
        if(nullptr != a_pParent)
        {
            m_pParent = a_pParent;
            fRetval = true;
        }
        return fRetval;
    }

    bool_t CLightIntensitySensor::init()
    {
        PRINT_INF("init()");
        bool fInitialized = true;

#ifdef __arm__
        m_i32I2CDeviceDescriptor = wiringPiI2CSetup(m_ui8I2CDeviceAddress);
        if(0 > m_i32I2CDeviceDescriptor)
        {
            PRINT_ERR("I2C init failed");
            fInitialized = false;
        }
        else
        {
            if(0 > wiringPiI2CWrite(m_i32I2CDeviceDescriptor,  POWER_UP))
            {
                PRINT_ERR("I2C init, power up failed");
                fInitialized = false;
            }
        }


#endif

#ifndef QT
        pthread_attr_init(&m_oAttr);
        pthread_attr_setdetachstate(&m_oAttr, PTHREAD_CREATE_JOINABLE);
#endif
        if(fInitialized)
            m_fInitialized = true;

        return true;
    }

    bool_t CLightIntensitySensor::deinit()
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

    ISensorCommonInterface::eReturnValue CLightIntensitySensor::isAvailable()
    {
        return E_NOT_IMPLEMENTED;
    }

    ISensorCommonInterface::eReturnValue CLightIntensitySensor::isActive()
    {
        return (m_fRun == false) ? E_FALSE : E_TRUE;
    }

#ifndef QT
    ISensorCommonInterface::eReturnValue CLightIntensitySensor::start()
    {
        PRINT_INF("start()");

        eReturnValue eRetVal = E_FALSE;

        if(false != m_fInitialized)
        {
            int iRetVal = pthread_create(&m_oThreadWorker, &m_oAttr, threadRoutineLightSensor, (void*)this);
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
    ISensorCommonInterface::eReturnValue CLightIntensitySensor::start()
    {
        QThread::start();
        return E_TRUE;
    }
#endif

    ISensorCommonInterface::eReturnValue CLightIntensitySensor::stopThread()
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

    ISensorCommonInterface::eReturnValue CLightIntensitySensor::unleashSensor(uint8_t, uint32_t)
    {
        return E_NOT_IMPLEMENTED;
    }

    ISensorCommonInterface::eSensorID CLightIntensitySensor::getSensorID()
    {
        return m_eSensorID;
    }

#ifndef QT
    void CLightIntensitySensor::workerThread()
#else
    void CLightIntensitySensor::run()
#endif
    {
        m_fRun = true;

        while(false != m_fRun)
        {
            if(m_i32I2CDeviceDescriptor > 0)
            {
#ifdef __arm__
                wiringPiI2CWrite(m_i32I2CDeviceDescriptor,  CONTINUOUS_HIGH_RES_MODE_1);
                usleep(500000); // 500ms

                int32_t i32Value = wiringPiI2CReadReg16(m_i32I2CDeviceDescriptor, CONTINUOUS_HIGH_RES_MODE_1);
                uint32_t ui32LuxVal = ((0xFF00 & i32Value) >> 8) | ((0x00FF & i32Value) << 8);

                //PRINT_INF(" CLightIntensitySensor: Lx: %u, HEX: 0x%x", ui32LuxVal, i32Value);

                if(abs(ui32LuxVal - m_ui32CurrentVal) >= m_u8DeathZone)
                {
                    if(nullptr != m_pParent)
                    {
                        sSensorCommonData sData;
                        sData.m_iSensorID = m_eSensorID;
                        sData.m_pvData = (void*)(new uint32_t(ui32LuxVal));
                        m_pParent->handleSensorEvent(sData);
                        m_ui32CurrentVal = ui32LuxVal;
                    }
                }
#endif
            }
            else
            {
                PRINT_ERR("Device descriptor -1, read failed. Stop reading.");
                break;
            }
        }
#ifndef QT
        pthread_exit(0);
#endif
    }

}
}
