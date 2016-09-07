#ifndef CCOMMONTYPES
#define CCOMMONTYPES

/// defines, common for all files
#define QT

typedef bool bool_t;

enum ePriority
{
    E_DEFAULT_PRIO = 0,
    E_SYSTEM_PRIO = 1,
    E_USER_PRIO = 2,

    E_BOOST_PRIO = 1
};

#endif // CCOMMONTYPES

