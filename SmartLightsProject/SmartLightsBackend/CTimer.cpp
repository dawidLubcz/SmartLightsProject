#include "CTimer.h"

namespace smartLights
{
    void* workerFriend(void *arg)
    {
        CTimer* pTmp = static_cast<CTimer*>(arg);
        pTmp->workerThread();
        return arg;
    }

    CTimer::CTimer(uint64_t a_u64Miliseconds, void(*a_pFunction)(void)) : m_u64MiliSeconds(0)
    {

    }

    void CTimer::startTimer(uint64_t a_u64Miliseconds, void (*a_pFunction)())
    {
        m_u64MiliSeconds = a_u64Miliseconds;
        pthread_create(&m_oThreadWorker, &m_oAttr, threadRoutineMotionSensor, (void*)this);
    }

    void CTimer::workerThread()
    {

    }
}
