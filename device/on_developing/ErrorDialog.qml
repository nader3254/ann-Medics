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
        id: rectangle2
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

        Text {
            id: errTxt
            objectName: "s_err"
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
