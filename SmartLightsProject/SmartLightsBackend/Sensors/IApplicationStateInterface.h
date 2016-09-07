#ifndef ISENSORINTERFACE_H
#define ISENSORINTERFACE_H

#include "common.h"

#include <stdint.h>

namespace smartLights
{
namespace smartLightsBackend
{
    ///////////////////
    /// \brief The ePersonState enum
    ///
    enum ePersonState
    {
        E_PERSON_DEFAULT = 0,
        E_PERSON_WENT_OUT_HIGH,
        E_PERSON_WENT_OUT_LOW,
        E_PERSON_PRESENT,
        E_PERSON_ABSENT
    };

    ///////////////////////////
    /// \brief The sCurrentState struct
    ///
    struct sCurrentState
    {
        uint8_t m_iGroup;           // 0- All or 1-4

        ePersonState m_eLightState; //

        uint8_t m_iPhotoresistorRes;    // 0-100%

        uint32_t m_uiLightIntensityLx;
    };

    class IApplicationStateInterfaceListener
    {
    public:
        virtual void handleStateChanged(sCurrentState a_sCurrState) = 0;
        virtual void handleLightIntesityChanged(uint32_t a_ui32LxVal) = 0;
    };

    class IApplicationStateInterface
    {
    public:
        ///////////////////////////////////////
        /// \brief ~IApplicationStateInterface
        ///
        virtual ~IApplicationStateInterface(){}

        //////////////////////////
        /// \brief init
        /// \return
        ///
        virtual bool_t init() = 0;

        ///////////////////////////
        /// \brief deinit
        /// \return
        ///
        virtual bool_t deinit() = 0;

        /////////////////////////
        /// \brief start
        ///
        virtual void start() = 0;

        /////////////////////////
        /// \brief start
        ///
        virtual void stop() = 0;

        ////////////////////////////////////
        /// \brief getState
        /// \return
        ///
        virtual sCurrentState getState() = 0;

        ////////////////////////////////////
        /// \brief registerListener
        /// \param a_pListener
        /// \return
        ///
        virtual bool_t registerListener(IApplicationStateInterfaceListener* a_pListener) = 0;

        ///////////////////////////////////
        /// \brief deregisterListener
        /// \param a_pListener
        /// \return
        ///
        virtual bool_t deregisterListener(IApplicationStateInterfaceListener* a_pListener) = 0;
    };
}
}

#endif // ISENSORINTERFACE_H

