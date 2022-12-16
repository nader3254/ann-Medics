QT += core gui
QT += widgets
QT += sql
#QT += multimedia
#QT += multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstract/databasecontrol.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    abstract/databasecontrol.h \
    login.h \
    mainwindow.h

FORMS += \
    login.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    database/annmedics.db \
    database/annmedics.sqbpro
