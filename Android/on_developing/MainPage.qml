import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Timeline 1.0
import ecg.graphics 1.0
import spo2.graphics 1.0
import rr.graphics 1.0

Rectangle {
    id: mainwindow
//    width: 800
//    height: 480
    width: parent.width
    height: parent.height
    color: "black"

        Image {
            id: background
            x: 0
            y: 0
            width: parent.width
            height: parent.height
            source: "qrc:/uiux/uiux/background.png"
            //fillMode: Image.PreserveAspectFit

            /* here you should insert your curve ... */
            Image {
                id: allbuttons
                x: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 20
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
                Rectangle
                {
                    x : 0
                    y:parent.top
                    width : 535
                    height : 15
                    color: "#02031c"
                }
                Rectangle
                {
                    x : 0
                    anchors.bottom:mute_btn.bottom
                    width : 535
                    height : 6
                    color: "#02031c"


                }
            }

            Rectangle{
                width: parent.width*0.32
                height: parent.height
                color: "transparent"
                anchors.bottom: allbuttons.top
                anchors.bottomMargin: 10
                anchors.right: parent.right
                anchors.top: parent.top
              //  color:"red"

                Label {
                    id: ecglabel
                    anchors.left: parent.left
                    anchors.top:  parent.top
                    anchors.topMargin: parent.height/4
                    color: "#00ffc7"
                    text: qsTr("HR")
                    font.family: "Verdana"
                    font.pointSize: 12
                    textFormat: Text.PlainText
                }

                Label {
                    id: spo2lbl
                    anchors.left: parent.left
                    anchors.top:  ecglabel.bottom
                    anchors.topMargin:parent.height/5
                    color: "#00b8ff"
                    text: qsTr("Spo2")
                    font.pointSize: 12
                    textFormat: Text.PlainText
                    font.family: "Verdana"

                }

                Label {
                    id: nbiplbl
                    anchors.left: parent.left
                    anchors.top:  spo2lbl.bottom
                    anchors.topMargin:parent.height/5
                    width: 38
                    height: 18
                    color: "#aaff00"
                    text: qsTr("NBIP")
                    font.pointSize: 12
                    textFormat: Text.PlainText
                    font.family: "Verdana"
                }
                Label {
                    id: spo2
                    objectName: "spo2"
                    anchors.left: parent.left
                    anchors.leftMargin: ((parent.width/2)-(spo2.width/2))
                    anchors.top: spo2lbl.top
                    anchors.topMargin: 10
                    color: "#00b8ff"
                    text: qsTr("93")
                    font.pointSize: 50
                    font.bold: true
                    textFormat: Text.PlainText
                    font.family: "Verdana"
                }

                Label {
                    id: heartrate
                    objectName: "heartrate"
                    anchors.left: parent.left
                    anchors.leftMargin: (parent.width/2-(heartrate.width/2))
                    anchors.top: ecglabel.top
                    anchors.topMargin: 10
                    color: "#00ffc7"
                    text: qsTr("71")
                    font.bold: true
                    font.pointSize: 50
                    textFormat: Text.PlainText
                    font.family: "Verdana"
                }




                Label {
                    id: nbip_min
                    objectName: "nbip_min"
                    anchors.left: parent.left
                    anchors.leftMargin: ((parent.width/2)-((nbip_min.width+nbiplbl1.width+nbi_pmax.width)/2))
                    anchors.top: nbiplbl.top
                    anchors.topMargin: 20
                    color: "#aaff00"
                    text: qsTr("90")
                    font.pointSize: 25
                    textFormat: Text.PlainText
                    font.family: "Verdana"
                }

                Label {
                    id: nbiplbl1
                    anchors.left: nbip_min.right
                    anchors.leftMargin: 2
                    anchors.top:nbip_min.top
                    color: "#aaff00"
                    text: qsTr("/")
                    font.italic: false
                    font.pointSize: 25
                    textFormat: Text.PlainText
                    font.family: "Times New Roman"
                }
                Label {
                    id: nbi_pmax
                    objectName: "nbi_pmax"
                    anchors.left: nbiplbl1.right
                    anchors.leftMargin: 2
                    anchors.top:nbip_min.top
                    color: "#aaff00"
                    text: qsTr("120")
                    textFormat: Text.PlainText
                    font.family: "Verdana"
                    font.pointSize: 25
                }

         }




            Item {
                id: battery
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.rightMargin: 50
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
 //   }
}
