#include "CMapperToLedCommand.h"

CMapperToLedCommand::CMapperToLedCommand()
{

}

commonTypes::sender::bool_t CMapperToLedCommand::mapGroupToHex(ILightSourceInterface::eGroup a_eGroup, commonTypes::limitless::eGroupOn &a_eHEX)
{
    commonTypes::sender::bool_t fRetVal = true;

    switch(a_eGroup)
    {
        case ILightSourceInterface::E_GROUP_ALL:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_ALL_ON;
        }
        break;

        case ILightSourceInterface::E_GROUP_1:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_1_ON;
        }
        break;

        case ILightSourceInterface::E_GROUP_2:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_2_ON;
        }
        break;

        case ILightSourceInterface::E_GROUP_3:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_3_ON;
        }
        break;

        case ILightSourceInterface::E_GROUP_4:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_4_ON;
        }
        break;

        default:
        {
            fRetVal = false;
        }
        break;
    }

    return fRetVal;
}

commonTypes::sender::bool_t CMapperToLedCommand::mapGroupToHex(ILightSourceInterface::eGroup a_eGroup, commonTypes::limitless::eGroupOff &a_eHEX)
{
    commonTypes::sender::bool_t fRetVal = true;

    switch(a_eGroup)
    {
        case ILightSourceInterface::E_GROUP_ALL:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_ALL_OFF;
        }
        break;

        case ILightSourceInterface::E_GROUP_1:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_1_OFF;
        }
        break;

        case ILightSourceInterface::E_GROUP_2:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_2_OFF;
        }
        break;

        case ILightSourceInterface::E_GROUP_3:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_3_OFF;
        }
        break;

        case ILightSourceInterface::E_GROUP_4:
        {
            a_eHEX = commonTypes::limitless::E_GROUP_4_OFF;
        }
        break;

        default:
        {
            fRetVal = false;
        }
        break;
    }

    return fRetVal;
}

commonTypes::sender::bool_t CMapperToLedCommand::mapGroupToHex(ILightSourceInterface::eGroup a_eGroup, commonTypes::limitless::eSetWhiteCol &a_eHEX)
{
    commonTypes::sender::bool_t fRetVal = true;

    switch(a_eGroup)
    {
        case ILightSourceInterface::E_GROUP_ALL:
        {
            a_eHEX = commonTypes::limitless::E_SET_COLOR_TO_WHITE_ALL;
        }
        break;

        case ILightSourceInterface::E_GROUP_1:
        {
            a_eHEX = commonTypes::limitless::E_SET_COLOR_TO_WHITE_G1;
        }
        break;

        case ILightSourceInterface::E_GROUP_2:
        {
            a_eHEX = commonTypes::limitless::E_SET_COLOR_TO_WHITE_G2;
        }
        break;

        case ILightSourceInterface::E_GROUP_3:
        {
            a_eHEX = commonTypes::limitless::E_SET_COLOR_TO_WHITE_G3;
        }
        break;

        case ILightSourceInterface::E_GROUP_4:
        {
            a_eHEX = commonTypes::limitless::E_SET_COLOR_TO_WHITE_G4;
        }
        break;

        default:
        {
            fRetVal = false;
        }
        break;
    }

    return fRetVal;
}
