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
#include "./tools/filebrowser.h"
#include <QStringList>
#include <QDebug>

#define SPO2_RX1    0
#define SPO2_RX2    527
#define SPO2_Ry     250
#define SPO2_RTime  1  /* 40 milli second */

class Spo2graph: public QQuickPaintedItem
{
    Q_PROPERTY(int spo2  READ getspo2  WRITE setspo2  NOTIFY spo2Changed    );
    Q_OBJECT
public:
    Spo2graph(QQuickItem *parent = nullptr);
    void  paint(QPainter *painter);
    bool  isConnected();
    int   getspo2();
    void  setspo2(int sp);

private slots:
    void SPO2Render();

signals:
void spo2Changed();


private:

 int c_spo2=0.0;
 int   _x=0;
 int   _y=0;

 int i=0;


 QTimer *spo2_t;
 QList <QPoint> points;
 QPoint pt;
 
 FileBrowser *FB;      /* from here */
 long IR,RED;
 long IR_dc=200000;
 int ir_dc_updater;
 int ry_prev;
 void readRED_IR();



};

#endif // SPO2GRAPH_H
