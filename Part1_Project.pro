QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bazi2nafare.cpp \
    bazi2nafare_game.cpp \
    bazi3nafare.cpp \
    bazi3nafare_game.cpp \
    bazi4nafare.cpp \
    bazi4nafare_game.cpp \
    main.cpp \
    firstpage.cpp

HEADERS += \
    bazi2nafare.h \
    bazi2nafare_game.h \
    bazi3nafare.h \
    bazi3nafare_game.h \
    bazi4nafare.h \
    bazi4nafare_game.h \
    firstpage.h

FORMS += \
    bazi2nafare.ui \
    bazi2nafare_game.ui \
    bazi3nafare.ui \
    bazi3nafare_game.ui \
    bazi4nafare.ui \
    bazi4nafare_game.ui \
    firstpage.ui \
    gameWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Eye.qrc \
    Flag.qrc \
    animal.qrc \
    reseticon.qrc \
    soldier.qrc

DISTFILES +=
