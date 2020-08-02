#-------------------------------------------------
#
# Project created by QtCreator 2020-07-11T10:17:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Supermarket_management_system
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        add_num.cpp \
        bill.cpp \
        goods.cpp \
        main.cpp \
        login.cpp \
        manager_operation.cpp \
        new_goods.cpp \
        new_staff.cpp \
        readwritejson.cpp \
        staff.cpp \
        staff_operation.cpp

HEADERS += \
        add_num.h \
        bill.h \
        goods.h \
        login.h \
        manager_operation.h \
        new_goods.h \
        new_staff.h \
        readwritejson.h \
        staff.h \
        staff_operation.h

FORMS += \
        add_num.ui \
        bill.ui \
        login.ui \
        manager_operation.ui \
        new_goods.ui \
        new_staff.ui \
        staff_operation.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    json.qrc

DISTFILES +=
