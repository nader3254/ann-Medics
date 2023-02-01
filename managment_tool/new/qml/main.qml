import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.VirtualKeyboard 2.15
import QtMultimedia 5.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15


Window {
    id: window
    width: 1280
    height: 1280
    visible: true
    title: qsTr("Hello World")
    Material.theme: Material.Dark
    Material.accent: Material.Purple

    // cloned from https://doc.qt.io/qt-5/qml-qtmultimedia-video.html#fillMode-prop
    // act as splash screen
        Video {
            id: video
           // visible: true
            autoPlay: true
            width : parent.width
            height : parent.height
            source: "/videos/anneMedintro.mkv"
            fillMode: VideoOutput.Stretch
            anchors.fill: parent
            focus: true
            onStopped: loginPageLoader.active = true
        }



   // load the login page
    Item
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent

        Loader
        {
            width: parent.width
            height: parent.height
            anchors.fill: parent
            active: false
            id: loginPageLoader
            source: "/qml/loginPage.qml"
        }

    }


    // load the dashboard Page
    Loader
    {
        width: parent.width
        height: parent.height
        anchors.fill: parent
        active: false
        id: dashboardPageLoader
        source: "/qml/dashBoardPage.qml"
    }





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
}
