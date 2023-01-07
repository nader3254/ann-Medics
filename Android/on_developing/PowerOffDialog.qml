import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick 2.12
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3
import QtQuick.Timeline 1.0
import ecg.graphics 1.0
import spo2.graphics 1.0
import rr.graphics 1.0


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
    width: parent.width
    height: parent.height

Rectangle {
    id:poweroffonPage
    //visible: false
//    width: 800
//    height: 480
    anchors.fill: parent
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
//                x: 740
//                y: 417
//                width: 52
//                height: 53
                anchors.fill: parent


                onClicked:
                {
                   root.close();
                }
            }

        }
}
}
