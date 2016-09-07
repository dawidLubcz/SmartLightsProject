#include "CLightsInterfacesFactory.h"

#include "CMilightSource.h"

namespace smartLights
{
namespace smartLightsBackend
{

    CLightsInterfacesFactory::CLightsInterfacesFactory()
    {

    }

    std::unique_ptr<ILightSourceInterface> CLightsInterfacesFactory::getInterface(ILightSourceInterface::eInterfaces a_eInterface)
    {
        std::unique_ptr<ILightSourceInterface> pIface = nullptr;
        switch(a_eInterface)
        {
            case ILightSourceInterface::E_IF_MILIGTH:
            {
                pIface = std::unique_ptr<ILightSourceInterface>(new CMilightSource());
            }
            break;

            default:
            {

            }
            break;
        }
        return pIface;
    }

}
}
