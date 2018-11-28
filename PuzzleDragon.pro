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

# Testing dedicated UI components
# You can change to the following values:
# RUN_MAIN_WINDOW
# RUN_START_WINDOW
# <nothing, comment the line out>
DEFINES += RUN_START_WINDOW
# As for other windows, if you make sure it can be dedicatedly constructed
# i.e. it can futher cunstruct other windows, as long as directly call
#
# xxWindow w(some default value if needed);
# w.show();
#
# in main.cpp behaves normally,
# you can add some line in this documentation (around line 26) and
# some #ifdef in main.cpp in the same format.

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        orbComponent/OrbGame.cpp \
        combatComponent/AbstractMonster.cpp \
        combatComponent/CombatGame.cpp \
        combatComponent/EnemyMonster.cpp \
        combatComponent/PetMonster.cpp \
    gameinstance.cpp \
    fileloader.cpp \
    uiComponent/OrbGameWindow.cpp \
    uiComponent/CombatGameWindow.cpp \
    uiComponent/OrbBox.cpp \
    uiComponent/petbox.cpp \
    uiComponent/AboutWindow.cpp \
    buttonwithdagger.cpp \
    uiComponent/SelectionWindow.cpp \
    uiComponent/StartWindow.cpp \
    Utils.cpp

HEADERS += \
        orbComponent/OrbGame.h \
        combatComponent/AbstractMonster.h \
        combatComponent/CombatGame.h \
        combatComponent/EnemyMonster.h \
        combatComponent/PetMonster.h \
        Utils.h \
    gameinstance.h \
    fileloader.h \
    uiComponent/OrbGameWindow.h \
    uiComponent/CombatGameWindow.h \
    uiComponent/OrbBox.h \
    uiComponent/petbox.h \
    uiComponent/AboutWindow.h \
    buttonwithdagger.h \
    uiComponent/SelectionWindow.h \
    uiComponent/StartWindow.h

FORMS += \
    uiComponent/combatgamewindow.ui \
    uiComponent/orbgamewindow.ui \
    uiComponent/AboutWindow.ui \
    buttonwithdagger.ui \
    uiComponent/StartWindow.ui \
    uiComponent/SelectionWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

CONFIG += resources_big
