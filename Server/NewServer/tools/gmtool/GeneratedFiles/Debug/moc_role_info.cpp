/****************************************************************************
** Meta object code from reading C++ file 'role_info.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../role_info.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'role_info.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CRoleInfo_t {
    QByteArrayData data[19];
    char stringdata[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CRoleInfo_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CRoleInfo_t qt_meta_stringdata_CRoleInfo = {
    {
QT_MOC_LITERAL(0, 0, 9),
QT_MOC_LITERAL(1, 10, 13),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 7),
QT_MOC_LITERAL(4, 33, 8),
QT_MOC_LITERAL(5, 42, 7),
QT_MOC_LITERAL(6, 50, 8),
QT_MOC_LITERAL(7, 59, 9),
QT_MOC_LITERAL(8, 69, 9),
QT_MOC_LITERAL(9, 79, 4),
QT_MOC_LITERAL(10, 84, 10),
QT_MOC_LITERAL(11, 95, 12),
QT_MOC_LITERAL(12, 108, 5),
QT_MOC_LITERAL(13, 114, 14),
QT_MOC_LITERAL(14, 129, 16),
QT_MOC_LITERAL(15, 146, 4),
QT_MOC_LITERAL(16, 151, 6),
QT_MOC_LITERAL(17, 158, 15),
QT_MOC_LITERAL(18, 174, 12)
    },
    "CRoleInfo\0SetTargetRole\0\0DelItem\0"
    "DelQuest\0DelMail\0TakeItem\0ReturnPos\0"
    "EndModify\0Exit\0closeEvent\0QCloseEvent*\0"
    "event\0BaseDataModify\0QTreeWidgetItem*\0"
    "item\0column\0BaseDataChanged\0ShowItemInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CRoleInfo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x0a /* Public */,
       3,    0,   75,    2, 0x0a /* Public */,
       4,    0,   76,    2, 0x0a /* Public */,
       5,    0,   77,    2, 0x0a /* Public */,
       6,    0,   78,    2, 0x0a /* Public */,
       7,    0,   79,    2, 0x0a /* Public */,
       8,    0,   80,    2, 0x0a /* Public */,
       9,    0,   81,    2, 0x0a /* Public */,
      10,    1,   82,    2, 0x0a /* Public */,
      13,    2,   85,    2, 0x0a /* Public */,
      17,    2,   90,    2, 0x0a /* Public */,
      18,    2,   95,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   15,   16,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   15,   16,
    QMetaType::Void, 0x80000000 | 14, QMetaType::Int,   15,   16,

       0        // eod
};

void CRoleInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CRoleInfo *_t = static_cast<CRoleInfo *>(_o);
        switch (_id) {
        case 0: _t->SetTargetRole(); break;
        case 1: _t->DelItem(); break;
        case 2: _t->DelQuest(); break;
        case 3: _t->DelMail(); break;
        case 4: _t->TakeItem(); break;
        case 5: _t->ReturnPos(); break;
        case 6: _t->EndModify(); break;
        case 7: _t->Exit(); break;
        case 8: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 9: _t->BaseDataModify((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->BaseDataChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->ShowItemInfo((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject CRoleInfo::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CRoleInfo.data,
      qt_meta_data_CRoleInfo,  qt_static_metacall, 0, 0}
};


const QMetaObject *CRoleInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CRoleInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CRoleInfo.stringdata))
        return static_cast<void*>(const_cast< CRoleInfo*>(this));
    return QDialog::qt_metacast(_clname);
}

int CRoleInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_END_MOC_NAMESPACE
