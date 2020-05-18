/****************************************************************************
** Meta object code from reading C++ file 'ConnectionEditorDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../dialogs/ConnectionEditorDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ConnectionEditorDialog.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_ConnectionEditorDialog_t {
    QByteArrayData data[12];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionEditorDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionEditorDialog_t qt_meta_stringdata_ConnectionEditorDialog = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ConnectionEditorDialog"
QT_MOC_LITERAL(1, 23, 15), // "connectionAdded"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 7), // "strName"
QT_MOC_LITERAL(4, 48, 17), // "connectionRemoved"
QT_MOC_LITERAL(5, 66, 15), // "onHelpRequested"
QT_MOC_LITERAL(6, 82, 6), // "accept"
QT_MOC_LITERAL(7, 89, 6), // "reject"
QT_MOC_LITERAL(8, 96, 15), // "editPreferences"
QT_MOC_LITERAL(9, 112, 13), // "addConnection"
QT_MOC_LITERAL(10, 126, 14), // "editConnection"
QT_MOC_LITERAL(11, 141, 16) // "removeConnection"

    },
    "ConnectionEditorDialog\0connectionAdded\0"
    "\0strName\0connectionRemoved\0onHelpRequested\0"
    "accept\0reject\0editPreferences\0"
    "addConnection\0editConnection\0"
    "removeConnection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionEditorDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   65,    2, 0x08 /* Private */,
       6,    0,   66,    2, 0x08 /* Private */,
       7,    0,   67,    2, 0x08 /* Private */,
       8,    0,   68,    2, 0x08 /* Private */,
       9,    0,   69,    2, 0x08 /* Private */,
      10,    0,   70,    2, 0x08 /* Private */,
      11,    0,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConnectionEditorDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectionEditorDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectionAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->connectionRemoved((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onHelpRequested(); break;
        case 3: _t->accept(); break;
        case 4: _t->reject(); break;
        case 5: _t->editPreferences(); break;
        case 6: _t->addConnection(); break;
        case 7: _t->editConnection(); break;
        case 8: _t->removeConnection(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConnectionEditorDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionEditorDialog::connectionAdded)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConnectionEditorDialog::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionEditorDialog::connectionRemoved)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionEditorDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ConnectionEditorDialog.data,
    qt_meta_data_ConnectionEditorDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConnectionEditorDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionEditorDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionEditorDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ConnectionEditorDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void ConnectionEditorDialog::connectionAdded(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectionEditorDialog::connectionRemoved(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
