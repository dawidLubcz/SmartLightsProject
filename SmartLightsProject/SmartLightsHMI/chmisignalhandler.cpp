#include "chmisignalhandler.h"
#include <QDebug>
CHMISignalHandler::CHMISignalHandler()
    :m_pIn(0)
{

}

void CHMISignalHandler::init()
{
    if(0 == m_pIn)
    {
        m_pIn = new smartLights::smartLightsFrontend::CSmartLightsInterface();
        m_pIn->create();
    }
}

void CHMISignalHandler::turnOnSlot()
{
    if(0 != m_pIn)
    {
        m_pIn->sendTurnOnReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL, smartLights::smartLightsFrontend::IsmartLightsInterface::E_USER_PRIO);
    }
}

void CHMISignalHandler::turnOffSlot()
{
    if(0 != m_pIn)
    {
        m_pIn->sendTurnOffReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL, smartLights::smartLightsFrontend::IsmartLightsInterface::E_USER_PRIO);
    }
}

void CHMISignalHandler::setColSlot(int a_iColour)
{
    if(0 != m_pIn)
    {
        m_pIn->sendColourReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL,a_iColour, smartLights::smartLightsFrontend::IsmartLightsInterface::E_USER_PRIO);
    }
}

void CHMISignalHandler::setBrightSlot(int a_iBrig)
{
    if(0 != m_pIn)
    {
        m_pIn->sendBrightnessReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL, a_iBrig, smartLights::smartLightsFrontend::IsmartLightsInterface::E_USER_PRIO);
    }
}

void CHMISignalHandler::setWhiteSlot()
{
    if(0 != m_pIn)
    {
        m_pIn->sendWhiteReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL, smartLights::smartLightsFrontend::IsmartLightsInterface::E_USER_PRIO);
    }
}

void CHMISignalHandler::setAutoDimming(int enabled)
{
    if(0 != m_pIn)
    {
        m_pIn->setAutoDimming((smartLights::smartLightsFrontend::IsmartLightsInterface::eAutoDimming)enabled, smartLights::smartLightsFrontend::IsmartLightsInterface::E_USER_PRIO);
    }
    qDebug() << "######## setAutoDimming" << enabled << "\n";
}

void CHMISignalHandler::setMinimumLuxVal(int val)
{
    if(0 != m_pIn)
    {
        m_pIn->setMinimumLuxValue(val, smartLights::smartLightsFrontend::IsmartLightsInterface::E_USER_PRIO);
    }
    qDebug() << "######## setMinimumLuxVal" << val << "\n";
}


