#include "CDistanceSensor.h"

#include "../../SmartLightsCommon/CLogger.h"
#include <unistd.h>
#include <vector>

#ifdef __arm__
    #include <wiringPi.h>
#endif

#undef PRINT_PREFIX
#define PRINT_PREFIX "SB:CDistanceSensor: "

namespace smartLights
{
namespace smartLightsBackend
{

    CDistanceSensor::CDistanceSensor(eSensorID a_eSensorID, uint8_t a_u8Trig, uint8_t a_u8Echo)
        : m_pParent(nullptr)
        , m_eSensorID(a_eSensorID)
        , m_iTrigger(a_u8Trig)
        , m_iEcho(a_u8Echo)
        , m_isActive(false)
    {

    }

    CDistanceSensor::~CDistanceSensor()
    {

    }

    bool_t CDistanceSensor::init()
    {
        PRINT_INF("init()");

        bool_t fResult = false;

        if(!(255 > m_iTrigger && 255 > m_iEcho && E_SENSOR_MIN < m_eSensorID && E_SENSOR_MAX > m_eSensorID))
        {
            PRINT_ERR("init() bad parameters!");
        }
        else
        {
#ifdef __arm__
            pinMode(m_iEcho, INPUT);
            pinMode(m_iTrigger, OUTPUT);
#endif
            fResult = true;
        }

        return fResult;
    }

    bool_t CDistanceSensor::deinit()
    {
        PRINT_INF("deinit()");

        return false;
    }

    bool_t CDistanceSensor::setParentPoiter(ISensorCommonInterfaceListener *a_pParent)
    {
        bool_t fRetval = false;
        if(nullptr != a_pParent)
        {
            m_pParent = a_pParent;
            fRetval = true;
        }
        return fRetval;
    }

    ISensorCommonInterface::eReturnValue CDistanceSensor::isAvailable()
    {
        return E_NOT_IMPLEMENTED;
    }

    ISensorCommonInterface::eReturnValue CDistanceSensor::isActive()
    {
        return (false != m_isActive)?E_TRUE:E_FALSE;
    }

    ISensorCommonInterface::eReturnValue CDistanceSensor::start()
    {
        return E_NOT_SUPPORTED;
    }

    ISensorCommonInterface::eReturnValue CDistanceSensor::stopThread()
    {
        return E_NOT_SUPPORTED;
    }

    ISensorCommonInterface::eReturnValue CDistanceSensor::unleashSensor(uint8_t a_u8Repeat, uint32_t a_u32TimePeriod)
    {
        eReturnValue eRetVal = E_FALSE;
        m_isActive = true;
        uint8_t u8RepeatCntr = 0;
        std::vector<double>* pResultsVector = new std::vector<double>();

        while(u8RepeatCntr < a_u8Repeat && u8RepeatCntr < 20)
        {
            high_resolution_clock::time_point oTimePointStart = high_resolution_clock::now();
            high_resolution_clock::time_point oTimePointEnd = oTimePointStart;
            std::chrono::duration<double> oTimePointDuration;

#ifdef __arm__
            digitalWrite(m_iTrigger, LOW);
            usleep(100000/2); // 100 ms

            digitalWrite(m_iTrigger, HIGH);
            usleep(10); // 10 us
            digitalWrite(m_iTrigger, LOW);

            while(LOW == digitalRead(m_iEcho))
            {
                oTimePointStart = high_resolution_clock::now();
            }
            while (HIGH == digitalRead(m_iEcho))
            {
                oTimePointEnd = high_resolution_clock::now();
            }
#endif
            oTimePointDuration = oTimePointEnd - oTimePointStart;
            double dDistance = oTimePointDuration.count() * 17150;

            //PRINT_INF("CDistanceSensor:::unleashSensor, duration %d ms, dDistance %f",oTimePointDuration.count(), dDistance);

            (*pResultsVector).push_back(dDistance);

            ++u8RepeatCntr;
            usleep(a_u32TimePeriod * 100); //ms
        }

        if(nullptr != m_pParent)
        {
            sSensorCommonData sData;
            sData.m_iSensorID = m_eSensorID;
            sData.m_pvData = (void*)(pResultsVector);
            m_pParent->handleSensorEvent(sData);
        }

        m_isActive = false;
        return eRetVal;
    }

    ISensorCommonInterface::eSensorID CDistanceSensor::getSensorID()
    {
        return m_eSensorID;
    }

}
}
