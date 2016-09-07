#include "CTime.h"
#include <string.h>
#include <cstdio>

namespace smartLights
{
namespace smartLightsBackend
{

    size_t strcpy_s(char *dest, size_t n, char *source)
    {
        return snprintf(dest, n, "%s", source);
    }

    CTime::CTime()
    {

    }

    bool_t CTime::getDayTime(uint8_t &a_u8Hours, uint8_t &a_u8Minutes)
    {
        time_t date = getTime();
        tm local_tm = *localtime(&date);

        a_u8Hours = local_tm.tm_hour;
        a_u8Minutes = local_tm.tm_min;
        return true;
    }

    bool_t CTime::getDayData(uint8_t &a_u8Day, uint8_t &a_u8Month, uint8_t &a_u8Year)
    {
        time_t date = getTime();
        tm local_tm = *localtime(&date);

        a_u8Day = local_tm.tm_mday;
        a_u8Month = local_tm.tm_mon + 1;
        a_u8Year = local_tm.tm_year;
        return true;
    }

    tm CTime::getTM()
    {
        time_t date = getTime();
        return *localtime(&date);
    }

    bool_t CTime::getDayTimeS(uint8_t &a_u8Hours, uint8_t &a_u8Minutes)
    {
        CTime tempObj;
        return tempObj.getDayTime(a_u8Hours, a_u8Minutes);
    }

    bool_t CTime::getData(char *pcData, uint32_t a_u32length)
    {
        time_t date = getTime();
        strcpy_s(pcData, a_u32length, ctime(&date));
        return true;
    }

    time_t CTime::getTime()
    {
        clock::time_point oNow = clock::now();
        std::time_t date;
        date = clock::to_time_t(oNow);
        return date;
    }

}
}
