import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls.Material
import Qt5Compat.GraphicalEffects
 import QtCharts 2.2
import QtQuick.Layouts 1.3

Window {
    width: 1920
    height: 1080
    visible: true
    title: qsTr("Hello World")
    ///Material.theme: darkMode ? Material.Dark : Material.Light
    color: "#000"


    LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, 0)
            end: Qt.point(0, parent.height)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#000000" }
                GradientStop { position: 0.2; color: "#010509" }
                GradientStop { position: 0.3; color: "#010B17" }
                GradientStop { position: 0.6; color: "#00162D" }
                GradientStop { position: 0.8; color: "#00162D" }
                GradientStop { position: 1.0; color: "#011C3A" }

            }
    }
    LinearGradient {
            anchors.fill: parent
            start: Qt.point(0, parent.height/2)
            end: Qt.point(parent.width,  parent.height/2)
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#000000" }
                GradientStop { position: 0.2; color: "#010509" }
                GradientStop { position: 0.3; color: "#010B17" }
                GradientStop { position: 0.6; color: "#00162D" }
                GradientStop { position: 0.8; color: "#00162D" }
                GradientStop { position: 1.0; color: "#011C3A" }

            }
    }


    /**********************************************Chart 1 ***************************************************/
    ChartView {
      id:chart1_id
      width: parent.width/2
      height: parent.height/2
      backgroundColor: "transparent"
      legend.visible: false
      antialiasing: true
      layer.enabled: true
      layer.effect: Glow { color: "red";  transparentBorder: true; radius: 85; spread:.8 }
       animationDuration : 5000
       animationOptions: ChartView.AllAnimations;
       animationEasingCurve.bezierCurve : [ 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.78, 0.93, 0.95, 1, 1 ]


      LineSeries {
                  axisX: ValueAxis{  min: 0; max: 100 ;  visible: true ;color :"#00ffffff";labelsColor :"#22ffffff";labelsVisible:false; gridVisible:false;}
                  axisY: ValueAxis{  min: 0; max: 100 ;  visible: true ;gridLineColor :"#5515bdff";color :"#00ffffff";labelsVisible:false;}
                  width:2
                  color: "#f00"
                  XYPoint { x: 0; y: 0 }
                  XYPoint { x: 10.1; y: 20.1 }
                  XYPoint { x: 11.9; y: 31.3 }
                  XYPoint { x: 12.1; y: 72.1 }
                  XYPoint { x: 32.9; y: 14.9 }
                  XYPoint { x: 35.4; y: 30.0 }
                  XYPoint { x: 38.4; y: 20.0 }
                  XYPoint { x: 40.1; y: 40.3 }
                  XYPoint { x: 80.1; y: 60.3 }
                  XYPoint { x: 90.1; y: 50.3 }
                  XYPoint { x: 95.1; y: 80.3 }

       }



    }
    /*********************************************************************************************************/

    /**********************************************Chart 2 ***************************************************/

    ChartView {
      width: parent.width/2
      height: parent.height/2
      x:parent.width/2
      backgroundColor: "transparent"
      legend.visible: false
      antialiasing: true
      layer.enabled: true
      layer.effect: Glow { color: "#18F3F2";  transparentBorder: true; radius: 50; spread:.3 }
      animationDuration : 5000
      animationOptions: ChartView.AllAnimations;

      AreaSeries {
                      name: "Humidity"
                      axisX: ValueAxis{  min: 0; max: 100 ;  visible: true ;color :"#00ffffff";labelsColor :"#22ffffff";labelsVisible:false; gridVisible:false;}
                      axisY: ValueAxis{  min: 0; max: 100 ;  visible: true ;gridLineColor :"#5515bdff";color :"#00ffffff";labelsVisible:false;}
                      color: "#5518F3F2"
                      borderColor: "#88ffffff";

                      upperSeries: LineSeries {
                          XYPoint { x: 0; y: 50 }
                          XYPoint { x: 10.1; y: 40.1 }
                          XYPoint { x: 11.9; y: 31.3 }
                          XYPoint { x: 12.1; y: 2.1 }
                          XYPoint { x: 32.9; y: 14.9 }
                          XYPoint { x: 35.4; y: 3.0 }
                          XYPoint { x: 40.1; y: 30.3 }
                          XYPoint { x: 80.1; y: 60.3 }
                          XYPoint { x: 100.; y: 30.3 }

                      }
                  }

      BarSeries {
              id: mySeries
              labelsVisible:false

              axisY: ValueAxis{  min: 0; max: 100 ;  visible: true ;gridLineColor :"#5515bdff";color :"#00ffffff";labelsVisible:false;}
              opacity:.5
              axisX: BarCategoryAxis {
                  gridVisible:false
                  gridLineColor:"transparent"
                  labelsVisible:false;
              }
              BarSet { label: "Bob"; values: [20, 20, 30, 40, 50, 60]; borderColor: "#55ffffff"; color: "#55FDFC88";}
              BarSet { label: "Susan"; values: [50, 10, 20, 40, 10, 70] ; borderColor: "transparent";color: "#55FD2222";}
              BarSet { label: "James"; values: [30, 50, 80, 13, 50, 80] ; borderColor: "transparent";color: "#5509C4F6";}

          }

    }


    /*********************************************************************************************************/

    /**********************************************Chart 3 ***************************************************/
    ChartView {
      width: parent.width/2
      height: parent.height/2
      backgroundColor: "transparent"
      legend.visible: true
      legend.labelColor: "#aaa"
      antialiasing: true
      layer.enabled: true
       y:parent.height/2
      layer.effect: Glow { color: "#F802BB";  transparentBorder: true; radius: 85; spread:.5 }
      animationDuration : 2000
      animationOptions: ChartView.AllAnimations;

      AreaSeries {
                      name: "Temperature"
                      axisX: ValueAxis{  min: 0; max: 100 ;  visible: true ;color :"#00ffffff";labelsColor :"#aaffffff";labelsVisible:false; gridVisible:false;}
                      axisY: ValueAxis{  min: 0; max: 100 ;  visible: true ;gridLineColor :"#5515bdff";color :"#00ffffff";labelsVisible:false;}
                      color: "#77F802BB"
                      borderColor: "#55ffffff";


                      upperSeries: LineSeries {
                          XYPoint { x: 0; y: 0 }
                          XYPoint { x: 10.1; y: 20.1 }
                          XYPoint { x: 11.9; y: 31.3 }
                          XYPoint { x: 12.1; y: 2.1 }
                          XYPoint { x: 32.9; y: 14.9 }
                          XYPoint { x: 35.4; y: 3.0 }
                          XYPoint { x: 40.1; y: 30.3 }
                          XYPoint { x: 80.1; y: 60.3 }
                      }
                  }

    }
    /*********************************************************************************************************/

    /**********************************************Chart 4 ***************************************************/

    ChartView {
      x:parent.width/2
      y:parent.height/2
      id:chart4_id

      width: parent.width/2
      height: parent.height/2
      backgroundColor: "transparent"
      //legend.visible: false
      legend.labelColor: "#aaa"

      antialiasing: true
      layer.enabled: true
      layer.effect: Glow { color: "#0266E5";  transparentBorder: true; radius: 50; spread:.4 }
      animationDuration : 4000
      animationOptions: ChartView.AllAnimations;
      animationEasingCurve.bezierCurve : [ 0.2, 0.2, 0.13, 0.5, 0.3, 0.8, 0.624, 0.98, 0.93, 0.95, 1, 1 ]

      PieSeries {
          id: pieOuter
          size: 0.95
          holeSize: 0.8

          PieSlice { id: slice; label: "Alpha"; value: 19511; color: "#0266E5" ;borderColor:  "#0266E5";}
     }
      PieSeries {
             size: 0.5
             id: pieInner
             holeSize: 0.3

             PieSlice { label: "Materials"; value: 10334; color: "#FDFC88" ;borderColor: "#FDFC88";}
             PieSlice { label: "Employee"; value: 3066; color: "#FD2222" ;borderColor: "#FD2222";}
             PieSlice { label: "Logistics"; value: 6111; color: "#09C4F6";borderColor:  "#09C4F6"; }


        }



  }

    /*********************************************************************************************************/




}
