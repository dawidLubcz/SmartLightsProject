#ifndef LIMITLESSCOMMONTYPES
#define LIMITLESSCOMMONTYPES

namespace commonTypes
{
    namespace sender
    {
        typedef bool bool_t;

    }


    namespace limitless
    {
        ////////////////
        /// \brief The eMessage enum
        ///
        enum eMessage
        {
            E_MESSAGE_SIZE = 3,
            E_MESSAGE_END_BYTE = 0x55,
            E_MESSAGE_PREFIX_BRIGHTNESS = 0x4E,
            E_MESSAGE_PREFIX_COLOUR = 0x40,

            E_MESSAGE_START_INDEX = 0,
            E_MESSAGE_END_INDEX = E_MESSAGE_SIZE - 1,
        };


        ////////////////////////////////////
        /// \brief The eGroupAllOn enum
        ///
        enum eGroupOn
        {
            E_GROUP_ON_INITIAL = 0x00,
            E_GROUP_ALL_ON = 0x42,
            E_GROUP_1_ON = 0x45,
            E_GROUP_2_ON = 0x47,
            E_GROUP_3_ON = 0x49,
            E_GROUP_4_ON = 0x4B,
        };

        ///////////////////////////////////
        /// \brief The eGroupAllOf enum
        ///
        enum eGroupOff
        {
            E_GROUP_OFF_INITIAL = 0x00,
            E_GROUP_ALL_OFF = 0x41,
            E_GROUP_1_OFF = 0x46,
            E_GROUP_2_OFF = 0x48,
            E_GROUP_3_OFF = 0x4A,
            E_GROUP_4_OFF = 0x4C,
        };

        ///////////////////////////////
        /// \brief The eSetWhiteCol enum
        ///
        enum eSetWhiteCol
        {
            E_SET_COLOR_TO_WHITE_INITIAL = 0x00,
            E_SET_COLOR_TO_WHITE_ALL = 0xC2,
            E_SET_COLOR_TO_WHITE_G1 = 0xC5,
            E_SET_COLOR_TO_WHITE_G2 = 0xC7,
            E_SET_COLOR_TO_WHITE_G3 = 0xC9,
            E_SET_COLOR_TO_WHITE_G4 = 0xCB
        };

    } // commonTypes

} //Limitless




#endif // LIMITLESSCOMMONTYPES

