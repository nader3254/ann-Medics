import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick3D 1.15


Rectangle {
    id : root
    x:0
    y:0
    width : parent.width
    height : parent.height
    color: "black"

    Image {
        id: login_backgrond
        anchors.fill: parent
        anchors.left: parent.left
        source: "/images/login_backGround.png"
        fillMode: Image.fillMode

    Rectangle
    {
        id:container
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 100
        anchors.leftMargin: 390
        width:parent.width/2
        height:parent.height/1.4
        //color:"black"
       // color:"transparent"

        gradient: Gradient {
              GradientStop { position: 0.0; color: "#3b057e" }
              GradientStop { position: 1.0; color: "#863ae3" }
          }

        Text {
            id: text1
            width: 285
            height: 72
            anchors.top:  parent.top ;anchors.topMargin: 15
            anchors.left: parent.left ;anchors.leftMargin:  250
            anchors.right: parent.right ;anchors.rightMargin: 40
           // x: (parent.width / 2) -143
            color: "#ffffff"
            text: qsTr("Ann-Med")
            font.pixelSize: 65
            font.family: "Arial"
        }


        TextField
        {
            id:uname
//            x:500
            y:400
            width:400
            anchors.right: parent.right ;anchors.rightMargin: 40
            anchors.left: parent.left ;anchors.leftMargin:  180
            anchors.top:  parent.top ;anchors.topMargin: parent.height/3

        }
        TextField
        {
            id:passwrd
            y:400
            width:400
            anchors.right: parent.right ;anchors.rightMargin: 40
            anchors.left: parent.left ;anchors.leftMargin:  180
            anchors.top:  parent.top ;anchors.topMargin: parent.height/3 +100

        }

        Button {
            id: button
            x: (parent.width / 2 )-75
            anchors.bottom: parent.bottom;  anchors.bottomMargin:  40;
            width: 150
            height: 50
            text: qsTr("Login")
            //highlighted: true
            //flat: true


        }
    }

    }

}
