import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {

    Rectangle{
        width:parent.width
        height: parent.height
        color:"black"



                RowLayout {
                    spacing: 2
                    anchors.top:  parent.top
                    width: 80
                    height:80
                    ToolButton {
                        width: 80
                        height:80
                        text: qsTr("Online Devices")
                       // onClicked:
                    }

                    ToolButton {
                        text: qsTr(" comming soon ")
                        width: 80
                        height:80
                        //onClicked: menu.open()
                    }
                    ToolButton {
                        width: 80
                        height:80
                        text: qsTr(" comming soon ")
                        //onClicked: menu.open()
                    }
                    ToolButton {
                        width: 80
                        height:80
                        text: qsTr(" comming soon ")
                        //onClicked: menu.open()
                    }
                    ToolButton {
                        width: 80
                        height:80
                        text: qsTr(" comming soon ")
                        //onClicked: menu.open()
                    }
                }



                StackView {
                       id: stack
                       anchors.fill: parent
                   }








    }
}
