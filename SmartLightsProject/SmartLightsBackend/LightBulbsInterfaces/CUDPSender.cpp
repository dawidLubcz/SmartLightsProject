#include "CUDPSender.h"

#include "../SmartLightsCommon/CLogger.h"

#undef PRINT_PREFIX
#define PRINT_PREFIX "SB:CUDPSender: "

CUDPSender::CUDPSender():
    m_pcIpAddress("10.10.100.255") , // default IP
    m_iPort(8899) // default port
{
    //
}

CUDPSender::CUDPSender(char *a_pcIpAddress, int a_iPort):
    m_pcIpAddress(a_pcIpAddress) ,
    m_iPort(a_iPort)
{
    //
}



bool_t CUDPSender::send (char a_aiMessage[] , uint8_t a_iSize)
{
    bool_t _iRetVal = false;
    int32_t _iBroadcastPerm = 1;

    int32_t _iUdpSocket = socket (AF_INET, SOCK_DGRAM, 0);

    if(setsockopt(_iUdpSocket, SOL_SOCKET, SO_BROADCAST, (void*)&_iBroadcastPerm, sizeof(_iBroadcastPerm)) < 0)
        _iBroadcastPerm = 0;

    if ( (_iUdpSocket >= 0) && (_iBroadcastPerm > 0) && (0 < a_iSize) )
    {
        struct sockaddr_in _sDestSockAddr;
        memset (&_sDestSockAddr, 0, sizeof (_sDestSockAddr));
        _sDestSockAddr.sin_family = AF_INET;
        _sDestSockAddr.sin_port = htons (m_iPort);
        _sDestSockAddr.sin_addr.s_addr = inet_addr (m_pcIpAddress);

        int32_t bytesSent = sendto (_iUdpSocket, a_aiMessage, a_iSize, 0, (const struct sockaddr*)&_sDestSockAddr, sizeof (_sDestSockAddr));

        if (bytesSent >= 0)
        {
            _iRetVal = true;

            for(int i=0; i<a_iSize; i++)
            {
                PRINT_INF("UDP was send, msg: 0x%x, IP: %s, port: %d", (uint16_t)a_aiMessage[i], m_pcIpAddress, m_iPort);
            }
        }
        else
        {
            PRINT_ERR("Failed to send data: %s", strerror (errno));
        }

        close (_iUdpSocket);
    }
    else
    {
        PRINT_ERR("Failed to open UDP socket: ", strerror (errno));
    }

    return _iRetVal;
}

bool_t CUDPSender::sendMessage(char a_aiMessage[] , uint8_t a_iSize)
{
    CUDPSender oSender;
    return oSender.send(a_aiMessage, a_iSize);
}
