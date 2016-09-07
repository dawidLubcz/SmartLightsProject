#ifndef CMSGQUEUEHANDLER_H
#define CMSGQUEUEHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "common.h"
#include "CAppMngr.h"

#include "SmartLightsFrontEnd/CSmartlightsinterface.h"

#ifndef QT
    #include <pthread.h>
#else
    #include <QThread>
    #include <QMutex>
#endif

namespace smartLights
{
namespace smartLightsBackend
{

    class CAppMngr;

#ifndef QT
    //////////////////////////////
    /// \brief threadRoutine
    /// \param arg
    /// \return
    ///
    void* threadRoutine(void* arg);
#endif

    //////////////////////////////
    /// \brief The CMsgQueueHandler class
    ///
#ifndef QT
    class CMsgQueueHandler
#else
    class CMsgQueueHandler : public QThread
#endif
    {
    friend void* threadRoutine(void *arg);

    public:
        /////////////////////////////////
        /// \brief CMsgQueueHandler
        /// \param a_pcCommonMsqQueueFile
        /// \param a_cProjectID
        /// \param a_pAppMngr
        ///
        CMsgQueueHandler( const char* a_pcCommonMsqQueueFile
                        , char a_cProjectID
                        , CAppMngr* a_pAppMngr
                        );

        /////////////////////
        /// \brief init
        /// \return
        ///
        bool_t init();

        ////////////////////
        /// \brief deinit
        /// \return
        ///
        bool_t deinit();

#ifndef QT
        void start();
#else
        ////////////////////
        /// \brief run
        /// \return
        ///
        void run();
#endif

        ///////////////////
        /// \brief stop
        /// \return
        ///
        bool_t stop();

        ///////////////////
        /// \brief isRunning
        /// \return
        ///
        bool_t isRunning();

    private:

#ifndef QT
        ///////////////////////
        /// \brief workerThread
        ///
        void workerThread();
#endif

        ////////////////////////////////////
        /// \brief setRunningState
        /// \param a_sRun
        ///
        void setRunningState(bool_t a_sRun);

        ////////////////////////
        /// \brief getRunningState
        /// \return
        ///
        bool_t getRunningState();

        /////////////////////////////
        /// \brief m_pcMsqQueueFile
        ///
        const char* m_pcMsqQueueFile;

        ///////////////////////
        /// \brief m_cProjectID
        ///
        char m_cProjectID;

        //////////////////////
        /// \brief m_pAppMngr
        ///
        CAppMngr* m_pAppMngr;

        //////////////////////////
        /// \brief m_i32MsgQueueID
        ///
        int32_t m_i32MsgQueueID;

        //////////////////////////
        /// \brief m_fRun
        ///
        bool_t m_fRun;

#ifndef QT
        /////////////////////////
        /// \brief oThreadWorker
        ///
        pthread_t oThreadWorker;
#endif

        ////////////////////////
        /// \brief m_fInitialized
        ///
        bool_t m_fInitialized;

#ifndef QT
        ////////////////////////
        /// \brief m_oMutex
        ///
        pthread_mutex_t m_oMutex;
#else
        /////////////////
        /// \brief m_oMutex
        ///
        QMutex m_oMutex;
#endif
    };

}
}

#endif // CMSGQUEUEHANDLER_H
