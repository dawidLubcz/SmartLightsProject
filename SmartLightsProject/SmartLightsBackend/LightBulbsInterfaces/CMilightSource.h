#ifndef CCOMMANDSENDERIMPL_H
#define CCOMMANDSENDERIMPL_H

#include "ILightSourceInterface.h"
#include "CUDPSender.h"
#include "CommonTypes.h"
#include "CMapperToLedCommand.h"
#include "CMessageCreator.h"

class CMilightSource : public ILightSourceInterface
{
public:
    CMilightSource();

private:
    //////////////////////////////////
    /// @see IcommandSenderInteface
    bool_t sendTurnOnReq(eGroup a_eGroup);

    //////////////////////////////////
    /// @see IcommandSenderInteface
    bool_t sendTurnOffReq(eGroup a_eGroup);

    //////////////////////////////////
    /// @see IcommandSenderInteface
    bool_t sendWhiteReq(eGroup a_eGroup);

    //////////////////////////////////
    /// @see IcommandSenderInteface
    bool_t sendBrightnessReq(eGroup a_eGroup, int16_t a_uiProc = 100);

    //////////////////////////////////
    /// @see IcommandSenderInteface
    bool_t sendColourReq(eGroup a_eGroup, eColours a_eColour);

    //////////////////////////////////
    /// @see IcommandSenderInteface
    bool_t sendColourReq(eGroup a_eGroup, int16_t a_uiColour);

    //////////////////////////////////
    /// \brief calculateBrightness
    /// \param a_iProc
    /// \return
    ///
    inline uint8_t calculateBrightness(uint8_t a_iProc);
};



#endif // CCOMMANDSENDERIMPL_H
