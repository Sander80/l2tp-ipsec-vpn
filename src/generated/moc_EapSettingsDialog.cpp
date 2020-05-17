/****************************************************************************
** Meta object code from reading C++ file 'EapSettingsDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogs/EapSettingsDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EapSettingsDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EapSettingsDialog_t {
    QByteArrayData data[11];
    char stringdata0[156];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EapSettingsDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EapSettingsDialog_t qt_meta_stringdata_EapSettingsDialog = {
    {
QT_MOC_LITERAL(0, 0, 17), // "EapSettingsDialog"
QT_MOC_LITERAL(1, 18, 34), // "onUseCertificateRadioButtonTo..."
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 8), // "fChecked"
QT_MOC_LITERAL(4, 63, 13), // "onCertificate"
QT_MOC_LITERAL(5, 77, 12), // "onPrivateKey"
QT_MOC_LITERAL(6, 90, 15), // "onCaCertificate"
QT_MOC_LITERAL(7, 106, 12), // "readSettings"
QT_MOC_LITERAL(8, 119, 13), // "writeSettings"
QT_MOC_LITERAL(9, 133, 15), // "onHelpRequested"
QT_MOC_LITERAL(10, 149, 6) // "accept"

    },
    "EapSettingsDialog\0onUseCertificateRadioButtonToggled\0"
    "\0fChecked\0onCertificate\0onPrivateKey\0"
    "onCaCertificate\0readSettings\0writeSettings\0"
    "onHelpRequested\0accept"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EapSettingsDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x08 /* Private */,
       4,    0,   57,    2, 0x08 /* Private */,
       5,    0,   58,    2, 0x08 /* Private */,
       6,    0,   59,    2, 0x08 /* Private */,
       7,    0,   60,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    0,   62,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void EapSettingsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EapSettingsDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onUseCertificateRadioButtonToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onCertificate(); break;
        case 2: _t->onPrivateKey(); break;
        case 3: _t->onCaCertificate(); break;
        case 4: _t->readSettings(); break;
        case 5: { bool _r = _t->writeSettings();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: _t->onHelpRequested(); break;
        case 7: _t->accept(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EapSettingsDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_EapSettingsDialog.data,
    qt_meta_data_EapSettingsDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *EapSettingsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EapSettingsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EapSettingsDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int EapSettingsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
