#include "CSensorsMngr.h"
#include "CLogger.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include <thread>

#include "CTime.h"

#ifdef QT
#include<QtConcurrent/QtConcurrent>
#endif

#ifdef __arm__
#include <wiringPi.h>
#endif

#undef PRINT_PREFIX
#define PRINT_PREFIX "SM:CSensorsMngr: "

namespace smartLights
{
namespace smartLightsBackend
{
    std::shared_ptr<IApplicationStateInterface> CSensorsMngr::m_pInstance = nullptr;

    std::shared_ptr<IApplicationStateInterface> CSensorsMngr::getInstance()
    {
        if(nullptr == m_pInstance)
        {
            m_pInstance = std::shared_ptr<IApplicationStateInterface>(new CSensorsMngr());
        }
        return m_pInstance;
    }

    CSensorsMngr::CSensorsMngr()
        : m_vpListeners()
        , m_sCurrentState()
        , m_vSensorsArray()
        , m_oHandlersMap()
        , m_u8RunningSensorsNumber(0)
        , m_u8MoveSensorsBitmask(0)
        , m_sDistanceSensorStatus()
        , m_u8MoveSensorGate(pow(2, ISensorCommonInterface::E_MOVE_SENSOR_1))
        , m_u8MoveSensorRoom(pow(2, ISensorCommonInterface::E_MOVE_SENSOR_2))
        , m_fTimerStarted(false)
        , m_fTimerStartedAbort(false)
    {
        m_vSensorsArray.resize(ISensorCommonInterface::E_SENSOR_MAX);
        m_vSensorsArray[ISensorCommonInterface::E_MOVE_SENSOR_1]    = new CMoveSensor(ISensorCommonInterface::E_MOVE_SENSOR_1, 17, 21);
        m_vSensorsArray[ISensorCommonInterface::E_MOVE_SENSOR_2]    = new CMoveSensor(ISensorCommonInterface::E_MOVE_SENSOR_2, 10, 21);
        m_vSensorsArray[ISensorCommonInterface::E_MOVE_SENSOR_3]    = new CMoveSensor(ISensorCommonInterface::E_MOVE_SENSOR_3, 27, 21);
        m_vSensorsArray[ISensorCommonInterface::E_DISTANCE_SENSOR]  = new CDistanceSensor(ISensorCommonInterface::E_DISTANCE_SENSOR, 23, 24);
        m_vSensorsArray[ISensorCommonInterface::E_PHOTO_R_SENSOR]   = new CPhotoResistorSensor(ISensorCommonInterface::E_PHOTO_R_SENSOR, 9, 11, 100);
        m_vSensorsArray[ISensorCommonInterface::E_I2C_LIGHT_SENSOR] = new CLightIntensitySensor(ISensorCommonInterface::E_I2C_LIGHT_SENSOR, 0x23, 0);

        m_oHandlersMap.insert(std::make_pair(ISensorCommonInterface::E_MOVE_SENSOR_1,    &CSensorsMngr::handleMoveSensorGate));
        m_oHandlersMap.insert(std::make_pair(ISensorCommonInterface::E_MOVE_SENSOR_2,    &CSensorsMngr::handleMoveSensorRoom));
        m_oHandlersMap.insert(std::make_pair(ISensorCommonInterface::E_MOVE_SENSOR_3,    &CSensorsMngr::handleMoveSensorRoom));
        m_oHandlersMap.insert(std::make_pair(ISensorCommonInterface::E_DISTANCE_SENSOR,  &CSensorsMngr::handleDistanceSensor));
        m_oHandlersMap.insert(std::make_pair(ISensorCommonInterface::E_PHOTO_R_SENSOR,   &CSensorsMngr::handlePhotoResistor));
        m_oHandlersMap.insert(std::make_pair(ISensorCommonInterface::E_I2C_LIGHT_SENSOR, &CSensorsMngr::handleI2CLightSensor));

        m_u8MoveSensorsBitmask = 0;

        m_sDistanceSensorStatus.m_eDirect = sDistanceSensorStatus::E_DIRECT_NOT_SET;
        m_sDistanceSensorStatus.m_fBusy = false;

#ifdef QT
        QObject::connect(this, SIGNAL(openTimeWindow()), this, SLOT(timerSlot()));
#endif
    }

    CSensorsMngr::~CSensorsMngr()
    {
        for(auto it = m_vSensorsArray.begin(); it != m_vSensorsArray.end(); ++it)
        {
            if(nullptr != (*it))
            {
                delete (*it);
                (*it) = nullptr;
            }
        }
        m_vSensorsArray.clear();
    }

    bool_t CSensorsMngr::init()
    {
        bool_t fRetVal = true;
#ifdef __arm__
        wiringPiSetupGpio();
#endif
        for(auto it = m_vSensorsArray.begin(); it != m_vSensorsArray.end(); ++it)
        {
            fRetVal &= (*it)->init();
            (*it)->setParentPoiter(this);
        }
        return fRetVal;
    }

    bool_t CSensorsMngr::deinit()
    {
        bool_t fRetVal = true;
        for(auto it = m_vSensorsArray.begin(); it != m_vSensorsArray.end(); ++it)
        {
            fRetVal &= (*it)->deinit();
        }
        return true;
    }

    void CSensorsMngr::start()
    {
        for(auto it = m_vSensorsArray.begin(); it != m_vSensorsArray.end(); ++it)
        {
            if(ISensorCommonInterface::E_FALSE != (*it)->start())
            {
                ++m_u8RunningSensorsNumber;
            }
        }
        return;
    }

    void CSensorsMngr::stop()
    {
        for(auto it = m_vSensorsArray.begin(); it != m_vSensorsArray.end(); ++it)
        {
            if(ISensorCommonInterface::E_FALSE != (*it)->stopThread())
            {
                --m_u8RunningSensorsNumber;
            }
        }
        return;
    }

    bool_t CSensorsMngr::registerListener(IApplicationStateInterfaceListener *a_pListener)
    {
        bool_t fResult = false;
        if(0 != a_pListener)
        {
            bool_t fExist = false;
            for(auto it = m_vpListeners.begin(); it != m_vpListeners.end(); ++it)
            {
                if((*it) == a_pListener) fExist = true;
            }

            if(false == fExist)
            {
                m_vpListeners.push_back(a_pListener);
                fResult = true;
            }
        }
        return fResult;
    }

    bool_t CSensorsMngr::deregisterListener(IApplicationStateInterfaceListener *a_pListener)
    {
        bool_t fResult = false;
        if(0 != a_pListener)
        {
            for(auto it = m_vpListeners.begin(); it != m_vpListeners.end(); ++it)
            {
                if((*it) == a_pListener)
                {
                    m_vpListeners.erase(it);
                    fResult = true;
                    break;
                }
            }
        }
        return fResult;
    }

    void CSensorsMngr::notifyListeners(sCurrentState a_sCurrState)
    {
        PRINT_INF("notifyListeners(): state: |%d|, density: |%d|", a_sCurrState.m_eLightState, a_sCurrState.m_iPhotoresistorRes);

        for(auto it = m_vpListeners.begin(); it != m_vpListeners.end(); ++it)
        {
            (*it)->handleStateChanged(a_sCurrState);
        }
    }

    void CSensorsMngr::stopTimer()
    {
        if(false != m_fTimerStarted)
        {
            PRINT_INF("CSensorsMngr::stopTimer()");
            m_fTimerStartedAbort = true;
        }
    }

    void CSensorsMngr::handleSensorEvent(ISensorCommonInterface::sSensorCommonData a_sData)
    {
        auto _pMethodPointer = m_oHandlersMap[static_cast<ISensorCommonInterface::eSensorID>(a_sData.m_iSensorID)];
        if(0 != _pMethodPointer)
        {
            (this->*_pMethodPointer)(a_sData);
        }
        else
        {
            PRINT_INF("handleSensorEvent(): NULL _pMethodPointer");
        }
    }

    void CSensorsMngr::handleDistanceSensor(ISensorCommonInterface::sSensorCommonData a_sData)
    {
        if(0 != a_sData.m_pvData)
        {
            std::vector<double>* pResVector = (std::vector<double>*)a_sData.m_pvData; // data comming from distance sensor
            uint8_t isCloser  = 0;
            uint8_t isFarther = 0;
            uint8_t isTheSame = 0;
            const uint8_t deathZone = 1;   // variable tells above how many centimeters app should measure

            // delete edge values
            (*pResVector).erase(std::min_element((*pResVector).begin(),(*pResVector).end()));
            (*pResVector).erase(std::max_element((*pResVector).begin(),(*pResVector).end()));

            // average from first 3 values is a reference value
            //long int i64ReferenceVal = std::round( ((*pResVector)[0] + (*pResVector)[1] + (*pResVector)[2])/3 );
            long int i64PrevVal = std::round( (*pResVector)[0]);

            for(uint8_t i=1; i < (*pResVector).size(); ++i)
            {
                long int liTmp = std::round((*pResVector)[i]);

                PRINT_INF("Distance measure, Index: |%d|: %ld, %ld", i, i64PrevVal, liTmp);

                if(abs(liTmp - i64PrevVal) > 50)continue;

                if(i64PrevVal - deathZone > liTmp)
                {
                    ++isFarther;
                }
                else if (i64PrevVal + deathZone < liTmp)
                {
                    ++isCloser;
                }
                else
                {
                    ++isTheSame;
                }
                i64PrevVal = liTmp;
            }

            if( (isTheSame < isCloser) || (isTheSame < isFarther))
            {
                if(isCloser > isFarther)
                {
                    // somebody is comming
                    PRINT_INF("handleDistanceSensor() CLOSER, C: %d, F: %d, T: %d",isCloser, isFarther, isTheSame);

                    //notifyPersonChange();
                }
                else
                {
                    PRINT_INF("handleDistanceSensor() FARTHER, C: %d, F: %d, T: %d",isCloser, isFarther, isTheSame);

                    //removePerson();
                }
            }
            else
            {
                PRINT_INF("handleDistanceSensor() THE SAME, C: %d, F: %d, T: %d",isCloser, isFarther, isTheSame);
            }

            // release memory
            delete (std::vector<double>*)a_sData.m_pvData;
        }
    }

    void CSensorsMngr::handleMoveSensorGate(ISensorCommonInterface::sSensorCommonData a_sData)
    {
        uint8_t pinValue = CMoveSensor::E_MOVE_DEFAULT;

        if(nullptr != a_sData.m_pvData)
        {
            pinValue = (((CMoveSensor::CMoveSensorData*)(a_sData.m_pvData)))->m_u8PinVal;

            PRINT_INF("handleMoveSensorGate(), mask: |0x%x|, pinVal: |%d|", m_u8MoveSensorsBitmask, pinValue);
        }

        if(0 < pinValue && CMoveSensor::E_MOVE_DEFAULT != pinValue)
        {
            //m_vSensorsArray[ISensorCommonInterface::E_DISTANCE_SENSOR]->unleashSensor(28,50);
        }

        if(0 < pinValue && CMoveSensor::E_MOVE_DEFAULT != pinValue)
        {
            m_u8MoveSensorsBitmask |= m_u8MoveSensorGate;

            stopTimer();

#ifndef MODULE_TESTS
        #ifdef QT
            emit openTimeWindow();
        #endif
#else
            QtConcurrent::run(this, &CSensorsMngr::timerSlot);
#endif
        }
        else
        {
            if(m_u8MoveSensorsBitmask & m_u8MoveSensorGate)
            {
                m_u8MoveSensorsBitmask = m_u8MoveSensorsBitmask & (~m_u8MoveSensorGate);
            }
        }

        delete (CMoveSensor::CMoveSensorData*)a_sData.m_pvData;
    }

    void CSensorsMngr::handleMoveSensorRoom(ISensorCommonInterface::sSensorCommonData a_sData)
    {
        uint8_t pinValue = CMoveSensor::E_MOVE_DEFAULT;

        if(nullptr != a_sData.m_pvData)
        {
            pinValue = ((CMoveSensor::CMoveSensorData*)(a_sData.m_pvData))->m_u8PinVal;

            PRINT_INF("handleMoveSensorRoom(), mask: |0x%x|, pinVal: |%d|", m_u8MoveSensorsBitmask, pinValue);
        }

        if(0 < pinValue && CMoveSensor::E_MOVE_DEFAULT != pinValue)
        {
            m_u8MoveSensorsBitmask |= m_u8MoveSensorRoom;

            stopTimer();
            notifyPersonChange(E_PERSON_PRESENT);
        }
        else
        {
            if(m_u8MoveSensorsBitmask & m_u8MoveSensorRoom)
            {
                m_u8MoveSensorsBitmask = m_u8MoveSensorsBitmask & (~m_u8MoveSensorRoom);
            }
        }

        delete (CMoveSensor::CMoveSensorData*)a_sData.m_pvData;
    }

    void CSensorsMngr::handlePhotoResistor(ISensorCommonInterface::sSensorCommonData a_sData)
    {
        uint32_t u32_R_Value = 0;

        if(nullptr != a_sData.m_pvData)
        {
             u32_R_Value = *((uint32_t*)(a_sData.m_pvData));

             PRINT_INF("handlePhotoResistor(), R: |%u|, currentProc: |%d|",u32_R_Value, m_sCurrentState.m_iPhotoresistorRes);
        }

        uint8_t u8LightDensity = 100 - (u32_R_Value)*100/300000;
        m_sCurrentState.m_iPhotoresistorRes = u8LightDensity;
        notifyListeners(m_sCurrentState);

        delete (uint32_t*)a_sData.m_pvData;
    }

    void CSensorsMngr::handleI2CLightSensor(ISensorCommonInterface::sSensorCommonData a_sData)
    {
        if(nullptr != a_sData.m_pvData)
        {
            uint32_t ui32Value = *((uint32_t*)(a_sData.m_pvData));

            notifyLightIntensityChanged(ui32Value);
            //PRINT_INF("handleI2CLightSensor(), newVal: |%u|, currVal: |%u| LX", ui32Value, m_sCurrentState.m_uiLightIntensityLx);

            m_sCurrentState.m_uiLightIntensityLx = ui32Value;

            delete (uint32_t*)a_sData.m_pvData;
        }
    }

    void CSensorsMngr::notifyPersonChange(ePersonState a_eState)
    {
        m_sCurrentState.m_eLightState = a_eState;

        notifyListeners(m_sCurrentState);
    }

    void CSensorsMngr::notifyLightIntensityChanged(uint32_t a_ui32LuxVal)
    {
        for(auto it = m_vpListeners.begin(); it != m_vpListeners.end(); ++it)
        {
            (*it)->handleLightIntesityChanged(a_ui32LuxVal);
        }

        static uint8_t u8Cntr;

        if(0 == u8Cntr % 10)
            PRINT_INF("notifyLightIntensityChanged(): Lx: |%u|", a_ui32LuxVal);
        ++u8Cntr;
    }

    sCurrentState CSensorsMngr::getState()
    {
        return m_sCurrentState;
    }

#ifdef QT
    void CSensorsMngr::timerSlot()
    {
        m_fTimerStartedAbort = false;
        m_fTimerStarted = true;
        const int i32Attemps = 10;

        notifyPersonChange(E_PERSON_WENT_OUT_HIGH);

        for(int i =0; i<i32Attemps; ++i)
        {
            if(false != m_fTimerStartedAbort)
            {
                break;
            }

            if(i32Attemps/2 == i)
            {
                notifyPersonChange(E_PERSON_WENT_OUT_LOW);
            }

            usleep(3000000); // 3s
            PRINT_INF("timerSlot(), sleep |%d|", (i+1) * 3);
        }
        m_fTimerStarted = false;

        if(false == m_fTimerStartedAbort)
        {
            notifyPersonChange(E_PERSON_ABSENT);
            PRINT_INF("timerActiveExpired() no move detected");
        }
        else
        {
            m_fTimerStartedAbort = false;
            PRINT_INF("timer stopped, move deteced");
        }
    }

#endif

}
}
