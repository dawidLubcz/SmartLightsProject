#include <iostream>
#include "IsmartLightsInterface.h"
#include "CSmartlightsinterface.h"
#include <thread>
#include <unistd.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;

    smartLights::smartLightsFrontend::IsmartLightsInterface* _pIn = new smartLights::smartLightsFrontend::CSmartLightsInterface();
    _pIn->create();

    char cChoose = ' ';
    cout<< "Choose an option:\n w-white, \nr-red, \ny-yellow, \nb-blue, \ng-green, \nq-quit"<<endl;


    while(cChoose != 'q')
    {
        cin>>cChoose;
        switch(cChoose)
        {
            case 'w':
            {
                _pIn->sendWhiteReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL);
            }break;

            case 'r':
            {
                _pIn->sendColourReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL,smartLights::smartLightsFrontend::IsmartLightsInterface::E_COLOUR_RED);
            }break;

            case 'y':
            {
                _pIn->sendColourReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL,smartLights::smartLightsFrontend::IsmartLightsInterface::E_COLOUR_YELLOW);
            }break;

            case 'b':
            {
                _pIn->sendColourReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL,smartLights::smartLightsFrontend::IsmartLightsInterface::E_COLOUR_B_BLUE);
            }break;

            case 'g':
            {
                _pIn->sendColourReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL,smartLights::smartLightsFrontend::IsmartLightsInterface::E_COLOUR_GREEN);
            }break;

            case 'q':
            {
                _pIn->destroy();
            }break;

        }
//        _pIn->sendTurnOnReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL);
//        usleep(1000000);
//        _pIn->sendTurnOffReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL);
//        usleep(1000000);
//        _pIn->sendBrightnessReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL,100);
//        usleep(1000000);
//       _pIn->sendColourReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL,0x15);
//       usleep(1000000);

//        usleep(1000000);
//          _pIn->sendBrightnessReq(smartLights::smartLightsFrontend::IsmartLightsInterface::E_GROUP_ALL, 100);
    }
    return 0;
}

