import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.15

Rectangle {
    id: root
    width: 800
    height: 480
    color: "#05142e"

    Image {
        id: background
        x: 0
        y: 0
        width: 800
        height: 480
        source: "qrc:/uiux/uiux/background2.png"
        fillMode: Image.PreserveAspectFit
        Rectangle
        {
            x:40
            y:80
            width:350
            height: 350
            color: "transparent"
        //    RadialGradient
        //    {
        //        anchors.fill: parent
        //        gradient: Gradient {
        //            GradientStop { position: 0.0; color: "#07bff7" }
        //            GradientStop { position: 0.5; color: "#4e0994" }
        //        }
        //    }
            Image {
                id: image1
                x: 105
                y: 36
                width: 103
                height: 77
                source: "qrc:/uiux/uiux/connect_page.png"
                fillMode: Image.PreserveAspectCrop
            }

            Text {

                y: cbox.y-30
                x:55
                color: "#ffffff"
                text: qsTr("select the available online device")
            }
            ListModel
            {
               id: cbItems
               ListElement { text: "virtual device" }
               onCountChanged: status.text="available online devices :"+cbItems.count
            }
            ComboBox
            {
                id:cbox
                x:65
                y:150
                currentIndex: 2
                model:cbItems
                width: 200
                onCurrentIndexChanged: console.debug(cbItems.get(currentIndex).text )
            }

                RoundButton {
                    id:scan
                    y:cbox.y+100
                    x:95
                    text: "scan"
                    radius:15
                    onClicked:
                    {
                        let all=[];
                        for(let i=0;i<cbItems.count;i++)
                        {
                           all.push(cbItems.get(i).text);
                        }
                        //console.log(all.length)
                       status.text="scanning devices on network.....";
                       let r="hello";
                       r= deviceInterface.get_online();
                       let xr=r.split("#");
                        const objectArray = Object.entries(xr);
                        objectArray.forEach(([key, value]) => {
                        var notinside=true;
                        for(let i=0;i<all.length;i++)
                        {
                            if(all[i]==value)
                            {
                                notinside=false;
                                break;
                            }

                        }
                        if(value!="" && notinside)
                        {
                          cbItems.append({"text":value})
                        }
                        });

                    }

                }
                RoundButton {
                    id:connect
                    x: scan.x+50
                    y:scan.y
                    text: "connect"
                    radius:15
                    onClicked:
                    {
                        if(deviceInterface.connect_device(cbItems.get(cbox.currentIndex).text )==false)
                        {
                            status.text="failed to connect to selected target device.......";
                        }

                    }
                }

        }


            Text {
                id: status
                x:5
                y:parent.height-20
                color: "#07f7e7"
                text: qsTr("No Online Devices........")
            }

    }
}
