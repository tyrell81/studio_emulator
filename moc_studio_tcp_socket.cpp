/****************************************************************************
** Meta object code from reading C++ file 'studio_tcp_socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "studio_tcp_socket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'studio_tcp_socket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StudioTcpSocket_t {
    QByteArrayData data[15];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StudioTcpSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StudioTcpSocket_t qt_meta_stringdata_StudioTcpSocket = {
    {
QT_MOC_LITERAL(0, 0, 15), // "StudioTcpSocket"
QT_MOC_LITERAL(1, 16, 13), // "recivedPacket"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 9), // "ba_packet"
QT_MOC_LITERAL(4, 41, 12), // "sendedPacket"
QT_MOC_LITERAL(5, 54, 6), // "status"
QT_MOC_LITERAL(6, 61, 10), // "sendPacket"
QT_MOC_LITERAL(7, 72, 14), // "onStateChanged"
QT_MOC_LITERAL(8, 87, 28), // "QAbstractSocket::SocketState"
QT_MOC_LITERAL(9, 116, 5), // "state"
QT_MOC_LITERAL(10, 122, 7), // "onError"
QT_MOC_LITERAL(11, 130, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(12, 159, 5), // "error"
QT_MOC_LITERAL(13, 165, 11), // "onReadyRead"
QT_MOC_LITERAL(14, 177, 11) // "resetRxBuff"

    },
    "StudioTcpSocket\0recivedPacket\0\0ba_packet\0"
    "sendedPacket\0status\0sendPacket\0"
    "onStateChanged\0QAbstractSocket::SocketState\0"
    "state\0onError\0QAbstractSocket::SocketError\0"
    "error\0onReadyRead\0resetRxBuff"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StudioTcpSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   55,    2, 0x0a /* Public */,
       7,    1,   58,    2, 0x09 /* Protected */,
      10,    1,   61,    2, 0x09 /* Protected */,
      13,    0,   64,    2, 0x08 /* Private */,
      14,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void StudioTcpSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        StudioTcpSocket *_t = static_cast<StudioTcpSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->recivedPacket((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 1: _t->sendedPacket((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 2: _t->sendPacket((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 3: _t->onStateChanged((*reinterpret_cast< const QAbstractSocket::SocketState(*)>(_a[1]))); break;
        case 4: _t->onError((*reinterpret_cast< const QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: _t->onReadyRead(); break;
        case 6: _t->resetRxBuff(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketState >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (StudioTcpSocket::*_t)(const QByteArray & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StudioTcpSocket::recivedPacket)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (StudioTcpSocket::*_t)(const bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&StudioTcpSocket::sendedPacket)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject StudioTcpSocket::staticMetaObject = {
    { &QTcpSocket::staticMetaObject, qt_meta_stringdata_StudioTcpSocket.data,
      qt_meta_data_StudioTcpSocket,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *StudioTcpSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StudioTcpSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StudioTcpSocket.stringdata0))
        return static_cast<void*>(const_cast< StudioTcpSocket*>(this));
    return QTcpSocket::qt_metacast(_clname);
}

int StudioTcpSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpSocket::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void StudioTcpSocket::recivedPacket(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void StudioTcpSocket::sendedPacket(const bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
