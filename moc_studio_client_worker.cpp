/****************************************************************************
** Meta object code from reading C++ file 'studio_client_worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "studio_client_worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'studio_client_worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StudioClientWorker_t {
    QByteArrayData data[12];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StudioClientWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StudioClientWorker_t qt_meta_stringdata_StudioClientWorker = {
    {
QT_MOC_LITERAL(0, 0, 18), // "StudioClientWorker"
QT_MOC_LITERAL(1, 19, 11), // "onConnected"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 14), // "onDisconnected"
QT_MOC_LITERAL(4, 47, 7), // "onError"
QT_MOC_LITERAL(5, 55, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(6, 84, 12), // "socket_error"
QT_MOC_LITERAL(7, 97, 14), // "onStateChanged"
QT_MOC_LITERAL(8, 112, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(9, 141, 12), // "socket_state"
QT_MOC_LITERAL(10, 154, 16), // "onReceivedPacket"
QT_MOC_LITERAL(11, 171, 9) // "ba_packet"

    },
    "StudioClientWorker\0onConnected\0\0"
    "onDisconnected\0onError\0"
    "QAbstractSocket::SocketError\0socket_error\0"
    "onStateChanged\0QAbstractSocket::SocketState\0"
    "socket_state\0onReceivedPacket\0ba_packet"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StudioClientWorker[] = {

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
       1,    0,   39,    2, 0x09 /* Protected */,
       3,    0,   40,    2, 0x09 /* Protected */,
       4,    1,   41,    2, 0x09 /* Protected */,
       7,    1,   44,    2, 0x09 /* Protected */,
      10,    1,   47,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::QByteArray,   11,

       0        // eod
};

void StudioClientWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StudioClientWorker *_t = static_cast<StudioClientWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onConnected(); break;
        case 1: _t->onDisconnected(); break;
        case 2: _t->onError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 3: _t->onStateChanged((*reinterpret_cast< QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 4: _t->onReceivedPacket((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        }
    }
}

const QMetaObject StudioClientWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_StudioClientWorker.data,
      qt_meta_data_StudioClientWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StudioClientWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StudioClientWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StudioClientWorker.stringdata0))
        return static_cast<void*>(const_cast< StudioClientWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int StudioClientWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
