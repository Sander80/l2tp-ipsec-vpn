/****************************************************************************
** Meta object code from reading C++ file 'PeerAuthenticationDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogs/PeerAuthenticationDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PeerAuthenticationDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PeerAuthenticationDialog_t {
    QByteArrayData data[6];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PeerAuthenticationDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PeerAuthenticationDialog_t qt_meta_stringdata_PeerAuthenticationDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "PeerAuthenticationDialog"
QT_MOC_LITERAL(1, 25, 12), // "readSettings"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 13), // "writeSettings"
QT_MOC_LITERAL(4, 53, 15), // "onHelpRequested"
QT_MOC_LITERAL(5, 69, 6) // "accept"

    },
    "PeerAuthenticationDialog\0readSettings\0"
    "\0writeSettings\0onHelpRequested\0accept"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PeerAuthenticationDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PeerAuthenticationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PeerAuthenticationDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->readSettings(); break;
        case 1: { bool _r = _t->writeSettings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->onHelpRequested(); break;
        case 3: _t->accept(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PeerAuthenticationDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_PeerAuthenticationDialog.data,
    qt_meta_data_PeerAuthenticationDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PeerAuthenticationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PeerAuthenticationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PeerAuthenticationDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int PeerAuthenticationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
