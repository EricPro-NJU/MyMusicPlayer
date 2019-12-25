/****************************************************************************
** Meta object code from reading C++ file 'minimizewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MyMediaPlayer/minimizewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'minimizewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MinimizeWidget_t {
    QByteArrayData data[21];
    char stringdata0[291];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MinimizeWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MinimizeWidget_t qt_meta_stringdata_MinimizeWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MinimizeWidget"
QT_MOC_LITERAL(1, 15, 15), // "playBtn_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 15), // "LastBtn_clicked"
QT_MOC_LITERAL(4, 48, 15), // "NextBtn_clicked"
QT_MOC_LITERAL(5, 64, 11), // "volumnMoved"
QT_MOC_LITERAL(6, 76, 15), // "cirType_clicked"
QT_MOC_LITERAL(7, 92, 4), // "back"
QT_MOC_LITERAL(8, 97, 12), // "changeVolumn"
QT_MOC_LITERAL(9, 110, 9), // "changeLab"
QT_MOC_LITERAL(10, 120, 7), // "playBtn"
QT_MOC_LITERAL(11, 128, 13), // "playBtn_pause"
QT_MOC_LITERAL(12, 142, 7), // "cirType"
QT_MOC_LITERAL(13, 150, 11), // "changeTitle"
QT_MOC_LITERAL(14, 162, 18), // "on_playBtn_clicked"
QT_MOC_LITERAL(15, 181, 18), // "on_lastBtn_clicked"
QT_MOC_LITERAL(16, 200, 18), // "on_nextBtn_clicked"
QT_MOC_LITERAL(17, 219, 27), // "on_volumnSlider_sliderMoved"
QT_MOC_LITERAL(18, 247, 8), // "position"
QT_MOC_LITERAL(19, 256, 18), // "on_cirType_clicked"
QT_MOC_LITERAL(20, 275, 15) // "on_back_clicked"

    },
    "MinimizeWidget\0playBtn_clicked\0\0"
    "LastBtn_clicked\0NextBtn_clicked\0"
    "volumnMoved\0cirType_clicked\0back\0"
    "changeVolumn\0changeLab\0playBtn\0"
    "playBtn_pause\0cirType\0changeTitle\0"
    "on_playBtn_clicked\0on_lastBtn_clicked\0"
    "on_nextBtn_clicked\0on_volumnSlider_sliderMoved\0"
    "position\0on_cirType_clicked\0on_back_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MinimizeWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  104,    2, 0x06 /* Public */,
       3,    0,  105,    2, 0x06 /* Public */,
       4,    0,  106,    2, 0x06 /* Public */,
       5,    1,  107,    2, 0x06 /* Public */,
       6,    0,  110,    2, 0x06 /* Public */,
       7,    0,  111,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,  112,    2, 0x0a /* Public */,
       9,    1,  115,    2, 0x0a /* Public */,
      10,    0,  118,    2, 0x0a /* Public */,
      11,    0,  119,    2, 0x0a /* Public */,
      12,    0,  120,    2, 0x0a /* Public */,
      13,    1,  121,    2, 0x0a /* Public */,
      14,    0,  124,    2, 0x08 /* Private */,
      15,    0,  125,    2, 0x08 /* Private */,
      16,    0,  126,    2, 0x08 /* Private */,
      17,    1,  127,    2, 0x08 /* Private */,
      19,    0,  130,    2, 0x08 /* Private */,
      20,    0,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MinimizeWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MinimizeWidget *_t = static_cast<MinimizeWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playBtn_clicked(); break;
        case 1: _t->LastBtn_clicked(); break;
        case 2: _t->NextBtn_clicked(); break;
        case 3: _t->volumnMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->cirType_clicked(); break;
        case 5: _t->back(); break;
        case 6: _t->changeVolumn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->changeLab((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->playBtn(); break;
        case 9: _t->playBtn_pause(); break;
        case 10: _t->cirType(); break;
        case 11: _t->changeTitle((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->on_playBtn_clicked(); break;
        case 13: _t->on_lastBtn_clicked(); break;
        case 14: _t->on_nextBtn_clicked(); break;
        case 15: _t->on_volumnSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->on_cirType_clicked(); break;
        case 17: _t->on_back_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MinimizeWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinimizeWidget::playBtn_clicked)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MinimizeWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinimizeWidget::LastBtn_clicked)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (MinimizeWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinimizeWidget::NextBtn_clicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (MinimizeWidget::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinimizeWidget::volumnMoved)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (MinimizeWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinimizeWidget::cirType_clicked)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (MinimizeWidget::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MinimizeWidget::back)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject MinimizeWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MinimizeWidget.data,
      qt_meta_data_MinimizeWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MinimizeWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinimizeWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MinimizeWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MinimizeWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void MinimizeWidget::playBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MinimizeWidget::LastBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MinimizeWidget::NextBtn_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MinimizeWidget::volumnMoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MinimizeWidget::cirType_clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MinimizeWidget::back()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
