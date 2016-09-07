#ifndef CTESTMOVESENSOR_H
#define CTESTMOVESENSOR_H

#include <stdio.h>
#include <memory>

#include "CAppMngr.h"
#include "IApplicationStateInterface.h"
#include "ISensorCommonInterface.h"
#include "CMoveSensor.h"

namespace smartLights
{
namespace smartLightsTests
{

class ILightSourceInterfaceStub : public ILightSourceInterface
{

public:

    typedef bool bool_t;

    enum eInterfaces
    {
        E_IF_MILIGTH,
    };

    /////////////////////////////////////
    /// \brief The eColors enum
    ///
    enum eColours
    {
        E_COLOUR_MIN = 0x00,
        E_COLOUR_VIOLET = 0x00, // Violet
        E_COLOUR_R_BLUE = 0x10, // Royal_Blue
        E_COLOUR_B_BLUE = 0x20, // Baby_Blue
        E_COLOUR_AQUA   = 0x30, // Aqua
        E_COLOUR_MINT   = 0x40, // Mint
        E_COLOUR_S_GREEN = 0x50, // Seafoam_Green
        E_COLOUR_GREEN  = 0x60, //Green
        E_COLOUR_L_GREEN = 0x70, // Lime_Green
        E_COLOUR_YELLOW = 0x80, //Yellow
        E_COLOUR_Y_ORANGE = 0x90, // Yellow_Orange
        E_COLOUR_ORANGE = 0xA0, // Orange
        E_COLOUR_RED = 0xB0, //Red
        E_COLOUR_PINK = 0xC0, // Pink
        E_COLOUR_FUSIA = 0xD0, // Fusia
        E_COLOUR_LILAC = 0xE0, // Lilac
        E_COLOUR_LAVENDAR = 0xF0, // Lavendar
        E_COLOUR_MAX = 0xFF,
    };

    ////////////////////////////////////
    /// \brief The eGroup enum
    ///
    enum eGroup
    {
        E_GROUP_ALL = 0,
        E_GROUP_1 = 1,
        E_GROUP_2 = 2,
        E_GROUP_3 = 3,
        E_GROUP_4 = 4,
        E_GROUP_MAX = 4
    };

    enum eBrightness
    {
        E_BRIGHTNESS_MIN = 0,
        E_BRIGHTNESS_MAX = 100
    };

    ILightSourceInterfaceStub()
    {

    }

    static std::shared_ptr<ILightSourceInterface> getInstance();

    //////////////////////////////////
    /// \brief sendTurnOnReq
    /// \param a_eGroup
    /// \return
    ///
    bool_t sendTurnOnReq(ILightSourceInterface::eGroup a_eGroup);

    /////////////////////////////////
    /// \brief sendTurnOffReq
    /// \param a_eGroup
    /// \return
    ///
    bool_t sendTurnOffReq(ILightSourceInterface::eGroup a_eGroup);

    /////////////////////////////////
    /// \brief sendWhiteReq
    /// \param a_eGroup
    /// \return
    ///
    bool_t sendWhiteReq(ILightSourceInterface::eGroup a_eGroup);

    /////////////////////////////////
    /// \brief sendBrightnessReq
    /// \param a_eGroup
    /// \param a_uiProc
    /// \return
    ///
    bool_t sendBrightnessReq(ILightSourceInterface::eGroup a_eGroup, int16_t a_uiProc = 100);

    ////////////////////////////////
    /// \brief sendColourReq
    /// \param a_eGroup
    /// \param a_eColour
    /// \return
    ///
    bool_t sendColourReq(ILightSourceInterface::eGroup a_eGroup, ILightSourceInterface::eColours a_eColour);

    ////////////////////////////////
    /// \brief sendColourReq
    /// \param a_eGroup
    /// \param a_uiColour
    /// \return
    ///
    bool_t sendColourReq(ILightSourceInterface::eGroup a_eGroup, int16_t a_uiColour);

    bool_t m_fSendTurnOnReq = false;
    bool_t m_fSendTurnOffReq = false;
    bool_t m_fSendWhiteReq = false;
    bool_t m_fSendBrightnessReq = false;
    int m_fSendBrightnessReqVal = 0;
    bool_t m_fSendColourReq = false;

    static std::shared_ptr<ILightSourceInterface> m_pInstance;
};

class CTestMoveSensor
{

public:
    CTestMoveSensor();
    bool createApp();
    bool TC_gate_room_sensor1_MoveDetected();
    bool TC_gate_room_sensor2_MoveDetected();
    bool TC_only_sensor2_MoveDetected();
    bool TC_only_sensor1_MoveDetected();
    bool TC_only_gate_MoveDetected();
    bool TC_turned_off_by_the_user();
    bool TC_turned_on_by_the_user();
    bool TC_brightness_set_by_the_user();
    bool destroyApp();

    void clean();
    void triggerSensorGate(int val);
    void triggerSensorRoom(int val);
    void triggerSensorRoom2(int val);

private:
    smartLights::smartLightsBackend::CAppMngr m_oAppMngr;

};

}
}

#endif // CTESTMOVESENSOR_H
