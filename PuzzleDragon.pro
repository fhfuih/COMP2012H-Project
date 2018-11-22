#-------------------------------------------------
#
# Project created by QtCreator 2018-11-11T23:20:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PuzzleDragon
TEMPLATE = app

INCLUDEPATH += uiComponent
INCLUDEPATH += orbComponent
INCLUDEPATH += combatComponent

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
        orbComponent/Orb.cpp \
        orbComponent/OrbGame.cpp \
        combatComponent/AbstractMonster.cpp \
        combatComponent/CombatGame.cpp \
        combatComponent/EnemyMonster.cpp \
        combatComponent/PetMonster.cpp \
        combatComponent/Type.cpp \
        uiComponent/mainwindow.cpp \
        uiComponent/gamewindow.cpp \
        uiComponent/square.cpp

HEADERS += \
        orbComponent/Orb.h \
        orbComponent/OrbGame.h \
        combatComponent/AbstractMonster.h \
        combatComponent/CombatGame.h \
        combatComponent/EnemyMonster.h \
        combatComponent/PetMonster.h \
        combatComponent/Type.h \
        uiComponent/mainwindow.h \
        uiComponent/gamewindow.h \
        uiComponent/square.h

FORMS += \
        uiComponent/mainwindow.ui \
        uiComponent/gamewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
