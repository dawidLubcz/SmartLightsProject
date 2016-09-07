#ifndef CMAPPERTOLEDCOMMAND_H
#define CMAPPERTOLEDCOMMAND_H

#include "CommonTypes.h"
#include "ILightSourceInterface.h"

class CMapperToLedCommand
{
public:
    //////////////////////////////
    /// \brief CMapperToLedCommand
    ///
    CMapperToLedCommand();

    ///////////////////////////////////////
    /// \brief mapGroupToHex
    /// \param a_eGroup
    /// \param a_eHEX
    /// \return
    ///
    commonTypes::sender::bool_t mapGroupToHex(ILightSourceInterface::eGroup a_eGroup, commonTypes::limitless::eGroupOn &a_eHEX);

    ////////////////////////////////////////
    /// \brief mapGroupToHex
    /// \param a_eGroup
    /// \param a_eHEX
    /// \return
    ///
    commonTypes::sender::bool_t mapGroupToHex(ILightSourceInterface::eGroup a_eGroup, commonTypes::limitless::eGroupOff &a_eHEX);

    ////////////////////////////////////////
    /// \brief mapGroupToHex
    /// \param a_eGroup
    /// \param a_eHEX
    /// \return
    ///
    commonTypes::sender::bool_t mapGroupToHex(ILightSourceInterface::eGroup a_eGroup, commonTypes::limitless::eSetWhiteCol &a_eHEX);
};

#endif // CMAPPERTOLEDCOMMAND_H
