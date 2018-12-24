#-------------------------------------------------
#
# Project created by QtCreator 2018-11-22T23:37:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = password
TEMPLATE = app

INCLUDEPATH += ui
INCLUDEPATH += src

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
        main.cpp \
    ui/ListWindow.cpp \
    ui/AddWindow.cpp \
    ui/RecordWindow.cpp \
    ui/LoginWindow.cpp \
    ui/ChangeMasterPassword.cpp\
    src/Bank.cpp \
    src/account.cpp \
    src/recordmanager.cpp \
    src/rsa.cpp \
    src/masterpassword.cpp


HEADERS += \
    ui/ListWindow.h \
    ui/AddWindow.h \
    ui/RecordWindow.h \
    ui/LoginWindow.h \
    ui/ChangeMasterPassword.h\
    src/Bank.h \
    src/RecordManager.h \
    src/Account.h \
    src/rsa.h \
    src/infint.h \
    src/masterpassword.h

FORMS += \
    ui/ListWindow.ui \
    ui/AddWindow.ui \
    ui/RecordWindow.ui \
    ui/LoginWindow.ui \
    ui/MasterWindow.ui

RESOURCES += \
    images/avatar.jpg \
    myresources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
