#ifndef CTIMER_H
#define CTIMER_H

#include "../../SmartLightsCommon/CCommonTypes.h"

#include <stdint.h>
#include <pthread.h>

namespace smartLights
{
    class CTimer
    {
    public:
        CTimer(uint64_t a_u64Miliseconds, void(*a_pFunction)(void));
        void static startTimer(uint64_t a_u64Miliseconds, void(*a_pFunction)(void));
    private:
        friend void* workerFriend(void *arg);
        void workerThread();

        uint64_t m_u64MiliSeconds;
        pthread_t m_oThreadWorker;
    };
}

#endif // CTIMER_H
