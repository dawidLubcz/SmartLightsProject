#ifndef ISENSORCOMMONINTERFACE
#define ISENSORCOMMONINTERFACE

#include <stdint.h>
#include "common.h"

namespace smartLights
{
namespace smartLightsBackend
{

    class ISensorCommonInterfaceListener;

    ///////////////////////////////
    /// \brief The ISensorCommonInterface class
    ///
    class ISensorCommonInterface
    {
    public:

        //////////////////////////////
        /// \brief The eSensorID enum
        ///
        enum eSensorID
        {
            E_SENSOR_MIN = 0,
            E_MOVE_SENSOR_1 = 0,
            E_MOVE_SENSOR_2,
            E_MOVE_SENSOR_3,
            E_DISTANCE_SENSOR,
            E_PHOTO_R_SENSOR,
            E_I2C_LIGHT_SENSOR,
            E_SENSOR_MAX
        };

        ////////////////////////////
        /// \brief The eReturnValue enum
        ///
        enum eReturnValue
        {
            E_TRUE = 0,
            E_FALSE,
            E_NOT_SUPPORTED,
            E_NOT_IMPLEMENTED,
        };

        ////////////////////////////
        /// \brief The eGPIO enum
        ///
        enum eGPIO
        {
            E_DEFAULT_GPIO = 255
        };

        //////////////////////////
        ///
        typedef struct
        {
            int32_t m_iSensorID;
            void* m_pvData;
        }sSensorCommonData;

        ///////////////////////////////////
        /// \brief ~ISensorCommonInterface
        ///
        virtual ~ISensorCommonInterface(){}

        //////////////////////////////////
        /// \brief init
        /// \return
        ///
        virtual bool_t init() = 0;

        /////////////////////////////////
        /// \brief deinit
        /// \return
        ///
        virtual bool_t deinit() = 0;

        /////////////////////////////////
        /// \brief setParentPoiter
        /// \param a_pParent
        /// \return
        ///
        virtual bool_t setParentPoiter(ISensorCommonInterfaceListener* a_pParent) = 0;

        ////////////////////////////////
        /// \brief isAvailable
        /// \return
        ///
        virtual eReturnValue isAvailable() = 0;

        ////////////////////////////////
        /// \brief isActive
        /// \return
        ///
        virtual eReturnValue isActive() = 0;

        ////////////////////////////////
        /// \brief startInThread
        /// \return
        ///
        virtual eReturnValue start() = 0;

        ///////////////////////////////
        /// \brief stopThread
        /// \return
        ///
        virtual eReturnValue stopThread() = 0;

        ///////////////////////////////
        /// \brief unleashSensor
        /// \param a_u8Repeat
        /// \param a_u32TimePeriod
        /// \return
        ///
        virtual eReturnValue unleashSensor(uint8_t a_u8Repeat, uint32_t a_u32TimePeriod) = 0;

        ///////////////////////////////
        /// \brief getSensorID
        /// \return
        ///
        virtual eSensorID getSensorID() = 0;
    };

    /////////////////////////////////////
    /// \brief The ISensorCommonInterfaceListener class
    ///
    class ISensorCommonInterfaceListener
    {
    public:
        /////////////////////////////
        /// \brief handleSensorEvent
        /// \param a_sData
        ///
        virtual void handleSensorEvent(ISensorCommonInterface::sSensorCommonData a_sData) = 0;
    };
}
}

#endif // ISENSORINTERFACE_H

