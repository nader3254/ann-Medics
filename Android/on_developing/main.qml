import QtQuick 2.15
import QtQuick.Window 2.15

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
    visible: true
    title: qsTr("Ann-Medics Managment tool")

    Timer{
        id:rt
        interval: 2;running: true; repeat: false
        onTriggered: window.showFullScreen();
    }

//    Video {
//        id: video
//       // visible: true
//        autoPlay: true
//        width : parent.width
//        height : parent.height
//        source: "/uiux/videos/anneMedintro.mp4"
//        fillMode: VideoOutput.Stretch
//        anchors.fill: parent
//        focus: true
//        onStopped: page1.visible = true
//    }
<<<<<<< HEAD


=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
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

<<<<<<< HEAD

=======
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
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

//    FastBlur {
//        id:blur
//        visible: false
//        anchors.fill: page1
//        source: page1
//        radius: 42
//    }
}
