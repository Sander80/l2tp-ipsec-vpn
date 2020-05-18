/****************************************************************************
** Meta object code from reading C++ file 'VpnControlDaemonClient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../util/VpnControlDaemonClient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VpnControlDaemonClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef QT_INIT_METAOBJECT
#  define QT_INIT_METAOBJECT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VpnControlDaemonClient_t {
    QByteArrayData data[14];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VpnControlDaemonClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VpnControlDaemonClient_t qt_meta_stringdata_VpnControlDaemonClient = {
    {
QT_MOC_LITERAL(0, 0, 22), // "VpnControlDaemonClient"
QT_MOC_LITERAL(1, 23, 15), // "notifyConnected"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 18), // "notifyDisconnected"
QT_MOC_LITERAL(4, 59, 12), // "notifyResult"
QT_MOC_LITERAL(5, 72, 11), // "iReturnCode"
QT_MOC_LITERAL(6, 84, 10), // "strCommand"
QT_MOC_LITERAL(7, 95, 19), // "notifyCommandOutput"
QT_MOC_LITERAL(8, 115, 13), // "strOutputLine"
QT_MOC_LITERAL(9, 129, 4), // "exit"
QT_MOC_LITERAL(10, 134, 5), // "leave"
QT_MOC_LITERAL(11, 140, 11), // "onConnected"
QT_MOC_LITERAL(12, 152, 14), // "onDisconnected"
QT_MOC_LITERAL(13, 167, 11) // "onReadyRead"

    },
    "VpnControlDaemonClient\0notifyConnected\0"
    "\0notifyDisconnected\0notifyResult\0"
    "iReturnCode\0strCommand\0notifyCommandOutput\0"
    "strOutputLine\0exit\0leave\0onConnected\0"
    "onDisconnected\0onReadyRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VpnControlDaemonClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    2,   61,    2, 0x06 /* Public */,
       7,    1,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   69,    2, 0x0a /* Public */,
      10,    0,   70,    2, 0x0a /* Public */,
      11,    0,   71,    2, 0x08 /* Private */,
      12,    0,   72,    2, 0x08 /* Private */,
      13,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VpnControlDaemonClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VpnControlDaemonClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->notifyConnected(); break;
        case 1: _t->notifyDisconnected(); break;
        case 2: _t->notifyResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->notifyCommandOutput((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->exit(); break;
        case 5: _t->leave(); break;
        case 6: _t->onConnected(); break;
        case 7: _t->onDisconnected(); break;
        case 8: _t->onReadyRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VpnControlDaemonClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VpnControlDaemonClient::notifyConnected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VpnControlDaemonClient::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VpnControlDaemonClient::notifyDisconnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VpnControlDaemonClient::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VpnControlDaemonClient::notifyResult)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (VpnControlDaemonClient::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VpnControlDaemonClient::notifyCommandOutput)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VpnControlDaemonClient::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_VpnControlDaemonClient.data,
    qt_meta_data_VpnControlDaemonClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VpnControlDaemonClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VpnControlDaemonClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VpnControlDaemonClient.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int VpnControlDaemonClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void VpnControlDaemonClient::notifyConnected()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VpnControlDaemonClient::notifyDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void VpnControlDaemonClient::notifyResult(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void VpnControlDaemonClient::notifyCommandOutput(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
