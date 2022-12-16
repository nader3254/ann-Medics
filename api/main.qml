import QtQuick
import QtQuick.Window
//import QtQuick.VirtualKeyboard
//import QtQuick.Controls
import QtMultimedia



Window {
    width: 400
    height: 260
    visible: true
    title: qsTr("Hello World")

    // act as splash screen
        Video {
            id: video
           // visible: true
          //  autoPlay: true
            width : parent.width
            height : parent.height
            source: "/videos/anneMedintro.mp4"
            fillMode: VideoOutput.Stretch
            anchors.fill: parent
            focus: true
            onStopped: page1.visible = true
        }

        InterfacePage
        {
            id: page1
            visible: false

        }
        Timer{
            id:tt
            interval: 2
            running: true
            onTriggered: {

                video.play();
                tt.running=false

            }
        }

}
