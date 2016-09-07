#include "CMilightSource.h"

CMilightSource::CMilightSource()
{

}

bool_t CMilightSource::sendTurnOnReq(ILightSourceInterface::eGroup a_eGroup)
{
    bool_t fRetVal = false;
    commonTypes::limitless::eGroupOn eHexMsg = commonTypes::limitless::E_GROUP_ON_INITIAL;

    CMapperToLedCommand oMapper;
    fRetVal = oMapper.mapGroupToHex(a_eGroup, eHexMsg);

    char _aiMessage[commonTypes::limitless::E_MESSAGE_SIZE];
    CMessageCreator::createMessage(_aiMessage, eHexMsg);

    if(false != fRetVal)
    {
        fRetVal = CUDPSender::sendMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_SIZE);
    }

    return fRetVal;
}

bool_t CMilightSource::sendTurnOffReq(ILightSourceInterface::eGroup a_eGroup)
{
    bool_t fRetVal = false;
    commonTypes::limitless::eGroupOff eHexMsg = commonTypes::limitless::E_GROUP_OFF_INITIAL;

    CMapperToLedCommand oMapper;
    fRetVal = oMapper.mapGroupToHex(a_eGroup, eHexMsg);

    char _aiMessage[commonTypes::limitless::E_MESSAGE_SIZE];
    CMessageCreator::createMessage(_aiMessage, eHexMsg);

    if(false != fRetVal)
    {
        fRetVal = CUDPSender::sendMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_SIZE);
    }

    return fRetVal;
}

bool_t CMilightSource::sendWhiteReq(ILightSourceInterface::eGroup a_eGroup)
{
    bool_t fRetVal = false;
    commonTypes::limitless::eSetWhiteCol eHexMsg = commonTypes::limitless::E_SET_COLOR_TO_WHITE_INITIAL;

    fRetVal = sendTurnOnReq(a_eGroup);

    sleep(0.1); // 100 ms

    CMapperToLedCommand oMapper;
    fRetVal &= oMapper.mapGroupToHex(a_eGroup, eHexMsg);

    char _aiMessage[commonTypes::limitless::E_MESSAGE_SIZE];
    CMessageCreator::createMessage(_aiMessage, eHexMsg);

    if(false != fRetVal)
    {
        fRetVal &= CUDPSender::sendMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_SIZE);
    }
    return fRetVal;
}

bool_t CMilightSource::sendBrightnessReq(ILightSourceInterface::eGroup a_eGroup, int16_t a_uiProc)
{
    bool_t fRetVal = false;

    if(ILightSourceInterface::E_BRIGHTNESS_MIN <= a_uiProc && ILightSourceInterface::E_BRIGHTNESS_MAX >= a_uiProc)
    {
        fRetVal = sendTurnOnReq(a_eGroup);
        usleep (100000); // 100 ms

        char _aiMessage[commonTypes::limitless::E_MESSAGE_SIZE];
        CMessageCreator::createMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_PREFIX_BRIGHTNESS, calculateBrightness(a_uiProc));

        if(false != fRetVal)
        {
            fRetVal &= CUDPSender::sendMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_SIZE);
        }
    }

    return fRetVal;
}

bool_t CMilightSource::sendColourReq(ILightSourceInterface::eGroup a_eGroup, ILightSourceInterface::eColours a_eColour)
{
    bool_t fRetVal = false;

    if( (ILightSourceInterface::E_COLOUR_MIN <= a_eColour) && (ILightSourceInterface::E_COLOUR_MAX >= a_eColour))
    {
        fRetVal = sendTurnOnReq(a_eGroup);
        usleep (100000); // 100 ms

        char _aiMessage[commonTypes::limitless::E_MESSAGE_SIZE];
        CMessageCreator::createMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_PREFIX_COLOUR, a_eColour);

        if(false != fRetVal)
        {
            fRetVal &= CUDPSender::sendMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_SIZE);
        }
    }
    return fRetVal;
}

bool_t CMilightSource::sendColourReq(ILightSourceInterface::eGroup a_eGroup, int16_t a_uiColour)
{
    bool_t fRetVal = false;

    if( ILightSourceInterface::E_COLOUR_MIN <= a_uiColour && ILightSourceInterface::E_COLOUR_MAX >= a_uiColour)
    {
        fRetVal = sendTurnOnReq(a_eGroup);
        usleep (100000); // 100 ms

        char _aiMessage[commonTypes::limitless::E_MESSAGE_SIZE];
        CMessageCreator::createMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_PREFIX_COLOUR, a_uiColour);

        if(false != fRetVal)
        {
            fRetVal &= CUDPSender::sendMessage(_aiMessage, commonTypes::limitless::E_MESSAGE_SIZE);
        }
    }
    return fRetVal;
}

uint8_t CMilightSource::calculateBrightness(uint8_t a_iProc)
{
    return (a_iProc / 4) + 2;
}
