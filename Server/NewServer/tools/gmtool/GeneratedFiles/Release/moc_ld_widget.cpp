/****************************************************************************
** Meta object code from reading C++ file 'ld_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../ld_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ld_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CLDWidget_t {
    QByteArrayData data[14];
    char stringdata[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CLDWidget_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CLDWidget_t qt_meta_stringdata_CLDWidget = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 11),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 13),
QT_MOC_LITERAL(4, 37, 15),
QT_MOC_LITERAL(5, 53, 8),
QT_MOC_LITERAL(6, 62, 13),
QT_MOC_LITERAL(7, 76, 16),
QT_MOC_LITERAL(8, 93, 4),
QT_MOC_LITERAL(9, 98, 6),
QT_MOC_LITERAL(10, 105, 15),
QT_MOC_LITERAL(11, 121, 11),
QT_MOC_LITERAL(12, 133, 13),
QT_MOC_LITERAL(13, 147, 16)
    },
    "CLDWidget\0ChangeGroup\0\0MoreTradeInfo\0"
    "ExportTradeInfo\0AddOrder\0OrderSelected\0"
    "QTreeWidgetItem*\0item\0column\0"
    "OrderSelected_2\0OrderDetail\0OrderDetail_2\0"
    "SetExchangeLimit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CLDWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    2,   63,    2, 0x0a /* Public */,
      10,    2,   68,    2, 0x0a /* Public */,
      11,    2,   73,    2, 0x0a /* Public */,
      12,    2,   78,    2, 0x0a /* Public */,
      13,    0,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    9,
    QMetaType::Void,

       0        // eod
};

void CLDWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CLDWidget *_t = static_cast<CLDWidget *>(_o);
        switch (_id) {
        case 0: _t->ChangeGroup(); break;
        case 1: _t->MoreTradeInfo(); break;
        case 2: _t->ExportTradeInfo(); break;
        case 3: _t->AddOrder(); break;
        case 4: _t->OrderSelected((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->OrderSelected_2((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->OrderDetail((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->OrderDetail_2((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->SetExchangeLimit(); break;
        default: ;
        }
    }
}

const QMetaObject CLDWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CLDWidget.data,
      qt_meta_data_CLDWidget,  qt_static_metacall, 0, 0}
};


const QMetaObject *CLDWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CLDWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CLDWidget.stringdata))
        return static_cast<void*>(const_cast< CLDWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int CLDWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
