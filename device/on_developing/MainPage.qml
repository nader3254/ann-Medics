import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.VirtualKeyboard 2.15
import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Timeline 1.0
import ecg.graphics 1.0
import spo2.graphics 1.0
import rr.graphics 1.0

Rectangle {
   // id: mainwindow
    width: 800
    height: 480

    color: "black"

    Image {
        id: background
        x: 0
        y: 0
        width: 800
        height: 480
        source: "qrc:/uiux/uiux/background.png"
        fillMode: Image.PreserveAspectFit
        Label{
            id:ipaddrs
            objectName: "device_addrs"
            x:parent.width/3+88
            y:15
            color: "#00b8ff"
            text:"Not Connected...."
        }

        /* here you should insert your curve ... */
        Image {
            id: allbuttons
            x: 0
            y: 394
            width: 533
            height: 86
            clip: false
            source: "qrc:/uiux/uiux/allbuttons.png"
            fillMode: Image.PreserveAspectFit

            Button {
                id: mute_btn
                x: 0
                y: 6
                width: 107
                height: 80

                Image {
                    id: mute_released
                    visible: true
                    x: 0
                    y: 0
                    width: 107
                    height: 80
                    source: "qrc:/uiux/uiux/mute_released.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: mute_pressed
                    visible: false
                    x: 0
                    y: 0
                    width: 107
                    height: 79
                    source: "qrc:/uiux/uiux/mute_pressed.png"
                    fillMode: Image.Stretch
                }
                onPressed: mute_pressed.visible=true;
                onReleased: mute_pressed.visible=false;


            }

            Button {
                id: systest_btn
                x: 107
                y: 6
                width: 107
                height: 80
                Image {
                    id: systst_pressed
                    visible: true
                    x: 0
                    y: 0
                    width: 107
                    height: 80
                    source: "qrc:/uiux/uiux/system_test_re.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: systst_released
                    visible: false
                    x: 1
                    y: 1
                    width: 107
                    height: 79
                    source: "qrc:/uiux/uiux/system_test_pressed.png"
                    fillMode: Image.Stretch
                }

                onPressed: systst_released.visible=true;
                onReleased: systst_released.visible=false;
            }

            Button {
                id: connect_btn
                x: 213
                y: 6
                width: 107
                height: 80
                Image {
                    id: connect_released
                    x: 0
                    y: 0
                    width: 107
                    height: 80
                    source: "qrc:/uiux/uiux/connect.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: connect_pressed
                    visible: false
                    x: 0
                    y: -1
                    width: 107
                    height: 79
                    source: "qrc:/uiux/uiux/connect_pressed.png"
                    fillMode: Image.Stretch
                }
                onPressed:{ connect_pressed.visible=true;
                            //connectPage.visible=true;
                            page2.open();

                          }
                onReleased: connect_pressed.visible=false;

            }

            Button {
                id: error_btn

                x: 320
                y: 6
                width: 107
                height: 80
                Image {
                    id: error_released
                    x: 0
                    y: 0
                    width: 107
                    height: 80
                    source: "qrc:/uiux/uiux/eerror.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: error_red
                    objectName: "err_btn"
                    visible: false
                    x: 0
                    y: -2
                    width: 107
                    height: 79
                    source: "qrc:/uiux/uiux/error_red.png"
                    fillMode: Image.Stretch
                }

                Image {
                    id: error_yellow
                    objectName: "warning_btn"
                    visible: false
                    x: 0
                    y: -2
                    width: 107
                    height: 79
                    source: "qrc:/uiux/uiux/error_yellow.png"
                    fillMode: Image.Stretch
                }
                onPressed:
                {
                    error_yellow.visible=true;
                    page3.open();
                    system_errors.stop();
                }
                onReleased: error_yellow.visible=false;

            }

            Button {
                id: poweroff_btn
                x: 426
                y: 5
                width: 107
                height: 80
                Image {
                    id: power_off_released
                    x: 0
                    y: 2
                    width: 107
                    height: 80
                    source: "qrc:/uiux/uiux/power.png"
                    fillMode: Image.PreserveAspectFit
                }

                Image {
                    id: power_off_pressed
                    visible: false
                    x: -1
                    y: -1
                    width: 107
                    height: 79
                    source: "qrc:/uiux/uiux/power_pressed.png"
                    fillMode: Image.Stretch

                }
                onPressed:  power_off_pressed.visible=true;
                onClicked: {
                   page4.open();
                }

                onReleased: power_off_pressed.visible=false;
            }
        }

        Label {
            id: ecglabel
            x: 544
            y: 62
            color: "#00ffc7"
            text: qsTr("HR")
            font.family: "Verdana"
            font.pointSize: 12
            textFormat: Text.PlainText
        }

        Label {
            id: spo2lbl
            x: 546
            y: 199
            color: "#00b8ff"
            text: qsTr("Spo2")
            font.pointSize: 12
            textFormat: Text.PlainText
            font.family: "Verdana"
        }

        Label {
            id: nbiplbl
            x: 546
            y: 361
            width: 38
            height: 18
            color: "#aaff00"
            text: qsTr("NBIP")
            font.pointSize: 12
            textFormat: Text.PlainText
            font.family: "Verdana"
        }

        Label {
            id: heartrate
            objectName: "heartrate"
            x: 594
            y: 80
            width: 198
            height: 121
            color: "#00ffc7"
            text: qsTr("71")
            font.bold: true
            font.pointSize: 70
            textFormat: Text.PlainText
            font.family: "Verdana"
        }

        Label {
            id: spo2
            objectName: "spo2"
            x: 594
            y: 226
            width: 198
            height: 113
            color: "#00b8ff"
            text: qsTr("93")
            font.pointSize: 70
            font.bold: true
            textFormat: Text.PlainText
            font.family: "Verdana"
        }

        Label {
            id: nbiplbl1
            x: 642
            y: 367
            width: 48
            height: 124
            color: "#aaff00"
            text: qsTr("/")
            font.italic: false
            font.pointSize: 70
            textFormat: Text.PlainText
            font.family: "Times New Roman"
        }

        Label {
            id: nbip_min
            objectName: "nbip_min"
            x: 553
            y: 377
            width: 104
            height: 86
            color: "#aaff00"
            text: qsTr("90")
            font.pointSize: 50
            textFormat: Text.PlainText
            font.family: "Verdana"
        }

        Label {
            id: nbi_pmax
            objectName: "nbi_pmax"
            x: 663
            y: 375
            width: 104
            height: 86
            color: "#aaff00"
            text: qsTr("120")
            textFormat: Text.PlainText
            font.family: "Verdana"
            font.pointSize: 50
        }

        Item {
            id: battery
            x: 663
            y: 1
            width: 131
            height: 44

            Image {
                id: full
                objectName: "full"
                visible: false
                x: 0
                y: 0
                width: 107
                height: 55
                source: "qrc:/uiux/uiux/battery_full.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: lvl3
                objectName: "lvl3"
                visible: false
                x: 0
                y: 0
                width: 107
                height: 55
                source: "qrc:/uiux/uiux/battery_lvl3.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: lvl2
                objectName: "lvl2"
                visible: false
                x: 0
                y: 0
                width: 107
                height: 55
                source: "qrc:/uiux/uiux/battery_lvl2.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: lvl1
                objectName: "lvl1"
                visible: false
                x: 0
                y: 0
                width: 107
                height: 55
                source: "qrc:/uiux/uiux/battery_lvl1.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: empty
                objectName: "empty"
                visible: false
                x: 0
                y: 0
                width: 107
                height: 55
                source: "qrc:/uiux/uiux/battery_empty.png"
                fillMode: Image.PreserveAspectFit
            }

            Image {
                id: charging
                objectName: "charging"
                visible: false
                x: 0
                y: 0
                width: 107
                height: 55
                source: "qrc:/uiux/uiux/battery_charging.png"
                fillMode: Image.PreserveAspectFit
            }
        }

    }



    Timeline {
        id: timeline
        animations: [
            TimelineAnimation {
                id: timelineAnimation
                running: true
                loops: 1
                duration: 1000
                to: 1000
                from: 0
            }
        ]
        startFrame: 0
        endFrame: 1000
        enabled: true
    }








transitions: Transition {
    from: ""
    to: "visible"
    reversible: true
    ParallelAnimation {
        NumberAnimation {
            properties: "y"
            duration: 250
            easing.type: Easing.InOutQuad
        }
    }
}
Rectangle
{
    x : 0
    y : 390
    width : 535
    height : 15
    color: "#02031c"


}
Rectangle
{
    x : 0
    y : 477
    width : 535
    height : 3
    color: "#02031c"


}


ECGGraph{
    width : 800
    height: 480
    objectName: "ecg_graph"
    voltage_mv: voltage_mv
}
SPO2Graph{
   width: 800
   height: 480
   objectName: "spo2_graph"
   spo2: spo2
}
RRGraph{
   width: 800
   height: 480
   objectName: "rr_graph"
   rr:rr
}

}
