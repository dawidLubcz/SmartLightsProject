#include <iostream>
#include "ApplicationMngr/CAppMngr.h"
#include "../SmartLightsCommon/common.h"

#ifdef QT
#include <QCoreApplication>
#endif

#ifdef QT
int main(int argc, char *argv[])
#else
int main(void)
#endif
{
#ifdef QT
    QCoreApplication a(argc, argv);
#endif
    smartLights::smartLightsBackend::CAppMngr _oAppMngr;
    _oAppMngr.create();
    _oAppMngr.init();
    _oAppMngr.run();

#ifndef QT
    return 0;
#else
    return a.exec();
#endif
}
