#include "CMsgQueueHandler.h"

#include "../SmartLightsCommon/CLogger.h"

#undef PRINT_PREFIX
#define PRINT_PREFIX "SM:CMsgQueueHandler: "

namespace smartLights
{
namespace smartLightsBackend
{

    CMsgQueueHandler::CMsgQueueHandler( const char* a_pcCommonMsqQueueFile
                                      , char a_cProjectID
                                      , CAppMngr* a_pAppMngr
                                      )
        : m_pcMsqQueueFile(a_pcCommonMsqQueueFile)
        , m_cProjectID(a_cProjectID)
        , m_pAppMngr(a_pAppMngr)
        , m_i32MsgQueueID(-1)
        , m_fRun(false)
#ifndef QT
        , oThreadWorker(0)
#endif
        , m_fInitialized(false)
        , m_oMutex()
    {

    }

    bool_t CMsgQueueHandler::init()
    {
        PRINT_INF("init()");

        bool_t _fResult = false;
        key_t _u32MsgQueueKey = -1;

#ifndef QT
        pthread_mutex_init(&m_oMutex, NULL);
#endif
        _u32MsgQueueKey = ftok(m_pcMsqQueueFile
                              ,m_cProjectID);
        if(-1 < _u32MsgQueueKey)
        {
            if(-1 == (m_i32MsgQueueID = msgget(_u32MsgQueueKey, 0644 | IPC_CREAT)))
            {
                PRINT_ERR("init(), msgget FAILED");
                perror("msgget");
            }
            else
            {
                _fResult = true;
                m_fInitialized = true;
            }
        }
        else
        {
            PRINT_ERR("init(), ftok FAILED");
            perror("ftok");
        }
        return _fResult;
    }

    bool_t CMsgQueueHandler::deinit()
    {
        PRINT_INF("deinit()");

        bool_t fResult = true;
        if(-1 == msgctl(m_i32MsgQueueID, IPC_RMID, NULL))
        {
            fResult = false;
            m_fInitialized = false;

            PRINT_ERR("deinit(), msgctl FAILED");
            perror("msgctl");
        }
        return fResult;
    }

#ifndef QT
    void CMsgQueueHandler::start()
    {
        PRINT_INF("start()");

        if(false != m_fInitialized)
        {
            m_fRun = true;
            int iRetVal = pthread_create(&oThreadWorker, 0, threadRoutine, (void*)this);

            if(iRetVal)
            {
                setRunningState(false);
                PRINT_ERR("CMsgQueueHandler::run(), pthread_create FAILED");
                perror("thread_create");
            }
        }
        else
        {
            PRINT_ERR("CMsgQueueHandler::run(), NOT INITIALIZED");
        }

        return;
    }

    void CMsgQueueHandler::workerThread()
    {
        PRINT_INF("CMsgQueueHandler::workerThread: run PT");
        setRunningState(true);

        while(getRunningState())
        {
            smartLights::smartLightsFrontend::CSmartLightsInterface::sMessage_t _sBuf;
            if(-1 == msgrcv(m_i32MsgQueueID, &_sBuf, sizeof (_sBuf), 0, 0))
            {
                PRINT_ERR("CMsgQueueHandler::workerThread(), msgrcv FAILED");
                perror("msgrcv");
            }
            else
            {
                if(0 != m_pAppMngr)
                {
                    m_pAppMngr->handleMessage(_sBuf.mmsg);

                    PRINT_INF("CMsgQueueHandler::workerThread: msg received ID: %d\n", _sBuf.mmsg.m_iID);
                }
            }
        }
        PRINT_INF("CMsgQueueHandler::workerThread: stop\n");
        return;
    }

    bool_t CMsgQueueHandler::stop()
    {
        setRunningState(false);
        pthread_join(oThreadWorker, 0);
        return true;
    }

    void* threadRoutine(void *arg)
    {
        CMsgQueueHandler* pTmp = static_cast<CMsgQueueHandler*>(arg);
        pTmp->workerThread();
        return arg;
    }

#else
    void CMsgQueueHandler::run()
    {
        PRINT_INF("workerThread: run QT\n");
        m_fRun = true;
        uint8_t u8Cntr = 0;
        while(false != m_fRun)
        {
            smartLightsFrontend::CSmartLightsInterface::sMessage_t _sBuf;
            if(-1 == msgrcv(m_i32MsgQueueID, &_sBuf, sizeof (_sBuf), 0, 0))
            {
                PRINT_ERR("workerThread(), msgrcv FAILED");
                perror("msgrcv");

                if(10 > u8Cntr)++u8Cntr;else break;
            }
            else
            {
                if(0 != m_pAppMngr)
                {
                    m_pAppMngr->handleMessage(_sBuf.mmsg);

                    PRINT_INF("workerThread: msg received ID: %d\n", _sBuf.mmsg.m_iID);
                }
            }
        }
        PRINT_INF("workerThread: stop");
        return;
    }

    bool_t CMsgQueueHandler::stop()
    {
        m_fRun = false;
        return true;
    }
#endif

    void CMsgQueueHandler::setRunningState(bool_t a_sRun)
    {
#ifndef QT
        pthread_mutex_lock (&m_oMutex);
        m_fRun = a_sRun;
        pthread_mutex_unlock(&m_oMutex);
#else
        m_oMutex.lock();
        m_fRun = a_sRun;
        m_oMutex.unlock();
#endif
    }

    bool_t CMsgQueueHandler::getRunningState()
    {
        bool_t fRetVal;
#ifndef QT
        pthread_mutex_lock (&m_oMutex);
        fRetVal = m_fRun;
        pthread_mutex_unlock(&m_oMutex);
#else
        m_oMutex.lock();
        fRetVal = m_fRun;
        m_oMutex.unlock();
#endif
        return fRetVal;
    }

    bool_t CMsgQueueHandler::isRunning()
    {
        return getRunningState();
    }

}
}

