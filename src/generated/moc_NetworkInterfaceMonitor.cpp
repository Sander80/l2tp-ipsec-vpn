/****************************************************************************
** Meta object code from reading C++ file 'NetworkInterfaceMonitor.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../util/NetworkInterfaceMonitor.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NetworkInterfaceMonitor.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_NetworkInterfaceMonitor_t {
    QByteArrayData data[9];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NetworkInterfaceMonitor_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NetworkInterfaceMonitor_t qt_meta_stringdata_NetworkInterfaceMonitor = {
    {
QT_MOC_LITERAL(0, 0, 23), // "NetworkInterfaceMonitor"
QT_MOC_LITERAL(1, 24, 10), // "routeAdded"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 16), // "NetworkInterface"
QT_MOC_LITERAL(4, 53, 9), // "interface"
QT_MOC_LITERAL(5, 63, 9), // "iPriority"
QT_MOC_LITERAL(6, 73, 12), // "routeDeleted"
QT_MOC_LITERAL(7, 86, 12), // "addressAdded"
QT_MOC_LITERAL(8, 99, 21) // "ptpInterfaceIsDeleted"

    },
    "NetworkInterfaceMonitor\0routeAdded\0\0"
    "NetworkInterface\0interface\0iPriority\0"
    "routeDeleted\0addressAdded\0"
    "ptpInterfaceIsDeleted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NetworkInterfaceMonitor[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       6,    2,   39,    2, 0x06 /* Public */,
       7,    1,   44,    2, 0x06 /* Public */,
       8,    1,   47,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    4,    5,
    QMetaType::Void, 0x80000000 | 3, QMetaType::UInt,    4,    5,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void NetworkInterfaceMonitor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NetworkInterfaceMonitor *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->routeAdded((*reinterpret_cast< NetworkInterface(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 1: _t->routeDeleted((*reinterpret_cast< NetworkInterface(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 2: _t->addressAdded((*reinterpret_cast< NetworkInterface(*)>(_a[1]))); break;
        case 3: _t->ptpInterfaceIsDeleted((*reinterpret_cast< NetworkInterface(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NetworkInterfaceMonitor::*)(NetworkInterface , unsigned int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkInterfaceMonitor::routeAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NetworkInterfaceMonitor::*)(NetworkInterface , unsigned int ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkInterfaceMonitor::routeDeleted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NetworkInterfaceMonitor::*)(NetworkInterface ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkInterfaceMonitor::addressAdded)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NetworkInterfaceMonitor::*)(NetworkInterface ) const;
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NetworkInterfaceMonitor::ptpInterfaceIsDeleted)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NetworkInterfaceMonitor::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_NetworkInterfaceMonitor.data,
    qt_meta_data_NetworkInterfaceMonitor,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NetworkInterfaceMonitor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NetworkInterfaceMonitor::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NetworkInterfaceMonitor.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int NetworkInterfaceMonitor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void NetworkInterfaceMonitor::routeAdded(NetworkInterface _t1, unsigned int _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(const_cast< NetworkInterfaceMonitor *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NetworkInterfaceMonitor::routeDeleted(NetworkInterface _t1, unsigned int _t2)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(const_cast< NetworkInterfaceMonitor *>(this), &staticMetaObject, 1, _a);
}

// SIGNAL 2
void NetworkInterfaceMonitor::addressAdded(NetworkInterface _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< NetworkInterfaceMonitor *>(this), &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NetworkInterfaceMonitor::ptpInterfaceIsDeleted(NetworkInterface _t1)const
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< NetworkInterfaceMonitor *>(this), &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
