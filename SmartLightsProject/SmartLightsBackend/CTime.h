#ifndef CTIME_H
#define CTIME_H

#include <stdint.h>
#include <ctime>
#include <chrono>

#include "common.h"

namespace smartLights
{
namespace smartLightsBackend
{

    class CTime
    {
        typedef std::chrono::system_clock clock;

    public:
        ////////////////
        /// \brief CTime
        ///
        CTime();

        //////////////////////
        /// \brief getDayTime
        /// \param a_u8Hours
        /// \param a_u8Minutes
        /// \return
        ///
        bool_t getDayTime(uint8_t &a_u8Hours, uint8_t &a_u8Minutes);

        ///////////////////////
        /// \brief getDayData
        /// \param a_u8Day
        /// \param a_u8Month
        /// \param a_u8Year
        /// \return
        ///
        bool_t getDayData(uint8_t &a_u8Day, uint8_t &a_u8Month, uint8_t &a_u8Year);

        //////////////////
        /// \brief getTM
        /// \return
        ///
        tm getTM();

        //////////////////////
        /// \brief getDayTimeS
        /// \param a_u8Hours
        /// \param a_u8Minutes
        /// \return
        ///
        static bool_t getDayTimeS(uint8_t &a_u8Hours, uint8_t &a_u8Minutes);

        ///////////////////////
        /// \brief getData
        /// \param pcData
        /// \param a_u32length
        /// \return
        ///
        bool_t getData(char* pcData, uint32_t a_u32length);

    private:

        ////////////////////////
        /// \brief getTime
        /// \return
        ///
        time_t getTime();
    };

}
}

#endif // CTIME_H
