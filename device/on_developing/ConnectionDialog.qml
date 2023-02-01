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
import QtGraphicalEffects 1.0


Dialog {
    id:root
    modal: true
    anchors.centerIn: parent
    leftInset: 0
    rightInset: 0
    leftPadding: 0
    rightPadding: 0
    topPadding: 0
    bottomPadding: 0
    width: parent.width/2.4
    height: parent.height/1.5


        Rectangle {
            id: rectangle
            anchors.fill: parent
            color: "#0a103d"
            gradient: Gradient {
                GradientStop {
                  position: 0.2
                  color: "#0a103d"
                }
                GradientStop {
                  position: 1.0
                  color: "#0cd6f5"
                }
              }

            TextField {
                id: nssid
                text: ""
                x: 97
                y: 132
                width: 185
                height: 32
                placeholderText: qsTr("Enter wifi network name")
            }

            TextField {
                id: npassword
                text: ""
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

            RoundButton {
                text: "connect"
                width:100
                x: 128
                y: 249
                onClicked: {
                    wifiConfig.connect_wifiNetwork(nssid.text,npassword.text);
                    deviceInterface.reconnect();
                    root.close();
                }

            }
//            Button {
//                id: connect2_btn
//                ColorOverlay:"0cd6f5"
//                x: 128
//                y: 249
//                text: "connect"

//            }

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
                    x: 220
                    y: 26
                    width: 100
                    height: 80


                    onClicked:
                    {
                        root.close()
                    }
                }
       }

}







//    Rectangle
//    {

//        anchors.fill: parent
//        color: "#04041a"
//     }






