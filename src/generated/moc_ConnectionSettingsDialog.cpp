/****************************************************************************
** Meta object code from reading C++ file 'ConnectionSettingsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogs/ConnectionSettingsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectionSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionSettingsDialog_t {
    QByteArrayData data[16];
    char stringdata0[251];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionSettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionSettingsDialog_t qt_meta_stringdata_ConnectionSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ConnectionSettingsDialog"
QT_MOC_LITERAL(1, 25, 15), // "onHelpRequested"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 6), // "accept"
QT_MOC_LITERAL(4, 49, 12), // "readSettings"
QT_MOC_LITERAL(5, 62, 13), // "writeSettings"
QT_MOC_LITERAL(6, 76, 15), // "onEapProperties"
QT_MOC_LITERAL(7, 92, 20), // "onPeerAuthentication"
QT_MOC_LITERAL(8, 113, 12), // "onIpSettings"
QT_MOC_LITERAL(9, 126, 18), // "onAdvancedSettings"
QT_MOC_LITERAL(10, 145, 39), // "onUseIPsecCertificateRadioBut..."
QT_MOC_LITERAL(11, 185, 7), // "fEnable"
QT_MOC_LITERAL(12, 193, 26), // "onUseEapRadioButtonToggled"
QT_MOC_LITERAL(13, 220, 8), // "fEnabled"
QT_MOC_LITERAL(14, 229, 12), // "onPrivateKey"
QT_MOC_LITERAL(15, 242, 8) // "onImport"

    },
    "ConnectionSettingsDialog\0onHelpRequested\0"
    "\0accept\0readSettings\0writeSettings\0"
    "onEapProperties\0onPeerAuthentication\0"
    "onIpSettings\0onAdvancedSettings\0"
    "onUseIPsecCertificateRadioButtonToggled\0"
    "fEnable\0onUseEapRadioButtonToggled\0"
    "fEnabled\0onPrivateKey\0onImport"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionSettingsDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    1,   82,    2, 0x08 /* Private */,
      12,    1,   85,    2, 0x08 /* Private */,
      14,    0,   88,    2, 0x08 /* Private */,
      15,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConnectionSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectionSettingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onHelpRequested(); break;
        case 1: _t->accept(); break;
        case 2: _t->readSettings(); break;
        case 3: { bool _r = _t->writeSettings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: _t->onEapProperties(); break;
        case 5: _t->onPeerAuthentication(); break;
        case 6: _t->onIpSettings(); break;
        case 7: _t->onAdvancedSettings(); break;
        case 8: _t->onUseIPsecCertificateRadioButtonToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->onUseEapRadioButtonToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->onPrivateKey(); break;
        case 11: _t->onImport(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionSettingsDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ConnectionSettingsDialog.data,
    qt_meta_data_ConnectionSettingsDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConnectionSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionSettingsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ConnectionSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
