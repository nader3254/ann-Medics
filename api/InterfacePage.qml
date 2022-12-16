import QtQuick 2.15
import QtQuick.Controls 2.15


Rectangle
{
    width: parent.width
    height: parent.height
    color: "black"
    Rectangle
    {
       width: parent.width-40
       height: parent.height-20
       anchors.top: parent.top
       anchors.bottom:  parent.bottom
       anchors.left: parent.left
      // anchors.right: parent.Right ;
       anchors.rightMargin: 20
       anchors.leftMargin: 20
       anchors.topMargin: 20
       anchors.bottomMargin: 20
       color: "white"
       Rectangle
       {
          width: parent.width-4
          height: parent.height-2
          anchors.top: parent.top
          anchors.bottom:  parent.bottom
          anchors.left: parent.left
          anchors.right: parent.Right
          anchors.leftMargin: 2
          anchors.rightMargin: 2
          anchors.topMargin: 2
          anchors.bottomMargin: 2
          color: "black"

          Text {
                     id: text1
                     x: (parent.width / 2) - (text1.width/2)
                     y: parent.height - (parent.height*0.9)
                     color: "#ffffff"
                     text: qsTr("Ann-Medics Web Server Api ")
                     font.pixelSize: 25
                     font.family: "Arial"
                 }

                 TextField
                 {
                     id:serverlink
                     objectName: "serverLink"
                     width:parent.width-40
                     anchors.left: parent.left   ; anchors.leftMargin: 20
                     anchors.right: parent.right ; anchors.rightMargin: 20
                     y: (parent.height/2)-(serverlink.height/2)
                     text: "The Web Server link will be there .... "
                     onActiveFocusChanged: serverlink.selectAll()

                 }


       }

    }

}
