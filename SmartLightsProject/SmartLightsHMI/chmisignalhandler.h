#ifndef CHMISIGNALHANDLER_H
#define CHMISIGNALHANDLER_H
#include <QObject>
#include <QColor>

#include "../SmartLightsFrontEnd/IsmartLightsInterface.h"
#include "../SmartLightsFrontEnd/CSmartlightsinterface.h"
using namespace smartLights;
class CHMISignalHandler : public QObject
{
    Q_OBJECT
public:
    void init();
    CHMISignalHandler();
    ~CHMISignalHandler()
    {
        if(0 != m_pIn)
        {
            delete m_pIn;
            m_pIn = 0;
        }
    }

public slots:
    void turnOnSlot();
    void turnOffSlot();
    void setColSlot(int a_iColour);
    void setBrightSlot(int a_iBrig);
    void setWhiteSlot();
    void setAutoDimming(int enabled);
    void setMinimumLuxVal(int val);

private:
    smartLights::smartLightsFrontend::IsmartLightsInterface* m_pIn;
};

#endif // CHMISIGNALHANDLER_H
