#ifndef CLIGHTSINTERFACESFACTORY_H
#define CLIGHTSINTERFACESFACTORY_H

#include "ILightSourceInterface.h"
#include <memory>

namespace smartLights
{
namespace smartLightsBackend
{
    class CLightsInterfacesFactory
    {
    public:
        ///////////////////////////////////
        /// \brief CLightsInterfacesFactory
        ///
        CLightsInterfacesFactory();

        ///////////////////////////////////
        /// \brief getInterface
        /// \param a_eInterface
        /// \return
        ///
        static std::unique_ptr<ILightSourceInterface> getInterface(ILightSourceInterface::eInterfaces a_eInterface);
    };
}
}
#endif // CLIGHTSINTERFACESFACTORY_H
