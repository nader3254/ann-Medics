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


Window {
    id: window
    width: 800
    height: 480
    visible: true
    title: qsTr("Hello World")

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                target: inputPanel
                y: window.height - inputPanel.height
            }
        }

       }
        Rectangle {
            id: mainwindow
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
                                    connectPage.visible=true;
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
                            errorPage.visible=true;
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
                            poweroffonPage.visible=true;
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

        Rectangle {
            id:connectPage
            visible: false
            width: 800
            height: 480
            color: "#04041a"

            Image {
                id: image
                x: -20
                y: 0
                width: 828
                height: 506
                source: "qrc:/uiux/uiux/MCU_uiux_blured.png"
                fillMode: Image.Stretch

                Rectangle {
                    id: rectangle
                    x: 220
                    y: 79
                    width: 335
                    height: 322
                    color: "#0a103d"
                    radius: 20

                    TextField {
                        id: nssid
                        x: 97
                        y: 132
                        width: 185
                        height: 32
                        placeholderText: qsTr("Enter wifi network name")
                    }

                    TextField {
                        id: npassword
                        x: 97
                        y: 173
                        width: 185
                        height: 32
                        placeholderText: qsTr("Enter wifi network password")
                        echoMode: TextInput.PasswordEchoOnEdit
                    }

                    Image {
                        id: image1
                        x: 105
                        y: 36
                        width: 103
                        height: 77
                        source: "qrc:/uiux/uiux/connect_page.png"
                        fillMode: Image.PreserveAspectCrop
                    }


                    Button {
                        id: connect2_btn
                        x: 128
                        y: 249
                        text: "connect"

                    }

                    Text {
                        id: text1
                        x: 33
                        y: 136
                        width: 51
                        height: 25
                        color: "#ffffff"
                        text: qsTr("Wifi SSID")
                        font.pixelSize: 12
                    }

                        Text {
                            id: text2
                            x: 8
                            y: 178
                            width: 76
                            height: 28
                            color: "#ffffff"
                            text: qsTr("Wifi password")
                            font.pixelSize: 12
                        }

                        Text {
                            id: text3
                            x: 291
                            y: 26
                            color: "#fdfdfd"
                            text: qsTr("X")
                            font.pixelSize: 20
                        }

                        MouseArea {
                            id: mouseArea
                            x: 282
                            y: 26
                            width: 32
                            height: 23


                            onClicked:
                            {
                                connectPage.visible=false;
                            }
                        }
                }

            }

}

        Rectangle {
            id:errorPage
            visible: false
            width: 800
            height: 480
            color: "#04041a"
            Image {
                id: image2
                x: -20
                y: 0
                width: 828
                height: 506
                source: "qrc:/uiux/uiux/MCU_uiux_blured.png"
                fillMode: Image.Stretch
                Rectangle {
                    id: rectangle2
                    x: 220
                    y: 79
                    width: 335
                    height: 322
                    color: "#04041a"
                    radius: 20

                    Text {
                        id: errTxt
                        x: 21
                        y: 116
                        width: 293
                        height: 190
                        color: "#00ff00"
                        text: qsTr("No errors at current time")
                        font.pixelSize: 14
                    }

                    Text {
                        id: text4
                        x: 291
                        y: 26
                        color: "#fdfdfd"
                        text: qsTr("X")
                        font.pixelSize: 20
                    }

                    MouseArea {
                        id: mouseArea2
                        x: 282
                        y: 26
                        width: 32
                        height: 23


                        onClicked:
                        {
                            errorPage.visible=false;
                        }
                    }

                }









            }
        }

        Rectangle {
            id:poweroffonPage
            visible: false
            width: 800
            height: 480
            color: "#04041a"
            Image {
                id: image3
                x: -20
                y: 0
                width: 828
                height: 506
                source: "qrc:/uiux/uiux/power_on.png"
                fillMode: Image.Stretch

                    MouseArea {
                        id: mouseArea3
                        x: 740
                        y: 417
                        width: 52
                        height: 53


                        onClicked:
                        {
                            poweroffonPage.visible=false;
                        }
                    }

                }
}
}
