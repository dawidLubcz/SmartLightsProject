#include "CSmartlightsinterface.h"

namespace smartLights
{
namespace smartLightsFrontend
{
    const char* g_pcCommonMsqQueueFile = "../SmartLightsCommon/smartLightsMessageQueueCommonFile";
    const char g_cProjectID = 'S' | 'L';

    CSmartLightsInterface::CSmartLightsInterface():
        m_i32MsgQueueID(-1)
    {

    }

    bool_t CSmartLightsInterface::create()
    {
        bool_t _fResult = true;
        key_t _u32MsgQueueKey = -1;

        _u32MsgQueueKey = ftok(smartLights::smartLightsFrontend::g_pcCommonMsqQueueFile
                              ,smartLights::smartLightsFrontend::g_cProjectID);
        if(-1 < _u32MsgQueueKey)
        {
            if(-1 == (m_i32MsgQueueID = msgget(_u32MsgQueueKey, 0644 | IPC_CREAT)))
            {
                perror("msgget");
                _fResult = false;
            }
        }
        else
        {
            perror("ftok");
        }
        return _fResult;
    }

    bool_t CSmartLightsInterface::destroy()
    {
        bool_t _fResult = true;
        if(-1 == msgctl(m_i32MsgQueueID, IPC_RMID, NULL))
        {
            perror("msgctl");
            _fResult = false;
        }
        return _fResult;
    }

    bool_t CSmartLightsInterface::sendTurnOnReq(IsmartLightsInterface::eGroup a_eGroup, ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_TURN_ON_REQ;
        _sMessage.mmsg.m_iGroup = a_eGroup;
        _sMessage.mmsg.m_aParamsCntr = 0;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::sendTurnOffReq(IsmartLightsInterface::eGroup a_eGroup, ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_TURN_OFF_REQ;
        _sMessage.mmsg.m_iGroup = a_eGroup;
        _sMessage.mmsg.m_aParamsCntr = 0;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::sendWhiteReq(IsmartLightsInterface::eGroup a_eGroup, ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_WHITE_REQ;
        _sMessage.mmsg.m_iGroup = a_eGroup;
        _sMessage.mmsg.m_aParamsCntr = 0;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::sendBrightnessReq(IsmartLightsInterface::eGroup a_eGroup, u_int8_t a_uiProc, ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_BRIGHTNESS_REQ;
        _sMessage.mmsg.m_iGroup = a_eGroup;
        _sMessage.mmsg.m_aParamsCntr = 1;
        _sMessage.mmsg.m_aParams[0] = a_uiProc;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::sendColourReq(IsmartLightsInterface::eGroup a_eGroup, IsmartLightsInterface::eColours a_eColour, ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_COLOUR_REQ_E;
        _sMessage.mmsg.m_iGroup = a_eGroup;
        _sMessage.mmsg.m_aParamsCntr = 1;
        _sMessage.mmsg.m_aParams[0] = a_eColour;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::sendColourReq(IsmartLightsInterface::eGroup a_eGroup, u_int8_t a_uiColour, ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_COLOUR_REQ_V;
        _sMessage.mmsg.m_iGroup = a_eGroup;
        _sMessage.mmsg.m_aParamsCntr = 1;
        _sMessage.mmsg.m_aParams[0] = a_uiColour;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::setAutoDimming(eAutoDimming a_eEnable, ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_SET_AUTO_DIMMING;
        _sMessage.mmsg.m_iGroup = E_GROUP_ALL;
        _sMessage.mmsg.m_aParamsCntr = 1;
        _sMessage.mmsg.m_aParams[0] = a_eEnable;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::setMinimumLuxValue(u_int32_t a_eValue, IsmartLightsInterface::ePriority a_ePriority)
    {
        sMessage_t _sMessage;
        _sMessage.mmsg.m_iPriority = a_ePriority;
        _sMessage.mmsg.m_iID = E_SEND_SET_MINIMUM_LUX_VAL;
        _sMessage.mmsg.m_iGroup = E_GROUP_ALL;
        _sMessage.mmsg.m_aParamsCntr = 1;
        _sMessage.mmsg.m_aParams[0] = a_eValue;
        return sendMessage(&_sMessage);
    }

    bool_t CSmartLightsInterface::sendMessage(CSmartLightsInterface::sMessage_t* a_sMsg)
    {
        bool_t _fRetval = false;
        if(-1 != m_i32MsgQueueID && 0 != a_sMsg)
        {
            a_sMsg->mtype = 1;
            if(-1 == msgsnd(m_i32MsgQueueID, a_sMsg, sizeof(sMessage_t),0))
            {
                perror("msgsnd");
            }
            else
                _fRetval = true;
        }
        return _fRetval;
    }

}
}

