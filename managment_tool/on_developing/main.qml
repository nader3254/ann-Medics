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
import QtGraphicalEffects 1.15
import QtMultimedia 5.15

Window {
    id: window
    width: 800
    height: 480
    visible: true
    title: qsTr("Ann-Medics Managment tool")

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

       }

//    Video {
//        id: video
//       // visible: true
//        autoPlay: true
//        width : parent.width
//        height : parent.height
//        source: "/uiux/videos/anneMedintro.mkv"
//        fillMode: VideoOutput.Stretch
//        anchors.fill: parent
//        focus: true
//        onStopped: page1.visible = true
//    }
    Onlinedevices
    {
      id:ol
      objectName: "online_ui"
    }
    MainPage
    {
        id:page1
        objectName: "monitor_ui"
        visible: false

    }
    ConnectionDialog
    {
        id:page2
        onOpened:
        {
            blur.visible=true
        }

        onClosed:
        {
             blur.visible=false
        }

    }


    ErrorDialog
    {
        id:page3
        onOpened:
        {
            blur.visible=true
        }

        onClosed:
        {
             blur.visible=false
        }
    }
    PowerOffDialog
    {
        id:page4
    }

    FastBlur {
        id:blur
        visible: false
        anchors.fill: page1
        source: page1
        radius: 42
    }
}
