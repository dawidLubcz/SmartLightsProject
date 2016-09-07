#ifndef CDISTANCESENSOR_H
#define CDISTANCESENSOR_H

#include "ISensorCommonInterface.h"

#include <chrono>

namespace smartLights
{
namespace smartLightsBackend
{
    /////////////////////////////////////////////////////
    /// \brief The CDistanceSensor class
    ///
    class CDistanceSensor : public ISensorCommonInterface
    {
        typedef std::chrono::high_resolution_clock high_resolution_clock;
        typedef std::chrono::milliseconds milliseconds;

    public:

        //////////////////////////////////////
        /// \brief CDistanceSensor
        /// \param a_eSensorID
        /// \param a_u8Trig
        /// \param a_u8Echo
        ///
        CDistanceSensor(eSensorID a_eSensorID, uint8_t a_u8Trig, uint8_t a_u8Echo);

        ////////////////////
        ///
        ~CDistanceSensor();

        ////////////////
        /// \brief init
        /// \return
        ///
        bool_t init();

        ////////////////
        /// \brief deinit
        /// \return
        ///
        bool_t deinit();

        /////////////////////////////////
        /// \brief setParentPoiter
        /// \param a_pParent
        /// \return
        ///
        bool_t setParentPoiter(ISensorCommonInterfaceListener* a_pParent);

        /////////////////////////////
        /// \brief isAvailable
        /// \return
        ///
        eReturnValue isAvailable();

        ////////////////////////////
        /// \brief isActive
        /// \return
        ///
        eReturnValue isActive();

        ////////////////////////////
        /// \brief startInThread
        /// \return
        ///
        eReturnValue start();

        ///////////////////////////
        /// \brief stopThread
        /// \return
        ///
        eReturnValue stopThread();

        ///////////////////////////
        /// \brief unleashSensor
        /// \param a_u8Repeat
        /// \param a_u32TimePeriod
        /// \return
        ///
        eReturnValue unleashSensor(uint8_t a_u8Repeat, uint32_t a_u32TimePeriod);

        /////////////////////////
        /// \brief getSensorID
        /// \return
        ///
        eSensorID getSensorID();

    private:
        ////////////////////////
        /// \brief m_pParent
        ///
        ISensorCommonInterfaceListener * m_pParent;

        ///////////////////////
        /// \brief m_eSensorID
        ///
        const eSensorID m_eSensorID;

        ////////////////////////
        /// \brief m_iTrigger
        ///
        const uint8_t m_iTrigger;

        ///////////////////////
        /// \brief m_iEcho
        ///
        const uint8_t m_iEcho;

        ///////////////////////
        /// \brief m_oTimePoint
        ///
        high_resolution_clock::time_point m_oTimePoint;

        ///////////////////////
        /// \brief m_isActive
        ///
        bool_t m_isActive;
    };
}
}

#endif // CDISTANCESENSOR_H
