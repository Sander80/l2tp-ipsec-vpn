/****************************************************************************
** Meta object code from reading C++ file 'L2tpIPsecVpnApplication.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../L2tpIPsecVpnApplication.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'L2tpIPsecVpnApplication.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_L2tpIPsecVpnApplication_t {
    QByteArrayData data[10];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_L2tpIPsecVpnApplication_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_L2tpIPsecVpnApplication_t qt_meta_stringdata_L2tpIPsecVpnApplication = {
    {
QT_MOC_LITERAL(0, 0, 23), // "L2tpIPsecVpnApplication"
QT_MOC_LITERAL(1, 24, 15), // "connectionAdded"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 17), // "strConnectionName"
QT_MOC_LITERAL(4, 59, 17), // "connectionRemoved"
QT_MOC_LITERAL(5, 77, 28), // "connectionEditorDialogClosed"
QT_MOC_LITERAL(6, 106, 9), // "iExitCode"
QT_MOC_LITERAL(7, 116, 17), // "onMessageReceived"
QT_MOC_LITERAL(8, 134, 10), // "strMessage"
QT_MOC_LITERAL(9, 145, 30) // "onConnectionEditorDialogClosed"

    },
    "L2tpIPsecVpnApplication\0connectionAdded\0"
    "\0strConnectionName\0connectionRemoved\0"
    "connectionEditorDialogClosed\0iExitCode\0"
    "onMessageReceived\0strMessage\0"
    "onConnectionEditorDialogClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_L2tpIPsecVpnApplication[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       5,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   48,    2, 0x08 /* Private */,
       9,    1,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void L2tpIPsecVpnApplication::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<L2tpIPsecVpnApplication *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectionAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->connectionRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->connectionEditorDialogClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onMessageReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onConnectionEditorDialogClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (L2tpIPsecVpnApplication::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&L2tpIPsecVpnApplication::connectionAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (L2tpIPsecVpnApplication::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&L2tpIPsecVpnApplication::connectionRemoved)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (L2tpIPsecVpnApplication::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&L2tpIPsecVpnApplication::connectionEditorDialogClosed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject L2tpIPsecVpnApplication::staticMetaObject = { {
    &QApplication::staticMetaObject,
    qt_meta_stringdata_L2tpIPsecVpnApplication.data,
    qt_meta_data_L2tpIPsecVpnApplication,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *L2tpIPsecVpnApplication::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *L2tpIPsecVpnApplication::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_L2tpIPsecVpnApplication.stringdata0))
        return static_cast<void*>(this);
    return QApplication::qt_metacast(_clname);
}

int L2tpIPsecVpnApplication::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void L2tpIPsecVpnApplication::connectionAdded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void L2tpIPsecVpnApplication::connectionRemoved(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void L2tpIPsecVpnApplication::connectionEditorDialogClosed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
