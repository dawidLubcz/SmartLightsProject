#ifndef ISMARTLIGHTSINTERFACE
#define ISMARTLIGHTSINTERFACE

#include <cstdlib>
#include "../SmartLightsCommon/common.h"

namespace smartLights
{
namespace smartLightsFrontend
{

    class IsmartLightsInterface
    {
    public:

        /////////////////////////////////////
        /// \brief The eColors enum
        ///
        enum eColours
        {
            E_COLOUR_MIN        = 0x00,
            E_COLOUR_VIOLET     = 0x00, // Violet
            E_COLOUR_R_BLUE     = 0x10, // Royal_Blue
            E_COLOUR_B_BLUE     = 0x20, // Baby_Blue
            E_COLOUR_AQUA       = 0x30, // Aqua
            E_COLOUR_MINT       = 0x40, // Mint
            E_COLOUR_S_GREEN    = 0x50, // Seafoam_Green
            E_COLOUR_GREEN      = 0x60, //Green
            E_COLOUR_L_GREEN    = 0x70, // Lime_Green
            E_COLOUR_YELLOW     = 0x80, //Yellow
            E_COLOUR_Y_ORANGE   = 0x90, // Yellow_Orange
            E_COLOUR_ORANGE     = 0xA0, // Orange
            E_COLOUR_RED        = 0xB0, //Red
            E_COLOUR_PINK       = 0xC0, // Pink
            E_COLOUR_FUSIA      = 0xD0, // Fusia
            E_COLOUR_LILAC      = 0xE0, // Lilac
            E_COLOUR_LAVENDAR   = 0xF0, // Lavendar
            E_COLOUR_MAX        = 0xFF,
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

        enum ePriority
        {
            E_DEFAULT_PRIO = 0,
            E_SYSTEM_PRIO = 1,
            E_USER_PRIO = 2,
        };

        enum eAutoDimming
        {
            E_AUTO_DIMMING_OFF = 0,
            E_AUTO_DIMMING_ON
        };

        ///////////////////////////////////
        /// \brief init
        /// \return
        ///
        virtual bool_t create() = 0;

        ///////////////////////////////////
        /// \brief destroy
        /// \return
        ///
        virtual bool_t destroy() = 0;

        //////////////////////////////////
        /// \brief sendTurnOnReq
        /// \param a_eGroup
        /// \return
        ///
        virtual bool_t sendTurnOnReq(eGroup a_eGroup, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        /////////////////////////////////
        /// \brief sendTurnOffReq
        /// \param a_eGroup
        /// \return
        ///
        virtual bool_t sendTurnOffReq(eGroup a_eGroup, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        /////////////////////////////////
        /// \brief sendWhiteReq
        /// \param a_eGroup
        /// \return
        ///
        virtual bool_t sendWhiteReq(eGroup a_eGroup, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        /////////////////////////////////
        /// \brief sendBrightnessReq
        /// \param a_eGroup
        /// \param a_uiProc
        /// \return
        ///
        virtual bool_t sendBrightnessReq(eGroup a_eGroup, u_int8_t a_uiProc = 100, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        ////////////////////////////////
        /// \brief sendColourReq
        /// \param a_eGroup
        /// \param a_eColour
        /// \return
        ///
        virtual bool_t sendColourReq(eGroup a_eGroup, eColours a_eColour, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        ////////////////////////////////
        /// \brief sendColourReq
        /// \param a_eGroup
        /// \param a_uiColour
        /// \return
        ///
        virtual bool_t sendColourReq(eGroup a_eGroup, u_int8_t a_uiColour, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        ////////////////////////////////
        /// \brief enableAutoDimming
        /// \param a_fEnable
        /// \return
        ///
        virtual bool_t setAutoDimming(eAutoDimming a_eEnable, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        ////////////////////////////////
        /// \brief setMinimumLuxValue
        /// \param a_eValue
        /// \param a_ePriority
        /// \return
        ///
        virtual bool_t setMinimumLuxValue(u_int32_t a_eValue, ePriority a_ePriority = E_DEFAULT_PRIO) = 0;

        /////////////////////////////
        /// \brief ~IsmartLightsInterface
        ///
        virtual ~IsmartLightsInterface(){};
    };

}
}
#endif // ISMARTLIGHTSINTERFACE

