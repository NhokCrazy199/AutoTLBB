#-------------------------------------------------
#
# Project created by QtCreator 2018-01-09T15:03:28
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AutoTLBB
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

# Libraries
LIBS += -lUser32 -lPsapi

CONFIG(release, debug|release) {
  CONFIG  += qt warn_off release
  DEFINES += QT_NO_DEBUG_OUTPUT
  DEFINES += QT_NO_DEBUG

  SOURCES += \
        InitCopyApp.cpp

  HEADERS += \
        InitCopyApp.hpp
}

SOURCES += \
        main.cpp \
        MainWindow.cpp \
        Constants.cpp \
    GameWindowInfo.cpp \
    Player.cpp \
    player_control_tabs/GeneralTab.cpp \
    player_control_tabs/ItemTab.cpp \
    player_control_tabs/SkillTab.cpp

HEADERS += \
        MainWindow.hpp \
        Constants.hpp \
    GameWindowInfo.hpp \
    Player.hpp \
    player_control_tabs/GeneralTab.hpp \
    player_control_tabs/ItemTab.hpp \
    player_control_tabs/SkillTab.hpp

FORMS += \
        MainWindow.ui \
    player_control_tabs/GeneralTab.ui \
    player_control_tabs/ItemTab.ui \
    player_control_tabs/SkillTab.ui

RESOURCES += \
        Resources/style.qrc \
    Resources/app_res.qrc
