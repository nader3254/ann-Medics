QT += quick virtualkeyboard
QT += quickcontrols2

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        SystemGraphics/alltexts.cpp \
        SystemGraphics/batterymanager.cpp \
        SystemGraphics/ecggraph.cpp \
        SystemGraphics/rrgraph.cpp \
        SystemGraphics/spo2graph.cpp \
        communication/deviceinterface.cpp \
        communication/wifi_config.cpp \
        main.cpp \
        tools/filebrowser.cpp \
        tools/scriptrunner.cpp \
        tools/systemerrors.cpp \
        tools/udp.cpp

RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /home/pi
else: unix:!android: target.path = /home/pi
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    uiux/MCU_uiux.png \
    uiux/MCU_uiux.psd \
    uiux/allbuttons.png \
    uiux/background.png \
    uiux/battery_charging.png \
    uiux/battery_empty.png \
    uiux/battery_full.png \
    uiux/battery_lvl1.png \
    uiux/battery_lvl2.png \
    uiux/battery_lvl3.png \
    uiux/connect.png \
    uiux/connect_pressed.png \
    uiux/connect_pressed.psd \
    uiux/eerror.png \
    uiux/error_red.png \
    uiux/error_yellow.png \
    uiux/mute_pressed.png \
    uiux/mute_released.png \
    uiux/power.png \
    uiux/power_pressed.png \
    uiux/system_test_pressed.png \
    uiux/system_test_re.png

HEADERS += \
    SystemGraphics/alltexts.h \
    SystemGraphics/batterymanager.h \
    SystemGraphics/ecggraph.h \
    SystemGraphics/rrgraph.h \
    SystemGraphics/spo2graph.h \
    communication/deviceinterface.h \
    communication/wifi_config.h \
    tools/filebrowser.h \
    tools/scriptrunner.h \
    tools/systemerrors.h \
    tools/udp.h
