#ifndef CSMARTLIGHTSINTERFACE_H
#define CSMARTLIGHTSINTERFACE_H

#include "IsmartLightsInterface.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//#include "../../SmartLightsCommon/CCommonTypes.h"
#include "../SmartLightsCommon/common.h"

namespace smartLights
{
namespace smartLightsFrontend
{
    class CSmartLightsInterface : public IsmartLightsInterface
    {
    public:
        CSmartLightsInterface();

        enum eCommon
        {
            E_MAX_PARAMS_COUNT = 3,
        };

        enum eInterfaceMethodID
        {
            E_SEND_TURN_ON_REQ,
            E_SEND_TURN_OFF_REQ,
            E_SEND_WHITE_REQ,
            E_SEND_BRIGHTNESS_REQ,
            E_SEND_COLOUR_REQ_E,
            E_SEND_COLOUR_REQ_V,
            E_SEND_SET_AUTO_DIMMING,
            E_SEND_SET_MINIMUM_LUX_VAL,
        };

        typedef struct
        {
            u_int8_t m_iPriority;
            u_int8_t m_iID;
            u_int8_t m_iGroup;
            u_int8_t m_aParamsCntr;
            int16_t m_aParams[E_MAX_PARAMS_COUNT];

        }sData_t;

        typedef struct
        {
            long mtype;
            sData_t mmsg;
        }sMessage_t;

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t create();

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t destroy();

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t sendTurnOnReq(eGroup a_eGroup, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t sendTurnOffReq(eGroup a_eGroup, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t sendWhiteReq(eGroup a_eGroup, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t sendBrightnessReq(eGroup a_eGroup, u_int8_t a_uiProc = 100, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t sendColourReq(eGroup a_eGroup, eColours a_eColour, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t sendColourReq(eGroup a_eGroup, u_int8_t a_uiColour, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t setAutoDimming(eAutoDimming a_eEnable, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// @see IsmartLightsInterface
        bool_t setMinimumLuxValue(u_int32_t a_eValue, ePriority a_ePriority = E_DEFAULT_PRIO);

        //////////////////////////////////
        /// \brief sendMessage
        /// \param a_sMsg
        /// \return
        ///
        bool_t sendMessage(sMessage_t *a_sMsg);

    private:
        // members
        int32_t m_i32MsgQueueID;
    };

}
}

#endif // CSMARTLIGHTSINTERFACE_H
