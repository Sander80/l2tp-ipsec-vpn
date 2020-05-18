/****************************************************************************
** Meta object code from reading C++ file 'VPNControlTask.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../VPNControlTask.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VPNControlTask.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_VPNControlTask_t {
    QByteArrayData data[12];
    char stringdata0[162];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VPNControlTask_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VPNControlTask_t qt_meta_stringdata_VPNControlTask = {
    {
QT_MOC_LITERAL(0, 0, 14), // "VPNControlTask"
QT_MOC_LITERAL(1, 15, 12), // "readyReadLog"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 21), // "commandOutputReceived"
QT_MOC_LITERAL(4, 51, 13), // "strOutputLine"
QT_MOC_LITERAL(5, 65, 18), // "errorMessageEmited"
QT_MOC_LITERAL(6, 84, 10), // "iErrorCode"
QT_MOC_LITERAL(7, 95, 19), // "readyReadVpnLogPipe"
QT_MOC_LITERAL(8, 115, 8), // "onResult"
QT_MOC_LITERAL(9, 124, 11), // "iReturnCode"
QT_MOC_LITERAL(10, 136, 9), // "stCommand"
QT_MOC_LITERAL(11, 146, 15) // "onCommandOutput"

    },
    "VPNControlTask\0readyReadLog\0\0"
    "commandOutputReceived\0strOutputLine\0"
    "errorMessageEmited\0iErrorCode\0"
    "readyReadVpnLogPipe\0onResult\0iReturnCode\0"
    "stCommand\0onCommandOutput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VPNControlTask[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    1,   45,    2, 0x06 /* Public */,
       5,    1,   48,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   51,    2, 0x08 /* Private */,
       8,    2,   52,    2, 0x08 /* Private */,
      11,    1,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void VPNControlTask::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VPNControlTask *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readyReadLog(); break;
        case 1: _t->commandOutputReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->errorMessageEmited((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->readyReadVpnLogPipe(); break;
        case 4: _t->onResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->onCommandOutput((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VPNControlTask::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VPNControlTask::readyReadLog)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VPNControlTask::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VPNControlTask::commandOutputReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VPNControlTask::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VPNControlTask::errorMessageEmited)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VPNControlTask::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_VPNControlTask.data,
    qt_meta_data_VPNControlTask,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VPNControlTask::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VPNControlTask::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VPNControlTask.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int VPNControlTask::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VPNControlTask::readyReadLog()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void VPNControlTask::commandOutputReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VPNControlTask::errorMessageEmited(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
