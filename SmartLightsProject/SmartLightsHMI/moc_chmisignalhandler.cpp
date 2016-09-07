/****************************************************************************
** Meta object code from reading C++ file 'chmisignalhandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "chmisignalhandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chmisignalhandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CHMISignalHandler_t {
    QByteArrayData data[9];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CHMISignalHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CHMISignalHandler_t qt_meta_stringdata_CHMISignalHandler = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CHMISignalHandler"
QT_MOC_LITERAL(1, 18, 10), // "turnOnSlot"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 11), // "turnOffSlot"
QT_MOC_LITERAL(4, 42, 10), // "setColSlot"
QT_MOC_LITERAL(5, 53, 9), // "a_iColour"
QT_MOC_LITERAL(6, 63, 13), // "setBrightSlot"
QT_MOC_LITERAL(7, 77, 7), // "a_iBrig"
QT_MOC_LITERAL(8, 85, 12) // "setWhiteSlot"

    },
    "CHMISignalHandler\0turnOnSlot\0\0turnOffSlot\0"
    "setColSlot\0a_iColour\0setBrightSlot\0"
    "a_iBrig\0setWhiteSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CHMISignalHandler[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    1,   41,    2, 0x0a /* Public */,
       6,    1,   44,    2, 0x0a /* Public */,
       8,    0,   47,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void CHMISignalHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CHMISignalHandler *_t = static_cast<CHMISignalHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->turnOnSlot(); break;
        case 1: _t->turnOffSlot(); break;
        case 2: _t->setColSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setBrightSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setWhiteSlot(); break;
        default: ;
        }
    }
}

const QMetaObject CHMISignalHandler::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CHMISignalHandler.data,
      qt_meta_data_CHMISignalHandler,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CHMISignalHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CHMISignalHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CHMISignalHandler.stringdata0))
        return static_cast<void*>(const_cast< CHMISignalHandler*>(this));
    return QObject::qt_metacast(_clname);
}

int CHMISignalHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
