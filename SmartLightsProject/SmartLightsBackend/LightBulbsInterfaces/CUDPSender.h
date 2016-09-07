#ifndef CUDPSENDER_H
#define CUDPSENDER_H

#include "ILightSourceInterface.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>

class CUDPSender
{

public:

    /////////////////////////////
    /// \brief sendMessage
    /// \param a_aiMessage
    /// \param a_iSize
    /// \return
    ///
    static bool_t sendMessage(char a_aiMessage[] , uint8_t a_iSize);

private:
    //////////////////////
    /// \brief CUDPSender
    ///
    CUDPSender();

    //////////////////////////
    /// \brief CUDPSender
    /// \param a_pcIpAddress
    /// \param a_iPort
    ///
    CUDPSender(char* a_pcIpAddress, int a_iPort);

    //////////////////////////////
    /// \brief send
    /// \param a_aiMessage
    /// \param a_iSize
    /// \return
    ///
    bool_t send (char a_aiMessage[] , uint8_t a_iSize);

    //////////////////////////
    /// \brief m_pcIpAddress
    ///
    const char* m_pcIpAddress;
    ////////////////////////
    /// \brief m_iPort
    ///
    const int m_iPort;
};

#endif // CUDPSENDER_H
