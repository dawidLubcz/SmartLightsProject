#include "ctestmovesensor.h"
#include <unistd.h>
#include <memory.h>
#include <stdio.h>

#include <future>

#define RETURN(b) printf("+--------------------------+\n"); \
                  b?printf("\033[1;32m"):printf("\033[0;31m"); \
                  printf("| %s -> %s |\n", __func__, b?"PASSED":"FAILED"); \
                  printf("\033[0m --------------------------+\n"); \
                  clean(); \
                  return b

namespace smartLights
{
namespace smartLightsTests
{

    std::shared_ptr<ILightSourceInterface> ILightSourceInterfaceStub::m_pInstance = nullptr;

    CTestMoveSensor::CTestMoveSensor() : m_oAppMngr()
    {
    }

    bool CTestMoveSensor::createApp()
    {

        bool result = m_oAppMngr.create();

        m_oAppMngr.m_pLightSource.reset(ILightSourceInterfaceStub::getInstance().get());
        result = m_oAppMngr.init();
        m_oAppMngr.run();

        QThread::usleep(1000000); // init time

        RETURN(result);
    }

    bool CTestMoveSensor::TC_gate_room_sensor1_MoveDetected()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;

        std::future<void> res1(std::async(std::launch::async, &CTestMoveSensor::triggerSensorGate, this, 1));
        usleep(100000);
        triggerSensorRoom(1);
        usleep(100000);

        if(((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendBrightnessReq == true)
        {
            fResult = true;
        }

        triggerSensorGate(0);
        triggerSensorRoom(0);
        ((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendBrightnessReq = false;

        RETURN(fResult);
    }

    bool CTestMoveSensor::TC_gate_room_sensor2_MoveDetected()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_ABSENT;
        m_oAppMngr.m_sBrightness.m_u8LastUserBr = 75;
        m_oAppMngr.m_sLightState.u8LastPriority = E_SYSTEM_PRIO;

        std::future<void> res1(std::async(std::launch::async, &CTestMoveSensor::triggerSensorGate, this, 1));
        usleep(100000);
        triggerSensorRoom2(1);
        usleep(100000);

        if(((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendBrightnessReq == true)
        {
            fResult = true;
        }

        triggerSensorGate(0);
        triggerSensorRoom2(0);

        RETURN(fResult);
    }

    bool CTestMoveSensor::TC_only_sensor2_MoveDetected()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_ABSENT;
        m_oAppMngr.m_sBrightness.m_u8LastUserBr = 75;
        m_oAppMngr.m_sLightState.u8LastPriority = E_SYSTEM_PRIO;

        triggerSensorRoom2(1);
        usleep(100000);

        if(((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendBrightnessReq == true)
        {
            fResult = true;
        }

        triggerSensorRoom2(0);
        RETURN(fResult);
    }

    bool CTestMoveSensor::TC_only_sensor1_MoveDetected()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_ABSENT;
        m_oAppMngr.m_sBrightness.m_u8LastUserBr = 75;
        m_oAppMngr.m_sLightState.u8LastPriority = E_SYSTEM_PRIO;

        triggerSensorRoom(1);
        usleep(100000);

        if(((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendBrightnessReq == true)
        {
            fResult = true;
        }

        triggerSensorRoom(0);
        RETURN(fResult);
    }

    bool CTestMoveSensor::TC_only_gate_MoveDetected()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;

        triggerSensorGate(1);
        usleep(5000000);

        if(m_oAppMngr.m_sCurrentState.m_eLightState != E_PERSON_PRESENT)
        {
            fResult = true;
        }
        ((CSensorsMngr*)m_oAppMngr.m_pSensorMngr.get())->m_fTimerStartedAbort = true;
        usleep(32000000);
        triggerSensorGate(0);

        RETURN(fResult);
    }

    bool CTestMoveSensor::TC_turned_off_by_the_user()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_PRESENT;

        smartLightsFrontend::CSmartLightsInterface::sData_t sData;
        sData.m_aParamsCntr = 0;
        sData.m_iGroup = 0;
        sData.m_iID = smartLightsFrontend::CSmartLightsInterface::E_SEND_TURN_OFF_REQ;
        sData.m_iPriority = smartLightsFrontend::CSmartLightsInterface::E_USER_PRIO;

        m_oAppMngr.handleMessage(sData);

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_ABSENT;

        usleep(100000);


        std::async(std::launch::async, &CTestMoveSensor::triggerSensorGate, this, 1);
        usleep(100000);
        triggerSensorRoom2(1);
        usleep(100000);

        if(m_oAppMngr.m_sLightState.isTurned == false)
        {
            fResult = true;
        }

        triggerSensorGate(0);
        triggerSensorRoom2(0);

        RETURN(fResult);
    }

    bool CTestMoveSensor::TC_turned_on_by_the_user()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_PRESENT;

        smartLightsFrontend::CSmartLightsInterface::sData_t sData;
        sData.m_aParamsCntr = 0;
        sData.m_iGroup = 0;
        sData.m_iID = smartLightsFrontend::CSmartLightsInterface::E_SEND_TURN_ON_REQ;
        sData.m_iPriority = smartLightsFrontend::CSmartLightsInterface::E_USER_PRIO;

        m_oAppMngr.handleMessage(sData);

        std::async(std::launch::async, &CTestMoveSensor::triggerSensorGate, this, 1);
        usleep(36000000);

        if(m_oAppMngr.m_sLightState.isTurned == false)
        {
            fResult = true;
        }

        triggerSensorRoom(1);

        if(m_oAppMngr.m_sLightState.isTurned != false)
        {
            fResult &= true;
        }
        else
        {
            fResult = false;
        }

        triggerSensorGate(0);
        triggerSensorRoom(0);

        RETURN(fResult);
    }

    bool CTestMoveSensor::TC_brightness_set_by_the_user()
    {
        using namespace smartLights::smartLightsBackend;

        bool_t fResult = false;
        const int value = 75;

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_PRESENT;

        smartLightsFrontend::CSmartLightsInterface::sData_t sData;
        sData.m_aParamsCntr = 1;
        sData.m_iGroup = 0;
        sData.m_iID = smartLightsFrontend::CSmartLightsInterface::E_SEND_BRIGHTNESS_REQ;
        sData.m_aParams[0] = value;
        sData.m_iPriority = smartLightsFrontend::CSmartLightsInterface::E_USER_PRIO;

        m_oAppMngr.handleMessage(sData);

        std::async(std::launch::async, &CTestMoveSensor::triggerSensorGate, this, 1);
        usleep(32000000);

        if(m_oAppMngr.m_sLightState.isTurned == false && 0 == m_oAppMngr.m_sBrightness.m_u8CurrentBr)
        {
            fResult = true;
        }

        triggerSensorRoom(1);

        if(m_oAppMngr.m_sLightState.isTurned != false && value == m_oAppMngr.m_sBrightness.m_u8CurrentBr)
        {
            fResult &= true;
        }
        else
        {
            fResult = false;
        }

        triggerSensorGate(0);
        triggerSensorRoom(0);

        RETURN(fResult);
    }

    bool CTestMoveSensor::destroyApp()
    {
        bool result = m_oAppMngr.stopApp();

        QThread::usleep(1000000); // deinit time

        result = m_oAppMngr.deinit();
        result = m_oAppMngr.destroy();

        QThread::usleep(1000000);
        RETURN(result);
    }

    void CTestMoveSensor::clean()
    {
        using namespace smartLights::smartLightsBackend;

        ((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendBrightnessReq = false;
        ((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendBrightnessReqVal = 0xFF;
        ((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendColourReq = false;
        ((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendTurnOffReq = false;
        ((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendTurnOnReq = false;
        ((ILightSourceInterfaceStub*)(ILightSourceInterfaceStub::getInstance().get()))->m_fSendWhiteReq = false;

        m_oAppMngr.m_sCurrentState.m_eLightState = E_PERSON_DEFAULT;
        m_oAppMngr.m_sBrightness.m_u8CurrentBr = 0xFF;
        m_oAppMngr.m_sBrightness.m_u8LastBr = 0xFF;
        m_oAppMngr.m_sCurrentState.m_uiLightIntensityLx = 0;
        m_oAppMngr.m_sLightState.isTurned = true;
        m_oAppMngr.m_sLightState.u8LastPriority = E_DEFAULT_PRIO;
    }

    void CTestMoveSensor::triggerSensorGate(int val)
    {
        using namespace smartLights::smartLightsBackend;

        ISensorCommonInterface::sSensorCommonData sData;
        sData.m_iSensorID = ISensorCommonInterface::E_MOVE_SENSOR_1;
        sData.m_pvData = (void*)(new CMoveSensor::CMoveSensorData(val));

        ((CSensorsMngr*)m_oAppMngr.m_pSensorMngr.get())->handleSensorEvent(sData);
    }

    void CTestMoveSensor::triggerSensorRoom(int val)
    {
        using namespace smartLights::smartLightsBackend;

        ISensorCommonInterface::sSensorCommonData sData;
        sData.m_iSensorID = ISensorCommonInterface::E_MOVE_SENSOR_2;
        sData.m_pvData = (void*)(new CMoveSensor::CMoveSensorData(val));

        ((CSensorsMngr*)m_oAppMngr.m_pSensorMngr.get())->handleSensorEvent(sData);
    }

    void CTestMoveSensor::triggerSensorRoom2(int val)
    {
        using namespace smartLights::smartLightsBackend;

        ISensorCommonInterface::sSensorCommonData sData;
        sData.m_iSensorID = ISensorCommonInterface::E_MOVE_SENSOR_2;
        sData.m_pvData = (void*)(new CMoveSensor::CMoveSensorData(val));

        ((CSensorsMngr*)m_oAppMngr.m_pSensorMngr.get())->handleSensorEvent(sData);
    }

    std::shared_ptr<ILightSourceInterface> ILightSourceInterfaceStub::getInstance()
    {
        if(nullptr == m_pInstance)
        {
            m_pInstance = std::shared_ptr<ILightSourceInterface>(new ILightSourceInterfaceStub);
        }
        return m_pInstance;
    }

    bool_t ILightSourceInterfaceStub::sendTurnOnReq(ILightSourceInterface::eGroup a_eGroup)
    {
        printf("sendTurnOnReq\n");

        m_fSendTurnOnReq = true;
        return true;
    }

    bool_t ILightSourceInterfaceStub::sendTurnOffReq(ILightSourceInterface::eGroup a_eGroup)
    {
        printf("sendTurnOffReq\n");

        m_fSendTurnOffReq = true;
        return true;
    }

    bool_t ILightSourceInterfaceStub::sendWhiteReq(ILightSourceInterface::eGroup a_eGroup)
    {
        printf("sendWhiteReq\n");

        m_fSendWhiteReq = true;
        return true;
    }

    bool_t ILightSourceInterfaceStub::sendBrightnessReq(ILightSourceInterface::eGroup a_eGroup, int16_t a_uiProc)
    {
        printf("sendBrightnessReq\n");

        m_fSendBrightnessReq = true;
        return true;
    }

    bool_t ILightSourceInterfaceStub::sendColourReq(ILightSourceInterface::eGroup a_eGroup, ILightSourceInterface::eColours a_eColour)
    {
        printf("sendColourReq\n");

        m_fSendColourReq = true;
        return true;
    }

    bool_t ILightSourceInterfaceStub::sendColourReq(ILightSourceInterface::eGroup a_eGroup, int16_t a_uiColour)
    {
        printf("sendColourReq\n");

        m_fSendColourReq = true;
        return true;
    }

}
}

