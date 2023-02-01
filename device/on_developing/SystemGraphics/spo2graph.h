#ifndef SPO2GRAPH_H
#define SPO2GRAPH_H

#include <QObject>
#include <QQuickPaintedItem>
#include <QString>
#include <QPainter>
#include <QPen>
#include <QtMath>
#include <QTimer>
#include <QList>
#include <QPoint>

#include "SystemGraphics/alltexts.h"
#include "./tools/filebrowser.h"
#include "tools/systemerrors.h"
#include "tools/scriptrunner.h"

#define SPO2_RX1    0
#define SPO2_RX2    527
#define SPO2_Ry     250
<<<<<<< HEAD
#define SPO2_RTime  10    /* 40 milli second */
#define SPO2_RTime2 20000  /* 3000 milli second */

=======
#define SPO2_RTime  40    /* 40 milli second */
#define SPO2_RTime2 20000  /* 3000 milli second */
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813
class Spo2graph: public QQuickPaintedItem
{
    Q_PROPERTY(int spo2  READ getspo2  WRITE setspo2  NOTIFY spo2Changed    );
    Q_OBJECT

    typedef struct
    {
       long ir;
       long red;
       int  spo2;
       int  hr;

    }max30102_data_t;
public:


    Spo2graph(QQuickItem *parent = nullptr);
    void  paint(QPainter *painter);
    bool  isConnected();
    bool  isSensorConnected();
    int   getspo2();
    void  setspo2(int sp);
    void  setText(AllTexts* txt);
    void  setSysERR(systemErrors *err);
    max30102_data_t getMax30102Values();


private slots:
    void SPO2Render();
    void curve_changer();
    void on_OMT();
signals:
void spo2Changed();


private:

 int c_spo2=0.0;
 int   _x=0;
 int   _y=0;

 int i=0;


 QTimer *spo2_t;
 QTimer *spo2_t2;
 QTimer *oneMT;
 QList <QPoint> points;
 QPoint pt;
 AllTexts    *Txt;
 systemErrors *_err;
 FileBrowser *FB;      /* from here */
 long IR,RED,prev_ir=0,no_sensor_ctr=0;
 int ir_dc_updater;
 int ry_prev;
 bool curve_change=false;

 long irac,irdc=160000,redac,reddc=160000;
 long max_ir=1000;
 int hr_ctr;
 bool OM_passed=false;
 max30102_data_t data;
 scriptRunner *spo2scr;
<<<<<<< HEAD
 float norm,theta=4.0;
=======
 float theta=4.0;
>>>>>>> aa1f01b9d0f3590d9575e9dc1a536fe2aee0f813

 void readRED_IR();
 void ConnectPoints(QPainter *painter);
 void spo2calculator();
 void hrcalculator();
};

#endif // SPO2GRAPH_H
